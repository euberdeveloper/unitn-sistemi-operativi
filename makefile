FLAGS = --std=gnu90 -lpthread 

ANALIZER_DEPENDENCIES = libs/colour/colour.c \
	libs/general/general.c \
    libs/communication/communication.c \
    libs/logger/logger.c \
    libs/util/util.c \
    libs/communications/communications.c \
    libs/process/process.c \
    libs/shell_utils/shell_utils.c \
    libs/text/text.c \
    src/analyzer/shell_commands/shell_commands.c \
    src/analyzer/functions/functions.c

REPORTER_DEPENDENCIES = libs/colour/colour.c \
	libs/general/general.c \
    libs/logger/logger.c \
    libs/shell_utils/shell_utils.c \
    libs/text/text.c \
    src/reporter/shell_commands/shell_commands.c \
    src/reporter/functions/data_formatter/data_formatter.c \
    src/reporter/functions/communication/communication.c \
    src/reporter/functions/functions.c

MAIN_DEPENDENCIES = libs/colour/colour.c \
	libs/general/general.c \
    libs/logger/logger.c \
    libs/shell_utils/shell_utils.c \
    libs/text/text.c \
    libs/forking/forking.c \
    src/main/shell_commands/shell_commands.c \
    src/main/pipes/pipes.c \
    src/main/functions/functions.c \
    src/main/functions/signals/signals.c
    

.PHONY: help

help: cat README.txt

build: bin/analyzer bin/reporter bin/main

bin/analyzer: $(ANALIZER_DEPENDENCIES)
	mkdir -p bin
	gcc src/analyzer/analyzer.c $(ANALIZER_DEPENDENCIES) -o bin/analyzer $(FLAGS)

bin/reporter: $(REPORTER_DEPENDENCIES)
	mkdir -p bin
	gcc src/reporter/reporter.c $(REPORTER_DEPENDENCIES) -o bin/reporter $(FLAGS)

bin/main: $(MAIN_DEPENDENCIES)
	mkdir -p bin
	gcc src/main/main.c $(MAIN_DEPENDENCIES) -o bin/main $(FLAGS)

