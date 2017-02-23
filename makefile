.SILENT:
TMP = "default"



all:
	clear
	clear
	echo make all
	



clean:
	clear
	clear
	echo clean
	rm -f *.o


git:
	clear
	clear
	git add -A
	git commit -m $(TMP)
	git push


ipcrm:
	clear
	ipcrm -Q 1234















