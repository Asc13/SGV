TARGET = sgv

CC = gcc

CC_FLAGS = -Wall -O3

OUTDIR = ./bin
DIR_OBJ = ./obj
SUBDIR = src src/Model src/View src/Controller

INCS = $(wildcard *.h $(foreach fd, $(SUBDIR), $(fd)/*.h))
SRCS = $(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.c))
NODIR_SRC = $(notdir $(SRCS))

OBJS = $(addprefix $(DIR_OBJ)/, $(SRCS:c=o))

INC_DIRS = -I./ $(addprefix -I, $(SUBDIR))

LIBS = -lpcre2-8

PHONY = $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(OUTDIR)/$@ $(OBJS) $(LIBS)

$(DIR_OBJ)/%.o: %.c $(INCS)
	mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $< $(INC_DIRS)

PHONY += clean

clean:
	rm -rf $(OUTDIR)/* $(DIR_OBJ)/*

run:
	./$(OUTDIR)/$(TARGET)

.PHONY: $(PHONY)