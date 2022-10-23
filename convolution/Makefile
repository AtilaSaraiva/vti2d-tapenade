conv: convolution.c
	gcc $< -o $@

inner: inner_prod.c
	gcc $< -o $@

convolution_b.c: convolution.c
	tapenade -parserfileseparator "/" -outvars "c" -vars "a b" -head "conv" -reverse -i4 -dr8 -r4 "./convolution.c"

adjoint: convolution_b.c
