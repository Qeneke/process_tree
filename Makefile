build: tree binary_process_tree

tree:
	@gcc tree.c -o tree
binary_process_tree:
	@gcc binary_process_tree.c -o binary_process_tree

start_tree:
	@./tree
start_binary_process_tree:
	@./binary_process_tree

.PHONY: clean
clean:
	@rm -rf *.tmp
	@rm -rf tree
	@rm -rf binary_process_tree
