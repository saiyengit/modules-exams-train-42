# cas de test de diff_chars (une ligne = un test)
t 'padinton' 'paqefwtdjetyiytjneytjoeyjnejeyj'
t 'bonjour' 'jour'
t 'rien' 'cette phrase ne cache rien'
t 'aabbccdd' 'bd'
t '' 'abc'
t 'abc' ''
t 'abc'
t
t 'a' 'b' 'c'
t 'Hello World' 'lo'
t '  espaces  ' 'e'
t $'\tta\tb' $'\t'
t 'zzzz' 'Z'
