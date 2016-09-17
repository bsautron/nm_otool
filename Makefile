.PHONY: nm otool

nm:
	make -C nm/
	cp nm/ft_nm .

otool:
	make -C otool/
	cp otool/ft_otool .
