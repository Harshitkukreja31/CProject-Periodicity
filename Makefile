CC = gcc
CFLAGS = -Wall -Wextra -I./include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/periodic_table

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
# Test-related variables
TEST_DIR = tests
TEST_SRC = $(TEST_DIR)/test_periodicity.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_EXEC = run_tests

# Existing source files (adjust as needed)
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# Test target
test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Compile test file
$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean test files
clean_test:
	rm -f $(TEST_EXEC) $(TEST_OBJ)

# Add clean_test to the main clean target
clean: clean_test
