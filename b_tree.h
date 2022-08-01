typedef struct arv_b_no *Arv_b_no;

typedef struct index Index;

Arv_b_no arv_b_cria(void);

void arv_b_free(Arv_b_no b);
int arv_b_pos_seek(Arv_b_no b, int chave, int *achou);

void arv_insere(Arv_b_no b, int chave, int pos_seek);

void btPrintKeys(Arv_b_no t);