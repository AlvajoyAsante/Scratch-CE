# ----------------------------
# Program Options
# ----------------------------

NAME         ?= SCRATCH
ICON         ?= icon.png
DESCRIPTION  ?= ""
COMPRESSED   ?= YES
ARCHIVED     ?= NO
FONTPACKNAME?=SCRFONT
# ----------------------------
# Compile Options
# ----------------------------

# That one gets passed by builder.sh inside EXTRA_CFLAGS
OPT_MODE      =
EXTRA_CFLAGS ?= -Oz -W -Wall -Wwrite-strings -Wno-unknown-pragmas -Wno-incompatible-library-redeclaration -Wno-main-return-type

# ----------------------------
# Debug Options
# ----------------------------

OUTPUT_MAP   ?= NO

include $(CEDEV)/include/.makefile

$(BINDIR)/$(FONTPACKNAME).bin: $(SRCDIR)/drsans-07-normal.fnt
	convfont -o fontpack -N "Dr. Sans" -P "Calculator 1252" \
	-D "A font designed for maximum readability [SCRATCH]" \
	-V "7/21/2020" \
	-f $(SRCDIR)/drsans-07-normal.fnt -l 8  -x 3 -c 1 -a 1 -b 1 -w normal -s 0 \
	$(BINDIR)/$(FONTPACKNAME).bin

$(BINDIR)/$(FONTPACKNAME).8xv: $(BINDIR)/$(FONTPACKNAME).bin
	convbin --iformat bin --input $(BINDIR)/$(FONTPACKNAME).bin --oformat 8xv --output $(BINDIR)/$(FONTPACKNAME).8xv --archive --name $(FONTPACKNAME)

all: $(BINDIR)/$(FONTPACKNAME).8xv

