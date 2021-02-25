# Trabalho 2

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

3.1 Numero de Acessos
3.2 Numero de Acertos
3.3 Numero de Faltas
3.4 Numero de Leituras
3.5 Numero de Escritas
3.6 Numero de Acertos na Leitura
3.7 Numero de Acertos na Escrita
3.8 Numero de Faltas na Leitura
3.9 Numero de Faltas na Escrita


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
