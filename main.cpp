#include <iostream>

using namespace std;

/*
    As operações de ponteiro foram realizadas utilizando uma abordagem aritmetica
    Foram alocadas areas de memoria, logo para acessar ou modificar um ponteiro devemos realizar uma operação matematica que retorna a posição dentro da area

    *((arr + i * n) + j) -> esta operação retorna uma referencia a posição do valor requisitado

    onde:   arr -> Matriz
            i -> posição da linha
            j -> posição da coluna
            n -> numero de linhas
*/

void print_array(const int &m, const int &n, int *matriz)
{
    for(int i = 0; i < m; i++)
    {
        cout << "[";
        for(int j = 0; j < n; j++)
        {
            cout << *((matriz + i * n) + j);
            if(j + 1 < n) cout << " ";
        }
        cout << "]" << endl;
    }
}

int explore_l(const int &m, const int &n, int *matriz, int i, int j)
{
    int jj = j + 1;

    if(jj < n)
    {
        int j_adj = *((matriz + i * n) + jj);
        if(j_adj == 1) return 1 + explore_l(m, n, matriz, i, jj);
    }

    return 0;
}

int explore_c(const int &m, const int &n, int *matriz, int i, int j)
{
    int ii = i + 1;

    if(ii < m)
    {
        int i_adj = *((matriz + ii * n) + j);
        if(i_adj == 1) return 1 + explore_c(m, n, matriz, ii, j);
    }

    return 0;
}

int explore(const int &m, const int &n, int *matriz, const int &i, const int &j)
{
    int b = 1;
    int h = 1;

    // Verificação maior direção possivel
    int range_l = 1 + explore_l(m, n, matriz, i, j);
    int range_c = 1 + explore_c(m, n, matriz, i, j);

    if(range_l > range_c){
        //Analise por linha
        if(range_c == 1) return range_l; // Caso particular, formação retangulo na linha
        b = range_l;

        int reduced = 0;

        for(int nl = 1; nl < range_c; nl++){
            int range_nl = 1 + explore_l(m, n, matriz, i + nl, j);
            if(range_nl >= b && reduced == 0) h = nl + 1; // Alcance se manteve na linha i + nl
            else
            {
                int temp_b = range_nl;
                int temp_h = nl + 1;

                // Verificação do sinalizador
                if(reduced != 0)
                {
                    if(temp_b > reduced) temp_b = reduced;  // Verificar se o alcance calculado é maior que o sinalizador de redução
                                                            // neste caso não podemos utilizar ele, para evitar uma area errada
                }

                if(temp_b*temp_h > b*h) // Verificação de aumento da area
                {
                    b = temp_b;
                    h = temp_h;
                }

                reduced = temp_b; // Atribuição do sinalizador de redução
            }
        }

        if(range_l > b*h) return range_l; // Caso particular, area menor que retangulo na linha

    }else{
        // Analise por coluna
        if(range_l == 1) return range_c; // Caso particular, formação retangulo na coluna
        h = range_c;

        int reduced = 0;

        for(int nc = 1; nc < range_l; nc++){
            int range_nc = 1 + explore_c(m, n, matriz, i, j + nc);
            if(range_nc >= h && reduced == 0) b = nc + 1; // Alcance se manteve na coluna j + nc
            else
            {
                int temp_b = nc + 1;
                int temp_h = range_nc;

                // Verificação do sinalizador
                if(reduced != 0)
                {
                    if(temp_h > reduced) temp_h = reduced;  // Verificar se o alcance calculado é maior que o sinalizador de redução
                                                            // neste caso não podemos utilizar ele, para evitar uma area errada
                }

                if(temp_b*temp_h > b*h) // Verificação de aumento da area
                {
                    b = temp_b;
                    h = temp_h;
                }

                reduced = temp_h; // Atribuição do sinalizador de redução
            }
        }

        if(range_c > b*h) return range_c; // Caso particular, area menor que retangulo na coluna
    }

    return b*h;
}

void parseToint(const int& m, const int& n, char* entry, int** result){
    *result = new int[m * n];

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(*((entry + i * n) + j) == '1') *((*result + i * n) + j) = 1;
            else *((*result + i * n) + j) = 0;
        }
    }
}

bool readData(int& m, int& n, char** result){

    cout << "Digite o numero de linhas da matriz booleana" << endl;
    cin >> m;

    cout << "Digite o numero de colunas que a matriz booleana" << endl;
    cin >> n;

    *result = new char[m * n]; //Reservando o bloco de memória necessario para armazenar a matriz de entrada

    cout << "Digite os valores [Linha 1]" << endl;

    char v;

    int i = 0;
    int j = 0;

    do
    {
        // A cada iteraçãoo o algoritmo verifica a validade da entrada e passa para a proxima coluna
        cin >> v;

        *((*result + i * n) + j) = v;
        j++;

        if(j > n - 1)
        {
            // Ao contemplar todas as colunas ele passa para a próxima linha
            j = 0;
            i++;
            cout << "Digite os valores [Linha " << i + 1 << "]" << endl;
        }
        if(i > m - 1)
        {
            // Ao finalizar a ultima linha ele retorna que a operação foi concluída
            return true;
        }
    }while(v == '1' || v == '0');

    // No caso de uma entrada invalida, o algoritmo finaliza
    return false;
}

int main()
{
    int m;
    int n;
    char* entry = nullptr;
    bool valid = readData(m, n, &entry);

    if(!valid)
    {
        cout << "Entrada errada da matriz";
        delete[] entry;

        return 0;
    }

    // Conversão da matriz [char*] para a nova matriz [int*]
    int* matrix = nullptr;
    parseToint(m, n, entry, &matrix);

    delete[] entry; // sempre limpar a memoria alocada...

    cout << "Entrada: " << endl;
    print_array(m, n, matrix);

    int m_area = 0;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(*((matrix + i * n) + j) == 1){
                int a = explore(m, n, (int*)matrix, i, j);
                if(a > m_area) m_area = a;
            }
        }
    }

    cout << "Maior Area: " << m_area << endl;

    delete[] matrix; // desalocar a memoria da matriz que foi trabalhada.
    return 0;
}
