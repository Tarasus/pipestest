
clear
cd parent
make clean
make

cd ../child
make clean
make

cd ../parent
echo "\n\nBUILD DONE\n\n"
echo "Run output:\n"


./parent "../child/child"
