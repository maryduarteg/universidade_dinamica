#include <stdio.h>
#include "TAD.h"

int main()
{
	FILE *ptr = fopen("alunos.dat","rb");
	FILE *ptrDisc = fopen("disciplinas.dat","rb");
	TpAluno aluno;
	TpDisciplina disc;
	fread(&aluno,sizeof(TpAluno),1,ptr);
	fread(&disc,sizeof(TpDisciplina),1,ptrDisc);
	if(ptr == NULL || ptrDisc == NULL)
	{
		printf("Erro de abertura.");
	}
	else
	{
		while(!feof(ptr))
		{
			printf("%s %d/%d/%d %s %s %s %s\n",aluno.nome,aluno.dia,aluno.mes,aluno.ano,aluno.estado,aluno.cidade,aluno.endereco,aluno.curso);
			printf("Qnt materias: %d\n",aluno.descr.qnt);
			fread(&aluno,sizeof(TpAluno),1,ptr);
		}
		
		printf("\n\n\n");
		
		while(!feof(ptrDisc))
		{
			printf("Disciplina: %s\n",disc.descricao);
			printf("Nota1: %f\n",disc.nota1);
			printf("Nota2: %f\n",disc.nota2);
			printf("Frequencia: %f\n",disc.frequencia);
			fread(&disc,sizeof(TpDisciplina),1,ptrDisc);
		}
	}
}
