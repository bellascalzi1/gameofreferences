# This script tests the game's look command. It tests bogus inputs, as well as whether the game puts the right information onto each tile.
echo Testing Look
./output01 < looktest-input-01.txt | diff - looktest-output01.txt -Z
