/*
**	Dll - Pacote de software para gerenciamento de listas 
**            circulares duplamente encadeadas. 
**
**	comentários:
**	---------------------------------------------------------------
**
**	Funcionalidade:
**      Este é um pacote para gerenciamento genérico de listas circulares
**      duplamente encadeadas. É generico no sentido de que realiza as 
**      operações básicas em listas duplamente encadeadas.
**      Para que isto seja possível, é necessário que os dois primeiros
**      campos de qualquer elemento da lista cliente sejam ponteiros para
**      os elementos anterior (previus) e posterior (next) na lista.
**      A alocação de memória para um elemento da lista é feito neste 
**      pacote. Para tal, os operadores de inserção necessitam que o 
**      tamanho do elemento da lista cliente seja passado como argumento 
**      (incluindo o tamanho dos campos next e previus).
**      Abaixo é mostrada a estrutura da lista dupla genérica:
**
**		typedef struct _dllrec {
**			struct _dllrec	*next;
**			struct _dllrec	*prev;
**		   } *Dll, DllRec;
**
**      Cabeça da lista:
**      Embora a lista circular não possua cabeça, neste pacote a cabeça
**      significa, por convenção, o primeiro elemento na lista. A cabeça
**      (head) funciona como uma referência para a lista, e é usada
**      para que se tenha acesso a lista.
**      Nos operadores deste pacote, o argumento head sempre é passado
**      por referência, porque sempre há a possibilidade de que a cabeça 
**      da lista possa ser alterada em cada operação.
**
**
**	---------------------------------------------------------------
**
**	Funções:
**	---------------------------------------------------------------
**
** 	DllRec	*DllAddEnd (Dll *head, unsigned int size)
**
**		    head	- cabeça da lista		(in/out)
**		    size	- tamanho do elemento da lista	(in)
**
**              Esta função insere um elemento no final de uma lista,
**              i.e, antes da cabeça (head). A função retorna um ponteiro
**              para o novo elemento.
**              O argumento size é usado para alocação dinâmica de 
**              memória para o elemento da lista a ser criado.
**              Se *head for null, assume-se que a lista está vazia e que
**              o novo elemento terá ambos os ponteiros next e previus
**              apontando para si próprio.
**              Se não for possível alocar memória para o elemento da 
**              lista, a função deve retornar um ponteiro nulo (null).
**
**	---------------------------------------------------------------
**
** 	DllRec	*DllAddAft (Dll *head, Dll elem, unsigned int size)
**
**		    head	- cabeça da lista		(in/out)
**		    elem	- elemento de referência	(in)
**		    size	- tamanho do elemento da lista	(in)
**
**              Esta função insere um elemento depois de um dado elemento
**              da lista (elemento de referência). A função retorna um
**              ponteiro para o novo elemento.
**              O argumento size é usado para alocação dinâmica de 
**              memória para o elemento da lista a ser criado.
**              Se *head for null, assume-se que a lista está vazia e que
**              o novo elemento terá ambos os ponteiros next e previus
**              apontando para si próprio. Caso contrário, assume-se que
**              o elemento de referência realmente pertence a lista.
**              Se não for possível alocar memória para o elemento da 
**              lista, a função deve retornar um ponteiro nulo (null).
**
**	---------------------------------------------------------------
**
**	void	DllDelOne (Dll *head, Dll elem)
**
**		    head	- cabeça da lista		(in/out)
**		    elem	- elemento a ser removido	(in)
**
**              Esta função remove um elemento da lista.
**              Assume-se que o elemento fornecido realmente pertence
**              a lista.
**              Aqui, remover um elemento implica em liberar a memória
**              utilizada pelo elemento.
**              Se o elemento a ser removido é a cabeça da lista, a nova
**              cabeça da lista (depois da remoção) será o seu elemento
**              sucessor na lista, que retornará' no argumento "head".
**              Se o elemento a ser removiso é o último elemento 
**              remanescente na lista, a função retorna um ponteiro 
**              nulo (null) no argumento head.
**              Se a lista está vazia, (head é igual a null), então nenhuma
**              ação será tomada.
**
**	---------------------------------------------------------------
**
**	void	DllDelAll (Dll *head)
**
**		    head	- cabeça da lista		(in/out)
**
**              Esta função remove todos os elementos de uma lista.
**              O valor de retorno da cabeça da lista é null.
**
**	---------------------------------------------------------------
**	Definições e variáveis globais:
*/
#include <stdio.h>
#include <stdlib.h>	/* calloc, free */
#include "dll.h"

/*
**	---------------------------------------------------------------
**	Definicões e variáveis locais: (nenhum)
*/


/*
**	---------------------------------------------------------------
**	Funcões privadas: (nenhuma)
*/


/*
**	---------------------------------------------------------------
**	Implementação das funções começa aqui:
*/

/*=========================  DllAddEnd  =========================*/
DllRec	*DllAddEnd (Dll *head, unsigned int size){
    DllRec* d = (DllRec *)calloc (1, size); 
    if (d != NULL) {
      if ((*head) != NULL) {
        Dll endAnterior = (*head)->prev;
        (*head)->prev = d;
        d->prev = endAnterior;
        d->next = (*head);
        endAnterior->next = d;
      } else {
        *head = d;
        (*head)->prev = (*head);
        (*head)->next = (*head);
      }
    }
    return d;
}

/*=========================  DllAddAft  =========================*/
DllRec	*DllAddAft (Dll *head, Dll elem, unsigned int size){
  DllRec *d = (DllRec *)calloc (1, size);
  if (d != NULL) {
      if ((*head) != NULL) {
        Dll nextAnt = elem->next;
        elem->next = d;
        d->prev = elem;
        nextAnt->prev = d;
        d->next = nextAnt;
      } else {
        *head = d;
        (*head)->prev = (*head);
        (*head)->next = (*head);
      }
    }
    return d;
}

/*=========================  DllDelOne  =========================*/
void	DllDelOne (Dll *head, Dll elem){
  if ((*head) != NULL){
    Dll prv = elem->prev;
    Dll nxt = elem->next;

    if (*head == elem){
      if (elem->next == elem) {
        (*head) = NULL;
      } else {
        (*head) = nxt;
      }
    }

    prv->next = nxt;
    nxt->prev = prv;

    free(elem);
  }
}

/*=========================  DllDelAll  =========================*/
void	DllDelAll (Dll *head){
  while (*head) {
    DllDelOne(head, *head);
  }
}