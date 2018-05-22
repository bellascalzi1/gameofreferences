#This test tests the process of building structures in the game. It covers building a building correctly, as well as giving fake co-ordinates and commands.
echo testing building tests
./output01 < buildingtest-input-01.txt | diff - buildingtest-output-01.txt -Z
