# exam_train : 20 exos format exam

Pack monté à partir de tes deux repos (`exams` lvl00 → lvl03, `modules-exams-train-42/exams`) et de l'examshell de wkratos (`PISCINE_PART` + `STUD_PART`).
Ce ne sont pas des copies du pool : ce sont des variantes qui retravaillent exactement ce qui casse dans ton code (section 2), au format des vrais sujets.

Pas de solutions dans le pack. Les indices sont des questions, sans code.

---

## 1. Comment t'en servir

```
exNN_nom/subject.en.txt   le sujet (en anglais, comme à l'exam)
exNN_nom/indice.txt       questions ciblées : à n'ouvrir qu'après ~20 min bloqué
exNN_nom/nom.c            ← ton rendu, à créer dans le dossier de l'exo
```

```bash
./grademe.sh          # la liste des exos + ce que t'as validé
./grademe.sh 4        # corrige l'exo 04   (ou : ./grademe.sh rev_epur)
./grademe.sh all      # corrige tout ce que t'as rendu
```

Le grademe :
- compile en `cc -Wall -Wextra -Werror`, comme l'exam. Si ça compile pas, il te dit pourquoi en français ;
- lance 7 à 22 tests par exo, cas limites compris (chaîne vide, que des espaces, INT_MIN, très longues entrées...) ;
- tourne avec AddressSanitizer quand ta machine l'a : il attrape les débordements, les NULL, les buffers trop petits, et il te donne **la ligne** ;
- coupe à 3 s : une boucle infinie ou un algo en force brute sur les grosses valeurs = timeout ;
- te montre le premier test raté : commande, attendu, obtenu (en `cat -e`).

Les exos 05, 06, 12 et 13 vérifient aussi ce que tu passes à malloc (taille exacte, copie ou pas, malloc interdit). Ces vérifs-là ne marchent que sous Linux ; sur macOS, le grademe les saute.

Options : `--no-asan` pour couper AddressSanitizer, `CC=clang ./grademe.sh 4` pour changer de compilo.
Ne fouille pas dans `.tests/` : il y a les mains de test et les sorties attendues, ça spoile les cas.

---

## 2. Ce que ton code montre

J'ai compilé et lancé tes fichiers (flags de l'exam + AddressSanitizer), et comparé tes programmes aux solutions de l'examshell sur une centaine d'entrées. Chaque point ci-dessous est vérifié. Je te donne la ligne, pas la correction.

**La logique est solide.** add_prime_sum, alpha_mirror, hidenp, inter, union, wdmatch, paramsum, print_hex, tab_mult, str_capitalizer, rstr_capitalizer, ft_itoa (INT_MIN géré), ft_atoi_base : tous justes sur tous les cas testés. Ce qui te coûte des points, c'est autour : la compilation, les tailles, les cas limites.

### a) Ça ne passe pas la compilation de l'exam → 0 direct

Dans `exams`, 6 fichiers sur 48 ne compilent pas avec les flags. Et un septième compile, mais la moulinette ne trouverait pas la fonction :

| Fichier | Ligne | Question |
|---|---|---|
| `exams/lvl03/ex07/expand_str.c` | 19 | Relis-la caractère par caractère. |
| `exams/lvl02/ex03/last_word.c` | 29 | Même famille. |
| `exams/lvl02/ex06/max.c` | 8 et 10 | Deux erreurs différentes. |
| `exams/lvl02/ex11/is_power_of_2.c` | 10 et 13 | Compare les types des deux côtés. |
| `exams/lvl02/ex00/ft_atoi.c` | 14 | Le nom de ta fonction existe déjà quelque part. |
| `exams/lvl03/ex12/paramsum.c` | 17 | Lequel de tes deux paramètres sert à quelque chose ? (Juste, mais refusé par `-Wextra`.) |
| `modules-exams-train-42/exams/ft_split/ft_spliit.c` | 63 | La logique est juste, mais quel nom demande le sujet ? |

Dans `modules-exams-train-42/exams`, c'est 15 fichiers sur 32 (souvent des brouillons : `ftput`, un backtick qui traîne, `ft_putchar` jamais déclaré...).
La logique était bonne dans la plupart de ces fichiers. Réflexe à prendre : **toujours compiler avec `-Wall -Wextra -Werror` avant de rendre.**

### b) Taille des malloc (off-by-one)

- `exams/lvl03/ex02/ft_rrange.c` l.17 : combien d'**octets** tu demandes ? Pose le calcul pour size = 2, puis compare avec ce que ta boucle écrit (AddressSanitizer : *heap-buffer-overflow* l.22).
- `modules-exams-train-42/exams/ft_range/ft_range.c` l.16 : combien de cases tu alloues, combien ta boucle en remplit ? Teste (3, 3).

### c) Buffers de taille fixe et chaînes vides

- `char cpy[100]` dans `epur_str.c` l.55, `expand_str.c` l.58 (et la version de modules l.62) : avec 60 mots en entrée, *stack-buffer-overflow*.
- `epur_str.c` l.36 : avec `""` ou `"   "`, où pointe `i` juste après cette ligne ?
  C'est la réponse à ta question en commentaire dans `expand_str.c` l.36 (« est-ce obligatoire ? ») : **oui**. Aujourd'hui ça marche par chance : tu lis après la fin de la chaîne. Avec une variable d'environnement un peu longue, ça plante (*stack smashing detected*, vérifié).

### d) Valeur de départ et ordre des opérations

- `max.c` l.6 : que renvoie ta fonction pour {-5, -3} ? (vérifié : 0)
- `do_op.c` l.33 : `./do_op 5 + 0` → *Floating point exception*. Qu'est-ce qui est calculé avant d'avoir regardé l'opérateur ?

### e) Overflow et force brute

- `lcm.c` l.36 : lcm(65536, 65536) renvoie 0 (vérifié). Et l.39 : un `main` laissé dans un exo « fonction » → *multiple definition of main* à l'exam.
- `pgcd.c` l.22 : `./pgcd 2147483646 2147483647` met 4 s. `is_power_of_2(3000000000)` met 3,4 s. L'exam ne teste peut-être pas ça, mais le jour où il le fait...

---

## 3. Les 15 exos

| # | Exo | Type | Ce que ça retravaille (section 2) |
|---|---|---|---|
| **Niveau 1** | | | **échauffement ciblé** |
| 00 | safe_op | programme | ordre des opérations (d), putnbr avec INT_MIN |
| 01 | tab_spread | fonction | valeur de départ (d), int vs unsigned (a), tableau vide |
| 02 | rotate_bits | fonction | opérateurs de bits (pas encore fait dans tes repos), modulo négatif, n énorme |
| 03 | nth_word | programme | parcours de mots, chaînes vides / que des espaces (c) |
| **Niveau 2** | | | **chaînes, cas limites, malloc au bon octet** |
| 04 | rev_epur | programme | famille epur/expand sans buffer fixe (c) |
| 05 | ft_wordjoin | fonction | calculer la taille exacte avant malloc, vérifiée à l'octet près (b, c) |
| 06 | ft_chunks | fonction | `char **` à deux niveaux de malloc, copie ou pointeur, overflow d'un calcul |
| 07 | sort_by_len | programme | trier des mots, tri stable, échanger des pointeurs |
| **Niveau 3** | | | **nombres : overflow et algos qui tiennent** |
| 08 | lcm_tab | fonction | PGCD rapide, ordre multiplication/division (e), unsigned |
| 09 | fprime_pow | programme | borne en racine carrée, `i * i` qui déborde, format de sortie |
| 10 | base_conv | programme | atoi_base + putnbr_base (ton convert_base), INT_MIN, "-0" |
| **Niveau 4** | | | **struct, listes chaînées, récursion** |
| 11 | ft_list_count_if | fonction + header | typedef/struct, parcours, pointeur sur fonction, « différent de 0 » |
| 12 | ft_list_push_back | fonction + header | `t_list **`, malloc d'un maillon, liste vide, malloc qui échoue |
| 13 | ft_list_reverse | fonction + header | rebrancher des pointeurs sans rien perdre |
| 14 | flood_count | fonction + header | récursion + `char **` + struct, sans abîmer le tableau |
| **Révisions** | | | **≤ C07, famille inter / union / wdmatch** |
| 15 | diff_chars | programme | inter à l'envers, sans doublons |
| 16 | sym_diff | programme | union « exclusive » : ce qui n'est que d'un côté |
| 17 | rev_wdmatch | programme | wdmatch en lisant s2 de droite à gauche |
| 18 | is_anagram | programme | compter les caractères, pas juste les repérer |
| 19 | ft_interdup | fonction | inter renvoyé dans une chaîne malloc (C07) |

Le niveau 4 prépare directement le dernier niveau de l'exam rank 02 (flood_fill, sort_list, ft_list_foreach, ft_list_remove_if) et la partie bonus de la libft (les `ft_lst*`).

---

## 4. Le vrai pool : ce qui te reste (d'après tes repos)

Dans l'examshell, `STUD_PART/exam_02` = l'exam rank 02 du tronc commun. Pas trouvé dans tes repos :

- niveau 1 : `print_bits`, `swap_bits`, `reverse_bits`, `camel_to_snake`, `snake_to_camel`, `ft_strcspn`
- niveau 2 : `ft_list_size`
- niveau 3 : `fprime`, `rev_wstr`, `rostring`, `sort_list`, `flood_fill`, `ft_list_foreach`, `ft_list_remove_if`

Attention : dans cet examshell, la solution de référence de `union` en mode STUD (`STUD_PART/exam_02/1/union/union.c`) est fausse. Elle parcourt aussi `argv[0]`, donc un `union` juste (comme le tien) serait refusé. Celle de `PISCINE_PART` est bonne.

---

## 5. Rappels exam

- `-Wall -Wextra -Werror` : un warning = 0.
- Exo « fonction » : **pas de `main`** dans le fichier rendu.
- Nom de fonction et prototype **exacts**, tous les *Expected files* rendus (header compris).
- Toujours tester : pas d'argument, trop d'arguments, `""`, `"   "`, INT_MIN / INT_MAX, une entrée très longue.
