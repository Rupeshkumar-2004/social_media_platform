# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = 

# Target executable
TARGET = social_media

# Source files
SRCS = main.c platform.c post.c comment.c reply.c

# Object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Header files (for dependency tracking)
HEADERS = platform.h post.h comment.h reply.h

# Default target - builds the executable
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile .c files to .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned build files"

# Rebuild everything from scratch
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build with additional flags
debug: CFLAGS += -DDEBUG -O0
debug: clean $(TARGET)

# Release build with optimizations
release: CFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

# Check for memory leaks using valgrind (if installed)
memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Display help
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  rebuild   - Clean and build from scratch"
	@echo "  run       - Build and run the program"
	@echo "  debug     - Build with debug symbols"
	@echo "  release   - Build optimized release version"
	@echo "  memcheck  - Run with valgrind memory checker"
	@echo "  help      - Show this help message"

# Phony targets (not actual files)
.PHONY: all clean rebuild run debug release memcheck help