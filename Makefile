all: simplified\ code_b.c simplified\ code_db.c

simplified\ code_b.c: simplified\ code.c
	tapenade -parserfileseparator "/" -outvars "u1 u2" -vars "vp u0 u1" -head "ForwardVTI" -reverse -i4 -dr8 -r4 "./simplified code.c"

simplified\ code_d.c: simplified\ code.c
	tapenade -parserfileseparator "/" -outvars "u1 u2" -vars "vp u0 u1" -head "ForwardVTI" -tangent -i4 -dr8 -r4 "./simplified code.c"

clean:
	rm *_*.c *.msg
