all: adivina.exe encuentra_el_tesoro.exe

adivina.exe: adivina.cpp
	g++ -o adivina.exe adivina.cpp

encuentra_el_tesoro.exe: encuentra_el_tesoro.cpp
	g++ -std=c++11 -o encuentra_el_tesoro.exe encuentra_el_tesoro.cpp

clean:
	rm adivina.exe encuentra_el_tesoro.exe