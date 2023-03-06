/*
**       dll.h:   Definições para listas circulares duplamente encadeadas.
*/

#ifndef _dll_h
#define _dll_h 

typedef struct _dllrec {
  struct _dllrec *next;
  struct _dllrec *prev;
} *Dll, DllRec;

/* protótipo das funções */

DllRec *DllAddEnd (Dll *head, unsigned int size);
DllRec *DllAddAft (Dll *head, Dll elem, unsigned int size);
void	DllDelOne (Dll *head, Dll elem);
void	DllDelAll (Dll *head);

#endif

