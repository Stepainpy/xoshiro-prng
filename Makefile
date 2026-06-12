.PHONY: all clean

CC = cc
CFLAGS += -O2 -std=c89
CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -I. -Iprng

PCFILES = $(wildcard prng/*/*.c)

NAME = tp
ifeq ($(OS),Windows_NT)
EXE = $(NAME).exe
else
EXE = $(NAME)
endif

OBJDIR = bin
OBJPDIR = $(OBJDIR)/prng

OBJPDIRS = $(addprefix $(OBJPDIR)/,$(notdir $(basename $(PCFILES))))

OBJS += $(OBJDIR)/test.o
OBJS += $(patsubst %.c,$(OBJDIR)/%.o,$(PCFILES))

ifeq ($(CC),clang)
CFLAGS += -Wno-newline-eof
endif

all: $(EXE)

clean:
ifneq ($(wildcard $(OBJDIR)/.*),)
	rm -fr $(EXE) $(OBJDIR)
else
	@echo "Already cleaned"
endif

$(EXE): $(OBJS)
	$(CC) -o $@ $^

$(OBJS): | $(OBJDIR) $(OBJPDIRS)

$(OBJDIR):
	mkdir $(OBJDIR)
$(OBJPDIRS):
	mkdir -p $(OBJPDIRS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPDIR)/%/%.o: prng/%/%.c
	$(CC) $(CFLAGS) -c -o $@ $<