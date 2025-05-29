OO_TOOLCHAIN ?= /media/kalaposfos/Shared/shadps4/tools/PS4Toolchain
TARGET      ?= libSceFios2
INTDIR      ?= build
OUTDIR      ?= out

CFLAGS   = -fPIC -funwind-tables --target=x86_64-pc-freebsd12-elf -I"$(OO_TOOLCHAIN)/include"
CXXFLAGS = $(CFLAGS) -I"$(OO_TOOLCHAIN)/include/c++/v1"
LDFLAGS  = -pie --script "$(OO_TOOLCHAIN)/link.x" --eh-frame-hdr -L"$(OO_TOOLCHAIN)/lib"
LIBS     = -lc -lkernel -lc++

STUBFLAGS = -ffreestanding -nostdlib -fno-builtin -fPIC
STUB_TARGET = x86_64-pc-linux-gnu

SRC_C   := $(wildcard *.c)
SRC_CPP := $(wildcard *.cpp)
OBJ     := $(patsubst %.c,$(INTDIR)/%.o,$(SRC_C)) $(patsubst %.cpp,$(INTDIR)/%.o,$(SRC_CPP))
STUBOBJ := $(patsubst %.c,$(INTDIR)/%.o.stub,$(SRC_C)) $(patsubst %.cpp,$(INTDIR)/%.o.stub,$(SRC_CPP))

OUTPUT_ELF  := $(INTDIR)/$(TARGET).elf
OUTPUT_OELF := $(INTDIR)/$(TARGET).oelf
OUTPUT_PRX  := $(TARGET).prx
OUTPUT_STUB := $(TARGET)_stub.so

.PHONY: all clean copy

all: $(OUTPUT_PRX)

$(INTDIR):
	mkdir -p $(INTDIR)

$(INTDIR)/%.o: %.c | $(INTDIR)
	clang $(CFLAGS) -c $< -o $@

$(INTDIR)/%.o: %.cpp | $(INTDIR)
	clang++ $(CXXFLAGS) -c $< -o $@

$(OUTPUT_ELF): $(OBJ)
	ld.lld -m elf_x86_64 $(LDFLAGS) $(LIBS) "$(OO_TOOLCHAIN)/lib/crtlib.o" $^ -o $@

$(INTDIR)/%.o.stub: %.c | $(INTDIR)
	clang -target $(STUB_TARGET) $(STUBFLAGS) -I"$(OO_TOOLCHAIN)/include" -c $< -o $@

$(INTDIR)/%.o.stub: %.cpp | $(INTDIR)
	clang++ -target $(STUB_TARGET) $(STUBFLAGS) -I"$(OO_TOOLCHAIN)/include" -I"$(OO_TOOLCHAIN)/include/c++/v1" -c $< -o $@

$(OUTPUT_STUB): $(STUBOBJ)
	clang++ -target $(STUB_TARGET) -shared -fuse-ld=lld $(STUBFLAGS) -L"$(OO_TOOLCHAIN)/lib" $(LIBS) $^ -o $@

$(OUTPUT_PRX): $(OUTPUT_ELF) $(OUTPUT_STUB)
	"$(OO_TOOLCHAIN)/bin/linux/create-fself" -in "$(OUTPUT_ELF)" --out "$(OUTPUT_OELF)" --lib "$(OUTPUT_PRX)" --paid 0x3800000000000011

copy:
	cp $(OUTPUT_PRX) $(OUTDIR)/
	cp $(OUTPUT_STUB) $(OUTDIR)/

clean:
	rm -rf $(INTDIR) $(OUTPUT_PRX) $(OUTPUT_STUB)
