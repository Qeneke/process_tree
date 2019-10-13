all:
	@gcc tree.c
	@./a.out

clean:
	@rm *.tmp
	@rm a.out
