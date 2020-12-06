out: main.c
	gcc main.c -LCSFML\lib\gcc -lcsfml-system -lcsfml-window -lcsfml-graphics -ICSFML\include -o out.exe
