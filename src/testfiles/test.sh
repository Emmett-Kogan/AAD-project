testdirs=(Example1 Spec TestCase1 TestCase2)

cd ..
make debug
failed=0
for i in "${testdirs[@]}"; do
    echo "$i:"
    ./aqueduct testfiles/$i/grid.txt
    diff pathLength.txt testfiles/$i/pathLength.txt

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