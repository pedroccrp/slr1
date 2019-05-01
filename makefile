# Compiler
CC := g++
CFLAGS := -g -Wall

# Directories 
SRCDIR := src
BUILDDIR := build
TARGET := bin/slr1

# Pre-compiling
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I include

$(TARGET) : $(OBJECTS)
	@echo " Linking..."; $(CC) $^ -o $(TARGET)
	@echo " Done!"

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " Generating: $@"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo " Done!"

info:
	@echo " Info..."
	@echo " SOURCES = $(SOURCES)"
	@echo " OBJECTS = $(OBJECTS)"