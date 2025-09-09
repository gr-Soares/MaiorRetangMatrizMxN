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

    if(ii < n)
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

    int ii = i + 1;
    int jj = j + 1;

    int dr = 1 + explore_l(m, n, matriz, i, j);
    int db = 1 + explore_c(m, n, matriz, i, j);

    if(dr > db)
    {
        if(db == 1) return dr;

        for(int vb = 0; vb < db - 1; vb++)
        {
            int tb = b;
            int th = h;

            int cr = 1 + explore_l(m, n, matriz, ii + vb, j);
            if(cr >= dr)
            {
                tb = dr;
                th++;
            }
            else
            {
                tb = cr;
                int tth = th + 1;
                if(tth*tb > b*h) th = tth;
            }

            if(tb*th > b*h)
            {
                b = tb;
                h = th;
            }
        }

        if(dr > b*h) return dr;
    }
    else
    {
        if(dr == 1) return db;
        for(int vr = 0; vr < dr - 1; vr++)
        {
            int tb = b;
            int th = h;

            int cb = 1 + explore_c(m, n, matriz, i, jj + vr);
            if(cb >= db)
            {
                th = db;
                tb++;
            }
            else
            {
                tb = cb;
                int tth = th + 1;
                if(tth*tb > b*h) th = tth;
            }

            if(tb*th > b*h)
            {
                b = tb;
                h = th;
            }
        }

        if(db > b*h) return db;
    }
    return b*h;
}

int main()
{
    const int M = 4;
    const int N = 5;
    int matrix[M][N] = {
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
    };

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
