.PHONY: release clean run gen_makefile

release:
	cd proj.linux && make

clean:
	cd proj.linux && make clean

run:
	cd proj.linux && make run

project_mkf:
	cd proj.linux && ruby ./generate-makefile.rb > Makefile

