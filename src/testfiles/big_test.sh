cd ..
make big

failed=0
for i in {1..100}; do
    echo "$i:"
    ./aqueduct testfiles/Big/input/gridRand_$i.input
    diff -w -B pathLength.txt testfiles/Big/output/pathLengthRand_$i.output

    if [[ $? -ne 0 ]]; then
        echo "Failed test $i"
        let "failed=failed+1"
    fi
done
echo "Tests failed: $failed"
# Cleanup
rm pathLength.txt
make clean
cd testfiles