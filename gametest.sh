echo testing game
./output < gametest-input-01.txt | diff - gametest-output-01.txt -Z
