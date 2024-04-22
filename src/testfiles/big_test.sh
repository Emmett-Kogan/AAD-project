cd ..
make big
for i in {1..100}; do
    echo "$i:"
    time ./aqueduct testfiles/Big/input/gridRand_$i.input
    diff -w -B pathLength.txt testfiles/Big/output/pathLengthRand_$i.output

    if [[ $? -ne 0 ]]; then
        echo "Failed test $i"
    fi

    # Just paranoid because of the times
    echo "Output:"
    cat pathLength.txt
    echo
    echo "Rubric:"
    cat testfiles/Big/output/pathLengthRand_$i.output
    echo
done

# Cleanup
rm pathLength.txt
make clean
cd testfiles