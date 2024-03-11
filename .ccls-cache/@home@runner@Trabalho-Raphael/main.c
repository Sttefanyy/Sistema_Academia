/*
Feito por

Aluno: Laíze dos Santos.
ALuno: Stefany Matos de Mendonça.
Aluno: Pedro Cézar Silva de Souza.

Turno: Noite.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structs do Sistema

// dados basicos de um aluno e seu id para guiar
struct aluno {
  int idAluno;
  char nomeAluno[50];
  char cpfAluno[15];
  char telefoneAluno[50];
  char emailAluno[100];
  int check; 
};

// dados basicos de um professor e seu id para guiar
struct professor {
  int idProfessor;
  char nomeProfessor[50];
  char cpfProfessor[15];
  char telefoneProfessor[50];
  char emailProfessor[100];
};

// dados basicos de uma Turma e seu id para guiar com id do professor para
// separa as turmas e evitar repetição
struct turma {
  int idTurma;
  int tipoTurma;
  char diaSemanaTurma[15];
  int horarioTurma[2];
  int idProfessorTurma;
  char faixaEtariaTurma[20];
  int numeroMinimoAlunos;
  int numeroMaximoAlunos;
  int situacaoTurma; // 1 para em matrícula 2 para ativa e 3 para cancelada
};

// struct de para manipular a alocação dinâmica com os ids.
struct inscricao {
  int situacaoInscricao; // 1 para ativo e 2 para cancelado
  int idInscricao;
  int idAlunoInscricao;
  int idTurmaInscricao;
};

// struct do desafio
struct inscricaoEmAula { 
  int idInscricaoAula;
  int idAluno;
  int idTurma;
  int ranking[3];
  int ano;
};

// Funções do Sistema

// Funções de cadastro
void cadastroAluno(struct aluno alunos[]);
void cadastroProfessor(struct professor professores[]);
void cadastroTurma(struct turma turmas[], struct professor professores[]);

// Funções de exibir infos
void exibirInfosAlunos(struct aluno alunos[]);
void exibirInfosProfessores(struct professor professores[]);
void exibirInfosTurmas(struct turma turmas[]);

// Funções complexas de alocação dinâmica
void inscrever(struct aluno alunos[], struct turma turmas[], struct inscricao inscricoes[]);
void funcInscrever(struct aluno alunos[], struct turma turmas[], struct inscricao inscricoes[]);
void cancelarInscricao(struct inscricao inscricoes[]);
void fecharTurmas(struct turma turmas[], struct inscricao inscricoes[]);
void confirmarTurmas(struct turma turmas[], struct inscricao inscricoes[]);


// Funções de consulta com lógica de ponteiro e/ou vetor
void exibirInfosTurmasConfirmadas(struct turma turmas[]);
void exibirInfosTurmasCanceladas(struct turma turmas[]);
void exibirInfosInscricoesCanceladas(struct inscricao inscricoes[]);
void exibirInfosInscricao(struct inscricao inscricao[]);

// Mandar informações para o arquivo binario
void carregarDadosAlunos(struct aluno alunos[]);
void carregarDadosProfessores(struct professor professores[]);
void carregarDadosTurmas(struct turma turmas[]);
void carregarDadosInscricoes(struct inscricao inscricoes[]);
//textando binario
void carregarDadosRanking(struct inscricaoEmAula ranking[]);


// Encerramento e fechamento do arquivo.
void salvarDados(struct aluno alunos[], struct professor professores[], struct turma turmas[], struct inscricao inscricoes[]);

// funções de tratamento
int existeAluno(struct aluno alunos[], int idAluno);
int existeTurma(struct turma turmas[], int idTurma);
int verificarExisteAlunoTurma(struct inscricao inscricoes[], int idAluno, int idTurma);
int verificarTurmaLotada(struct inscricao inscricoes[], struct turma turmas[], int idTurma);
int turmaCancelada(struct turma turmas[], int idTurma);
int turmaConfirmada(struct turma turmas[], int idTurma);
int verificaConfirmacao(struct turma turmas[], struct inscricao inscricoes[], int idTurma);
int verificaCancelamento(struct turma turmas[], struct inscricao inscricoes[],int idTurma);

// funções de apoio
void limparBuffer();
int lerOpcao();
int menuInsc();
int declararData(int);


// Função desafio
void inscricaoEmAula(struct inscricao inscricoes[], struct turma turmas[],struct inscricaoEmAula ranking[], struct aluno alunos[]);

void mostrarAulasProximas(struct turma turmas[], struct inscricao inscricoes[]);

int main() {
  char debug;

  // criação do struct no main e Vetores do struct
  struct aluno alunos[100];
  struct professor professores[100];
  struct turma turmas[100];
  struct inscricao inscricoes[1000];
  struct inscricaoEmAula ranking[12];
  // Ler dados dos arquivos
  carregarDadosAlunos(alunos);
  carregarDadosProfessores(professores);
  carregarDadosTurmas(turmas);
  carregarDadosInscricoes(inscricoes);
  printf("\n\nAperte qualquer tecla para inicar o programa!\n");
  scanf("%c", &debug);
  // limpar informações do arquivo
  printf("\e[1;1H\e[2J");

  int opcao;

  do {
    opcao = lerOpcao();
    debug = 's';

    switch (opcao) {
    case 1:
      cadastroAluno(alunos); // Cadastra alunos
      break;
    case 2:
      inscrever(alunos, turmas, inscricoes); // Inscrever aluno
      break;
    case 3:
      cadastroProfessor(professores); // Cadastrar professor
      break;
    case 4:
      cadastroTurma(turmas, professores); // Cadastrar turma
      break;
    case 5:
      cancelarInscricao(inscricoes); // 5- Cancelar inscrição
      break;
    case 6:
      fecharTurmas(turmas, inscricoes); // 6- Fechar turmas
      break;
    case 7:
      confirmarTurmas(turmas, inscricoes); // 7- Confirmar turmas
      break;
    case 8:
      exibirInfosTurmasConfirmadas(turmas); // 8- Exibição de aulas confirmadas
      break;
    case 9:
      exibirInfosTurmasCanceladas(turmas); // 9- Exibição de aulas canceladas
      break;
    case 10:
      exibirInfosInscricoesCanceladas(inscricoes); // 10- Exibição de inscrições canceladas
      break;

    case 11: // Desafio
      inscricaoEmAula(inscricoes, turmas, ranking, alunos);
      break;

    case 12:
      // 12- Salva e fecha o programa
      salvarDados(alunos, professores, turmas, inscricoes); // salvarAula(turmas);
      exit(0);
      break;

    default:
      printf("Opção inválida, insira qualquer tecla para volta para o menu.. \n");
      scanf(" %c", &debug);
      debug = 'n';

      break;
    }
  } while (opcao > 0 && opcao < 11 || debug == 'n');

};
//Funções do Desafio!!!

int declararData(int tipo){

    // Obtém a hora atual em UTC
    time_t raw_time;
    time(&raw_time);

    // Ajusta o fuso horário para Brasília (UTC-3)
    struct tm *brasilia_time = gmtime(&raw_time);
    brasilia_time->tm_hour -= 3;

    // Corrige o resultado, ajustando para valores válidos (positivos) após a subtração
    if (brasilia_time->tm_hour < 0) {
        brasilia_time->tm_hour += 24;
        brasilia_time->tm_mday--;  // Decrementa o dia
    }

    // Converte o tempo para a estrutura tm
    time_t brasilia_raw_time = mktime(brasilia_time);

    // Converte o tempo de volta para a estrutura tm para obter a data correta
    struct tm *brasilia_time_final = localtime(&brasilia_raw_time);

    // Exibe a data e hora atual em Brasília
  if(tipo == 1){
    printf("Data e Hora Atuais em Brasília: %02d/%02d/%04d %02d:%02d\n",
           brasilia_time_final->tm_mday,
           brasilia_time_final->tm_mon + 1,
           brasilia_time_final->tm_year + 1900,
           brasilia_time_final->tm_hour,
           brasilia_time_final->tm_min);
  }
  if (tipo == 0){
    return brasilia_time_final->tm_min;
  }

    if(tipo == 2)
      return brasilia_time_final->tm_mon + 1;

    if(tipo==3){
    return  brasilia_time_final->tm_wday;
  }
      if(tipo==4){
        return  brasilia_time_final->tm_hour;
      }
  else{return brasilia_time_final->tm_year + 1900;
}
}
//funcao para retornar o dia da semana atual
const char* diaSemanaAtual() {
    // Obtém a hora atual
    time_t tempoAtual;
    struct tm *infoTempo;

    time(&tempoAtual);
    infoTempo = localtime(&tempoAtual);

    // Mapeia os valores tm_wday para os dias da semana
    const char *diasSemana[] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};

    // Obtém e retorna o dia da semana atual
    int diaSemana = infoTempo->tm_wday;
    return diasSemana[diaSemana];
}

//mostrar aulas nos proximos 30 min deste dia da semana
void mostrarAulasProximas(struct turma turmas[], struct inscricao inscricoes[]) {
    const char *dia = diaSemanaAtual();
    int horaAtual = 22;// declararData(4);
    int minAtual =  30;// declararData(0);
  int debug;
    int tempoAtualEmMinutos = horaAtual * 60 + minAtual;
  int temTurma = 0;
    printf("\n\nHoje é %s %i:%i", dia, horaAtual, minAtual);

    printf("\n\nAulas disponíveis nos próximos 30 minutos são:\n");
    for (int i = 0; turmas[i].situacaoTurma != 0; i++) {
        if (strcmp(turmas[i].diaSemanaTurma, dia) == 0) {
            int horarioTurmaEmMinutos = turmas[i].horarioTurma[0] * 60 + turmas[i].horarioTurma[1];
            // Verifica se a aula está nos próximos 30 minutos
            if (horarioTurmaEmMinutos >= tempoAtualEmMinutos && horarioTurmaEmMinutos <= tempoAtualEmMinutos + 30) {
                temTurma = 1;
                printf("\n\n%i - Turma ID: %i\n", turmas[i].idTurma ,turmas[i].idTurma);
                printf("Horário: %i:%i\n", turmas[i].horarioTurma[0],turmas[i].horarioTurma[1]);
                printf("Tipo da Turma: %i\n", turmas[i].tipoTurma);
                printf("Id Professor: %i\n", turmas[i].idProfessorTurma);
                // Adicione aqui qualquer outra informação que deseja exibir
            }
        }
    }
  if(temTurma == 0){
    printf( "\n\nNão há aulas disponíveis nos próximos 30 minutos.\n");
    printf( "\n\nAperte qualquer tecla para voltar ao menu.\n");
    scanf( "%i", &debug);
    main();
  }
  }

//verificar se o aluno esta matriculado na turma
int verificaMatricula(struct inscricao inscricoes[], int idAluno, int idTurma){
  for(int i = 0; inscricoes[i].situacaoInscricao == 1; i++){
    if(inscricoes[i].idTurmaInscricao == idAluno && inscricoes[i].idTurmaInscricao == idTurma){
      return 1;
    }
}return 0;
}

// funcao para participar em aula
void participarAula(struct inscricao inscricoes[], struct turma turmas[], struct inscricaoEmAula inscricoesAula[], struct aluno alunos[]){
  printf("\n\033[102mParticipar em Aula:\033\n[0m \n");
  int idAl = 0;
  int idT = 0;
   int debug;
  // Seleciona a primeira posição vazia do vetor de struct inscricoes
  int inscricoesFeitas = 0;
  for (int i = 0; inscricoes[i].situacaoInscricao != 0 && inscricoes[i].situacaoInscricao != 2;
       i++) {
    inscricoesFeitas++;
  }
  mostrarAulasProximas(turmas, inscricoes);

  // tratamento de turma nao existente
  //  Coloca o id da turma no vetor de struct inscrições
  printf("\n\nInforme o Id da turma que o aluno deseja aplicar: ");
  scanf("%i", &idT);
  int existeT = existeTurma(turmas, idT);
  if (existeT == 0) {
    printf("\033[41;4m""Id de Turma não cadastrada!!! Voltando ao Menu""\033[0m");
    return;
  };
  // fim do tratamento de turma nao existente

  // Coloca o id do aluno no vetor de struct inscrições
  printf("\nInforme o Id do aluno que deseja participar da aula: ");
  scanf("%i", &idAl);

  // Tratamento de aluno não cadastrado
  int existeA = 0;
  existeA = existeAluno(alunos, idAl);
  while (existeA == 0) {
    printf("\nId do aluno não cadastrado!!! ");
    printf("\nInforme o Id do aluno que deseja participar da aula: ");
    scanf("%i", &idAl);
    existeA = existeAluno(alunos, idAl);
  };

  // Fim do tratamento de aluno não cadastrado
  //tratamento se o aluno não estiver inscrito
  int inscAl = verificaMatricula(inscricoes, idAl, idT);

  if(inscAl == 1){
    printf("\033[41;4m""Aluno não matriculado na turma!!! Voltando ao menu""\033[0m");
    scanf("%i", &debug);
    main();
      }

  // tratamento de aluno já cadastrado

  // fim do tratamento de aluno já cadastrado

  // salvando informações após tratamentos de dados
  if (existeT == 1 ) {
    inscricoesAula[inscricoesFeitas].idInscricaoAula = inscricoesFeitas;
    inscricoesAula[inscricoesFeitas].idAluno = idAl;
  }

  if (existeA == 1) {
      inscricoesAula[inscricoesFeitas].idTurma = idAl;
  }
  printf("\n\033[102;4mPresença Marcada!!\033\n[0m \n");
  printf("Digite qualquer tecla para voltar ao menu: ");
  scanf("%i" ,&debug);
  main();
}
//Função do ranking
// funcao para mostrar o ranking dos 3 primeiros alunos que mais participaram de aulas

void mostrarRanking(struct inscricaoEmAula inscricoesEmAula[]) {
    int contPart;
    int i = 0;

    while (inscricoesEmAula[i].idTurma != 0) {
        int idAlunoAtual = inscricoesEmAula[i].idAluno;
        contPart = 0;

        // Loop para contar as participações do aluno atual
        while (inscricoesEmAula[i].idAluno == idAlunoAtual && inscricoesEmAula[i].idAluno != 0) {
            contPart++;
            i++;
        }

        // Imprimir a participação do aluno
        printf("Participação do aluno %i foi de %i\n", idAlunoAtual, contPart);
    }

    printf("\nRanking dos Alunos:\n");

}

 void inscricaoEmAula(struct inscricao inscricoes[], struct turma turmas[],struct inscricaoEmAula inscricoesAula[], struct aluno alunos[]){
    int resp = 0;

    printf("\n\n▬▬▬▬▬▬▬▬▬▬▬▬ MENU DE INSCRIÇÃO ✍️  ▬▬▬▬▬▬▬▬▬▬▬▬\n\n");
    printf("\n\n\033""[35;1m ► Escolha a Opção desejada ◄" "\033\n\n[0m");
    printf("\033[34;1m00""➦ Voltar ao Menu Principal\n");
    printf("\033[34;1m01" "➦ Participar em aula\n");
    printf("\033[34;1m02""➦ Mostrar ranking\n");
    printf("\n\033""[35;1m  Opção: " "\033[0m" "\033[34;1m");
    scanf("%d", &resp);

    if(resp == 0){
      main();
    }

   switch(resp){
     case 1:
       participarAula(inscricoes, turmas, inscricoesAula, alunos);
     break;
     case 2:
     mostrarRanking(inscricoesAula);
     break;
   }

    }


// Função que mostra o menu e recebe a opção do usuário

int lerOpcao() {

  int opcao;
  printf("\n\n🏋  Academia ""\033[44;41m\033[35;1m""♥ Força prog ♥" "\033\n\n[0m");
   declararData(1);
  printf("\n▬▬▬▬▬▬▬▬▬▬▬▬ MENU PRINCIPAL👊 ▬▬▬▬▬▬▬▬▬▬▬▬\n\n");
  printf("\n\033""[35;1m ► Escolha a Opção desejada ◄" "\033\n[0m");
  printf("\n");
  printf("\033[34;1m" "01➦ Cadastrar aluno\n");
  printf("\033[34;1m" "02➦ Inscrever aluno \n");
  printf("\033[34;1m" "03➦ Cadastrar Professores \n");
  printf("\033[34;1m" "04➦ Cadastrar turma" "\033[0m \n");
  printf("\033[31;1m" "05➦ Cancelar inscrição" "\033[0m \n\033");
  printf("\033[31;1m" "06➦ Fechar turmas" "\033[0m \n");
  printf("\033[32;1m" "07➦ Confirmar turmas" "\033[0m \n");
  printf("\033[33;1m" "08➦ Relatório de aulas confirmadas" "\033[0m \n");
  printf("\033[33;1m" "09➦ Relatório de aulas canceladas" "\033[0m \n");
  printf("\033[33;1m" "10➦ Relatório de inscrições canceladas" "\033[0m \n");
  printf("\033[37;1m" "11➦ \033[101m\033[33;1m"  "★★ Menu inscrição em aula ★★" "\033[0m \n");
  printf("\033[37;1m" "12➦ Salvar e fechar o sistema" "\033[0m \n");
  printf("\n");
  printf("\033[35;1m" " Opção: " "\033[0m");
  scanf("%d", &opcao);
  system("clear");
  return opcao;
}

int menuInsc() {
  int opcao;
  printf("\nAcademia ""\033[44;41m\033[35;1m""♥ Força prog ♥""\033\n[0m");
  printf("\n\n▬▬▬▬▬▬▬▬▬▬▬ MENU SECUNDÁRIO✌ ▬▬▬▬▬▬▬▬▬▬▬\n\n");
  printf("\n\033[35;1m" " ► Escolha a Opção desejada ◄" "\033\n\n[0m");
  printf("\033[24;30m""00-Voltar""\n01-Consultar Alunos Cadastrados" "\n02-Consultar Turmas " "Cadastradas\n03-Consultar Inscrições""\033[32;1m""\n04-Inscrever Aluno\n");
  printf("\033[35;1m"" \nOpção: ""\033[0m");
  scanf("%d", &opcao);
  system("clear");
  return opcao;
};

// Função que limpa o buffer
void limparBuffer() {
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
  }
}

// Mostrar listagem de alunos cadastrados no sistema
// Função que cadastra os alunos

void cadastroAluno(struct aluno alunos[]) {

  // Seleciona a primeira posição vazia do vetor de struct alunos
  int alunosCad = 0;
  int comp;
  int qtd;
  int qtdSemelhante;
  for (int i = 0; alunos[i].cpfAluno[0] != '\0'; i++) {
    alunosCad++;
  }

  alunos[alunosCad].idAluno = alunosCad;

  limparBuffer();

  // Coloca o nome do aluno no vetor de struct
  printf("\n\033[102m" "02- Cadastrar aluno""\033\n[0m");

  printf("\n\033[43m""Informe o nome do aluno:""\033[0m\033[34m ");
  gets(alunos[alunosCad].nomeAluno);
  // Coloca o CPF do aluno no vetor de struct

  do {
    qtdSemelhante = 0;
    qtd = 0;

    printf("\n\033[43m""Informe o CPF do aluno (11 dígitos):""\033[0m\033[34m");
    scanf("%s", alunos[alunosCad].cpfAluno);

    if (strlen(alunos[alunosCad].cpfAluno) != 11) {
      printf("\033[0m""\nCPF inválido! Deve conter 11 dígitos. Tente novamente!\n");
      continue; // Pede ao usuário para fornecer o CPF novamente
    }

    for (int j = 0; j < strlen(alunos[alunosCad].cpfAluno); j++) {
      if (alunos[alunosCad].cpfAluno[j] > 47 && alunos[alunosCad].cpfAluno[j] < 58)
        qtd++;
    }

    if (qtd < 11 && strlen(alunos[alunosCad].cpfAluno) == 11) {
      printf("\033[0m""\nUm CPF é composto por números!\n");
      continue; // Pede ao usuário para fornecer o CPF novamente
    }

    for (int i = 0; i < alunosCad; i++) {
      if (strcmp(alunos[alunosCad].cpfAluno, alunos[i].cpfAluno) == 0)
        qtdSemelhante++;

      if (qtdSemelhante > 0) {
        printf("\033[31;1m" "ERRO!! O CPF já está cadastrado com o nome de: %s\033[0m", alunos[i].nomeAluno);
        // Pede ao usuário para fornecer o CPF novamente
        break; // Encerra o loop se encontrar um CPF semelhante
      }
    }

  } while (strlen(alunos[alunosCad].cpfAluno) != 11 || qtd != 11 || qtdSemelhante > 0);

  // Coloca o telefone do aluno no vetor de struct
  do {
    printf("\n\033[43m""Informe o telefone do aluno (11 dígitos considere o ddd):""\033[0m\033[34m");
    scanf("%s", alunos[alunosCad].telefoneAluno);

    if (strlen(alunos[alunosCad].telefoneAluno) != 11) {
      printf("\033[0m""\nTelefone inválido! Deve conter 11 dígitos. Tente novamente!\n");
    }
  } while (strlen(alunos[alunosCad].telefoneAluno) != 11);

  int aux = 1; // controle de email

  // Coloca o email do aluno no vetor de struct
  do {

    printf("\n\033[43m""Informe o e-mail do aluno:""\033[0m\033[34m");
    scanf("%s", alunos[alunosCad].emailAluno);

    for (int i = 0; i < strlen(alunos[alunosCad].emailAluno); i++) {
      if (alunos[alunosCad].emailAluno[i] == 64)
        aux = 0;

      else if (i == strlen(alunos[alunosCad].emailAluno) - 1 && aux != 0)
        printf( "\033[0m""Favor informe um e-mail válido (um email deve conter um '@')\n");
    }
  } while (aux == 1);
  printf("\n\033[102;4m""Aluno cadastrado com sucesso!""\033\n[0m\n\n");
}

// Função que cadastra os professores

void cadastroProfessor(struct professor professores[]) {
  // Seleciona a primeira posição vazia do vetor de struct professores
  int professoresCad = 0;
  int comp;
  int qtdSemelhante;
  int qtd;

  for (int i = 0; professores[i].cpfProfessor[0] != '\0'; i++) {
    professoresCad++;
  }

  professores[professoresCad].idProfessor = professoresCad;

  limparBuffer();

  printf("\n\033[102m""03- Cadastrar Professor" "\033\n[0m");

  // Coloca o nome do professor no vetor de struct professores
  printf("\n\033[43m""Informe o nome do professor:" "\033[0m\033[34m");
  gets(professores[professoresCad].nomeProfessor);

  // Coloca o CPF do professor no vetor de struct professores

  do {
    qtdSemelhante = 0;
    qtd = 0;

    printf("\n\033[43m""Informe o CPF do Professor (11 dígitos):" "\033[0m\033[34m");
    scanf("%s", professores[professoresCad].cpfProfessor);

    if (strlen(professores[professoresCad].cpfProfessor) != 11) {
      printf("\033[0m""\nCPF inválido! Deve conter 11 dígitos. Tente novamente!\n");
      continue; // Pede ao usuário para fornecer o CPF novamente
    }

    for (int j = 0; j < strlen(professores[professoresCad].cpfProfessor); j++) {
      if (professores[professoresCad].cpfProfessor[j] > 47 &&  professores[professoresCad].cpfProfessor[j] < 58)
        qtd++;
    }

    if (qtd < 11 && strlen(professores[professoresCad].cpfProfessor) == 11) {
      printf("\033[0m""\nUm CPF é composto por números!\n");
      continue; // Pede ao usuário para fornecer o CPF novamente
    }

    for (int i = 0; i < professoresCad; i++) {
      if (strcmp(professores[professoresCad].cpfProfessor, professores[i].cpfProfessor) == 0)
        qtdSemelhante++;

      if (qtdSemelhante > 0) {
        printf("\033[31;1m""ERRO!! O CPF já está cadastrado com o nome de: %s\033[0m", professores[i].cpfProfessor);
        // Pede ao usuário para fornecer o CPF novamente
        break; // Encerra o loop se encontrar um CPF semelhante
      }
    }

  } while (strlen(professores[professoresCad].cpfProfessor) != 11 || qtd != 11 || qtdSemelhante > 0);

  // Coloca o telefone do professor no vetor de struct professores
  do {
    printf("\n\033[43m" "Informe o telefone do professor (11 dígitos considere o ddd):""\033[0m\033[34m");
    scanf("%s", professores[professoresCad].telefoneProfessor);

    if (strlen(professores[professoresCad].telefoneProfessor) != 11) {
      printf("\033[0m""Telefone inválido! Deve conter 11 dígitos. Tente novamente!\n");
    }
  } while (strlen(professores[professoresCad].telefoneProfessor) != 11);

  // Coloca o e-mail do professor no vetor de struct professores

  int aux = 1;
  do {

    printf("\n\033[43m""Informe o e-mail do professor: ""\033[0m\033[34m");
    scanf("%s", professores[professoresCad].emailProfessor);

    for (int i = 0; i < strlen(professores[professoresCad].emailProfessor);
         i++) {
      if (professores[professoresCad].emailProfessor[i] == 64)
        aux = 0;

      else if (i == strlen(professores[professoresCad].emailProfessor) - 1)
        printf("\033[0m" "\nPor favor, informe um e-mail válido\n");
    }
  } while (aux == 1);
  printf("\n\033[102;4m""Professor cadastrado com sucesso!""\033\n[0m\n\n");
}

// Função que cadastra a turma

void cadastroTurma(struct turma turmas[], struct professor professores[]) {
  int tipoTurma;
  char diaSemanaTurma;
  int opErro, comp1, comp2;
  int turmasCad = 0;
  int aux;
  int resp;
  // Seleciona a primeira posição vazia do vetor de struct turmas
  for (int i = 0; turmas[i].faixaEtariaTurma[0] != '\0'; i++) { // aqui
    turmasCad++;
  }

  turmas[turmasCad].idTurma = turmasCad;

  // Limpa o buffer para usar o gets
  limparBuffer();

  printf("\n\033[102m" "04- Cadastrar Turma" "\033\n[0m\n");

  // Coloca o dia da semana no vetor de struct turmas

  do {
    aux = 0;
    printf("\n\033[43m"
           "Escolha o dia da semana da turma: Usando (1-7)"
           "\033[0m"
           "\n\033[0m\033[34m"
           "\n1. Domingo"
           "\n2. Segunda"
           "\n3. Terça"
           "\n4. Quarta"
           "\n5. Quinta"
           "\n6. Sexta"
           "\n7. Sabado"
           "\033[0m\033[34m");

    printf("\033[35;1m"" \nOpção: ""\033[0m");
    scanf("%d", &resp);

    switch (resp) {
    case 1:
      printf("\n\033[35;1m""Turma de domingo selecionada\n");
      strcpy(turmas[turmasCad].diaSemanaTurma, "Domingo");
      break;

    case 2:
      printf("\n\033[35;1m""Turma de segunda selecionada\n");
      strcpy(turmas[turmasCad].diaSemanaTurma, "Segunda");
      break;

    case 3:
      printf("\n\033[35;1m""Turma de terça selecionada\n");
      strcpy(turmas[turmasCad].diaSemanaTurma, "Terça");
      break;

    case 4:
      printf("\n\033[35;1m""Turma de quarta selecionada\n");
      strcpy(turmas[turmasCad].diaSemanaTurma, "Quarta");
      break;

    case 5:
      printf("\n\033[35;1m" "Turma de quinta selecionada\n");
      strcpy(turmas[turmasCad].diaSemanaTurma, "Quinta");
      break;

    case 6:
      printf("\n\033[35;1m""Turma de sexta selecionada\n");
      strcpy(turmas[turmasCad].diaSemanaTurma, "Sexta");
      break;

    case 7:
      printf("\n\033[35;1m""Turma de sabado selecionada\n");
      strcpy(turmas[turmasCad].diaSemanaTurma, "Sabado");
      break;

    default:
      printf("\n\033[41;4m""Opção inválida, tente novamente""\033\n[0m\n");
      aux = 1;
      break;
    }

  } while (aux == 1);

  // Coloca o horário da turma no vetor de struct turmas

  printf("\n\033[43m""Informe o horário da turma:""\033[0m\033[34m");
  do {
    aux = 1;

    printf("Diga a Hora seguindo o modelo (00-23): ");
    scanf("%d", &turmas[turmasCad].horarioTurma[0]);
    if (turmas[turmasCad].horarioTurma[0] >= 0 && turmas[turmasCad].horarioTurma[0] <= 23)
      aux = 0;
    else
      printf("Hora inválida! Tente novamente.\n");

  } while (aux == 1);

  do {
    aux = 1;

    printf("\n\nDiga o minuto seguindo o modelo (00-60): ");
    scanf("%d", &turmas[turmasCad].horarioTurma[1]);
    if (turmas[turmasCad].horarioTurma[1] >= 0 && turmas[turmasCad].horarioTurma[1] <= 60)
      aux = 0;
    else
      printf("Hora inválida! Tente novamente.\n");

  } while (aux == 1);

   // Tratamento de dia e hora repetidos
for (int i = 0; i < turmas[turmasCad].idTurma; i++) {

  do {
    comp1 = strcmp(turmas[turmasCad].diaSemanaTurma, turmas[i].diaSemanaTurma);
    comp2 = (turmas[turmasCad].horarioTurma[0] == turmas[i].horarioTurma[0] && turmas[turmasCad].horarioTurma[1] == turmas[i].horarioTurma[1]) ? 0 : 1;

    if (comp1 == 0 && comp2 == 0) {
      printf("\n\033[41;4m""ERRO!! Já Existe Cadastro de uma turma neste horário e dia""\033\n[0m\n");

      printf("\n");

      do {
        opErro = 0;
        printf("\nO que Deseja mudar?:""\033[0m\033[34m""\n 1-Dia da semana ou  \n2-Horário (2):\033[0m");
        scanf("%d", &opErro);
        limparBuffer();
        switch (opErro) {

        case 1:
          printf("\033[35;1m""\nInforme outro dia da semana: ");
          gets(turmas[turmasCad].diaSemanaTurma);
          break;
        case 2:
          printf("\033[35;1m""\nInforme outro horário da turma (hora minuto): ");
          scanf("%d %d", &turmas[turmasCad].horarioTurma[0], &turmas[turmasCad].horarioTurma[1]);
          limparBuffer();
          break;
        default:
          printf("\033\n[0m\n\033[41;4m""Opção inválida, tente novamente!!!""\033\n[0m\n");
          break;
        }
      } while (opErro != 1 && opErro != 2);
    }
    comp1 = strcmp(turmas[turmasCad].diaSemanaTurma, turmas[i].diaSemanaTurma);
    comp2 = (turmas[turmasCad].horarioTurma[0] == turmas[i].horarioTurma[0] && turmas[turmasCad].horarioTurma[1] == turmas[i].horarioTurma[1]) ? 0 : 1;

  } while (comp1 == 0 && comp2 == 0);
}

  // Seleção de tipo de turma
  do {
    printf("\n\033[43m"
           "Escolha a aula da truma:""\033[0m"
           "\n\033[0m\033[34m"
           "\n1. Artes Marciais"
           "\n2. Crossfit"
           "\n3. Boxe"
           "\n4. Dança\n"
           "\033[0m\033[34m");
    printf("\033[35;1m"" \nOpção: ""\033[0m");
    scanf("%d", &tipoTurma);

    switch (tipoTurma) {
    case 1:
      printf("\n\033[35;1m""Turma de Artes Marciais selecionada\n");
      turmas[turmasCad].tipoTurma = 1;
      break;

    case 2:
      printf("\n\033[35;1m""Turma de Crossfit selecionada\n");
      turmas[turmasCad].tipoTurma = 2;
      break;

    case 3:
      printf("\n\033[35;1m""Turma de Boxe selecionada\n");
      turmas[turmasCad].tipoTurma = 3;
      break;

    case 4:
      printf("\n\033[35;1m""Turma de Dança selecionada\n");
      turmas[turmasCad].tipoTurma = 4;
      break;

    default:
      printf("\n\033[41;4m""Opção inválida, tente novamente""\033\n[0m\n");
      break;
    }
  } while (tipoTurma > 4 || tipoTurma <= 0);

  // Mostra os professores disponiveis para cadastrar
  printf("\n\033[32;1m" "Os professores disponíveis para cadastro:" "\033\n[0m\n");

  for (int j = 0; professores[j].cpfProfessor[0] != '\0'; j++) {
    printf("Professor: %s - Id: %i\n", professores[j].nomeProfessor, professores[j].idProfessor);
  }

  // Coloca o id do professor no vetor de struct turmas
  printf("\n\033[33;1m""Informe o Id do professor que deseja cadastrar:""\033\n[0m\n");
  scanf("%i", &turmas[turmasCad].idProfessorTurma);

  int professoresCad = 0;

  do {

    professoresCad = 0;

    for (int i = 0; professores[i].cpfProfessor[0] != '\0'; i++) {
      professoresCad++;
    }

    if (turmas[turmasCad].idProfessorTurma > professoresCad) {

      printf("\nId de professor inesistente");

      printf("\n\033[32;1m""Os professores disponíveis para cadastro são:""\033\n[0m \n");

      for (int j = 0; professores[j].nomeProfessor[0] != '\0'; j++) {
        printf("\nProfessor: %s - Id: %i", professores[j].nomeProfessor,
               professores[j].idProfessor);
      }

      printf("\n\033[43m" "Informe o Id do professor que deseja cadastrar:" "\033\n[0m \n");
      scanf("%i", &turmas[turmasCad].idProfessorTurma);
    }

  } while (turmas[turmasCad].idProfessorTurma > professoresCad);

  // Limpa o buffer para usar o gets
  limparBuffer();

  // Coloca a faixa etária da turma no vetor de struct turmas
  printf("\n\033[43m" "Informe a faixa etária da turma em anos (1-120):" "\033[0m\033[34m");
scanf("%d", &aux);

    if(aux<=15)
    resp=1;

    if(aux>15&&aux<=64)
    resp=2;

    if(aux>=65)
    resp=3;

  switch (resp) {
    case 1:
      printf("\n\033[35;1m""Turma na Faixa Etária Jovem\n");
      strcpy(turmas[turmasCad].faixaEtariaTurma, "Jovem");
      break;

    case 2:
      printf("\n\033[35;1m""Turma na Faixa Etária Adulto\n");
      strcpy(turmas[turmasCad].faixaEtariaTurma, "Adultos");
      break;

    case 3:
      printf("\n\033[35;1m""Turma na Faixa Etária Idoso\n");
      strcpy(turmas[turmasCad].faixaEtariaTurma, "Idosos");
      break;
  }

aux=0;

do{ 

  if(aux!=0)
  printf("\033[0m" "\nPor favor, informe um valor Máximo maior que o valor Mínimo\n");

  aux=0;
  // Coloca o número mínimo de alunos no vetor de struct turmas
  printf("\n\033[43m""Informe o número mínimo de alunos para essa turma:" "\033[0m\033[34m");
  scanf("%i", &turmas[turmasCad].numeroMinimoAlunos);

  // Coloca o número máximo de alunos no vetor de struct turmas
  printf("\n\033[43m" "Informe o número máximo de alunos para essa turma:" "\033[0m\033[34m");
  scanf("%i", &turmas[turmasCad].numeroMaximoAlunos);

  aux++;  

}while(turmas[turmasCad].numeroMaximoAlunos<turmas[turmasCad].numeroMinimoAlunos);

  turmas[turmasCad].situacaoTurma = 1;
}

// Função para inscrever alunos 

void inscrever(struct aluno alunos[], struct turma turmas[],
               struct inscricao inscricoes[]) {
  int op = 0;
  do {
    op = menuInsc();

    switch (op) {
    case 1:
      exibirInfosAlunos(alunos);
      break;
    case 2:
      exibirInfosTurmas(turmas);
      break;
    case 3:
      exibirInfosInscricao(inscricoes);
      break;
    case 4:
      funcInscrever(alunos, turmas, inscricoes);
      break;
    case 0:
      // voltar
      break;
    default:
      printf("\n\033[41;4m Opção inválida, tente novamente!!!\033\n[0m\n");
      break;
    }
  } while (op > 0 && op < 4);
}

int existeAluno(struct aluno alunos[], int idAluno) {
  int existe = 0; // 1 se existir e 0 se não existir
  for (int i = 0; alunos[i].nomeAluno[0] != '\0'; i++) {
    if (alunos[i].idAluno == idAluno) {
      return 1;
      break;
    }
  }
  return 0;
};

int existeTurma(struct turma turmas[], int idTurma) {
  int existe = 0; // 1 se existir e 0 se não existir
  for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {
    if (turmas[i].idTurma == idTurma) {
      return 1;
      break;
    }
  }
  return 0;
};

int verificarExisteAlunoTurma(struct inscricao inscricoes[], int idAluno,int idTurma) {
  for (int i = 0; inscricoes[i].situacaoInscricao != 0 && inscricoes[i].situacaoInscricao != 2;
       i++) {
    if (inscricoes[i].idAlunoInscricao == idAluno && inscricoes[i].idTurmaInscricao == idTurma) {
      return 1;
    }
  }
  return 0;
};

int verificarTurmaLotada(struct inscricao inscricoes[], struct turma turmas[],int idTurma) {
  int contAlunos = 0;
  for (int i = 0; inscricoes[i].idTurmaInscricao == idTurma && inscricoes[i].situacaoInscricao == 1; i++) {
    contAlunos++;
  }
  printf("%i", contAlunos);
  if (contAlunos >= turmas[idTurma].numeroMaximoAlunos) {
    return 1; // retorna 1 para turma lotada
  } else {
    return 0; // retorna 0 para turma com vagas
  }
  return 0;
};

void funcInscrever(struct aluno alunos[], struct turma turmas[], struct inscricao inscricoes[]) {

  printf("\n\033[102m 02- Inscrever aluno:\033\n[0m \n");
  int idAl = 0;
  int idT = 0;
  // Seleciona a primeira posição vazia do vetor de struct inscricoes
  int inscricoesFeitas = 0;
  for (int i = 0; inscricoes[i].situacaoInscricao != 0 && inscricoes[i].situacaoInscricao != 2;
       i++) {
    inscricoesFeitas++;
  }

  // Coloca o id do aluno no vetor de struct inscrições
  printf("\nInforme o Id do aluno que deseja cadastrar: ");
  scanf("%i", &idAl);

  // Tratamento de aluno não cadastrado
  int existeA = 0;
  existeA = existeAluno(alunos, idAl);
  while (existeA == 0) {
    printf("\nId do aluno não cadastrado!!! ");
    printf("\nInforme o Id do aluno que deseja cadastrar: ");
    scanf("%i", &idAl);
    existeA = existeAluno(alunos, idAl);
  };

  // Fim do tratamento de aluno não cadastrado

  // tratamento de turma nao existente
  //  Coloca o id da turma no vetor de struct inscrições
  printf("\nInforme o Id da turma que deseja cadastrar: ");
  scanf("%i", &idT);
  int existeT = existeTurma(turmas, idT);
  if (existeT == 0) {
    printf("\033[41;4m""Id de Turma não cadastrada!!! Voltando ao Menu""\033[0m");
    return;
  };

  // fim do tratamento de turma nao existente

  // tratamento de turma lotada

  int turmaLotada = 0;
  turmaLotada = verificarTurmaLotada(inscricoes, turmas, idT);
  if (turmaLotada == 1) {
    printf("\033[41;4m" "\nTurma lotada!!! Voltando ao Menu""\033[0m"); 
    return;
  }

  // tratamento de aluno já cadastrado

  int existeAT = 0;
  existeAT = verificarExisteAlunoTurma(inscricoes, idAl, idT);

  if (existeAT == 1 && existeT == 1) {
    printf("\033[41;4m" "\nO aluno já está cadastrado nesta turma!!! Voltando ao Menu""\033[0m"); 

    return;
  };
  // fim do tratamento de aluno já cadastrado

  // salvando informações após tratamentos de dados
  if (existeT == 1 && existeAT == 0 && turmaLotada == 0) {
    inscricoes[inscricoesFeitas].idTurmaInscricao = idT;
    inscricoes[inscricoesFeitas].idInscricao = inscricoesFeitas;

    // situacao == 1 inscricao ativa
    inscricoes[inscricoesFeitas].situacaoInscricao = 1;
  }

  if (existeA == 1) {
    inscricoes[inscricoesFeitas].idAlunoInscricao = idAl;
  }
  printf("\n\033[102;4mAluno Inscrito com Sucesso!\033\n[0m \n");
}
// fim da função inscrever

// Função que printa os professores cadastrados
void exibirInfosProfessores(struct professor professores[]) {

  for (int i = 0; professores[i].nomeProfessor[0] != '\0'; i++) {
    printf("\n\033[42;1mProfessores Cadastrados\033\n[0m \n");
    printf("Id: %i\n", professores[i].idProfessor);
    printf("Nome: %s\n", professores[i].nomeProfessor);

    printf("\nCPF: %c%c%c.%c%c%c.%c%c%c-%c%c", professores[i].cpfProfessor[0],
           professores[i].cpfProfessor[1], professores[i].cpfProfessor[2],
           professores[i].cpfProfessor[3], professores[i].cpfProfessor[4],
           professores[i].cpfProfessor[5], professores[i].cpfProfessor[6],
           professores[i].cpfProfessor[7], professores[i].cpfProfessor[8],
           professores[i].cpfProfessor[9], professores[i].cpfProfessor[10]);

    printf("\nTelefone: (%c%c) %c%c%c%c%c%-c%c%c%c", professores[i].telefoneProfessor[0], 
           professores[i].telefoneProfessor[1], professores[i].telefoneProfessor[2], 
           professores[i].telefoneProfessor[3], professores[i].telefoneProfessor[4],
           professores[i].telefoneProfessor[5], professores[i].telefoneProfessor[6], 
           professores[i].telefoneProfessor[7], professores[i].telefoneProfessor[8],
           professores[i].telefoneProfessor[9], professores[i].telefoneProfessor[10]);

    printf("\nE-mail: %s\n", professores[i].emailProfessor);
    printf("\n");
  }
}

// Função que printa os alunos cadastrados
void exibirInfosAlunos(struct aluno alunos[]) {

  printf("\n\033[42;1m""Alunos Cadastrados""\033[0m \n");
  for (int i = 0; alunos[i].nomeAluno[0] != '\0'; i++) {
    printf("\nAluno %i \n", i);
    printf("Id: %i\n", alunos[i].idAluno);
    printf("Nome: %s\n", alunos[i].nomeAluno);

    printf("\nCPF: %c%c%c.%c%c%c.%c%c%c-%c%c", alunos[i].cpfAluno[0],
           alunos[i].cpfAluno[1], alunos[i].cpfAluno[2], alunos[i].cpfAluno[3],
           alunos[i].cpfAluno[4], alunos[i].cpfAluno[5], alunos[i].cpfAluno[6],
           alunos[i].cpfAluno[7], alunos[i].cpfAluno[8], alunos[i].cpfAluno[9],
           alunos[i].cpfAluno[10]);

    printf("\nTelefone: (%c%c) %c%c%c%c%c%-c%c%c%c", alunos[i].telefoneAluno[0],
           alunos[i].telefoneAluno[1], alunos[i].telefoneAluno[2],
           alunos[i].telefoneAluno[3], alunos[i].telefoneAluno[4],
           alunos[i].telefoneAluno[5], alunos[i].telefoneAluno[6],
           alunos[i].telefoneAluno[7], alunos[i].telefoneAluno[8],
           alunos[i].telefoneAluno[9], alunos[i].telefoneAluno[10]);

    printf("\nE-mail: %s\n", alunos[i].emailAluno);
    printf("\n");
  }
}

// Função que printa as turmas cadastradas
void exibirInfosTurmas(struct turma turmas[]) {
  // verificar quantidade de turmas
  int temMatricula = 0;
  if (turmas[0].diaSemanaTurma[0] == '\0') {
    printf("\n\033[33;1mNenhuma turma foi cadastrada!\033\n[0m"); 
  } else {
    for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0' && turmas[i].situacaoTurma == 1; i++) {
      printf("\n\033[42;1mTurma Para Matrícula:\033\n[0m \n");
      printf("Id da Turma: %i\n", turmas[i].idTurma);
      printf("Dia da semana: %s\n", turmas[i].diaSemanaTurma);
      printf("Horário da turma: %d:%d Hrs\n", turmas[i].horarioTurma[0], turmas[i].horarioTurma[1]);
      printf("Id do professor: %i\n", turmas[i].idProfessorTurma);
      printf("Faixa Etária: %s\n", turmas[i].faixaEtariaTurma);
      printf("Número mínimo de alunos: %i\n", turmas[i].numeroMinimoAlunos);
      printf("Número máximo de alunos: %i\n", turmas[i].numeroMaximoAlunos);
      printf("Situação da Turma: %i\n", turmas[i].situacaoTurma);
      printf("\n");
      temMatricula = 1;
    }
  }if(temMatricula == 0){
     printf("\n\033[33;1mNenhuma turma está disponível para matricula!\033\n[0m");
  }
}

// Mostra na tela todas as turmas confirmadas
void exibirInfosTurmasConfirmadas(struct turma turmas[]) {
  int temMatricula = 0;

    for (int i = 0;turmas[i].situacaoTurma != '\0' ; i++) { 
      if(turmas[i].situacaoTurma == 2){
      printf("\n\033[42;1mTurma Confirmada:\033\n[0m \n");
      printf("Id da Turma: %i\n", turmas[i].idTurma);
      printf("Dia da semana: %s\n", turmas[i].diaSemanaTurma);
      printf("Horário da turma: %d:%d Hrs\n", turmas[i].horarioTurma[0], turmas[i].horarioTurma[1]);
      printf("Id do professor: %i\n", turmas[i].idProfessorTurma);
      printf("Faixa Etária: %s\n", turmas[i].faixaEtariaTurma);
      printf("Número mínimo de alunos: %i\n", turmas[i].numeroMinimoAlunos);
      printf("Número máximo de alunos: %i\n", turmas[i].numeroMaximoAlunos);
      printf("Situação da Turma: %i\n", turmas[i].situacaoTurma);
      printf("\n");
      temMatricula = 1;
      }
  }if(temMatricula == 0){
      printf("\n\033[33;1mNenhuma Turma está confirmada no momento!\033\n[0m");
  }
}

// Mostra na tela todas as turmas canceladas
void exibirInfosTurmasCanceladas(struct turma turmas[]) {

  int temMatricula = 0;

    for (int i = 0;turmas[i].situacaoTurma != '\0' ; i++) { 
      if(turmas[i].situacaoTurma == 3){
      printf("\n\033[42;1mTurma Cancelada:\033\n[0m \n");
      printf("Id da Turma: %i\n", turmas[i].idTurma);
      printf("Dia da semana: %s\n", turmas[i].diaSemanaTurma);
      printf("Horário da turma: %d:%d Hrs\n", turmas[i].horarioTurma[0], turmas[i].horarioTurma[1]);
      printf("Id do professor: %i\n", turmas[i].idProfessorTurma);
      printf("Faixa Etária: %s\n", turmas[i].faixaEtariaTurma);
      printf("Número mínimo de alunos: %i\n", turmas[i].numeroMinimoAlunos);
      printf("Número máximo de alunos: %i\n", turmas[i].numeroMaximoAlunos);
      printf("Situação da Turma: %i\n", turmas[i].situacaoTurma);
      printf("\n");
      temMatricula = 1;
      }
  }if(temMatricula == 0){
      printf("\n\033[33;1mNenhuma Turma está cancelada no momento!\033\n[0m");
  }
}

// Mostra na tela todas as incrições canceladas
void exibirInfosInscricoesCanceladas(struct inscricao inscricoes[]) {
   int temInscricao = 0;

   printf("\n\n\033[32;1m""Inscrições Canceladas""\033[0m \n\n"); 

  for (int i = 0; inscricoes[i].situacaoInscricao == 2; i++) {
    printf("\nAluno Cancelado:\n");
    printf("Id do aluno: %d\n", inscricoes[i].idAlunoInscricao);
    printf("Id da turma: %d\n", inscricoes[i].idTurmaInscricao);
    printf("\n");
    temInscricao = 1;

  }if(temInscricao == 0){
    printf("\n\033[33;1mNenhuma Inscrição está cancelada no momento!\033\n[0m");
}
}

// Função que printa as inscrições cadastradas
void exibirInfosInscricao(struct inscricao inscricoes[]) {

  for (int i = 0; inscricoes[i].situacaoInscricao == 1 ||
                  inscricoes[i].situacaoInscricao == 2;
       i++) {
    printf("\033[32;1m" "Inscrições:" "\033[0m \n");
    printf("Situação da Inscrição: ");
    if (inscricoes[i].situacaoInscricao == 2)
      printf("Incrição Fechada!");
    else {
      printf("Incrição Aberta!");
    }
    printf("\nId inscrição: %d\n", inscricoes[i].idInscricao);
    printf("Id aluno: %d\n", inscricoes[i].idAlunoInscricao);
    printf("Id turma: %d\n", inscricoes[i].idTurmaInscricao);
    printf("\n");
  }
}
// funcoes para tratamento de cancelar inscricoes
int existeInsc(struct inscricao inscricoes[], int idInsc) {
  for (int i = 0; inscricoes[i].situacaoInscricao != 0; i++) {
    if (inscricoes[i].idInscricao == idInsc) {
      return 1;
      break;
    }
  }
  return 0;
};

int inscricaoCancelada(struct inscricao inscricoes[], int idInsc) {
  for (int i = 0; inscricoes[i].situacaoInscricao == 2; i++) {
    if (inscricoes[i].idInscricao == idInsc) {
      return 1;
      break;
    }
  }
  return 0;
}

// Cancela as inscrições nas turma
void cancelarInscricao(struct inscricao inscricoes[]) {

  int id = 0;
  printf("\n\033[32;1mCancelamento de  Inscrições\033\n[0m \n");
  printf("\nInforme o número do Id da incrição que deseja cancelar: ");
  scanf("%i", &id);

  // tratando se o idInscricao nao existe
  int existeIns = existeInsc(inscricoes, id);
  while (existeIns == 0) {
    printf("\nId de inscrição não cadastrado!!!");
    printf("\nInforme o Id de inscrição que deseja cancelar: ");
    scanf("%i", &id);
    existeIns = existeInsc(inscricoes, id);
  };
  // tratando se a inscricao esta cancelada
  int inscCancelada = inscricaoCancelada(inscricoes, id);
  if (inscCancelada == 1) {
    printf("\nInscrição já cancelada!!!");
    return;
  }

  if (existeIns == 1 && inscCancelada == 0) {
    inscricoes[id].situacaoInscricao = 2;
    printf("Inscrição cancelada com sucesso!");
  }
}

// funcao para verificar se a turma já esta cancelada
int turmaCancelada(struct turma turmas[], int idTurma) {
  for (int i = 0; turmas[i].situacaoTurma == 3; i++) {
    if (turmas[i].idTurma == idTurma) {
      return 1;
      break;
    }
  }
  return 0;
}

// funcao para verificar se a turma já esta cancelada
int turmaConfirmada(struct turma turmas[], int idTurma) {
  for (int i = 0; turmas[i].situacaoTurma == 2 || turmas[i].situacaoTurma == 3;
       i++) {
    if (turmas[i].situacaoTurma == 2) {
      if (turmas[i].idTurma == idTurma) {
        return 1;
        break;
      }
    }else if(turmas[i].situacaoTurma == 3){}
  }
  return 0;
}
// funcao para verificar se a turma está para ser confirmada
int verificaConfirmacao(struct turma turmas[], struct inscricao inscricoes[], int idTurma) {
  int contInsc = 0;
  for (int j = 0; inscricoes[j].idTurmaInscricao == turmas[idTurma].idTurma && inscricoes[j].situacaoInscricao == 1;
       j++) {
    contInsc++;
  }
  if (contInsc >= turmas[idTurma].numeroMinimoAlunos &&
      turmas[idTurma].situacaoTurma != 3) {
    return 1; // se o retorno for 1 quer dizer que a turma está para confirmação
  }
  contInsc = 0;
  return 0; // se o retorno for 0 quer dizer que a turma pode ser fechada
}
// funcao para verificar se a turma está para ser cancelada
int verificaCancelamento(struct turma turmas[], struct inscricao inscricoes[],int idTurma) {
  int contInsc = 0;
  for (int j = 0; inscricoes[j].idTurmaInscricao == turmas[idTurma].idTurma && inscricoes[j].situacaoInscricao == 1;
       j++) {
    contInsc++;
  }
  if (contInsc < turmas[idTurma].numeroMinimoAlunos &&
      turmas[idTurma].situacaoTurma != 3) {
    return 1; // se o retorno for 1 quer dizer que a turma está para confirmação
  }
  contInsc = 0;
  return 0; // se o retorno for 0 quer dizer que a turma pode ser fechada
}

void fecharTurmas(struct turma turmas[], struct inscricao inscricoes[]) {
  int contInsc = 0;
  int opcao = 0;
  int temTurma = 0;
  printf("\n\n\033[44;41m\033[35;1m""Turmas Para Fechar""\033\n\n[0m");
  printf("\nNa listagem aparecem as turmas que não atingiram o número mínimo de ""inscrições, selecione a turma que deseja fechar:\n\n\n");
  for (int i = 0; turmas[i].situacaoTurma != 0; i++) {
    for (int j = 0; inscricoes[j].idTurmaInscricao == turmas[i].idTurma &&inscricoes[j].situacaoInscricao == 1;
         j++) {
      contInsc++;
    }

    if (contInsc < turmas[i].numeroMinimoAlunos &&
        turmas[i].situacaoTurma != 0) {
      temTurma = 1;
      printf("\n%i-Id da Turma: %i\n", turmas[i].idTurma, turmas[i].idTurma);
      printf("Dia da Semana: %s\n", turmas[i].diaSemanaTurma);
      printf("Número de Inscrições: %i\n", contInsc);
      printf("Número Mínimo: %i\n", turmas[i].numeroMinimoAlunos);
      printf("Número Máximo: %i\n", turmas[i].numeroMaximoAlunos);
      printf("Tipo da Turma: %i\n", turmas[i].tipoTurma);
      printf("Stuação da Turma: %i\n", turmas[i].situacaoTurma);
    }
    contInsc = 0;
  }
  if (temTurma == 0) {
    printf("\n\033[44;41m\033[35;1m""Não há turmas para Cancelar""\033\n[0m");
    return;
  }
  printf("\nInforme o Id da turma que deseja fechar ou digite -1 para sair: ");
  scanf("%i", &opcao);
  if (opcao == -1) {
    return;
  }

  // tratando se a turma não existe
  int existeT = existeTurma(turmas, opcao);
  while (existeT == 0) {
    printf("\nId de turma não cadastrado!!! ");
    printf("\nInforme o Id da turma que deseja fechar ou digite -1 para sair: ");
    scanf("%i", &opcao);
    if (opcao == -1) {
      return;
    }
    existeT = existeTurma(turmas, opcao);
  }
  // tratamento se a turma está para ser confirmada
  int turmaConf = verificaConfirmacao(turmas, inscricoes, opcao);
  if (turmaConf == 1) {
    printf("\nTurma está para ser confirmada!!!");
    return;
  }
  // tratamento se a turma já estiver cancelada
  int cancelado = turmaCancelada(turmas, opcao);
  if (cancelado == 1) {
    printf("\nTurma já cancelada!!!");
    return;
  }
  // tratamento se a turma já estiver confirmada
  int confirmado = turmaConfirmada(turmas, opcao);
  if (confirmado == 1) {
    printf("\n\033[102;4m""Turma já confirmada!!!""\033\n[0m\n\n");
    return;
  }
  if (existeT == 1 && cancelado == 0 && confirmado == 0 && turmaConf == 0) {
    turmas[opcao].situacaoTurma = 3;
    printf("\n\033[102;4m""Turma Fechada com sucesso!!!""\033\n[0m\n\n");
  }
}

//  Confirma a turma printando as turmas não canceladas
void confirmarTurmas(struct turma turmas[], struct inscricao inscricoes[]) {
  int temTurma = 0; // 0 se não possuir turma para confirmar e 1 para se possuir
                    // turmas para fechar
  int opcao = 0;
  int contInsc = 0;
  printf("\n\033[42;1mTurmas Para Confirmar\033\n[0m \n");
  printf("\nNa Listagem aparecem as turmas que atigiram o mínimo de inscrições:\n");

  for (int i = 0; turmas[i].situacaoTurma != 0; i++) {
    for (int j = 0; inscricoes[j].idTurmaInscricao == turmas[i].idTurma &&
                    inscricoes[j].situacaoInscricao == 1;
         j++) {
      contInsc++;
    }

    if (contInsc >= turmas[i].numeroMinimoAlunos &&
        turmas[i].situacaoTurma != 3 && turmas[i].situacaoTurma != 2) {
      temTurma = 1;
      printf("\n%i-Id da Turma: %i\n", turmas[i].idTurma, turmas[i].idTurma);
      printf("Dia da Semana: %s\n", turmas[i].diaSemanaTurma);
      printf("Número de Inscrições: %i\n", contInsc);
      printf("Número Mínimo: %i\n", turmas[i].numeroMinimoAlunos);
      printf("Número Máximo: %i\n", turmas[i].numeroMaximoAlunos);
      printf("Tipo da Turma: %i\n", turmas[i].tipoTurma);
      printf("Stuação da Turma: %i\n", turmas[i].situacaoTurma);
    }
    contInsc = 0;
  }
  if (temTurma == 0) {
    printf("\n\033[44;41m\033[35;1m""Não há turmas para confirmar""\033\n[0m");
    return;
  }
  printf("\nInforme o Id da turma que deseja fechar ou digite -1 para sair: ");
  scanf("%i", &opcao);
  if (opcao == -1) {
    return;
  }

  // tratando se a turma não existe
  int existeT = existeTurma(turmas, opcao);
  while (existeT == 0) {
    printf("\nId de turma não cadastrado!!! ");
    printf("\nInforme o Id da turma que deseja fechar ou digite -1 para sair: ");
    scanf("%i", &opcao);
    if (opcao == -1) {
      return;
    }
    existeT = existeTurma(turmas, opcao);
  }
  // tratamento se a turma está para ser cancelada
  int turmaCanc = verificaCancelamento(turmas, inscricoes, opcao);
  if (turmaCanc == 1) {
    printf("\nTurma está para ser cancelada!!!");
    return;
  }
  // tratamento se a turma já estiver cancelada
  int cancelado = turmaCancelada(turmas, opcao);
  if (cancelado == 1) {
    printf("\nTurma já cancelada!!!");
    return;
  }
  // tratamento se a turma já estiver confirmada
  int confirmado = turmaConfirmada(turmas, opcao);
  if (confirmado == 1) {
    printf("\nTurma já confirmada!!!");
    return;
  }

  if (existeT == 1 && cancelado == 0 && confirmado == 0 && turmaCanc == 0) {
    turmas[opcao].situacaoTurma = 2;
    printf("\n\033[102;4m""Turma Confirmada com sucesso!!!""\033\n[0m\n\n");

  }
}
// Carrega os dados do arquivo alunos para dentro do vetor alunos
void carregarDadosAlunos(struct aluno alunos[]) {

  FILE *fp;
  fp = fopen("./Alunos.bin", "rb");
  if (fp == NULL) {
    printf("\n\033[34;4m Erro ao abrir arquivo! Caminho ""inexistente!\033\n[0m\n");
    exit(1);
  }

  fread(alunos, sizeof(struct aluno), 100, fp);
  printf("Arquivo Alunos.bin carregado\n");
  fclose(fp);
}

// Carrega os dados do arquivo professores para dentro do vetor professores
void carregarDadosProfessores(struct professor professores[]) {

  FILE *fp;
  fp = fopen("./Professores.bin", "rb");
  if (fp == NULL) {
    printf("\n\033[34;4m Erro ao abrir arquivo! Caminho ""inexistente!\033\n[0m\n");
    exit(1);
  }

  fread(professores, sizeof(struct professor), 100, fp);
  printf("Arquivo Professores.bin carregado\n");
  fclose(fp);
}

// Carrega os dados do arquivo turmas para dentro do vetor turmas
void carregarDadosTurmas(struct turma turmas[]) {

  FILE *fp;
  fp = fopen("./Turmas.bin", "rb");
  if (fp == NULL) {
    printf("\n\033[34;4m Erro ao abrir arquivo! Caminho ""inexistente!\033\n[0m\n");
    exit(1);
  }

  fread(turmas, sizeof(struct turma), 100, fp);
  printf("Arquivo Turmas.bin carregado\n");
  fclose(fp);
}

// Carrega os dados do arquivo inscricoes para dentro do vetor inscricoes
void carregarDadosInscricoes(struct inscricao inscricoes[]) {

  FILE *fp;
  fp = fopen("./Inscricoes.bin", "rb");
  if (fp == NULL) {
    printf("\n\033[34;4m Erro ao abrir arquivo! Caminho ""inexistente!\033\n[0m\n");
    exit(1);
  }

  fread(inscricoes, sizeof(struct inscricao), 1000, fp);
  printf("Arquivo Inscricoes.bin carregado\n");
  fclose(fp);
}

// Salva os dados dos vetores nos arquivos
void salvarDados(struct aluno alunos[], struct professor professores[], struct turma turmas[], struct inscricao inscricoes[]) {

  // Salva os dados do vetor alunos no arquivo alunos
  FILE *arquivoAlunos;
  arquivoAlunos = fopen("./Alunos.bin", "wb");
  if (arquivoAlunos == NULL) {
    printf("\n\033[34;4mErro ao abrir o arquivo! Caminho não ""existe!\033\n[0m\n");
  } else {
    printf("\n\033[32;4m→Alunos Salvos←\033\n[0m \n");

    int alunosCadastrados = 0;
    for (int i = 0; alunos[i].nomeAluno[0] != '\0'; i++) {
      alunosCadastrados++;
    }

    fwrite(alunos, sizeof(struct aluno), alunosCadastrados, arquivoAlunos);
    for (int i = 0; i < alunosCadastrados; i++) {
      if (alunos[i].idAluno != -1)
        printf("%d ", alunos[i].idAluno);
    }
    fclose(arquivoAlunos);
  }

  // Salva os dados do vetor Professores no arquivo Professores
  FILE *arquivoProfessores;
  arquivoProfessores = fopen("./Professores.bin", "wb");
  if (arquivoProfessores == NULL) {
    printf("\n\033[34;4m Erro ao abrir o arquivo! Caminho não ""existe!\033\n[0m\n");
  } else {
    printf("\n\033[102;1m→Professores Salvos←\033\n[0m \n");

    int professoresCadastrados = 0;
    for (int i = 0; professores[i].nomeProfessor[0] != '\0'; i++) {
      professoresCadastrados++;
    }

    fwrite(professores, sizeof(struct professor), professoresCadastrados,
           arquivoProfessores);
    for (int i = 0; i < professoresCadastrados; i++) {
      if (professores[i].idProfessor != -1)
        printf("%d ", professores[i].idProfessor);
    }
    fclose(arquivoProfessores);
  }

  // Salva os dados do vetor Turmas no arquivo Turmas
  FILE *arquivoTurmas;
  arquivoTurmas = fopen("./Turmas.bin", "wb");
  if (arquivoTurmas == NULL) {
    printf("\n\033[34;4mErro ao abrir o arquivo! Caminho não "
           "existe!\033\n[0m\n");
  } else {
    printf("\n\033[102;4m→Turmas Salvas←\033\n[0m \n");

    int turmasCadastradas = 0;
    for (int i = 0; turmas[i].diaSemanaTurma[0] != '\0'; i++) {
      turmasCadastradas++;
    }

    fwrite(turmas, sizeof(struct turma), turmasCadastradas, arquivoTurmas);
    for (int i = 0; i < turmasCadastradas; i++) {
      if (turmas[i].idTurma != -1)
        printf("%d ", turmas[i].idTurma);
    }
    fclose(arquivoTurmas);
  }

  // Salva os dados do vetor Inscricoes no arquivo Inscricoes
  FILE *arquivoInscricoes;
  arquivoInscricoes = fopen("./Inscricoes.bin", "wb");
  if (arquivoInscricoes == NULL) {
    printf("\n\033[41;4mErro ao abrir o arquivo! Caminho não ""existe!\033\n[0m\n");
  } else {
    printf("\n\033[42;4m→Inscrições Salvas←\033\n[0m \n");

    int inscricoesFeitas = 0;
    for (int i = 0; inscricoes[i].situacaoInscricao != 0; i++) { 
      inscricoesFeitas++;
    }

    fwrite(inscricoes, sizeof(struct inscricao), inscricoesFeitas, arquivoInscricoes);
    for (int i = 0; i < inscricoesFeitas; i++) {
      if (inscricoes[i].idInscricao != -1)
        printf("%d ", inscricoes[i].idInscricao);
    }
    fclose(arquivoInscricoes);
  }
}