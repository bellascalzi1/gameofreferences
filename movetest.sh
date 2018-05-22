echo testing move
./output01 < movetest-input-01.txt | diff - movetest-output-01.txt  -Z
