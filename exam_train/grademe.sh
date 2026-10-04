#!/usr/bin/env bash
# **************************************************************************** #
#                                                                              #
#   grademe.sh - correcteur local du pack exam_train                           #
#                                                                              #
#   ./grademe.sh              liste des exos + ce que t'as deja valide         #
#   ./grademe.sh 4            corrige l'exo 04   (ou : ./grademe.sh rev_epur)  #
#   ./grademe.sh all          corrige tous les exos ou t'as rendu un fichier   #
#                                                                              #
#   --no-asan                 desactive AddressSanitizer                       #
#   CC=clang ./grademe.sh 4   change de compilateur (defaut : cc)              #
#                                                                              #
# **************************************************************************** #

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TESTS="$ROOT/.tests"
PROGRESS="$ROOT/.progress"
CC="${CC:-cc}"
FLAGS=(-Wall -Wextra -Werror)
ASAN_ENV="detect_leaks=0:exitcode=86:color=never"
USE_ASAN=1
ASAN=0
HAVE_TIMEOUT=0

if [ -t 1 ]; then
	GRN=$'\033[32m'; RED=$'\033[31m'; YEL=$'\033[33m'
	BLD=$'\033[1m'; DIM=$'\033[2m'; RST=$'\033[0m'
else
	GRN=''; RED=''; YEL=''; BLD=''; DIM=''; RST=''
fi

WORK="$(mktemp -d "${TMPDIR:-/tmp}/grademe.XXXXXX")" || exit 1
trap 'rm -rf "$WORK"' EXIT

LEVEL_TITLE[1]="Niveau 1 - echauffement cible"
LEVEL_TITLE[2]="Niveau 2 - chaines, edge cases, malloc au bon octet"
LEVEL_TITLE[3]="Niveau 3 - nombres : overflow et algos qui tiennent la route"
LEVEL_TITLE[4]="Niveau 4 - struct, listes chainees, recursion"
LEVEL_TITLE[5]="Revisions <= C07 - famille inter / union / wdmatch"

# ---------------------------------------------------------------------------- #
#  outils                                                                      #
# ---------------------------------------------------------------------------- #

asan_ok() {
	[ "$USE_ASAN" = 1 ] || return 1
	printf '#include <stdlib.h>\nint main(void){char *p = malloc(8); p[0] = 1; free(p); return (0);}\n' > "$WORK/asan.c"
	"$CC" -g -fsanitize=address "$WORK/asan.c" -o "$WORK/asan" > /dev/null 2>&1 || return 1
	ASAN_OPTIONS="$ASAN_ENV" "$WORK/asan" > /dev/null 2>&1 || return 1
	if ! command -v llvm-symbolizer > /dev/null 2>&1; then
		local s
		for s in /usr/bin/llvm-symbolizer-*; do
			[ -x "$s" ] && { export ASAN_SYMBOLIZER_PATH="$s"; break; }
		done
	fi
	return 0
}

ex_name() {
	local b
	b="$(basename "$1")"
	echo "${b#ex[0-9][0-9]_}"
}

find_ex() {
	local q="$1" d
	if [[ "$q" =~ ^[0-9]+$ ]]; then
		q="$(printf '%02d' "$((10#$q))")"
		for d in "$ROOT"/ex"$q"_*/; do
			[ -d "$d" ] && { echo "${d%/}"; return 0; }
		done
	else
		q="${q%/}"
		q="${q##*/}"
		for d in "$ROOT"/ex[0-9][0-9]_"$q"/ "$ROOT"/"$q"/; do
			[ -d "$d" ] && { echo "${d%/}"; return 0; }
		done
	fi
	return 1
}

load_config() {
	NAME=""; TYPE=""; FILES=""; WRAP=0; TIMEOUT=3; LEVEL=0
	# shellcheck disable=SC1090
	. "$TESTS/$1/config"
}

progress_get() {
	[ -f "$PROGRESS" ] && grep "^$1 " "$PROGRESS" | tail -n 1 | cut -d' ' -f2
}

progress_set() {
	{
		[ -f "$PROGRESS" ] && grep -v "^$1 " "$PROGRESS"
		echo "$1 $2 $(date '+%Y-%m-%d_%H:%M')"
	} > "$WORK/progress"
	cat "$WORK/progress" > "$PROGRESS"
}

# ---------------------------------------------------------------------------- #
#  compilation                                                                 #
# ---------------------------------------------------------------------------- #

build() {
	local dir="$1" f
	local objs=() san=() defs=() ldw=()
	[ "$ASAN" = 1 ] && san=(-g -fsanitize=address)
	: > "$WORK/cc.log"
	rm -f "$WORK"/*.o "$WORK/bin"
	for f in $FILES; do
		case "$f" in *.c) ;; *) continue ;; esac
		"$CC" "${FLAGS[@]}" "${san[@]}" -I"$dir" -c "$dir/$f" -o "$WORK/${f%.c}.o" 2>> "$WORK/cc.log" || return 1
		objs+=("$WORK/${f%.c}.o")
	done
	if [ "$TYPE" = function ]; then
		if [ "$WRAP" = 1 ]; then
			if [ "$(uname -s)" = Darwin ]; then defs=(-DNO_WRAP); else ldw=(-Wl,--wrap=malloc); fi
		fi
		"$CC" -Wall -Wextra "${san[@]}" "${defs[@]}" -I"$dir" -c "$TESTS/$NAME/main.c" -o "$WORK/main_test.o" 2>> "$WORK/cc.log" || return 1
		objs+=("$WORK/main_test.o")
	fi
	"$CC" "${san[@]}" "${objs[@]}" "${ldw[@]}" -o "$WORK/bin" 2>> "$WORK/cc.log" || return 1
	return 0
}

compile_hints() {
	local log="$1"
	grep -qE "multiple definition of .main|redefinition of 'main'|duplicate symbol '?_?main" "$log" \
		&& echo "  ${YEL}->${RST} Ton fichier contient un main. Pour un exo \"fonction\", la moulinette amene le sien : a l'exam c'est 0 direct. Enleve-le (ou mets-le en commentaire) avant de rendre."
	grep -qE "undefined reference to .main|_main\", referenced from" "$log" \
		&& echo "  ${YEL}->${RST} Pas de main : c'est un exo \"programme\", il en faut un."
	grep -qE "undefined reference to .[a-z]" "$log" && ! grep -qE "undefined reference to .main" "$log" \
		&& echo "  ${YEL}->${RST} La moulinette ne trouve pas une fonction : verifie le nom et le prototype exacts dans le sujet."
	grep -qE "signedness|different signs|sign-compare" "$log" \
		&& echo "  ${YEL}->${RST} Comparaison entre un int et un unsigned : -Wextra la refuse. Regarde le type de ton compteur."
	grep -qE "built-in function|library function|incompatible redeclaration" "$log" \
		&& echo "  ${YEL}->${RST} Une de tes fonctions porte le nom d'une fonction de la libc : renomme-la."
	grep -qE "implicit declaration|undeclared function|undeclared identifier|undeclared \(first use" "$log" \
		&& echo "  ${YEL}->${RST} Nom inconnu : faute de frappe, ou fonction utilisee avant d'etre ecrite ?"
	grep -qE "uninitiali[sz]ed" "$log" \
		&& echo "  ${YEL}->${RST} Variable utilisee sans avoir ete initialisee."
	grep -qE "no effect|result unused" "$log" \
		&& echo "  ${YEL}->${RST} Une instruction ne fait rien (un - ou un == a la place d'un = ?) : relis la ligne indiquee caractere par caractere."
	grep -qE "unused (variable|parameter|function)|set but not used" "$log" \
		&& echo "  ${YEL}->${RST} Variable, parametre ou fonction inutilise : -Wall / -Wextra le refusent."
	grep -qE "No such file|file not found" "$log" \
		&& echo "  ${YEL}->${RST} Un fichier inclus est introuvable : t'as bien rendu tous les \"Expected files\" (header compris) ?"
	grep -qE "has no member named|no member named" "$log" \
		&& echo "  ${YEL}->${RST} Ta structure ne correspond pas a celle du sujet (noms des champs ?)."
}

# ---------------------------------------------------------------------------- #
#  execution d'un test                                                         #
# ---------------------------------------------------------------------------- #

run_bin() {
	if [ "$HAVE_TIMEOUT" = 1 ]; then
		{ ASAN_OPTIONS="$ASAN_ENV" timeout "$TIMEOUT" "$WORK/bin" "$@" > "$WORK/out" 2> "$WORK/err" < /dev/null; } 2> /dev/null
	else
		{ ASAN_OPTIONS="$ASAN_ENV" "$WORK/bin" "$@" > "$WORK/out" 2> "$WORK/err" < /dev/null; } 2> /dev/null
	fi
	RC=$?
}

sig_name() {
	case "$1" in
		139) echo "Segmentation fault (acces memoire invalide : NULL, hors du tableau...)" ;;
		134) echo "Abort (souvent : free() invalide, ou \"stack smashing\" = debordement d'un tableau local)" ;;
		136) echo "Floating point exception (division ou modulo par 0)" ;;
		138) echo "Bus error" ;;
		*)   echo "tue par le signal $(($1 - 128))" ;;
	esac
}

show_file() {
	if [ ! -s "$1" ]; then
		echo "    ${DIM}(rien)${RST}"
		return
	fi
	cat -e "$1" | head -n 15 \
		| awk '{ if (length($0) > 150) print "    " substr($0, 1, 150) " [...]"; else print "    " $0 }'
	local n
	n=$(wc -l < "$1")
	[ "$n" -gt 15 ] && echo "    ${DIM}... ($n lignes au total)${RST}"
}

show_cmd() {
	local a
	printf '  Commande : ./%s' "$NAME"
	for a in "$@"; do
		if [ "${#a}" -gt 80 ]; then
			printf ' %q' "${a:0:60}"
			printf '...[%d caracteres]' "${#a}"
		else
			printf ' %q' "$a"
		fi
	done
	printf ' | cat -e\n'
}

is_small() {
	local lines width
	lines=$(wc -l < "$1")
	width=$(awk '{ if (length($0) > m) m = length($0) } END { print m + 0 }' "$1")
	[ "$lines" -le 15 ] && [ "$width" -le 150 ]
}

show_window() {
	local start=$(($2 - 60))
	[ "$start" -lt 1 ] && start=1
	tail -c +"$start" "$1" | head -c 120 | cat -e | sed 's/^/    /'
	echo
}

show_diff() {
	local exp="$1" out="$2" off s1 s2
	if is_small "$exp" && is_small "$out"; then
		echo "  Attendu :"
		show_file "$exp"
		echo "  Obtenu :"
		show_file "$out"
		return
	fi
	off=$(cmp -l "$exp" "$out" 2> /dev/null | head -n 1 | awk '{ print $1 }')
	if [ -z "$off" ]; then
		s1=$(wc -c < "$exp")
		s2=$(wc -c < "$out")
		if [ "$s1" -lt "$s2" ]; then off=$((s1 + 1)); else off=$((s2 + 1)); fi
	fi
	echo "  Sortie longue : premiere difference a l'octet $off. Zoom autour :"
	echo "  Attendu :"
	show_window "$exp" "$off"
	echo "  Obtenu :"
	show_window "$out" "$off"
}

show_asan() {
	local kind expl
	kind=$(grep -m 1 "ERROR: AddressSanitizer" "$WORK/err" | sed -E 's/.*AddressSanitizer: ([^ :]+).*/\1/')
	case "$kind" in
		heap-buffer-overflow)   expl="lecture/ecriture en dehors d'une zone allouee par malloc (taille du malloc ? index ?)" ;;
		stack-buffer-overflow)  expl="tu depasses un tableau local (buffer de taille fixe ?)" ;;
		global-buffer-overflow) expl="tu lis en dehors d'une chaine ou d'un tableau constant" ;;
		SEGV)                   expl="acces a une adresse invalide (pointeur NULL, pas initialise, ou deja libere ?)" ;;
		FPE)                    expl="division ou modulo par 0" ;;
		stack-overflow)         expl="pile explosee : recursion sans fin (condition d'arret ?)" ;;
		heap-use-after-free)    expl="tu utilises une zone deja liberee par free" ;;
		attempting)             expl="free() sur un pointeur qui ne vient pas de malloc, ou double free" ;;
		requested|allocation-size-too-big) expl="malloc d'une taille delirante : un calcul de taille a deborde ?" ;;
		*)                      expl="" ;;
	esac
	echo "  ${YEL}Erreur memoire${RST} (AddressSanitizer) : ${BLD}$kind${RST}"
	[ -n "$expl" ] && echo "    -> $expl"
	grep -q "zero page" "$WORK/err" && echo "    -> l'adresse est proche de 0 : c'est un pointeur NULL"
	awk -v q="'" '
		function short(line,   fn, loc, n, parts) {
			fn = line
			sub(/^ *#[0-9]+ 0x[0-9a-f]+ in /, "", fn)
			loc = fn
			sub(/ .*$/, "", fn)
			sub(/^[^ ]+ /, "", loc)
			n = split(loc, parts, "/")
			return fn "  (" parts[n] ")"
		}
		function skip(line) {
			return line ~ /libc|_start|asan|sanitizer|interceptor|__wrap_malloc|compiler-rt/
		}
		/ERROR: AddressSanitizer/ { state = 1; next }
		/^(READ|WRITE) of size/ { sub(/ at 0x[0-9a-f]+/, ""); print "    " $0; next }
		state == 1 && /^ +#[0-9]+ / {
			if (!skip($0) && shown < 3) { print "    " short($0); shown++ }
			seen = 1
			next
		}
		state == 1 && seen && /^ *$/ { state = 2; next }
		/allocated by thread|freed by thread/ {
			what = "allouee"
			if ($0 ~ /freed/) what = "liberee"
			state = 3
			next
		}
		state == 3 && /^ +#[0-9]+ / {
			if (!skip($0)) { print "    zone " what " ici : " short($0); state = 2 }
			next
		}
		/is located [0-9]+ bytes.*-byte region/ {
			match($0, /is located [0-9]+ bytes/)
			nb = substr($0, RSTART + 11, RLENGTH - 17)
			match($0, /[0-9]+-byte region/)
			sz = substr($0, RSTART, RLENGTH - 12)
			dir = "dans"
			if ($0 ~ /after|to the right/) dir = "apres la fin"
			if ($0 ~ /before|to the left/) dir = "avant le debut"
			print "    acces a " nb " octet(s) " dir " d" q "une zone de " sz " octets"
		}
		/<== Memory access/ {
			name = ""; ln = ""; size = ""
			p = index($0, q)
			if (p > 0) {
				rest = substr($0, p + 1)
				name = q substr(rest, 1, index(rest, q) - 1) q
			}
			if (match($0, /\(line [0-9]+\)/)) ln = ", declaree ligne " substr($0, RSTART + 6, RLENGTH - 7)
			if (match($0, /\[[0-9]+, [0-9]+\)/)) {
				split(substr($0, RSTART + 1, RLENGTH - 2), o, ", ")
				size = " (" (o[2] - o[1]) " octets)"
			}
			print "    variable locale debordee : " name size ln
		}
	' "$WORK/err"
}

t() {
	CASE=$((CASE + 1))
	local exp="$TESTS/$NAME/expected/$CASE" verdict="" a
	run_bin "$@"
	if [ "$HAVE_TIMEOUT" = 1 ] && [ "$RC" -eq 124 ]; then
		verdict=timeout
	elif grep -q "ERROR: AddressSanitizer" "$WORK/err" 2> /dev/null; then
		verdict=asan
	elif [ "$RC" -ge 128 ]; then
		verdict=crash
	elif ! cmp -s "$WORK/out" "$exp"; then
		verdict=diff
	fi
	if [ -z "$verdict" ]; then
		PASS=$((PASS + 1))
		return
	fi
	FAIL=$((FAIL + 1))
	[ "$FAIL" -eq 1 ] || return
	echo "  ${RED}x Test $CASE${RST}"
	[ "$TYPE" = program ] && show_cmd "$@"
	case "$verdict" in
		timeout) echo "  ${YEL}Timeout${RST} : plus de ${TIMEOUT}s. Boucle infinie, ou algo trop lent pour cette entree." ;;
		asan)    show_asan ;;
		crash)   echo "  ${YEL}Crash${RST} : $(sig_name "$RC")" ;;
	esac
	if [ "$verdict" = diff ]; then
		show_diff "$exp" "$WORK/out"
	else
		echo "  Attendu :"
		show_file "$exp"
		echo "  Obtenu avant l'arret :"
		show_file "$WORK/out"
	fi
}

# ---------------------------------------------------------------------------- #
#  correction d'un exo                                                         #
# ---------------------------------------------------------------------------- #

grade() {
	local dir="$1" name f missing=0
	name="$(ex_name "$dir")"
	if [ ! -f "$TESTS/$name/config" ]; then
		echo "${RED}Pas de tests pour $name${RST}"
		return 2
	fi
	load_config "$name"
	echo "${BLD}== $(basename "$dir") ==${RST}"
	for f in $FILES; do
		if [ ! -f "$dir/$f" ]; then
			echo "  ${RED}Fichier manquant :${RST} $(basename "$dir")/$f"
			missing=1
		fi
	done
	[ "$missing" = 1 ] && return 1
	if ! build "$dir"; then
		echo "  ${RED}x Compilation KO${RST}  ${DIM}($CC ${FLAGS[*]})${RST}"
		grep -E "error|undefined|multiple|duplicate" "$WORK/cc.log" | head -n 10 \
			| sed "s|$dir/||g; s|$TESTS/$NAME/||g; s|$WORK/||g; s/^/    /"
		compile_hints "$WORK/cc.log"
		echo "  ${DIM}A l'exam, un rendu qui ne compile pas avec ces flags = 0, meme si la logique est juste.${RST}"
		progress_set "$name" KO
		return 1
	fi
	CASE=0; PASS=0; FAIL=0
	# shellcheck disable=SC1090
	. "$TESTS/$name/cases.sh"
	if [ "$FAIL" -eq 0 ]; then
		echo "  ${GRN}OK $PASS/$CASE tests - valide${RST}"
		progress_set "$name" OK
		return 0
	fi
	echo "  ${RED}KO : $PASS/$CASE tests passent${RST} ${DIM}(le detail montre le premier test rate)${RST}"
	progress_set "$name" KO
	return 1
}

has_rendu() {
	local dir="$1" name f
	name="$(ex_name "$dir")"
	[ -f "$TESTS/$name/config" ] || return 1
	load_config "$name"
	for f in $FILES; do
		case "$f" in *.c) [ -f "$dir/$f" ] && return 0 ;; esac
	done
	return 1
}

show_list() {
	local d name st mark lvl=0 ok=0 total=0
	echo "${BLD}exam_train${RST} - ${GRN}v${RST} valide  ${RED}x${RST} dernier essai KO  ${DIM}.${RST} pas encore tente"
	for d in "$ROOT"/ex[0-9][0-9]_*/; do
		d="${d%/}"
		name="$(ex_name "$d")"
		[ -f "$TESTS/$name/config" ] || continue
		load_config "$name"
		if [ "$LEVEL" != "$lvl" ]; then
			lvl="$LEVEL"
			echo
			echo "${BLD}${LEVEL_TITLE[$lvl]}${RST}"
		fi
		st="$(progress_get "$name")"
		total=$((total + 1))
		case "$st" in
			OK) mark="${GRN}v${RST}"; ok=$((ok + 1)) ;;
			KO) mark="${RED}x${RST}" ;;
			*)  mark="${DIM}.${RST}" ;;
		esac
		printf '  %s  %s\n' "$mark" "$(basename "$d")"
	done
	echo
	echo "$ok/$total valides.   ./grademe.sh <numero>  pour corriger un exo."
}

main() {
	local args=() a d rc=0
	for a in "$@"; do
		case "$a" in
			--no-asan) USE_ASAN=0 ;;
			-h|--help) sed -n '3,13p' "${BASH_SOURCE[0]}"; exit 0 ;;
			*) args+=("$a") ;;
		esac
	done
	command -v timeout > /dev/null 2>&1 && HAVE_TIMEOUT=1
	if [ "${#args[@]}" -eq 0 ]; then
		show_list
		return 0
	fi
	command -v "$CC" > /dev/null 2>&1 || { echo "${RED}Compilateur introuvable : $CC${RST}"; exit 1; }
	asan_ok && ASAN=1
	if [ "$ASAN" = 1 ]; then
		echo "${DIM}$CC ${FLAGS[*]} + AddressSanitizer (debordements, NULL...)${RST}"
	else
		echo "${DIM}$CC ${FLAGS[*]} (AddressSanitizer indisponible ou desactive)${RST}"
	fi
	if [ "${args[0]}" = all ]; then
		local n=0 v=0
		for d in "$ROOT"/ex[0-9][0-9]_*/; do
			d="${d%/}"
			has_rendu "$d" || continue
			n=$((n + 1))
			grade "$d" && v=$((v + 1))
			echo
		done
		[ "$n" -eq 0 ] && echo "Aucun rendu trouve : ecris ton .c dans le dossier de l'exo (ex : ex00_safe_op/safe_op.c)."
		[ "$n" -gt 0 ] && echo "${BLD}$v/$n exos rendus valides.${RST}"
		return 0
	fi
	for a in "${args[@]}"; do
		d="$(find_ex "$a")" || { echo "${RED}Exo introuvable : $a${RST}"; rc=1; continue; }
		grade "$d" || rc=1
	done
	return "$rc"
}

main "$@"
