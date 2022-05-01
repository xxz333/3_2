#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
//��������
const int row_num_1 = 22;
const int row_num_2 = 8;
int row_n_1 = row_num_1;//��Ԫ��
int row_n_2 = row_num_2;//����Ԫ��
int col_num = 130;//��������
//���ڴ�Ŷ����ʮ���Ƶ���Ԫ�Ӻͱ���Ԫ��
int** a, ** b;
void malloc_ab();
//�����ݶ����ڴ�
void read_data(string file_name, int **x);
//������ת��Ϊ��������ʽ�洢
unsigned int** bin_a;
unsigned int** bin_b;
int bin_col_num;//�洢���������ľ�������   �磺��һ�е�130������Ϊ32+32+32+32+2��5��4Byte����ʽ���洢����bin_col_num=5;
void malloc_ab_bin();
//��ʮ������תΪ�����ƴ洢 eg.5->100000����һλΪ1�ʹ���������λλ����ͬ��ʮ��������ֵ
void dec_to_bin(int** x, unsigned int** bin_x, int row_num);
//����������תΪʮ����
void bin_to_dec(int** x, vector<unsigned int*> bin_v);
//�洢������ת��Ϊʮ���ƵĽ��
int** a1, ** b1;
void malloc_a1b1();
//��������ڴ����ͷ�
void d_mem();
//����Ԫ�Ӻͱ���Ԫ�б��浽vector��
vector<unsigned int*> bin_a_v;
vector<unsigned int*> bin_b_v; 
//�ҵ�һ�����׸�����Ԫ��λ��(bin_a/bin_b)
int find_first(unsigned int* k);
//�������м����ȥ����
void handle_one(unsigned int *k1,unsigned int *k2, int n_bei, bool& judge1,bool& judge2);
//�鿴����Ԫ�������Ƿ������λ�ö�Ӧ����Ԫ��
bool equal_loc(int first_1_loc);
//�ҵ�����Ԫ�в��뵽��Ԫ����ʱ�Ĳ���λ��
int find_insert_loc(int& loc);
bool cmp1(unsigned int* a1, unsigned int* a2)
{
    if (a1[0] > a2[0])
        return true;
    else
        return false;
}

int main()
{
    //��ȡ�ļ��е�����
    string str1 = "��Ԫ��.txt";
    string str2 = "����Ԫ��.txt";
    malloc_ab();
    read_data(str1, a);
    read_data(str2, b);
    //������ת��Ϊ��������ʽ�洢
    malloc_ab_bin();
    dec_to_bin(a, bin_a, row_num_1);
    dec_to_bin(b, bin_b, row_num_2);
    //����Ԫ�Ӻͱ���Ԫ�б��浽vector��
    bin_a_v.insert(bin_a_v.begin(), bin_a, bin_a + row_num_1);
    bin_b_v.insert(bin_b_v.begin(), bin_b, bin_b + row_num_2);
    //����ÿ������Ԫ�У�����������Ԫ��,��һ����Ԫ����֮���������
    for (int i = 0; i < bin_b_v.size(); i++)   
    //for (int i = 0; i < 1; i++)
    {
        
        for (int j = 0; j < bin_a_v.size(); j++)
        //for (int j = 0; j < 1; j++)
        {
            //�ڽ�ԭ���ı���Ԫ�б�Ϊ��Ԫ��ʱ����
            int n_1 = find_first(bin_b_v[i]);
            int n_2 = find_first(bin_a_v[j]);
            //cout<< j << " " << find_first(bin_a_v[21]) << endl;
            //�жϴ�ʱ��Ԫ���뱻��Ԫ�е���Ԫ���Ƿ�λ��ͬһλ��
            if (n_1==n_2)//λ��ͬһλ��
            {
                //cout << i << " " << j << endl;
                bool judge1 = false, judge2 = false;
                handle_one(bin_a_v[j], bin_b_v[i], i ,judge1,judge2);//���м������ȥ
                if (judge1 == true)//����ֱ��������һ��
                    break;
                if (judge2 == true)
                {
                    /*
                    for (int k = 0; k < i; k++)
                    {
                        //�Ե�k�к͵�i�н�����Ԫ����
                        int n_11 = find_first(bin_b_v[k]);
                        int n_22 = find_first(bin_b_v[i]);
                        if (n_11 == n_22)
                        {
                            judge2 = false;
                            handle_one(bin_b_v[i], bin_b_v[k], k, judge1, judge2);
                        }
                    }*/
                    break;
                }
            }
        }
        //����
        //sort(bin_a_v.begin(), bin_a_v.end(), cmp1);
        //sort(bin_b_v.begin(), bin_b_v.end(), cmp1);
    }
    //������������תΪʮ������ʽ�洢
    malloc_a1b1();
    bin_to_dec(b1, bin_b_v);
    bin_to_dec(a1, bin_a_v);
    cout << "����Ԫ��" << endl;
    for (int i = 0; i < bin_b_v.size(); i++)
    {
        for (int j = 0;; j++)
        {
            if (b1[i][j] == -1)
                break;
            else
                cout << b1[i][j] << " ";
        }
        cout << endl;
    }
    /*
    cout << "��Ԫ��" << endl;
    for (int i = 0; i < bin_a_v.size(); i++)
    {
        for (int j = 0;; j++)
        {
            if (a1[i][j] == -1)
                break;
            else
                cout << a1[i][j] << " ";
        }
        cout << endl;
    }
    */
    //�ڴ��ͷ�
    d_mem();
}

void malloc_ab()
{
    //����ռ�洢ԭʼ����
    a = new int* [row_num_1];
    b = new int* [row_num_2];
    for (int i = 0; i < row_num_1; i++)
        a[i] = new int[col_num];
    for (int i = 0; i < row_num_2; i++)
        b[i] = new int[col_num];
}
void read_data(string file_name, int **x)
{
    ifstream ifs(file_name, ifstream::in);
    string str;
    int row_num_now = 0;
    while (getline(ifs, str))
    {
        int intS[200];
        //int i = 0;//ĳ������λ��
        int num = 0;//һ���е�������Ŀ
        int len = str.length();
        int len_temp = 0;
        string temp[200];
        for (; len_temp < len; )
        {
            while (str[len_temp] != ' ' && len_temp < len)
            {
                temp[num] += str[len_temp];
                len_temp++;
            }
            //��string���͵�tempת��Ϊint����
            intS[num] = atoi(temp[num].c_str());
            num++;
            len_temp++;
        }
        for (int i = 0; i < num; i++)
            x[row_num_now][i] = intS[i];
        x[row_num_now][num] = -1;//������
        row_num_now++;
    }
    ifs.close();
}
void malloc_ab_bin()
{
    //����ռ�
    bin_a = new unsigned int* [row_num_1];
    bin_b = new unsigned int* [row_num_2];
    if ((col_num % 32) == 0)
        bin_col_num = col_num / 32;
    else
        bin_col_num = col_num / 32 + 1;
    for (int i = 0; i < row_num_1; i++)
        bin_a[i] = new unsigned int[bin_col_num];
    for (int i = 0; i < row_num_2; i++)
        bin_b[i] = new unsigned int[bin_col_num];
    //��ʼ��Ϊ0
    for (int i = 0; i < row_num_1; i++)
    {
        for (int j = 0; j < bin_col_num; j++)
            bin_a[i][j] = 0;
    }
    for (int i = 0; i < row_num_2; i++)
    {
        for (int j = 0; j < bin_col_num; j++)
            bin_b[i][j] = 0;
    }
}
void dec_to_bin(int** x, unsigned int** bin_x, int row_num)
{
    for (int i = 0; i < row_num; i++)
    {
        int temp1;
        int temp2;
        int j = 0;
        while (x[i][j] != -1)
        {
            //bin_x[i][temp1]+=1(������temp2��0)->������ʱ����Ϊ1������������tempλ
            temp1 = bin_col_num - 1 - x[i][j] / 32;
            temp2 = x[i][j] % 32;
            unsigned int temp3 = 1;
            temp3 <<= temp2;
            bin_x[i][temp1] += temp3;
            j++;
        }
    }
}
bool cmp(int x,int y)
{
    return x>y;
}
void bin_to_dec(int** x, vector<unsigned int*> bin_v)
{
    for (int i = 0; i < bin_v.size(); i++)
    {
        int num = 0;//ÿһ�д洢�����ĸ���
        for (int j = 0; j < bin_col_num; j++)
        {
            int mov_num = 0;//ÿ��bin_x�����е��������ƶ���λ��
            while (bin_v[i][j] != 0)
            {
                if (bin_v[i][j] & 1)//��ǰλ��ֵΪ1
                {
                    int t = 32 * (bin_col_num - j - 1) + mov_num;//��ǰλ�ö�Ӧ��ʮ��������ֵ
                    x[i][num] = t;
                    num++;//����ѭ���󣬸��д洢��num��ֵ
                }
                //����
                bin_v[i][j] >>= 1;
                mov_num++;
            }
        }
        //������һ�н�������
        sort(x[i], x[i] + num, cmp);
        //��ÿ�к��һ������-1��λ����Ϊ�����ı�ʶλ
        x[i][num] = -1;
    }
}
void malloc_a1b1()
{
    a1 = new int* [bin_a_v.size()];
    b1 = new int* [bin_b_v.size()];
    for (int i = 0; i < bin_a_v.size(); i++)
        a1[i] = new int[col_num+1];
    for (int i = 0; i < bin_b_v.size(); i++)
        b1[i] = new int[col_num+1];
}
void d_mem()
{
    for (int i = 0; i < row_num_1; i++)
    {
        delete[]a[i];
        delete[]bin_a[i];
        delete[]a1[i];
    }    
    delete[]a;
    delete[]bin_a;
    delete[]a1;
    for (int i = 0; i < row_num_2; i++)
    {
        delete[]b[i];
        delete[]bin_b[i];
        delete[]b1[i];
    }    
    delete[]b;
    delete[]bin_b;
    delete[]b1;
}

int find_first(unsigned int* k)
{
    int pos_n = -1;
    for (int i = 0; i < bin_col_num; i++)
    {
        if (k[i] != 0)
        {
            unsigned int temp = k[i];
            int n = 0;
            //���������ƣ�ֱ��Ϊ0������ȷ����һ��1����λ��
            while (temp != 0)
            {
                temp >>= 1;
                n++;
            }
            pos_n = 32 * (i + 1) - n - 30;
            break;
        }
    }
    return pos_n;
}

void handle_one(unsigned int* k1, unsigned int* k2,int n_bei,bool& judge1,bool& judge2)//k1->��Ԫ��,k2->����Ԫ��
{
    //ͨ��������������Ԫ
    //for (int i = 0; i < bin_col_num; i++)
       // k2[i] = k1[i] ^ k2[i];
    //��������ʱ����������k1��k2�е�ֵ
    //cout << find_first(k1) << " " << find_first(k2) << endl;
    unsigned int* temp_k1 = new unsigned int[bin_col_num];
    unsigned int* temp_k2 = new unsigned int[bin_col_num];
    for (int i = 0; i < bin_col_num; i++)
    {
        temp_k1[i] = k1[i];
        temp_k2[i] = k2[i];
        k2[i] = 0;
    }
    for (int i = 0; i < bin_col_num; i++)
    {
        int mov_time = 0;
        unsigned int tem;
        while (temp_k1[i] != 0||temp_k2[i] != 0)
        {
            tem = (temp_k1[i] & 1) ^ (temp_k2[i] & 1);
            if (tem == 1)
            {
                tem <<= mov_time;
                k2[i] += tem;
            } 
            temp_k1[i] >>= 1;
            temp_k2[i] >>= 1;
            mov_time++;
        }
    }

    //cout << find_first(k2) << endl;
    //��Ԫ��Ĵ���
    //��Ԫ��1������Ԫ�б�Ϊ0->����
    //        2������Ԫ������û�ж�Ӧ����Ԫ��->����Ϊ��Ԫ�ӣ�����Ϊ����Ԫ�У�
    
    bool j1 = false;
    for (int i = 0; i < bin_col_num; i++)
    {
        if (k2[i] != 0)
        {
            j1 = true;
            break;
        }
    }
    if (j1 == false)//�ñ���Ԫ��Ϊ0->����
    {
        bin_b_v.erase(bin_b_v.begin() + n_bei, bin_b_v.begin() + n_bei + 1);
        row_n_2--;
        judge1 = true;
        //sort(bin_b_v.begin(), bin_b_v.end(), cmp1);
    }
    int bei_first_1_loc = find_first(bin_b_v[n_bei]);
    
    if (equal_loc(bei_first_1_loc) == false)//����Ԫ������û�ж�Ӧ����Ԫ��
    {
        //�Ѹñ���Ԫ��bin_b_v[n_bei]��Ϊ��Ԫ��
        //�ҵ�����Ӧ�ò��뵽��λ��
        int l = find_insert_loc(bei_first_1_loc);//��Ԫ���ǰ����׸�����Ԫ������λ�ô�С�����źõ�
        bin_a_v.insert(bin_a_v.begin() + l, bin_b_v[n_bei]);
        row_n_1++;
        //�����дӱ���Ԫ����ɾ��
        //bin_b_v.erase(bin_b_v.begin() + n_bei, bin_b_v.begin() + n_bei + 1);
        //row_n_2--;  
        /*
        for (int i = 0; i < n_bei; i++)
        {
            //�Ե�i�к͵�n_bei�н�����Ԫ����
            int n_1 = find_first(bin_b_v[i]);
            int n_2 = find_first(bin_b_v[n_bei]);
            if (n_1 == n_2)
            {
                handle_one(bin_b_v[n_bei], bin_b_v[i], i, judge1, judge2);
            }
        }
        */
        //sort(bin_b_v.begin(), bin_b_v.end(), cmp1);
        judge2 = true;
    }
}
bool equal_loc(int first_1_loc)
{
    int judge = false;
    //������Ԫ��
    for (int ui = 0; ui < bin_a_v.size(); ui++)
    {
        if (first_1_loc == find_first(bin_a_v[ui]))
        {
            judge = true;
            break;
        }            
    }
    return judge;
}
int find_insert_loc(int& loc)
{
    int lll = -1;
    for (int i = 0; i < row_n_1; i++)
    {
        if (find_first(bin_a_v[i]) < loc)
        {
            lll = i + 1;
        }
    }
    if (lll == -1)
        lll = row_n_1;
    return lll;
}