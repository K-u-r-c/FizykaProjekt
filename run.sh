echo "Enter mode: 0 or 1"
read m
if [ $m == 0 ]
then
    echo "Enter phi1 phi2 l1 l2 m1 m2 width height"
    read a b c d e f g h
    ./prog.out $a $b $c $d $e $f $g $h & python3 graph.py
else
    echo "Enter width height number"
    read a b c
    ./prog.out $a $b $c
fi