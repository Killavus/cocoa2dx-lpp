.PHONY: release clean run gen_makefile

release: gen_makefile
	cd proj.linux && make

clean: gen_makefile
	cd proj.linux && make clean

run: gen_makefile
	cd proj.linux && make run

gen_makefile:
	cd proj.linux && ruby ./generate-makefile.rb > Makefile

