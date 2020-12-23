out: main.c map.c vector.c humen.c object.c
	gcc -g main.c map.c vector.c humen.c object.c -LCSFML\lib\gcc -lcsfml-system -lcsfml-window -lcsfml-graphics -ICSFML\include -o out.exe
