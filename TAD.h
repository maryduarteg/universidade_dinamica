#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio2.h>
#include <ctype.h>
#define MAX 40

//STRUCTS
struct TpDisciplina
{
	char descricao[MAX];
	float nota1, nota2, frequencia;
	TpDisciplina *prox;
};

struct TpDescritor
{
	TpDisciplina *inicio, *fim;
	int qnt;
};

struct TpAluno
{
	char nome[MAX], curso[MAX], endereco[MAX], cidade[MAX], estado[3];
	int dia, mes, ano;
	TpDisciplina *inicio;
	TpDescritor descr;
};

struct listAluno
{
	TpAluno aluno;
	listAluno *ant, *prox;
};



////////////////////////////////////////////////////////////////////////////////////

//FUNÇÕES PARA MANIPULAR A INTERFACE


void LimparSaida(void){
	int x1 = 37, x2 = 88, y1 = 7, y2 = 22, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}


void LimparMsg(void){
	int x1 = 14, x2 = 88, y1 = 25, y2 = 28, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}

void LimparMenu(void){
	int x1 = 4, x2 = 35, y1 = 7, y2 = 22, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}

////////////////////////////////////////////////////////////////////////////////////

//FUNÇÕES PARA FAZER O ALGORITMO


////////////////////////////////// PARTE ALUNO




TpDisciplina* EncadearDisciplina(int qnt, FILE *ptr)
{
    TpDescritor desc;
    desc.inicio = desc.fim = NULL; 
    TpDisciplina *aux = NULL; 

    for (int i = 0; i < qnt; i++)
    {
        TpDisciplina *novaDisciplina = new TpDisciplina; 
        fread(novaDisciplina, sizeof(TpDisciplina), 1, ptr); 
        novaDisciplina->prox = NULL;

        if (desc.inicio == NULL)
        {
            desc.inicio = novaDisciplina; // Primeira disciplina
            desc.fim = novaDisciplina;    // Atualiza o fim
        }
        else
        {
            desc.fim->prox = novaDisciplina; // Encadeia a nova disciplina no final
            desc.fim = novaDisciplina;       // Atualiza o fim
        }
    }

    return desc.inicio; // Retorna o início da lista
}


listAluno *EncadearAluno(listAluno *inicio, TpAluno aluno) {
    listAluno *nodo = new listAluno;
    listAluno *aux = inicio;
    nodo->aluno = aluno;
    nodo->prox = NULL;
    nodo->ant = NULL;

    if (inicio == NULL) // Caso a lista esteja vazia
	{
        return nodo;
    } 
	else if (strcmp(nodo->aluno.nome, inicio->aluno.nome) < 0)  // Inserir no início
	{
        nodo->prox = inicio;
        inicio->ant = nodo;
        inicio = nodo;
    } 
	else // Percorrer a lista para achar a posição correta
	{
        while (aux->prox != NULL && strcmp(nodo->aluno.nome, aux->aluno.nome) > 0) 
            aux = aux->prox;
        
        if (aux->prox == NULL && strcmp(nodo->aluno.nome, aux->aluno.nome) > 0) // Inserir no final da lista
		{
            aux->prox = nodo;
            nodo->ant = aux;
            nodo->prox = NULL;
            
        } else 
		{
            // Inserir no meio da lista
            nodo->prox = aux;
            nodo->ant = aux->ant;

            if (aux->ant != NULL) {
                aux->ant->prox = nodo;
            }
            aux->ant = nodo;
        }
    }

    return inicio;
}

TpDisciplina *CadastrarDisciplinas(TpAluno *aluno) 
{
    LimparSaida();
    TpDisciplina *disciplina = new TpDisciplina;
    TpDisciplina *aux;
    disciplina->prox = NULL;
    
    gotoxy(43, 7);
    printf("### CADASTRO DE DISCIPLINA ###\n");
    gotoxy(40, 9);
    printf("ALUNO: %s", aluno->nome);
    fflush(stdin);
    gotoxy(40, 10);
    printf("Descricao:");
    fflush(stdin);
    gets(disciplina->descricao);
            
    gotoxy(40, 11);
    printf("Frequencia: ");
    scanf("%f", &disciplina->frequencia);
    while(disciplina->frequencia < 0 || disciplina->frequencia>100)
    {
    	gotoxy(40, 11);
    	printf("                     ");
    	gotoxy(40, 11);
	    printf("Frequencia: ");
	    scanf("%f", &disciplina->frequencia);
	}
    
    gotoxy(40, 12);
    printf("Nota 1: ");
    scanf("%f", &disciplina->nota1);
    while(disciplina->nota1 < 0 || disciplina->nota1 > 10)
    {
    	gotoxy(40, 12);
    	printf("                     ");
    	gotoxy(40, 12);
	    printf("Nota 1: ");
	    scanf("%f", &disciplina->nota1);
	}
    gotoxy(40, 13);
    printf("Nota 2: ");
    scanf("%f", &disciplina->nota2);
    while(disciplina->nota2 < 0 || disciplina->nota2 > 10)
    {
    	gotoxy(40, 13);
    	printf("                     ");
    	gotoxy(40, 13);
	    printf("Nota 2: ");
	    scanf("%f", &disciplina->nota2);
	}
    
    if(aluno->descr.qnt == 0)  // Encadeia no começo
        aluno->inicio = disciplina;
    else  // Encadeia no final
    {
        aux = aluno->inicio;
        while(aux->prox != NULL)
            aux = aux->prox;
        
        aux->prox = disciplina;
    }

    LimparSaida(); // Limpa a tela
    gotoxy(15, 26);
    printf("Disciplina cadastrada");
    Sleep(1000);
    LimparMsg();
    
    return aluno->inicio; // Retorna o ponteiro atualizado para as disciplinas
}

listAluno *CadastroAlunos(listAluno *inicio) {
    TpAluno Aluno; 
    char op;

    LimparSaida();
    
    do 
	{    
        gotoxy(43, 7);
        printf("### CADASTRO DE ALUNOS ###\n");
        gotoxy(40, 9);
        printf("Nome do aluno: ");
        fflush(stdin);
        gets(Aluno.nome); 
        
        gotoxy(40, 10);
        printf("Data de nascimento (dd mm yyyy): ");
        scanf("%d %d %d", &Aluno.dia, &Aluno.mes, &Aluno.ano);
                
        gotoxy(40, 11);
        printf("Estado do aluno: ");
        scanf("%s", &Aluno.estado);

        gotoxy(40, 12);
        printf("Cidade do aluno: ");
        fflush(stdin);
        gets(Aluno.cidade); 
                
        gotoxy(40, 13);
        printf("Endereco do aluno: ");
        fflush(stdin);
        gets(Aluno.endereco); 
                
        gotoxy(40, 14);
        printf("Curso do aluno: ");
        fflush(stdin);
        gets(Aluno.curso); 
        
        Aluno.descr.qnt = 0;
        Aluno.descr.inicio = NULL;
        Aluno.descr.fim = NULL;
        Aluno.inicio = NULL;
               
        LimparSaida(); // Limpa a tela
        gotoxy(15, 26);
        printf("Aluno cadastrado");
        Sleep(1000);
        LimparMsg();
        gotoxy(15, 26);
        printf("Adicionar disciplina para o aluno? S/N");
        op = toupper(getch());
        LimparMsg();
        
        while (op == 'S') {
            Aluno.inicio = CadastrarDisciplinas(&Aluno);  // Cadastra disciplinas
            gotoxy(15, 26);
            printf("Disciplina cadastrada");
            Sleep(1500);
            LimparMsg();
            Aluno.descr.qnt++;
            printf("Adicionar disciplina para o aluno? S/N");
            op = toupper(getch());
            LimparMsg();
        }
        inicio = EncadearAluno(inicio, Aluno);
        gotoxy(15, 26);
        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
        op = toupper(getch());
        LimparMsg();
    } while (op != 27);

    return inicio;  // Retorna o ponteiro de inicio atualizado
}


void GravarAlunos(listAluno *inicio, char arqAlunos[MAX], char arqDisc[40]) {
    FILE *ptr = fopen(arqAlunos, "wb");         // "wb" para sobrescrever o arquivo de alunos
    FILE *ptrDisc = fopen(arqDisc, "wb");      // "wb" para sobrescrever o arquivo de disciplinas
    

    if (ptr == NULL || ptrDisc == NULL) {
        LimparMsg();
        gotoxy(15, 26);
        printf("Erro de abertura!");
        Sleep(1500);
        getch();
        return;
    }

    TpAluno atual;

    while (inicio != NULL)
	{
		atual = inicio->aluno;
	    fwrite(&atual, sizeof(TpAluno), 1, ptr);  // Grava os dados do aluno no arquivo de alunos
	    TpDisciplina *inicioDisc = atual.inicio;
	    while (inicioDisc != NULL) {
	        TpDisciplina atualDisc = *inicioDisc;
	        atualDisc.prox = NULL;
	        fwrite(&atualDisc, sizeof(TpDisciplina), 1, ptrDisc);
	        inicioDisc = inicioDisc->prox;  // Avança para a próxima disciplina
	    }
  		inicio = inicio->prox;  // Avança para o próximo aluno
	}
    fclose(ptr);     
    fclose(ptrDisc); 

    LimparMsg();
    gotoxy(15, 26);
    printf("Gravacao atualizada.");
    Sleep(1000);
    LimparMsg();
}

void RelatorioAlunos(listAluno *inicio)
{
	int linha = 11;
    int coluna = 40;
    TpAluno aluno;
    
    LimparSaida();
    
	if(inicio != NULL)
	{
		RelatorioAlunos(inicio->ant); 
			
	    LimparSaida();
	    LimparMsg();
			
		aluno = inicio->aluno;
	 
	    gotoxy(coluna,linha++);
		printf("Nome: %s",aluno.nome);
		gotoxy(coluna,linha++);
		printf("Data de nascimento: %d/%d/%d",aluno.dia,aluno.mes,aluno.ano);
		gotoxy(coluna,linha++);
		printf("Estado: %s",aluno.estado);
		gotoxy(coluna,linha++);
		printf("Cidade: %s",aluno.cidade);
		gotoxy(coluna,linha++);
		printf("Endereco: %s",aluno.endereco);
		gotoxy(coluna,linha++);
		printf("Curso: %s",aluno.curso);
		gotoxy(coluna,linha++); 
		gotoxy(15, 26);
	    printf("Pressione qualquer tecla para continuar...");
	    Sleep(1500);	
		getch();
	}
}


void PesquisarAlunos(listAluno *inicio)
{
	listAluno *aux;
	char nome[MAX], op;
	int linha = 10, linhamax = 19;
    int coluna = 40;
    TpDisciplina *disciplina;
    
	LimparSaida();
	
	do 
	{ 	
		LimparSaida();
	    gotoxy(43, 7);
	    printf("### CONSULTA DE ALUNOS ###\n");
	    gotoxy(40, 9);
	    printf("Informe o aluno: ");
		fflush(stdin);
		gets(nome);
		linha = 10;
		
		aux = inicio;
		while(aux != NULL && strcmp(nome,aux->aluno.nome)!= 0)
		{
			aux = aux->prox;
		}
		if(aux == NULL)
		{
			LimparSaida();
			gotoxy(15, 26);
		    printf("Aluno nao cadastrado");
		    Sleep(1000);
		    LimparMsg();
		}
		else
		{
			LimparSaida();
			gotoxy(40, 7);
		    printf("\t\tDADOS DO ALUNO");
			gotoxy(40, linha++);
		    printf("Nome: %s",aux->aluno.nome);
	
		    gotoxy(40, linha++);
		    printf("Data de nascimento: %d/%d/%d",aux->aluno.dia,aux->aluno.mes,aux->aluno.ano);

		    gotoxy(40, linha++);
		   	printf("Estado: %s",aux->aluno.estado);
		        
		    gotoxy(40, linha++);
		    printf("Cidade: %s",aux->aluno.cidade);
		    
		    gotoxy(40, linha++);
		    printf("Endereco: %s",aux->aluno.endereco);
		    
		    gotoxy(40, linha++);
		    printf("Curso: %s",aux->aluno.curso); 
			
			LimparMsg();
			gotoxy(15, 26);
		    printf("[ENTER] - CONTINUAR");
		    Sleep(1500);
		    op = toupper(getch());  
		    LimparMsg();
		    linha=9;
		    LimparSaida();
			gotoxy(40, 7);
		    printf("\t\tDISCIPLINA DO ALUNO");
		    if(aux->aluno.inicio == NULL)
		    {
		    	gotoxy(15, 26);
			    printf("Aluno sem disciplinas cadastradas. [ESC]-SAIR  [ENTER]-CONTINUAR");
			    Sleep(1500);
			}
		    else
		    {
		    	disciplina = aux->aluno.inicio;

		    	while(disciplina != NULL)
		    	{
		    		gotoxy(coluna,linha++);
		    		printf("Descricao: %s",disciplina->descricao);
		    		gotoxy(coluna,linha++);
		    		printf("Frequencia: %.2f %",disciplina->frequencia);
		    		gotoxy(coluna,linha++);
		    		printf("Nota 1: %.2f",disciplina->nota1);
		    		gotoxy(coluna,linha++);
		    		printf("Nota 2: %.2f",disciplina->nota2);
		    		linha++;
		    		gotoxy(coluna,linha++);
		    		if(linha == linhamax)
		    		{
		    			linha=9;
		    			LimparSaida();
						gotoxy(40, 8);
					    printf("\t\tDISCIPLINA DO ALUNO");
					    gotoxy(15, 26);
					    printf("Pressione [ENTER] para continuar");
					    Sleep(1500);
					    getch();
					}
		    		disciplina = disciplina->prox;	
				}
			}
		}
			    
	    gotoxy(15, 26);
	    printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
	    Sleep(1500);
	    LimparMsg();
	    op = toupper(getch());
	} while (op != 27);
}

listAluno *InicializarEstrutura(listAluno *inicio)
{
	FILE *ptr = fopen("alunos.dat","rb");
	FILE *ptrDisc = fopen("disciplinas.dat","rb+");

	listAluno *aux;
	TpAluno aluno;
	fseek(ptr,0,2);
	if(ptr != NULL && ftell(ptr)/sizeof(TpAluno)!=0) 
	{
		fseek(ptr,0,0);
		fread(&aluno,sizeof(TpAluno),1,ptr);
		while(!feof(ptr))
		{
			
			aluno.inicio = NULL;
           if(aluno.descr.qnt > 0)
			{
				aluno.inicio = EncadearDisciplina(aluno.descr.qnt, ptrDisc);
			}
			
			listAluno *pontAluno = new listAluno;
			pontAluno->aluno = aluno;
			pontAluno->prox = NULL;
			pontAluno->ant= NULL;
		
			if(inicio==NULL)
			{
				inicio = pontAluno;
				aux = pontAluno;
				pontAluno->ant = NULL;
			}
			else
			{
				aux->prox = pontAluno;
				pontAluno->ant = aux;
				aux = aux->prox;
			}
			fread(&aluno,sizeof(TpAluno),1,ptr);
		}	

	}
	fclose(ptr);
	fclose(ptrDisc);
	
	return inicio;
}


listAluno *ExcluirAlunos(listAluno *inicio)
{
	char nome[MAX], op;
	int linha = 10, coluna = 40;
    TpDisciplina *disciplina, *auxDisc;
    listAluno *aux;
    
	LimparSaida();
	
	if(inicio == NULL)
	{
		gotoxy(15,26);
		printf("Lista vazia. Pressione qualquer tecla para continuar.");
		getch();
		LimparMsg();
	}
	else
	{
		do 
		{ 	
			LimparSaida();
		    gotoxy(43, 7);
		    printf("### EXCLUSAO DE ALUNOS ###\n");
		    gotoxy(40, 9);
		    printf("Informe o aluno: ");
			fflush(stdin);
			gets(nome);
			
			aux = inicio;
			while(aux != NULL && strcmp(aux->aluno.nome,nome)!= 0)
			{
				aux = aux->prox;
			}
			if(aux == NULL)
			{
				LimparSaida();
				gotoxy(15, 26);
			    printf("Aluno nao cadastrado");
			    Sleep(1000);
			    LimparMsg();
			}
			else
			{
				LimparSaida();
				gotoxy(40, 7);
			    printf("\t\tDADOS DO ALUNO");
			    linha = 10;
				coluna = 40;
				gotoxy(40, linha++);
			    printf("Nome: %s",aux->aluno.nome);
		
			    gotoxy(40, linha++);
			    printf("Data de nascimento: %d/%d/%d",aux->aluno.dia,aux->aluno.mes,aux->aluno.ano);
	
			    gotoxy(40, linha++);
			   	printf("Estado: %s",aux->aluno.estado);
			        
			    gotoxy(40, linha++);
			    printf("Cidade: %s",aux->aluno.cidade);
			    
			    gotoxy(40, linha++);
			    printf("Endereco: %s",aux->aluno.endereco);
			    
			    gotoxy(40, linha++);
			    printf("Curso: %s",aux->aluno.curso); 
			    
				
				LimparMsg();
				gotoxy(15, 26);
			    printf("Excluir aluno %s? S/N",aux->aluno.nome);
			    Sleep(1500);
			    op = toupper(getch());  
			    LimparMsg();
			    gotoxy(15,26);
			
			    if(op == 'S')
			    {
			    	if(aux->ant == NULL)//apenas um para excluir 
			    	{
			    		aux = inicio;
			    		inicio = NULL;
			    		delete aux;
			    		FILE *ptr1 = fopen("alunos.dat","wb");
			    		FILE *ptr2 = fopen("disciplinas.dat","wb");
			    		fclose(ptr1);
			    		fclose(ptr2);	
					}
					else
					{
						if(inicio == aux) //significa que é o primeiro que será excluído
				    	{
				    		inicio = aux->prox;
				    		inicio->ant = NULL;
				    		disciplina = aux->aluno.inicio;
						}
						
		
						else if(aux->prox == NULL)//ou e o último
						{
							aux->ant->prox = NULL;
							disciplina = aux->aluno.inicio;
						}
						else//ou está no meio
						{
							aux->ant->prox = aux->prox;
							aux->prox->ant = aux->ant;
							disciplina = aux->aluno.inicio;
				    		
						}
						while (disciplina != NULL)
						{
						    auxDisc = disciplina->prox;
						    delete disciplina;
						    disciplina = auxDisc;
						}
		
						delete aux;
						
					    printf("Aluno excluido.");
					    Sleep(1000);
					    LimparMsg();							
					}
				}
			}
				    
		    gotoxy(15, 26);
		    printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		    Sleep(1500);
		    op = toupper(getch());
		    LimparMsg();
		} while (op != 27);
	}
	LimparSaida();
	return inicio;
}

listAluno *AlterarAlunos(listAluno *inicio)
{
	char nome[MAX], op;
	int linha = 10, coluna = 40;
    listAluno *aux;
    TpAluno aluno;
	LimparSaida();
	
	if(inicio == NULL)
	{
		gotoxy(15,26);
		printf("Lista vazia. Pressione qualquer tecla para continuar.");
		getch();
		LimparMsg();
	}
	else
	{
		do 
		{ 	
			LimparSaida();
		    gotoxy(43, 7);
		    printf("### ALTERACAO DE DADOS  ###\n");
		    gotoxy(40, 9);
		    printf("Informe o aluno: ");
			fflush(stdin);
			gets(nome);
			
			aux = inicio;
			while(aux != NULL && strcmp(aux->aluno.nome,nome)!= 0)
				aux = aux->prox;
			
			if(aux == NULL)
			{
				LimparSaida();
				gotoxy(15, 26);
			    printf("Aluno nao cadastrado");
			    Sleep(1500);
			    LimparMsg();
			}
			else
			{
				LimparSaida();
				gotoxy(40, 7);
			    printf("\t\tDADOS DO ALUNO");
			    linha = 10;
				coluna = 40;
				gotoxy(40, linha++);
			    printf("Nome: %s",aux->aluno.nome);
		
			    gotoxy(40, linha++);
			    printf("Data de nascimento: %d/%d/%d",aux->aluno.dia,aux->aluno.mes,aux->aluno.ano);
	
			    gotoxy(40, linha++);
			   	printf("Estado: %s",aux->aluno.estado);
			        
			    gotoxy(40, linha++);
			    printf("Cidade: %s",aux->aluno.cidade);
			    
			    gotoxy(40, linha++);
			    printf("Endereco: %s",aux->aluno.endereco);
			    
			    gotoxy(40, linha++);
			    printf("Curso: %s",aux->aluno.curso); 
			    
				
				LimparMsg();
				gotoxy(15, 26);
			    printf("Alterar: 1 - Data | 2 - Estado | 3 - Cidade | 4 - Endereco | 5 - Curso");
			    Sleep(1500);
			    op = toupper(getch());  
			    LimparMsg();
			    
				if(op != '1' && op != '2' && op != '3' && op != '4' && op != '5')
				{
					gotoxy(15,26);
					printf("Opcao invalida.");
					getch();
					LimparMsg();
				}
			    else
			    {
			    	LimparSaida();	
			    	gotoxy(43, 7);
				    printf("### ALTERACAO DE DADOS  ###\n");
				    gotoxy(40, 9);
				    printf("Aluno: %s",aux->aluno.nome);
			    	if(op == '1')//alterar data de nascimento
			    	{
					    gotoxy(40,10);
					    printf("Data de nascimento atual: %d/%d/%d",aux->aluno.dia,aux->aluno.mes,aux->aluno.ano);
					    gotoxy(40,11);
					    printf("Alterar para (dd mm aaaa): ");
					    scanf("%d %d %d",&aux->aluno.dia,&aux->aluno.mes,&aux->aluno.ano);
			    		
					}
					else if(op == '2')
					{
					    gotoxy(40,10);
					    printf("Estado: %s",aux->aluno.estado);
					    gotoxy(40,11);
					    printf("Alterar para: ");
					    fflush(stdin);
					    gets(aux->aluno.estado);
					}
					else if(op == '3')
					{
					    gotoxy(40,10);
					    printf("Cidade: %s",aux->aluno.cidade);
					    gotoxy(40,11);
					    printf("Alterar para: ");
					    fflush(stdin);
					    gets(aux->aluno.cidade);
					}
					else if(op == '4')
					{
					    gotoxy(40,10);
					    printf("Endereco: %s",aux->aluno.endereco);
					    gotoxy(40,11);
					    printf("Alterar para: ");
					    fflush(stdin);
					    gets(aux->aluno.endereco);
					}
					else
					{
					    gotoxy(40,10);
					    printf("Curso: %s",aux->aluno.curso);
					    gotoxy(40,11);
					    printf("Alterar para: ");
					    fflush(stdin);
					    gets(aux->aluno.curso);
					}
					gotoxy(15,26);
					printf("Aluno alterado.");
					Sleep(1000);
				    LimparMsg();
				    
				}
			}
				    
		    gotoxy(15, 26);
		    printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		    op = toupper(getch());
		    LimparMsg();
		} while (op != 27);
	}
	
	return inicio;
}

listAluno *CadastroNotas(listAluno *inicio)
{
	
	char nome[MAX], op;
	int linha = 10, coluna = 40;
    listAluno *aux;
    
	LimparSaida();
	
	if(inicio == NULL)
	{
		gotoxy(15,26);
		printf("Lista vazia. Pressione qualquer tecla para continuar.");
		getch();
		LimparMsg();
	}
	else
	{
		do 
		{ 	
			LimparSaida();
		    gotoxy(43, 7);
		    printf("### CADASTRO DE DISCIPLINAS  ###\n");
		    gotoxy(40, 9);
		    printf("Informe o aluno: ");
			fflush(stdin);
			gets(nome);
			
			aux = inicio;
			while(aux != NULL && strcmp(aux->aluno.nome,nome)!= 0)
			{
				aux = aux->prox;
			}
			if(aux == NULL)
			{
				LimparSaida();
				gotoxy(15, 26);
			    printf("Aluno nao cadastrado");
			    Sleep(1000);
			    LimparMsg();
			}
			else 
			{
				LimparSaida();
			    linha = 10;
				coluna = 40;
				gotoxy(40, linha++);
			    printf("Aluno: %s",aux->aluno.nome);
			    aux->aluno.descr.qnt++;
			    
			    TpDisciplina *atualDisc = new TpDisciplina;
			    atualDisc->prox = NULL;
			    TpDisciplina *auxDisc = aux->aluno.inicio;
		
			    gotoxy(40, linha++);
			    printf("Descricao: ");
			    fflush(stdin);
			    gets(atualDisc->descricao);
	
			    gotoxy(40, linha++);
			   	printf("Frequencia: ");
			   	scanf("%f",&atualDisc->frequencia);
			   	while(atualDisc->frequencia < 0 || atualDisc->frequencia > 100)
			    {
			    	
			    	gotoxy(40, linha-1);
			    	printf("                  ");
			    	gotoxy(40, linha-1);
				    printf("Frequencia: ");
				    scanf("%f", &atualDisc->frequencia);
				}
			   	
			   	gotoxy(40, linha++);
			   	printf("Nota 1: ");
			   	scanf("%f",&atualDisc->nota1);
			   	while(atualDisc->nota1 < 0 || atualDisc->nota1 > 10)
			    {
			    	gotoxy(40, linha-1);
			    	printf("                  ");
			    	gotoxy(40, linha-1);
				    printf("Nota 1: ");
				    scanf("%f", &atualDisc->nota1);
				}
			   	
			   	gotoxy(40, linha++);
			   	printf("Nota 2: ");
			   	scanf("%f",&atualDisc->nota2);
			   	while(atualDisc->nota2 < 0 || atualDisc->nota2 > 100)
			    {
			    	gotoxy(40, linha-1);
			    	printf("                  ");
			    	gotoxy(40, linha-1);
				    printf("Nota 2: ");
				    scanf("%f", &atualDisc->nota2);
				}
			    
			    if(auxDisc == NULL)//se for a primeira disciplina
			    {
			    	aux->aluno.inicio = atualDisc;
				}
				else //encadear no final
				{
					while(auxDisc->prox != NULL)
						auxDisc = auxDisc->prox;
					auxDisc->prox = atualDisc;
				}
				
				LimparMsg();
				gotoxy(15, 26);
			    printf("Disciplina cadastrada ao aluno %s.",aux->aluno.nome);
			    Sleep(1500);
			    LimparMsg();
			}
				    
		    gotoxy(15, 26);
		    printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		    Sleep(1500);
		    op = toupper(getch());
		} while (op != 27);
	}
	LimparSaida();
	return inicio;
}


listAluno *ExcluirDisciplina(listAluno *inicio)
{
	char desc[MAX], op;
	int linha = 10, coluna = 40;
    listAluno *aluno;
    TpDisciplina *disc, *aux;
    
	LimparSaida();
	
	if(inicio == NULL)
	{
		gotoxy(15,26);
		printf("Lista vazia. Pressione qualquer tecla para continuar.");
		getch();
		LimparMsg();
	}
	else
	{
		do 
		{ 	
			LimparSaida();
		    gotoxy(43, 7);
		    printf("### EXCLUSAO DE DISCIPLINAS  ###\n");
		    gotoxy(40, 9);
		    printf("Informe a disciplina: ");
			fflush(stdin);
			gets(desc);
			
			aluno = inicio;

			if(aluno == NULL)
			{
				LimparSaida();
				gotoxy(15, 26);
			    printf("Lista vazia.");
			    Sleep(1000);
			    LimparMsg();
			}
			else 
			{
				while(aluno != NULL)
				{
					if(aluno->aluno.descr.qnt != 0)
					{
						disc = aluno->aluno.inicio;
						if(strcmp(desc,disc->descricao)==0)//o primeiro
						{
							aluno->aluno.descr.qnt--;
							aluno->aluno.inicio = aluno->aluno.inicio->prox;
							delete disc;
						}
						else
						{
							while(disc != NULL && strcmp(desc,disc->descricao)!=0)
							{
								aux = disc;
								disc = disc->prox;
							}
							if(disc != NULL)
							{
								aluno->aluno.descr.qnt--;
								
								if(disc->prox == NULL) 
									aux->prox = NULL;
								
								else
									aux->prox = disc->prox;
									
								delete disc;
							}
						}
					}
					aluno =  aluno->prox;
				}
				LimparMsg();
				gotoxy(15, 26);
			    printf("Disciplina excluida.");
			    Sleep(1500);
			    LimparMsg();
			}
				    
		    gotoxy(15, 26);
		    printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		    Sleep(1500);
		    op = toupper(getch());
		    LimparMsg();
		} while (op != 27);
	}
	LimparSaida();
	return inicio;
}

listAluno *AlterarNotas(listAluno *inicio)
{
	char descricao[MAX], nome[MAX], op;
	int linha = 10, coluna = 40, linhaMax = 19;
    listAluno *aux;
    TpDisciplina *disc;
	LimparSaida();
	
	if(inicio == NULL)
	{
		gotoxy(15,26);
		printf("Lista vazia. Pressione qualquer tecla para continuar.");
		getch();
		LimparMsg();
	}
	else
	{
		do 
		{ 	
			LimparSaida();
		    gotoxy(43, 7);
		    printf("### ALTERACAO DE DISCIPLINAS  ###\n");
		    gotoxy(40, 9);
		    printf("Informe o aluno: ");
			fflush(stdin);
			gets(nome);
			
			aux = inicio;
			while(aux != NULL && strcmp(aux->aluno.nome,nome)!= 0)
				aux = aux->prox;
			
			if(aux == NULL)
			{
				LimparSaida();
				gotoxy(15, 26);
			    printf("Aluno nao cadastrado");
			    Sleep(1500);
			    LimparMsg();
			}
			else
			{
				LimparSaida();
				gotoxy(coluna, 7);
			    printf("\t\tDISCIPLINAS DO ALUNO");
				
				gotoxy(coluna, linha++);
			    printf("Nome: %s",aux->aluno.nome);
			    disc = aux->aluno.inicio;
			    gotoxy(40, linha++);
			   	while(disc != NULL)
			   	{
					gotoxy(coluna,linha++);
					printf("Disciplina: %s",disc->descricao);
					if(linha == linhaMax)
			   		{
			   			linha = 10;
			   			gotoxy(15,26);
			   			printf("Pressione qualquer tecla para continuar.");
			   			getch();
			   			LimparMsg();
			   			LimparSaida();
					}
					disc = disc->prox;
				}
				LimparMsg();
				gotoxy(15,26);
				printf("Qual disciplina alterar? ");
				fflush(stdin);
				gets(descricao);
				LimparMsg();
				
				disc = aux->aluno.inicio;//resetar novamente
				while(disc != NULL && strcmp(descricao,disc->descricao) != 0)
					disc = disc->prox;
					
				if(disc == NULL)
				{
					LimparSaida();
					gotoxy(15,26);
					printf("Disciplina nao cadastrada.");
					getch();
					LimparMsg();
				}
				else
				{
					LimparSaida();
					gotoxy(coluna,linha++);
					printf("Descricao: %s",disc->descricao);
					gotoxy(coluna,linha++);
					printf("Frequencia: %.2f",disc->frequencia);
					gotoxy(coluna,linha++);
					printf("Nota 1: %.2f",disc->nota1);
					gotoxy(coluna,linha++);
					printf("Nota 2: %.2f",disc->nota2);
					
					LimparMsg();
					gotoxy(15, 26);
				    printf("Alterar: 1 - Descricao | 2 - Frequencia | 3 - Nota 1 | 4 - Nota 2 ");
				    Sleep(1500);
				    op = toupper(getch());  
				    LimparMsg();
				    
					if(op != '1' && op != '2' && op != '3' && op != '4')
					{
						gotoxy(15,26);
						printf("Opcao invalida.");
						getch();
						LimparMsg();
					}
					
					 else
				    {
				    	LimparSaida();	
				    	gotoxy(43, 7);
					    printf("### ALTERACAO DE DISCIPLINA  ###\n");
					    gotoxy(40, 9);
					    printf("Aluno: %s",aux->aluno.nome);
				    	if(op == '1')//alterar descricao
				    	{
						    gotoxy(40,10);
						    printf("Descricao atual: %s",disc->descricao);
						    gotoxy(40,11);
						    printf("Alterar para: ");
						    fflush(stdin);
						    gets(disc->descricao);
				    		
						}
						else if(op == '2')
						{
						    gotoxy(40,10);
						    printf("Frequencia: %.2f",disc->frequencia);
						    gotoxy(40,11);
						    printf("Alterar para: ");
						    scanf("%f",&disc->frequencia);
						}
						else if(op == '3')
						{
						    gotoxy(40,10);
						    printf("Nota 1: %.2f",disc->nota1);
						    gotoxy(40,11);
						    printf("Alterar para: ");
						    scanf("%f",&disc->nota1);
						}
						else
						{
						    gotoxy(40,10);
						    printf("Nota 1: %.2f",disc->nota2);
						    gotoxy(40,11);
						    printf("Alterar para: ");
						    scanf("%f",&disc->nota2);
						}
						gotoxy(15,26);
						printf("Disciplina alterada.");
						Sleep(1000);
					    LimparMsg();
					}
				}
			}
		    gotoxy(15, 26);
		    printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		    op = toupper(getch());
		    LimparMsg();
		} while (op != 27);
	}
	return inicio;
}

listAluno *ExcluirNotas(listAluno *inicio)
{
	char descricao[MAX], nome[MAX], op;
	int linha = 10, coluna = 40, linhaMax = 19;
    listAluno *aux;
    TpDisciplina *disc;
	LimparSaida();
	
	if(inicio == NULL)
	{
		gotoxy(15,26);
		printf("Lista vazia. Pressione qualquer tecla para continuar.");
		getch();
		LimparMsg();
	}
	else
	{
		do 
		{ 	
			LimparSaida();
		    gotoxy(43, 7);
		    printf("### EXCLUIR NOTAS ###\n");
		    gotoxy(40, 9);
		    printf("Informe o aluno: ");
			fflush(stdin);
			gets(nome);
			
			aux = inicio;
			while(aux != NULL && strcmp(aux->aluno.nome,nome)!= 0)
				aux = aux->prox;
			
			if(aux == NULL)
			{
				LimparSaida();
				gotoxy(15, 26);
			    printf("Aluno nao cadastrado");
			    Sleep(1500);
			    LimparMsg();
			}
			else
			{
				LimparSaida();
				gotoxy(coluna, 7);
			    printf("\t\tDISCIPLINAS DO ALUNO");
				
				gotoxy(coluna, linha++);
			    printf("Nome: %s",aux->aluno.nome);
			    disc = aux->aluno.inicio;
			    gotoxy(40, linha++);
			   	while(disc != NULL)
			   	{
					gotoxy(coluna,linha++);
					printf("Disciplina: %s",disc->descricao);
					if(linha == linhaMax)
			   		{
			   			linha = 10;
			   			gotoxy(15,26);
			   			printf("Pressione qualquer tecla para continuar.");
			   			getch();
			   			LimparMsg();
			   			LimparSaida();
					}
					disc = disc->prox;
				}
				LimparMsg();
				gotoxy(15,26);
				printf("Qual disciplina alterar? ");
				fflush(stdin);
				gets(descricao);
				LimparMsg();
				
				disc = aux->aluno.inicio;//resetar novamente
				while(disc != NULL && strcmp(descricao,disc->descricao) != 0)
					disc = disc->prox;
					
				if(disc == NULL)
				{
					LimparSaida();
					gotoxy(15,26);
					printf("Disciplina nao cadastrada.");
					getch();
					LimparMsg();
				}
				else
				{
					LimparSaida();
					gotoxy(coluna,linha++);
					printf("Descricao: %s",disc->descricao);
					gotoxy(coluna,linha++);
					printf("Frequencia: %.2f",disc->frequencia);
					gotoxy(coluna,linha++);
					printf("Nota 1: %.2f",disc->nota1);
					gotoxy(coluna,linha++);
					printf("Nota 2: %.2f",disc->nota2);
					
					LimparMsg();
					gotoxy(15, 26);
				    printf("Alterar: 1 - Nota 1 | 2 - Nota 2 | 3 - Ambas");
				    Sleep(1500);
				    op = toupper(getch());  
				    LimparMsg();
				    
					if(op != '1' && op != '2' && op != '3')
					{
						gotoxy(15,26);
						printf("Opcao invalida.");
						getch();
						LimparMsg();
					}
					
					 else
				    {
				    	LimparSaida();	
				    	gotoxy(43, 7);
					    printf("### EXCLUIR NOTAS  ###\n");
					    gotoxy(40, 9);
					    printf("Aluno: %s",aux->aluno.nome);
				    	if(op == '1')//alterar descricao
				    	{
						    disc->nota1 = 0;
				    		
						}
						else if(op == '2')
						{
						    disc->nota2 = 0;
						}
						else
						{
						    disc->nota1 = 0;
						    disc->nota1 = 2;
						}
						gotoxy(15,26);
						printf("Nota(s) excluidas.");
						Sleep(1000);
					    LimparMsg();
					}
				}
			}
		    gotoxy(15, 26);
		    printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		    op = toupper(getch());
		    LimparMsg();
		    LimparSaida();
		} while (op != 27);
	}
	return inicio;
}

void RelatorioDisciplina(listAluno *inicio)
{
	char descricao[MAX], op;
	int linha = 10, coluna = 40, linhaMax = 19, qnt=0, achou = 0;
	float mediaNotas = 0, mediaFreq = 0;
    listAluno *aux;
    TpDisciplina *disc;
	LimparSaida();
	
	if(inicio == NULL)
	{
		gotoxy(15,26);
		printf("Lista vazia. Pressione qualquer tecla para continuar.");
		getch();
		LimparMsg();
	}
	else
	{
		do 
		{ 	
			LimparSaida();
		    gotoxy(43, 7);
		    printf("### RELATORIO DE DISCIPLINAS ###\n");
		    gotoxy(40, 9);
		    printf("Informe a disciplina: ");
			fflush(stdin);
			gets(descricao);
			
			LimparSaida();
			gotoxy(43, 7);
			printf("### RELATORIO DE DISCIPLINAS ###\n");
			gotoxy(40, 9);
			printf("Disciplina: %s",descricao);
			
			aux = inicio;
			

			while (aux != NULL && !achou) 
			{
			    disc = aux->aluno.inicio; 
			
			    while (disc != NULL) 
			    {
			        if (strcmp(disc->descricao, descricao) == 0) 
			        {
			            achou = 1; 
			            break; 
			        }
			        disc = disc->prox; 
			    }
			    if (!achou) 
			        aux = aux->prox;
			}

			if(!achou)
			{
				gotoxy(15, 26);
			    printf("Disciplina %s nao cadastrada",descricao);
			    getch();
			    LimparMsg();
			    LimparSaida();
			}
			
			else
			{
				aux = inicio;
				while(aux != NULL)
				{
					disc = aux->aluno.inicio;
					while(disc != NULL)
					{
						if(strcmp(descricao,disc->descricao) == 0)
						{
							qnt++;
							mediaNotas += (disc->nota1 + disc->nota2)/2;
							mediaFreq +=  disc->frequencia;
							gotoxy(coluna,linha++);
							printf("Aluno: %s",aux->aluno.nome);
							gotoxy(coluna,linha++);
							printf("Nota 1: %2.f",disc->nota1);
							gotoxy(coluna,linha++);
							printf("Nota 2: %2.f",disc->nota2);
							if(linha == linhaMax)
				    		{
				    			linha=9;
				    			LimparSaida();
								gotoxy(40, 7);
							    printf("### RELATORIO DE DISCIPLINAS ###\n");
							    gotoxy(15, 26);
							    printf("Pressione [ENTER] para continuar");
							    Sleep(1500);
							    getch();
							}
							gotoxy(coluna,linha++);
							printf("\n");
						}
						disc = disc->prox;
					}
					aux = aux->prox;
				}
				mediaFreq = mediaFreq/qnt;
				mediaNotas = mediaNotas/qnt;
				gotoxy(15, 26);
			    printf("Media de notas: %.2f | Frequencia media: %.2f [ENTER] - CONTINUAR",mediaNotas,mediaFreq);
			    getch();
			    LimparMsg();
			}
			
			
		    gotoxy(15, 26);
		    printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		    op = toupper(getch());
		    LimparMsg();
		    LimparSaida();
		} while (op != 27);
	}
}

void GerarRelReprovas(listAluno *inicio)
{
	TpAluno atual;
	TpDisciplina *disc;
	float n1, n2;
	int rep = 0;
	
	if(inicio == NULL)
	{
		gotoxy(15,26);
		LimparMsg();
		printf("Lista vazia.");
		getch();
		LimparMsg();
	}
	else
	{
		FILE *ptr = fopen("relatorioAluno.txt","w");
		atual = inicio->aluno;
		while(inicio != NULL)
		{
			atual = inicio->aluno;
			fprintf(ptr,"%s: ",atual.nome);
			disc = atual.inicio;
			while(disc != NULL)
			{
				if((disc->nota1+disc->nota2)/2 < 6)
				{
					rep = 1;
					fprintf(ptr,"%s, ",disc->descricao);
				}
				disc = disc->prox;
			}
			if(rep == 0)
				fprintf(ptr,"Sem reprovacoes.");
			
			fprintf(ptr,"\n");
			rep = 0;
			inicio = inicio->prox;
		}
	} 
	
	gotoxy(15, 26);
	printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
    getch();
	LimparMsg();
	LimparSaida();
}
