# Código Born e Adjunto da equação pseudo acústica de Reynam VTI 2D

Esse repositório contém um código gerado de modelagem da equação pseudo acústica de Reynam VTI 2D (`simplified code.c`), e os códigos gerados pelo software [Tapenade](https://team.inria.fr/ecuador/en/tapenade/) da modelagem Born (`simplified code_d.c`) e do estado adjunto (`simplified code_b.c`).

## Reproduzindo os resultados

Usando [nix](https://nixos.org/download.html#nix-install-linux), rode:
```
git clone <este-repositório>
cd <este-repositório>
nix-shell
make
```
e uma shell efêmera com o tapenade disponível, e com `make` os códigos serão gerados.
