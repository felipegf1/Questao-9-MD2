#include <stdio.h>
#include <stdlib.h>

void limpa_tela() {
    system("cls"); 
}

int exponenciacao(int base, int expoente) { // funçao feita porque em C nao existe exponenciação nativa
    int resultado = 1;                      // e usando a biblioteca o tipo de variavel poderia conflitar com os inteiros do meu codigo
    for (int i = 0; i < expoente; i++) {
        resultado *= base;
    }
    return resultado;
}

int verificar_primo(int n) {  // retorna 0 para positivo e 1 para negativo
    if (n <= 1) return 1;        // exclui o 0 e o 1 
    if (n == 2) return 0;        // considera o 2 , o unico primo par
    if (n % 2 == 0) return 1;    // e exclui todos numeros pares (divisiveis por 2)

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 1; // divisor encontrado, não é primo
    }
    return 0; 
}

int euclides(int a, int b) { //algoritmo de euclides para encontrar o MDC
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

int totiente(int n) { // funçao totiente de euler 
    int count = 0;
    for (int i = 1; i < n; i++) {
        if (euclides(i, n) == 1) {
            count++;
        }
    }
    return count;
}

int inverso(int a, int m) { // a = valor a ser invertido , m = modulo (Zn)
    int m_original = m;
    int x_antigo = 0, x_atual = 1;
    int quociente, resto;

    if (m == 1) {
        printf("Não existe inverso módulo 1.\n");
        return 0;
    }

    // Algoritmo de Euclides estendido
    while (a > 1) {
        quociente = a / m;
        resto = a % m;

        // Atualiza a e m
        a = m;
        m = resto;

        // Atualiza x_antigo e x_atual
        int temp = x_antigo;
        x_antigo = x_atual - quociente * x_antigo;
        x_atual = temp;
    }

    // Garante que o resultado esteja dentro de Zm: [0, m-1]
    x_atual = (x_atual % m_original + m_original) % m_original;

    printf("Inverso encontrado dentro de Zn\n", x_atual);
    return x_atual;
}


int main() { // nao coloquei muitos comentarios na main do codigo porque durante a execução coloquei muitos prints com o passo a passo
                // apenas especifiquei as etapas descritas no pdf caso facilite a sua avaliaçao
    int H, G, n, a, x, n1, mdc, inv, x1, x2, q, r, exp1, exp2, intermed2, intermed3, valor_final;
    printf("Digite os Valores de H , G e n para calcular a base a: "); // entradas do codigo
    scanf("%d %d %d", &H, &G, &n);
    printf("Digite o valor do expoente X e do modulo n1: ");
    scanf("%d %d", &x, &n1);

    mdc = euclides(G , n); // etapa 1 , se o mdc for diferente de 1 a justificativa está no else la embaixo do codigo

    if (mdc == 1){ // se G e n forem coprimos a execução começa
        limpa_tela();
        printf("\nAs variaveis escolhidas foram: H = %d, G = %d, n = %d, x = %d, n1 = %d\n", H, G, n, x, n1);
        
        printf("\n%d e %d sao primos entre si, Hora de calcular o Inverso de G! \n", G, n); // etapa 2 
        inv = inverso(G,n);
        if (inv == 0){
            return 0;
        }
        printf("Inverso = %d\n", inv);
        
        printf("\nHora de encontrar o valor de a\n"); //etapa 3
        a = (H * inv) % n;
        printf("Divisao feita, a = %d\n", a);
        
        printf("\nHora de testar se a e n1 sao coprimos: \n"); //etapa 4
        if(euclides(a,n1) == 1){        // se forem coprimos o codigo continua, caso contrario o aviso está no else após esse if
                                        // alertando que nao será possivel continuar com esses valores
            printf("Os dois sao coprimos!!\n");
            printf("\nHora de verificar se n1 e primo:\n");
            
            if(verificar_primo(n1) == 0){
                printf("n1 e primo, Vamos aplicar o pequeno teorema de Fermat\n"); //etapa 5 / 6 (n1 primo)
                x1 = n1 - 1;
                printf("x1 = n1 - 1. O valor de x1 sera: %d\n", x1);
                
                }else {
                    printf("n1 nao é primo, Vamos aplicar o teorema de Euler\n"); //etapa 5 / 7 (n1 nao primo)
                    x1 = totiente(n1);
                    printf("Usando a funcao totiente de Euler o valor de x1 sera: %d\n", x1);}
            q = x/x1;
            r = x%x1;
            printf("Apos aplicar o teorema da divisao, x = %d, x1 = %d, q = %d, r = %d\n",x, x1, q, r); // etapa 8 
            
            exp1 = exponenciacao(a,x) % n1;
            printf("\n a^x mod n1 = %d\n", exp1);

            exp2 = ((exponenciacao(exponenciacao(a,x1),q) % n1) * (exponenciacao(a,r) % n1)) % n1; // etapa 9
            printf("Agora reescrevendo a^x mod n1 em (((a^x1)^q mod n1)*(a^r mod n1))mod n1 = %d\n", exp2);
            
            printf("\nAgora calculando os valores intermediarios...\n"); // etapa 10
            x2 = exponenciacao(a,x1) % n1;
            printf("x2 = a^x1 mod n1 = %d\n", x2);
            
            intermed2 = exponenciacao(x2,q) % n1;
            printf("x2^q mod n1 = %d\n", intermed2);

            intermed3 = exponenciacao(a,r) % n1;
            printf("a^r mod n1 = %d\n", intermed3);
                
            printf("\n Agora combinando os resultados para o valor final da congruencia:\n"); //etapa 11
            valor_final = (exponenciacao(x2,q)*exponenciacao(a,r)) % n1;
            printf("((x2^q)*(a^r)) mod n1 = %d\n", valor_final);
        }else {
            printf("Eles nao sao coprimos, nao sera possivel usar Euler ou Fermat.\n"); // justificativa da etapa 4
        }
        
    } else {
        printf("Os valores %d e %d nao sao primos entre si, MDC = %d, a Divisao nao sera possivel", G, n, mdc); //justificativa da 1
    }
    return 0;
}
