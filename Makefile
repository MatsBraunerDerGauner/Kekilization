out: main.c button.c map.c vector.c humen.c tree.c object.c
	gcc -g main.c button.c map.c vector.c humen.c tree.c object.c -LCSFML\lib\gcc -lcsfml-system -lcsfml-window -lcsfml-graphics -ICSFML\include -o out.exe
