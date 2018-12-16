compiler=g++
flags=-Wall

tests:
	$(compiler) $(flags) tests.cpp -o tests

menu:
	$(compiler) $(flags) menu.cpp -o menu