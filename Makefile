CC = gcc
CFLAGS = -Wall -g -Iinclude
RM = rm -rf

SRC_DIR = src
BIN_DIR = bin
INC_DIR = include

TARGET = $(BIN_DIR)/main

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
HEADERS = $(wildcard $(INC_DIR)/*.h)
all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "Build complete: $(TARGET)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	$(RM) $(BIN_DIR)
	@echo "Clean complete"

run: $(TARGET)
	@echo "Running program..."
	@./$(TARGET)

info:
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"
	@echo "Headers: $(HEADERS)"
	@echo "Target: $(TARGET)"

DOC_DIR = doc
DOXYFILE = Doxyfile

doc: $(DOXYFILE)
	@echo "Generating documentation with Doxygen..."
	doxygen $(DOXYFILE)
	@echo "Documentation generated in $(DOC_DIR)/"

$(DOXYFILE):
	@echo "Creating Doxyfile configuration..."
	doxygen -g $(DOXYFILE)
	@echo "Configuring Doxyfile for this project..."
	@sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "Student Management System"/' $(DOXYFILE)
	@sed -i 's/OUTPUT_DIRECTORY       =/OUTPUT_DIRECTORY       = $(DOC_DIR)/' $(DOXYFILE)
	@sed -i 's/INPUT                  =/INPUT                  = $(SRC_DIR) $(INC_DIR)/' $(DOXYFILE)
	@sed -i 's/RECURSIVE              = NO/RECURSIVE              = YES/' $(DOXYFILE)
	@sed -i 's/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/' $(DOXYFILE)
	@sed -i 's/GENERATE_LATEX         = YES/GENERATE_LATEX         = NO/' $(DOXYFILE)
	@echo "Doxyfile created successfully!"

clean-doc:
	$(RM) $(DOC_DIR) $(DOXYFILE)
	@echo "Documentation cleaned"

.PHONY: all clean run info doc clean-doc
