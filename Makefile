all:
	@gcc tree.c
	@./a.out

build:
	@mkdir -p /tmp/process_example

clean:
	@rm -rf /tmp/process_example
