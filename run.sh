echo "Enter mode: 0, 1 or 2"
read m
if [ $m == 0 ]
then
    echo "Enter phi1 phi2 l1 l2 m1 m2 width height"
    read a b c d e f g h
    ./prog.out $a $b $c $d $e $f $g $h & python3 graph.py
    python3 graph2.py
elif [ $m == 1 ]
then
    echo "Enter width height number"
    read a b c
    ./prog.out $a $b $c
else
    echo "Enter width height number"
    read a b c
    ./prog.out $a $b $c 1
fi
