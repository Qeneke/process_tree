all: build start

build: tree.c
	@gcc $^ -o tree

start:
	@./tree

clean:
	@rm *.tmp
	@rm tree
