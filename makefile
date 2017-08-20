rwildcard     = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# source files
SRCS := $(call rwildcard,,*.cpp)
TEST_SRCS = $(call rwildcard,tests,*.cpp)
ENTRY_POINT = src/program.cpp

# files included in the tarball generated by 'make dist' (e.g. add LICENSE file)
DISTFILES := $(BIN)

# intermediate directory for generated object files
OBJDIR := bin
# intermediate directory for generated dependency files
DEPDIR := bin

# output binary
BIN := $(OBJDIR)/program

# object files, auto generated from source files
OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))
TEST_OBJS = := $(patsubst %,$(OBJDIR)/%.o,$(basename $(TEST_SRCS)))
# dependency files, auto generated from source files
DEPS := $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
TEST_DEPS := $(patsubst %,$(DEPDIR)/%.d,$(basename $(TEST_SRCS)))

# compilers (at least gcc and clang) don't create the subdirectories automatically
$(shell mkdir -p $(dir $(OBJS)))

# C compiler
CC := gcc
# C++ compiler
CXX := g++
# linker
LD := g++
# tar
TAR := tar

# C flags
CFLAGS := -std=c11
# C++ flags
CXXFLAGS := -std=c++11
# C/C++ flags
CPPFLAGS := -g -Wall -Wextra -Iinclude
# linker flags
LDFLAGS :=
# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# compile C source files
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c -o $@
# compile C++ source files
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@
# link object files to binary
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS)

all: .removeTests .bin

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(DEPDIR)

.PHONY: check
check: .removeEntryPoint .changeBinName .bin
	$(BIN)

.removeEntryPoint:
	$(eval SRCS = $(ENTRY_POINT), $(SRCS))
	$(eval OBJS = $(filter-out $(OBJDIR)/$(ENTRY_POINT:.cpp=.o), $(OBJS)))

.removeTests:
	$(eval SRCS := $(filter-out $(TEST_SRCS), $(SRCS)))
	$(eval OBJS := $(filter-out $(TEST_OBJS), $(OBJS)))
	$(eval DEPS := $(filter-out $(TEST_DEPS), $(DEPS)))

.changeBinName:
	$(eval BIN := $(OBJDIR)/.check)


.PHONY: help
help:
	@echo available targets: all clean check

.bin: $(OBJS)
	$(LINK.o) $(OBJS) -o $(BIN)

$(OBJDIR)/%.o: %.cpp
	$(COMPILE.cc) $<

.PRECIOUS = $(DEPDIR)/%.d
$(DEPDIR)/%.d: ;

-include $(DEPS)
