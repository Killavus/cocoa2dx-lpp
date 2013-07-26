.PHONY: release clean run gen_makefile

release:
	cd Project.Linux && make

clean:
	cd Project.Linux && make clean

run:
	cd Project.Linux && make run

project_mkf:
	cd Project.Linux && ruby ./generate-makefile.rb > Makefile

