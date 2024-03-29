BIN_NAME=pwgencc
PWGENCC_OBJ=pwgencc.o
MAIN_OBJ=main.o

build: build_pwgencc build_main
	@echo "Building pwgen++"
	clang++ ${MAIN_OBJ} ${PWGENCC_OBJ} -o ${BIN_NAME} -O2
	@echo "Build done!"

build_pwgencc:
	@echo "Building pwgencc object"
	clang++ -c pwgencc.cc -o ${PWGENCC_OBJ}
	@echo "Build of pwgencc object done!"

build_main:
	@echo "Building main object"
	clang++ -c main.cc -o ${MAIN_OBJ}
	@echo "Build of main object done!"

clean:
	@echo "Cleaning up"
	rm -rf *.o
	rm -rf ${BIN_NAME} 
	@echo "Cleanup complete!"