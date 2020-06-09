gcc  -lpthread \
    ../../libs/colour/colour.c \
    ../../libs/general/general.c \
    ../../libs/logger/logger.c \
    ../../libs/shell_utils/shell_utils.c \
    ../../libs/text/text.c \
        ../../libs/util/util.c \

    ../../libs/communications/communications.c \

    ../../libs/process/process.c \

    ./shell_commands/shell_commands.c \
    ./functions/functions.c \
    ./analyzer.c \
    -o analyzer