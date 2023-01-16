# check installation of githooks and display help message when typing make
all: help

# ==================================================================================== #
# HELPERS
# ==================================================================================== #

## help: print this help message
.PHONY: help
help:
	@echo 'Usage:'
	@sed -n 's/^##//p' ${MAKEFILE_LIST} | column -t -s ':' |  sed -e 's/^/ /'

BUILDDIR ?= build

## setup: create a build directory for meson.
setup:
	meson setup $(BUILDDIR)

## setup/reconfigure: reconfigure a build directory for meson.
setup/reconfigure:
	meson setup --reconfigure $(BUILDDIR)


## build: build binaries.
build:
	meson compile -C $(BUILDDIR)

## test: run all tests.
test:
	meson test -C $(BUILDDIR)

## clean: clean all artefacts.
clean:
	-rm -rf build
	
.PHONY: help setup build test clean
