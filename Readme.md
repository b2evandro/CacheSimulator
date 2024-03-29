# Trabalho 2
![Codigo sendo executado](CPT2209011038-514x551.gif)
## Criar Simulador de memória cache

* Politica de Mapeamento Direto:
   - Associativo
   
   Existentes:
    1. Direto 
    1. Associativo por conjunto
    1. Associativo 


* **Politica de escrita**
   - Write - Back

   Existentes:
    1. Write 
    1. Through 
    1. Write - Back

* **Politica de substituição**
   - FIFO 
   Existentes:
    1. LRU 
    1. LFU 
    1. FIFO
    1. ALEATÓRIO

### Possibilidade de Implementação
 Pode ser implementado em **qualquer** linguagem, e deve seguir o padrão das estruturas do código em C abaixo, respeitando todos os tamanhos dados. 

Tamanho de quadros ou conjuntos:

   - **MemCache cache[16];**

Número de células

   - **MemPrincipal principal[2048];**

Opções de Menu

1. Ler Memoria
1. Escrever memoria
1. Estatísticas

As estatísticas abaixo devem ser implementadas:

1. Numero de Acessos
1. Numero de Acertos
1. Numero de Faltas
1. Numero de Leituras
1. Numero de Escritas
1. Numero de Acertos na Leitura
1. Numero de Acertos na Escrita
1. Numero de Faltas na Leitura
1. Numero de Faltas na Escrita


Pontuação
Em caso da politica direta:

- Politica de Mapeamento: 5 pts
- Politica de escrita: 2 pts
- Estatísticas: 3 pts
- Senão:
- Politica de Mapeamento: 5 pts
- Politica de troca: 1 pts
- Politica de escrita: 2 pts
- Estatísticas: 2 pts

Observações:

O tamanho do quadro deve ser definido pelo grupo.

Os dados de endereço e rótulo devem ser exibidos em binário.

O conteúdo de cada célula é um char, que pode ser preenchido aleatoriamente na memória principal.

Caso seja necessário adição de variáveis ou modificação no tamanho dos atributos nas estruturas, deve ser feito. Mas sempre respeitando o tamanho da cache, da memória principal e das células.

Duplas serão definidas e sorteados os temas durante a conferência.
