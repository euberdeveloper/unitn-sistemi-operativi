# the name of the libraries
LIBRARIES = analyser
# all the object files from the libraries names (name/name.o)
LIBRARIES_O = $(foreach lib,$(LIBRARIES),$(lib)/$(lib).o)
# all the c files from the libraries names (name/name.c)
LIBRARIES_C = $(foreach lib,$(LIBRARIES),$(lib)/$(lib).c)
# all the header files from the libraries names (name/name.h)
LIBRARIES_H = $(foreach lib,$(LIBRARIES),$(lib)/$(lib).h)
# all the test.c files from the libraries names (name/test.c)
LIBRARIES_TEST = $(foreach lib,$(LIBRARIES),$(lib)/test)

# clean is not a target file
.PHONY: clean
# If there is an error creating an object file (also on test), it will be erased
.DELETE_ON_ERROR: %.o

# The output of the project
main: $(LIBRARIES_O)
	$(CC) $@.c $(LIBRARIES_O) -o $@

# Every file object
%.o: %.c %.h
	# Compile the c file into an object file
	$(CC) -c $< -o $@
	# Get the name of the librery, compile the test.c file, execute it, remove it and return the execution result (if test fails, everything fails)
	NAME=$(word 1,$(subst /, ,$@)) ; \
		$(CC) $$NAME/$$NAME.o $$NAME/test.c -o $$NAME/test && \
		./$$NAME/test ; \
		OUTCOME=$$? ; \
		rm $$NAME/test ; \
		exit $$OUTCOME

# Delete the main, all the object files and for security also all the test.o files
clean:
	rm -f main $(LIBRARIES_O) $(LIBRARIES_TEST)