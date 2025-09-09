#include <iostream>

using namespace std;

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

    int range_l = 1 + explore_l(m, n, matriz, i, j);
    int range_c = 1 + explore_c(m, n, matriz, i, j);

    if(range_l > range_c){
        if(range_c == 1) return range_l;
        b = range_l;

        int reduced = 0;

        for(int nl = 1; nl < range_c; nl++){
            int range_nl = 1 + explore_l(m, n, matriz, i + nl, j);
            if(range_nl >= b && reduced == 0) h = nl + 1;
            else
            {
                int temp_b = range_nl;
                int temp_h = nl + 1;

                if(reduced != 0)
                {
                    if(temp_b > reduced) temp_b = reduced;
                }

                if(temp_b*temp_h > b*h)
                {
                    b = temp_b;
                    h = temp_h;
                }

                reduced = temp_b;
            }
        }

        if(range_l > b*h) return range_l;

    }else{
        if(range_l == 1) return range_c;
        h = range_c;

        int reduced = 0;

        for(int nc = 1; nc < range_l; nc++){
            int range_nc = 1 + explore_c(m, n, matriz, i, j + nc);
            if(range_nc >= h && reduced == 0) b = nc + 1;
            else
            {
                int temp_b = nc + 1;
                int temp_h = range_nc;

                if(reduced != 0)
                {
                    if(temp_h > reduced) temp_h = reduced;
                }

                if(temp_b*temp_h > b*h)
                {
                    b = temp_b;
                    h = temp_h;
                }

                reduced = temp_h;
            }
        }

        if(range_c > b*h) return range_c;
    }

    return b*h;
}

int main()
{
    const int M = 4;
    const int N = 5;
    int matrix[M][N] = {
        {1,0,1,0,0},
        {1,0,1,1,1},
        {1,1,1,1,1},
        {1,0,0,1,0}
    };

    cout << "Entrada: " << endl;
    print_array(M, N, (int*)matrix);

    int m_area = 0;

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(matrix[i][j] == 1){
                int a = explore(M, N, (int*)matrix, i, j);
                if(a > m_area) m_area = a;
            }
        }
    }

    cout << "Maior Area: " << m_area << endl;

    return 0;
}
