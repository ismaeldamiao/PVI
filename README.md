# Problema Valoris Inicialis

*Problema Valoris Inicialis*, ou simplesmente PVI,
é um cabeçalho para C que
oferece diversas rotinas implementadas na forma de macros para
resolver numericamente o problema de valor inicial.

Última modificação: 07 de janeiro de 2026.

```C
#include "pvi.h"
```

## Integradores

Métodos de Runge-Kutta:
- [x] Euler: `EULER`
- [x] Euler melhorado: `RK2`
- [x] Runge-Kutta clássico de 4a ordem: `RK4`

Métodos de multipasso:
- [x] Adams-Bashforth de dois passos: `AB2`
- [x] Adams-Bashforth de três passos: `AB3`
- [x] Adams-Bashforth de quatro passos: `AB4`
- [x] Adams-Bashforth de cinco passos: `AB5`
- [ ] Adams-Bashforth de oito passos: `AB8`
- [x] Adams-Bashforth de dez passos: `AB10`

Métodos previsor-corretor:
- [x] Adams-Bashforth-Moulton de um passo: `ABM1`
- [x] Adams-Bashforth-Moulton de dois passos: `ABM2`
- [x] Adams-Bashforth-Moulton de três passos: `ABM3`
- [x] Adams-Bashforth-Moulton de quatro passos: `ABM4`
- [x] Adams-Bashforth-Moulton de cinco passos: `ABM5`
- [ ] Adams-Bashforth-Moulton de oito passos: `ABM8`
- [x] Adams-Bashforth-Moulton de dez passos: `ABM10`

Métodos simpléticos:
- [x] Euler symplecticus: `EULER_SYMPLECTICUS`
- [ ] Euler implícito: `EULER_SYMPLECTICUS_IMPLICITUS`
- [x] Störmer-Verlet: `VERLET`
- [ ] Störmer-Verlet implícito: `VERLET_IMPLICITUS`
- [x] Ruth de terceira ordem: `RUTH3`
- [x] Ruth de quarta ordem: `RUTH4`

## Instruções de uso

Statistica é uma implementação do cabeçalho especificado
em [05-pvi.md](../../spec/textual/05-pvi.md),
a especificação deve ser consultada para maiores detalhes.

## Teoria

O espaço de estados é um subconjunto aberto $\mathcal{V}\subseteq\mathbb{F}^d$,
onde $\mathbb{F}\in\{\mathbb{R}, \mathbb{C}\}$.
O inteiro $d$ é chamado de dimensão do espaço de estados.

O estado do sistema é dinâmico, isto é, ele evolui.
Assim se o sistema está inicialmente em um estado
$x_0\in\mathcal{V}$ então posteriormente
será encontrado em um estado $\Phi(t, x_0)\in\mathcal{V}$.
O parâmetro real $t$ é chamado de tempo e a função de evolução
satisfaz às relações $\Phi(0, x_0) = x_0$ e
$\Phi(t + s, x_0) = \Phi(t, \Phi(s, x_0))$.
Um campo vetorial $f:\mathbb{R}\times\mathcal{V}\rightarrow\mathbb{F}^d$
é uma lei de evolução se a seguinte equação diferencial ordinária é válida.

$$
\frac{d}{dt} \Phi(t, x_0) = f(t, \Phi(t, x_0)).
\tag{1}
$$

Um método de integração numérica de
(1) é uma função fornece uma solução aproximada $\Phi^{\text{METODO}}(h, x_0)$
para o PVI que é mais precisa conforme menor for $h$,i isto é,

$$
\lim_{h\to 0} ||\Phi^{\text{METODO}}(h, x_0) - \Phi(h, x_0)|| = 0.
$$

O espaço de estados é dito simplético se $d$ for par, denote $d = 2f$,
se ${\mathbb{F} = \mathbb{R}}$ e se alguma forma bilinear
antisimétrica e não degenerada $\omega$ for de particular relevância.
Um integrador é simplético se também for um simplectomorfismo.

## Como usar a biblioteca PVI

* Copie o arquivo `pvi.h` para o mesmo lugar que o seu código.
* Inclua o cabeçalho.
  ```c
  #include "pvi.h"
  ```
* Implemente sua lei de evolução, uma função do tipo, como abaixo.
  ```c
  #define f(i, t, x) /* .... */
  /* ou */
  static double f(size_t i, double t, double *x){ /* .... */ }
  static double _Complex f(size_t i, double t, double _Complex *x){ /* .... */ }
  ```
  O usuário é livre para usar o nome que quiser no lugar de `f`.
* Já na rotina, defina o tempo limite de integração
  e o tamanho do passo $h$, como abaixo.
  ```c
  pvi_finalis = /* valor double */;
  pvi_h = /* valor double */;
  ```
* Defina também a dimensão $d$ do espaço de estados, como abaixo.
  ```c
  pvi_dimensio = /* valor size_t */;
  ```
* Declare ponteiros e aloque memória para representar o estado,
  como abaixo.
  ```c
  double *x /* ou outro nome */;
  /* ... */
  x = malloc(pvi_dimensio*sizeof(double));
  ```
* Defina o instante inicial e o estado inicial, como abaixo.
  ```c
  double t;
  /* ... */
  t = /* Instante inicial, em geral 0.0 */;
  x[0] = /* Valor inicial da componente 0 */;
  /* ... */
  x[pvi_dimensio-1] = /* Valor inicial da componente d-1 */;
  ```
* Chame o integrador, como abaixo.
  ```c
  PVI_INTEGRATOR_EULER(t, x, f);
  ```
  O sufixo `EULER` deve ser substituído pelo do método desejado,
  verifique as opções disponíveis na sessão "Integradores".

## Exemplos

Se seu compilador é o `clang` use o seguinte comando para
compilar, executar e plotar um exemplo:

```sh
clang -std=c23 -flto -O3 main.c -o main -lm && time ./main && gnuplot plot.gp
```

Para remover os arquivos gerados use o seguinte comando:

```sh
rm main dados.dat figura.png
```

## Contato e doações

Contribua para a manutenção dessa biblioteca
relatando falhas, fazendo sugestões ou fazendo uma doação.

Autor: [I.F.F. dos Santos](https://github.com/ismaeldamiao)

- Endereço eletrônico: [ismaellxd@gmail.com](mailto:ismaellxd@gmail.com)
- Instagram: [@ismael_damiao_al](https://www.instagram.com/ismael_damiao_al/)

Doações:

- PayPal: <https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=D66EM3DGU35EE>.
- PIX: Use a chave PIX `ismaellxd@gmail.com` ou o [código QR](../../QR_PIX.svg).