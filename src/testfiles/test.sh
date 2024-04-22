testdirs=(Example1 Spec TestCase1 TestCase2)

cd ..
make debug
for i in "${testdirs[@]}"; do
    echo "$i:"
    time ./aqueduct testfiles/$i/grid.txt
    diff pathLength.txt testfiles/$i/pathLength.txt

    if [[ $? -ne 0 ]]; then
        echo "Failed test $i"
    fi

    echo "Output:"
    cat pathLength.txt
    echo
    echo "Rubric:"
    cat testfiles/$i/pathLength.txt
    echo
done

# Cleanup
rm pathLength.txt
make clean
cd testfiles