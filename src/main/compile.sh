gcc ../../libs/colour/colour.c \
    ../../libs/general/general.c \
    ../../libs/logger/logger.c \
    ../../libs/shell_utils/shell_utils.c \
    ../../libs/text/text.c \
    ./shell_commands/shell_commands.c \
    ./forking/forking.c \
    ./functions/functions.c \
    ./functions/signals/signals.c \
    main.c \
    -o main \
    -lpthread 