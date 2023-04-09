CC=latexmk

report.pdf: report.tex
	$(CC) -pdf --shell-escape $^

.PHONY: pdf clean
pdf: report.pdf

clean: 
	$(CC) -C -bibtex
	rm -f *.xml
	rm -f *.bcf