all:
	gcc main.c graph.c -o graphs -g

clear:
	-rm -rvf *core graphs
