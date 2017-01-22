none: help

help:
	@echo "=== Anari ==="
	@echo "Select a build target:"
	@echo "  make ready         Build Anari and bundles it for distribution."
	@echo "  make clean         Clean up Anari and Tester."
	@echo "  make cleandebug    Clean up Anari and Tester Debug."
	@echo "  make cleanrelease  Clean up Anari and Tester Release."
	@echo "  make docs          Generate HTML docs."
	@echo "  make docs_pdf      Generate PDF docs."
	@echo "  make anari         Build Anari as release."
	@echo "  make anari_debug   Build Anari as debug."
	@echo "  make tester        Build Anari Tester (+Anari) as release."
	@echo "  make tester_debug  Build Anari Tester (+Anari) as debug."
	@echo "  make all           Build everything."
	@echo "  make allfresh      Clean and rebuild everything."
	@echo
	@echo "Clang Sanitizers (requires Debug build and Clang.)"
	@echo "  SAN=address     Use AddressSanitizer"
	@echo "  SAN=leak        Use LeakSanitizer w/o AddressSanitizer (Linux only)"
	@echo "  SAN=memory      Use MemorySanitizer"
	@echo "  SAN=thread      Use ThreadSanitizer"
	@echo "  SAN=undefined   Use UndefiniedBehaviorSanitizer"
	@echo
	@echo "Optional Architecture"
	@echo "  ARCH=32         Make x86 build (-m32)"
	@echo "  ARCH=64         Make x64 build (-m64)"
	@echo
	@echo "Use Configuration File"
	@echo "  CONFIG=foo      Uses the configuration file 'foo.config'"
	@echo "                  in the root of this repository."
	@echo "  When unspecified, default.config will be used."
	@echo
	@echo "For other build options, see the 'make' command in 'docs/', 'anari-source/', 'anari-tester/', and 'cpgf/build/'."

clean:
	$(MAKE) clean -C anari-source
	$(MAKE) clean -C anari-tester

cleanall: clean
	$(MAKE) clean -C docs

cleandebug:
	$(MAKE) cleandebug -C anari-source
	$(MAKE) cleandebug -C anari-tester

cleanrelease:
	$(MAKE) cleanrelease -C anari-source
	$(MAKE) cleanrelease -C anari-tester

docs:
	$(MAKE) html -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/html/index.html'."
	@echo "-------------"

docs_pdf:
	$(MAKE) latexpdf -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/latex/Anari.pdf'."
	@echo "-------------"

anari:
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C anari-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "Anari is in 'anari-source/lib/Release'."
	@echo "-------------"

anari_debug:
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C anari-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo  on "anari is in 'anari-source/lib/Debug'."
	@echo "-------------"

ready: anari
	@rm -rf anari
	@echo "Creating file structure..."
	@mkdir -p anari/lib
	@echo "Copying Anari..."
	@cp -r anari-source/include anari/
	@cp anari-source/lib/Release/libanari.a anari/lib/libanari.a
	@echo "Copying README and LICENSE..."
	@cp README.md anari/README.md
	@cp LICENSE.md anari/LICENSE.md
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "The libraries are in 'anari'."
	@echo "-------------"

tester: anari
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C anari-tester
	@rm -f tester
	@ln -s anari-tester/bin/Release/anari-tester tester
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "Anari Tester is in 'anari-tester/bin/Release'."
	@echo "The link './tester' has been created for convenience."
	@echo "-------------"


tester_debug: anari_debug
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C anari-tester
	@rm -f tester_debug
	@ln -s anari-tester/bin/Debug/anari-tester tester_debug
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "Anari Tester is in 'anari-tester/bin/Debug'."
	@echo "The link './tester_debug' has been created for convenience."
	@echo "-------------"

all: docs tester

allfresh: cleanall all

.PHONY: all allfresh clean cleanall cleandebug cleanrelease docs docs_pdf anari anari_debug ready tester tester_debug
