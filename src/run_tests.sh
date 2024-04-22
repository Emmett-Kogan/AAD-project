cd testfiles

for script in *".sh"; do
    echo "Running $script"
    chmod +x $script
    ./$script
done

cd ..
