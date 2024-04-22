testdirs=(Example1 Spec TestCase1 TestCase2)

make debug
for i in "${testdirs[@]}"; do
    ./aqueduct testfiles/$i/grid.txt
    diff pathLength.txt testfiles/$i/pathLength.txt

    if [[ $? -ne 0 ]]; then
        echo "Failed test $i"
    fi
done

# Cleanup
rm pathLength.txt
make clean
