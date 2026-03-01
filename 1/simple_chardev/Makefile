obj-m += simple_chardev.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(CURDIR)

.PHONY: all clean help install

all: modules

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

install: modules
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

help:
	@echo "Targets:"
	@echo "  make              - Build kernel module"
	@echo "  make clean        - Remove build artifacts"
	@echo "  make install      - Install module to system"
	@echo "  make help         - Show this message"

