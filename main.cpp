#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio2.h>
#include <ctype.h>
#include "TAD.h"

//Apenas grava os dados quando fecha o programa voltando ao menu inicial

void Moldura(int CI, int LI, int CF, int LF, int cor)
{
	int i;
	textcolor(cor);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	
	for(i=CI+1;i<CF;i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		gotoxy(i,LF);
		printf("%c",205);
	}
	
	for(i=LI+1;i<LF;i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		gotoxy(CF,i);
		printf("%c",186);
	}
	
	textcolor(7);
};

void MoldPrincipal(void)
{
	clrscr();
	Moldura(1,1,90,30,5); // MOLDURA DE FORA
    Moldura(3,2,85,4,10); // MOLDURA TÍTULO
    
	
	gotoxy(19,3);
	printf("###  S I S T E M A    U N I V E R S I D A D E  ###");
	Moldura(3,6,35,22,5); // MOLDURA MENU
	Moldura(36,6,88,22,5); // MOLDURA SAÍDA
	Moldura(3,24,88,28,10); // MOLDURA MENSAGEM
	
	gotoxy(5,26);
	printf("Mensagem: ");
};

char Menu(void)
{
	char op;
	LimparMsg();
	LimparSaida();
	gotoxy(8,8);
	textcolor(10);
	printf("###  M E N U  ###");
	gotoxy(8,10);
	textcolor(7);
	printf("[A] Lista alunos");
	gotoxy(8,11);
	printf("[B] Lista disciplinas");
    gotoxy(8,12);
    printf("[C] Outros");
    gotoxy(8,13);
	printf("[ESC] Sair");
	gotoxy(8,18);
	printf("Opcao desejada: ");
	return toupper(getch());
}



void Relatorio(listAluno *inicio)
{
	if(inicio == NULL)
	{
		LimparMsg();
		gotoxy(15,26);
		printf("Lista vazia. Pressione qualquer tecla para sair.");
		getch();
		LimparMsg();
	}
	else
	{
		while(inicio->prox != NULL)
			inicio = inicio->prox;
		
		RelatorioAlunos(inicio);
		LimparSaida();
		LimparMsg();
	}	
}


void Imprimir(listAluno *inicio)
{
	printf("\n\n\n\n\n");
	if(inicio == NULL )
	{
		printf("Vazio.");
	}
	else
	{
		while(inicio != NULL)
		{
			printf("Aluno: %s\n",inicio->aluno.nome);
			printf("Qnt: %d",inicio->aluno.descr.qnt);
			if(inicio->aluno.inicio == NULL)
				printf("Aluno sem disciplinas cadastradas.");
			else
			{
				while(inicio->aluno.inicio != NULL)
				{
					printf("Disciplina: %s\n",inicio->aluno.inicio->descricao);
					printf("Frequencia: %f\n",inicio->aluno.inicio->frequencia);
					printf("Nota1: %f\n",inicio->aluno.inicio->nota1);
					printf("Nota2: %f\n\n",inicio->aluno.inicio->nota2);
					
					inicio->aluno.inicio = inicio->aluno.inicio->prox;
				}
			}
			printf("\n\n");
			inicio = inicio->prox;
		}	
	}
	getch();
}

listAluno *MenuAlunos(listAluno *inicio)
{
	//ler aqui
	LimparMenu();
	char opCadastro;
	LimparSaida();

	do
	{
		LimparSaida();
		gotoxy(8,8);
		textcolor(10);
		printf("### ALUNOS ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Cadastrar aluno"); 
		gotoxy(8,11);
		printf("[B] Excluir aluno"); 
	    gotoxy(8,12);
		printf("[C] Consultar aluno"); 
		gotoxy(8,13);
		printf("[D] Alterar aluno"); 
		gotoxy(8,14);
		printf("[E] Relatorio alunos"); 
		gotoxy(8,15);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,18);
		printf("Opcao desejada: ");
		fflush(stdin);
		opCadastro = toupper(getch());
		switch(opCadastro)
			{
				case 'A': inicio = CadastroAlunos(inicio);
						  break;
				case 'B': inicio = ExcluirAlunos(inicio);
						  break;
				case 'C': PesquisarAlunos(inicio);
						  break;
				case 'D': inicio = AlterarAlunos(inicio); 
						  break;
				case 'E': Relatorio(inicio);
						  break;
			}
	}while(opCadastro!=27);
	LimparMenu();
	return inicio;
}

listAluno *MenuDisciplinas(listAluno *inicio)
{
	LimparMenu();
	char opCadastro;
	LimparSaida();	
	
	
	do
	{
		LimparMsg();
		gotoxy(8,8);
		textcolor(10);
		printf("### DISCIPLINAS ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Cadastro de disciplinas"); 
		gotoxy(8,11);
		printf("[B] Alterar disciplinas"); 
	    gotoxy(8,12);
		printf("[C] Exclusao de notas"); 
		gotoxy(8,13);
		printf("[D] Relatorio disciplinas"); 
		gotoxy(8,14);
		printf("[E] Exclusao disciplinas"); 
		gotoxy(8,15);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,18);
		printf("Opcao desejada: ");
		fflush(stdin);
		opCadastro = toupper(getch());
		switch(opCadastro)
			{
				case 'A': inicio = CadastroNotas(inicio);
						  break;
				case 'B': inicio = AlterarNotas(inicio);
						  break;
				case 'C': inicio = ExcluirNotas(inicio);
					  	  break;
				case 'D': RelatorioDisciplina(inicio);
						  break;		
				case 'E': inicio = ExcluirDisciplina(inicio);
					  	  break;
			}
	}while(opCadastro!=27);
	LimparMenu();
	return inicio;
}
void MenuOutros(listAluno *inicio)
{
	LimparMenu();
	char opCadastro;
	LimparSaida();	
	
	
	do
	{
		LimparMsg();
		gotoxy(8,8);
		textcolor(10);
		printf("### DISCIPLINAS ###");
		gotoxy(8,10);
		textcolor(7);
		printf("[A] Relatorio de reprovas"); 
		gotoxy(8,11);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,18);
		printf("Opcao desejada: ");
		fflush(stdin);
		opCadastro = toupper(getch());
		switch(opCadastro)
			{
				case 'A': GerarRelReprovas(inicio);
						  break;
			}
	}while(opCadastro!=27);
}

int main()
{
	char opcao;
	
	LimparSaida();
	listAluno *inicio = NULL, *aux;
	inicio = InicializarEstrutura(inicio);

	textbackground(0); // (preto) 0..7 (cinza)
	
	do
	{
		MoldPrincipal();
		opcao = Menu();
		switch(opcao)
		{
			case 'A': inicio = MenuAlunos(inicio);
					  break;
			case 'B': inicio = MenuDisciplinas(inicio);
					  break;
			case 'C': MenuOutros(inicio);
					  break;
		}

	}while(opcao!=27);
		
	GravarAlunos(inicio,(char *)"alunos.dat",(char *)"disciplinas.dat");
	return 0;
}
