/* EXERCÍCIO PROGRAMA DE CALCULO NUMÉRICO - ENGENHARIA DE TELECOMUNIÇÕES
 * PROFESSOR: GLAUBER CINTRA                ENTREGA: 09/05/2022
 * INTEGRANTES(ORDEM ALFABÉTICA):           MATRÍCULA:
 * DAVISON LUCAS MENDES VIANA               20211015020050
 * JOÃO EDER SANTOS DA SILVA                20201015030075
 * GABRIEL LEAL                             20152015030383
 * VIVIANE PINTO DE SOUZA                   20191015030260                  */


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

FILE *f;

void menu();
void sistemalinear();
void equacaoalgebrica();
void abrir_arq();
void fechar_arq();
double **criaMatriz(int l, int c);
void leMatriz(double **m, FILE *file, int n);
void exibeMatriz(double **m, int l, int c);
int criterioLinhasColunas(double **m, int n);
double *criarVetor(int n);
void gaussSeidel(double **m, int n);
double lagrange(int grau, double *coeficientes);
double encontraK(int grau, double *coeficientes);
double encontraB(int grau, double *coeficientes);
void inverteSinal(int n, double *v);
void *derivarPolinomio(int grau, double *coeficientes, double *derivada);
void newton(double x0, int grau, double *coeficiente, double *derivada);
void conversor_octal(double input);
void conversor_binario(double input);
void conversor_hexadecimal(double input);
void alfa_hexa(int input);
void convesao();


int main() {
    menu();
    return 0;
}

void menu(){

    char op, op2, op3;

    do {
        printf("\nPara utilizar o exercicio programa, escolha uma das opcoes abaixo:\n");
        printf("C - Conversao\nS - Sistema Linear\nE - Equacao Algebrica\n");
        printf("F - Finalizar\n");

        scanf(" %c", &op);
        op2 = toupper (op);

        switch (op2) {
            case 'C':
                convesao();
                break;
            case 'S':
                sistemalinear();
                break;
            case 'E':
                equacaoalgebrica();
                break;
            case 'F':
                printf("Finalizando programa...\n");
                op3 = 'F';
                break;
            default:
                printf("Digite uma opçao valida.\n");
        }

        if(op2 != 'F'){
            printf("\nFazer nova consulta? (S/N)\n");
            scanf(" %c", &op);
            op2 = toupper (op);
        }

    } while (op2 != 'N' && op3 != 'F');
}


//-------------------------------------------------------------------------------------------------------------------//
/* Funções utilizadas para resolver a opção C - conversão.                                                           */
void convesao(){
    double input;

    printf("O valor a ser convertido: ");
    scanf("%lf",&input); // Lendo o valor a ser convertido
    conversor_binario(input);
    printf("\n");
    conversor_octal(input);
    printf("\n");
    conversor_hexadecimal(input);
}

void conversor_octal(double input){

    //double input ;		//Entrada
    int a;  			//Parte inteira
    double b,aux2; 			// Parte fracionária
    int aux1;
    int conti = 0,contf = 0;
    int v[32];			// Armazena os valores inteiros.
    int w[32];			// Armazena os valores fracionarios.
    bool keyi = true,keyf = true;

    a = (int)input;         //valor inteiro
    b = input- a;//valor fracionário

/*            conversão parte inteira                            */

    while (keyi){
        if(a >= 8){
            v[conti] = a%8;		//pega o resto da divisão.
            a = a/8;
            conti++;
        }
        else{
            v[conti] = a;
            keyi = false;       //fim do laço
        }
    }

/*          conversão parte fracionária                           */


    for (int x = 0;x<20;x++){

        b = b*8;
        aux1 = (int)b;
        aux2 = b - (double )aux1; //Parte fracionária da multiplicação
        w[contf] = aux1;
        b = aux2;
        contf++;

    }

    for (int i = conti; i>=0 ;i--){
        printf("%d",v[i]);
    }

    printf(",");

    for (int j = 0; j<contf;j++){
        printf("%d",w[j]);
    }

}

void conversor_binario(double input){

    //double input ;		//Entrada
    int a;  			//Parte inteira
    double b,aux2; 			// Parte fracionária
    int aux1;
    int conti = 0,contf = 0;
    int v[32];			// Armazena os valores inteiros.
    int w[32];			// Armazena os valores fracionarios.
    bool keyi = true,keyf = true;


    a = (int)input;         //valor inteiro
    b = input-a;//valor fracionário

/*            conversão parte inteira                            */

    while (keyi){
        if(a >= 2){
            v[conti] = a%2;		//pega o resto da divisão.
            a = a/2;
            conti++;
        }
        else{
            v[conti] = 1;
            keyi = false;       //fim do laço
        }
    }

/*          conversão parte fracionária                           */


    for (int x = 0;x<20;x++){

        b = b*2;
        aux1 = (int)b;
        aux2 = b - (double )aux1; //Parte fracionária da multiplicação
        w[contf] = aux1;
        b = aux2;

        contf++;

    }

    for (int i = conti; i>=0 ;i--){
        printf("%d",v[i]);
    }

    printf(",");

    for (int j = 0; j<contf;j++){
        printf("%d",w[j]);
    }


}

void conversor_hexadecimal(double input){

    //double input ;		//Entrada
    int a;  			//Parte inteira
    double b,aux2; 			// Parte fracionária
    int aux1;
    int conti = 0,contf = 0;
    int v[32];			// Armazena os valores inteiros.
    int w[32];			// Armazena os valores fracionarios.
    bool keyi = true,keyf = true;
    int restodiv=0 ;

    a = (int) input;         //valor inteiro
    b = input-(double )a;//valor fracionário

/*            conversão parte inteira                            */

    while (keyi){
        if(a >= 16){
            restodiv = a%16;
            v[conti] =restodiv;
            a = a/16;
            conti++;
        }
        else{
            v[conti] =a;
            keyi = false;       //fim do laço
        }
    }

/*          conversão parte fracionária                           */


    for (int x = 0;x<20;x++){
        b = b*16;
        //printf("iteração : %d -  b :%f - ",contf,b);
        aux1 = (int) b;
        //printf("-  aux1 : %d - ",aux1);
        aux2 = b - (double )aux1; //Parte fracionária da multiplicação
        //printf("-  aux2 : %f - ",aux2);
        w[contf] = aux1;
        b = aux2;
        //printf("-  w[contf] : %d  ",	w[contf]);
        //printf("\n");
        contf++;

    }


    for (int i = conti; i>=0 ;i--){
        alfa_hexa(v[i]);
        //printf("%d",v[i]);
    }

    printf(",");

    for (int j = 0; j<contf;j++){
        alfa_hexa(w[j]);
        //printf("%d",w[j]);
    }

}

void alfa_hexa(int input){
    if (input == 10){
        printf("A");
    }else if(input == 11){
        printf("B");
    }else if(input == 12){
        printf("C");
    }else if(input == 13){
        printf("D");
    }else if(input == 14){
        printf("E");
    }else if (input == 15){
        printf("F");

    }else{
        printf("%d",input);
    }
}


//-------------------------------------------------------------------------------------------------------------------//
/* Funções para resolver a opção S - Sistema linear. Lê um arquivo de texto contendo um sistema linear de n
 * equações e n variáveis. O lay-out foi previamente definido no exercício programa. Uso um arquivo
 * nomeado = "sistemalinear.txt".                                                                                    */
void sistemalinear(){
    /* Esta função exige um arquivo de texto "sistemalinear.txt" de lay-out
     * previamente estabelecido nas normas do exercício programa.           */

    double **m;
    char primeiroCharDoArquivo;
    int n;
    int criteriolinhascolunas;

    abrir_arq();
    primeiroCharDoArquivo = fgetc(f);
    n = primeiroCharDoArquivo - '0';
    printf("%d", n);
    m = criaMatriz(n, n+1);
    leMatriz(m, f, n);
    exibeMatriz(m, n, n+1);
    criteriolinhascolunas = criterioLinhasColunas(m, n);
    if(criteriolinhascolunas == 0){
        gaussSeidel(m, n);
    }
    else{
        printf("O SL nao satisfaz nem o criterio das linhas");
        printf(" nem o criterio das colunas.\n");
    }
    fechar_arq();
}

int criterioLinhasColunas(double **m, int n){

    double sum = 0;
    double sum2 = 0;
    int countl = 0, countc = 0;

    //Critério das linhas
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(j == 0){
                sum = 0;
            }
            if(j != i){
                sum += fabs(m[i][j]);
            }
        }
        if(sum > fabs(m[i][i])){
            countl++;
        }
    }

    //Critério das Colunas
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(j == 0) {
                sum2 = 0;
            }
            if(j != i){
                sum2 += fabs(m[j][i]);
            }
        }
        if(sum2 > fabs(m[i][i])){
            countc++;
        }
    }

    if(countl != 0 && countc != 0){
        return 1;
    }

    return 0;
}

void gaussSeidel(double **m, int n){

    int k = 0;
    double somatorio, erro = 1;
    double **ma;
    double *mb;
    double *xi, *xant;

    /* Dividindo a matriz do SL em matrizes de coeficientes e vetor de termos
     * independentes.                                                           */
    ma = criaMatriz(n, n);
    mb = criarVetor(n);

    for (int i = 0; i < n; ++i) {
        mb[i] = m[i][n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ma[i][j] = m[i][j];
        }
    }

    /*Criando vetor para valores iniciais*/
    xi = criarVetor(n);
    for (int i = 0; i < n; ++i) {
        xi[i] = 0.0;
    }

    xant = criarVetor(n);
    for (int i = 0; i < n; ++i) {
        xant[i] = 0.0;
    }

    /* Serão feitas 1000 iterações*/
    while (k < 1000 && erro > 0.00000001){
        for (int i = 0; i < n; ++i) {
            xant[i] = xi[i];
            somatorio = 0;
            /* Somatorio de Ai,j * Xj */
            for (int j = 0; j < n; ++j) {
                if(j != i){
                    somatorio += ma[i][j]*xi[j];
                }
            }
            /*Aplicando o método*/
            xi[i] = (mb[i] - somatorio)/ma[i][i];
            erro = fabs(xi[i] - xant[i]);
        }
        k++;
    }

    printf("\nA soulucao do sistema linear:");
    for (int i = 0; i < n; ++i) {
        printf("\nX[%d] = %lf\n",i+1, xi[i]);
    }
    printf("\nForarm feitas %d iteracoes.\n", k);
}


//-------------------------------------------------------------------------------------------------------------------//
/* Funções para resolver a opção E - Equação Algébrica. Recebe um polinômio de grau n e usa o teorema de Lagrange
 * para encontrar intervalos para as raizes superiores e inferiores. Após isso, usa-se o método de Newton para
 * determinar uma aproximação para uma raiz.                                                                        */
void equacaoalgebrica(){

    int grau = 0;
    double *coeficientes;
    double *coeficientesDerivada;
    double x0;

    printf("\nDetermine o grau do polinomio:");
    scanf("%d", &grau);

    coeficientes = criarVetor(grau + 1);
    printf("\nDigite os coeficientes do polinomio(an > 0 && a0 != 0):");
    for (int i = 0; i < grau + 1; ++i) {
        double valor;
        scanf("%lf", &valor);
        coeficientes[i] = valor;
    }

    x0 = lagrange(grau, coeficientes);

    coeficientesDerivada = criarVetor(grau + 1);
    derivarPolinomio(grau, coeficientes, coeficientesDerivada);

    newton(x0, grau, coeficientes, coeficientesDerivada);
}

double lagrange(int grau, double *coeficientes){
    /*A função aplica o teorema de Lagrange em uma equação algébrica. Ela
    calcula os limites inferiores e superiores onde se encontram as raízes
    reais positivas e negativas.
    */

    int i;
    double grau_double = grau, K[4], B[4], an[4], limites[4];
    double *coeficientes_inverso, *coeficientes_ex_invertido, *coeficientes_ex_invertido_ex;
    coeficientes_inverso = criarVetor(grau + 1); //equação com os indices invertidos
    coeficientes_ex_invertido = criarVetor(grau +1); //equação com os expoentes impares invertidos
    coeficientes_ex_invertido_ex = criarVetor(grau +1); //equação invertida com os expoentes impares invertidos

    //obtém a equação com os indices invertidos

    for(i = 0; i <= grau ; i++){
        coeficientes_inverso[i] = coeficientes[grau-i];
    }

    printf("\n");
    printf("\nCoeficientes Inveritdos:");
    for(i = 0; i <= grau ; i++){
        printf("%10.2lf ", coeficientes_inverso[i]);
    }

    //obtém a equação com os expoentes impares invertidos
    for(i = 0; i <= grau ; i++){
        coeficientes_ex_invertido[i] = coeficientes[i];
        if(i%2 != 0 && i != 0){
            coeficientes_ex_invertido[i] = -coeficientes_ex_invertido[i];
        }
    }

    printf("\n");
    printf("\nSinais expoentes impares invertidos:");
    for(i = 0; i <= grau ; i++){
        printf("%10.2lf ", coeficientes_ex_invertido[i]);
    }

    //obtém a equação invertida com os expoentes impares invertidos
    for(i = 0; i <= grau ; i++){
        coeficientes_ex_invertido_ex[i] = coeficientes_ex_invertido[grau-i];
    }

    printf("\n");
    printf("\nCoeficientes invertidos e sinaeis dos expoentes impares invertidos:");
    for(i = 0; i <= grau ; i++){
        printf("%10.2lf ", coeficientes_ex_invertido_ex[i]);
    }


    /*if(coeficientes_inverso[0] < 0) inverteSinal(grau, (double *) &coeficientes_inverso);

    if(coeficientes_ex_invertido[0] < 0) inverteSinal(grau, (double *) &coeficientes_ex_invertido);

    if(coeficientes_ex_invertido_ex[0] < 0) inverteSinal(grau, (double *) &coeficientes_ex_invertido_ex);*/

    //calculando limite positivo
    // econtrando limite superior
    K[0] = encontraK(grau,coeficientes);
    B[0] = encontraB(grau,coeficientes);
    an[0] = coeficientes[0];
    limites[0] = 1.0 + pow(B[0]/an[0], 1.0/(grau_double-K[0]));

    // econtrando limite inferior
    K[1] = encontraK(grau,  coeficientes_inverso);
    B[1] = encontraB(grau,  coeficientes_inverso);
    an[1] = coeficientes_inverso[0];
    limites[1] = 1.0 / (1 + pow(B[1]/an[1], 1.0/(grau_double-K[1])));

    //calculando limite negativo
    // econtrando limite inferior
    K[2] = encontraK(grau, coeficientes_ex_invertido);
    B[2] = encontraB(grau, coeficientes_ex_invertido);
    an[2] = coeficientes_ex_invertido[0];
    limites[2] = -1.0*(1 + pow(B[2]/an[2], 1.0/(grau_double-K[2])));

    // econtrando limite superior
    K[3] = encontraK(grau, coeficientes_ex_invertido_ex);
    B[3] = encontraB(grau, coeficientes_ex_invertido_ex);
    an[3] = coeficientes_ex_invertido_ex[0];
    limites[3] = -1.0/(1 + pow(B[3]/an[3], 1.0/(grau_double-K[3])));

    //Mostra a respota
    printf("\nLimite Positivo: %3.4lf %c%c X+ %c%c %3.4lf \n", limites[1], 60, 61, 60, 61, limites[0]);
    printf("\nLimite Negativo: %3.4lf %c%c X- %c%c %3.4lf \n", limites[2], 60, 61, 60, 61, limites[3]);

    return limites[0];
}

double encontraK(int grau, double *coeficientes){
    /*Função que retorna o maior índice dentre os índices dos coeficientes
    negativos de uma equação algébrica.
    */
    int i;
    double aux = 0;
    for(i = 0; i < grau ; i++){// Achar raiz superior
        if(coeficientes[i] < 0){
            if(aux < grau - i){
                aux = grau - i;
            }
        }
    }
    return aux;
}

double encontraB(int grau, double *coeficientes){
    /*Função que retorna o módulo do menor coeficiente negativo de uma
    equação algébrica.
    */
    int i;
    double aux1 = 0;
    double modulo = -1;
    for(i = 0; i <= grau ; i++){
        if(coeficientes[i] < 0){
            if(aux1 > coeficientes[i]){
                aux1 = coeficientes[i];
            }
        }
    }
    return aux1*modulo;
}

void inverteSinal(int n, double *v){
    /*Função que modifica os vetores de coeficientes caso an < 0.
    */
    int j;
    for(j=n; j>=0; j--){
        v[j] = - v[j];
    }
}

void *derivarPolinomio(int grau, double *coeficientes, double *derivada){

    for (int i = 0; i < grau + 1; ++i) {
        derivada[i] = coeficientes[i] * (grau - i);
        scanf("lf", &derivada[i]);
    }
}

void newton(double x0, int grau, double *coeficiente, double *derivada){

    int k = 0;
    double x = x0;
    double *px, *dpx;
    double respx, resdpx;
    double x1, erro = 1;


    px = criarVetor(grau + 1);
    dpx = criarVetor(grau);

    for (int i = 0; i < grau + 1; ++i) {
        px[i] = coeficiente[i];
    }

    for (int i = 0; i < grau; ++i) {
        dpx[i] = derivada[i];
    }
    printf("\nOs coeficientes da derivada do polinomio:");
    for (int i = 0; i < grau; ++i) {
        printf("%10.3lf",dpx[i]);
    }

    while(k < 100 && erro > 0.00000001){

        respx = 0;
        for (int i = 0; i < grau + 1; ++i) {
            respx += px[i] * pow(x, grau - i);
        }

        resdpx = 0;
        for (int i = 0; i < grau; ++i) {
            resdpx += dpx[i] * pow(x, grau - 1 - i);
        }
        x1 = x - (respx/resdpx);
        erro = fabs(x - x1);
        x = x1;
        k++;
    }

    printf("\nA raiz do polinomio: %10.3lf", x1);
    printf("\nForarm feitas %d iteracoes usando o Glorioso metodo de Newton.\n", k);
}


//-------------------------------------------------------------------------------------------------------------------//
/* Funções para criar matrizes alocadas dinâmicamente a partir de
 * um arquivo de texto com lay-out previamente estabelecido no
 * exercicioPrograma.                                               */
double **criaMatriz(int l, int c) {
    /* Se houver memória suficiente, cria uma matriz de double com n linhas *
     * e n colunas e devolve um ponteiro para a matriz; Caso contrário,     *
     * devolve um ponteiro nulo.                                            */

    int i, j;
    double **m = NULL;

    m = malloc(sizeof (double *) * l);

    if(m == NULL){
        printf("\nMem\xF3rio insuficiente.\n");
        return NULL;
    }

    for (i = 0; i < l; ++i) {
        m[i] = malloc(sizeof (double) * c);
        if(m[i] == NULL){
            printf("\nMem\xF3ria insuficiente.\n");
            for (j = 0; j < i; ++j) {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
    }

    return m;

}

void leMatriz(double **m, FILE *file, int n) {
    /* Lê valores para a matriz M, que é uma matriz double com n linhas e   *
     * n colunas presente no arquivo de texto.                              */

    printf("\nInserindo os elementos da matriz aumentada...\n");

    while(!feof(f)){
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n+1; ++j) {
                fscanf(f, "%lf", &m[i][j]);
            }
        }
    }

    printf("\n");

}

void exibeMatriz(double **m, int l, int c) {
    /* Exibe o conteúdo de uma matriz de double com n linhas e n colunas    *
     * presente no arquivo.                                                 */

    for (int i = 0; i < l; ++i) {
        printf("|");
        for (int j = 0; j < c; ++j) {
            printf("%10.3lf", m[i][j]);
        }
        printf("\t|\n");
    }

    printf("\n");
}

double *criarVetor(int n) {
    /* Se houver memória suficiente, cria um vetor de doubles com   *
     * tamanho l. Caso contrário, devolve um ponteiro nulo.         */

    double *x;
    x = malloc(sizeof(double) * n);

    if (x == NULL) {
        printf("Não foi possivel criar o vetor!\n");
        return NULL;
    }

    return x;

}


/* ----------------------Funções para criar/ler e encerrar arquivos de texto------------------------------------------*/
void abrir_arq(){

    f = fopen("sistemalinear.txt","r+");
    if (f == NULL){
        f = fopen("sistemalinear.txt","w+");
        if(f == NULL){
            printf("\nNão foi possível criar o arquivo.\n");
            exit(1);
        }
    }
}

void fechar_arq(){
    fclose(f);
}