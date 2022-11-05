#include<iostream>
#include<vector>
#include<math.h>

using namespace std;


class Z_order
{
    int order = 0;
    
    // dimentions
    int d = 0;

    // quantity of size matrix
    int n = 0;

    vector<int> zorder;

    public:

        Z_order(int order, int dimention)
        {
            this->order = order;
            this->n = pow(2, order);
            this->d = dimention;
        }

        string stob(int num, int size_b)
        {

            string str;
            while (num) {
                if (num & 1) // 1
                str = '1' + str;
                else // 0
                str = '0' + str;
                num >>= 1; // Right Shift by 1
            }

            str.insert(str.begin(), size_b - str.size(), '0');
            return str;
        }

        int btod(string n)
        {
            string num = n;
            int dec_value = 0;

            // Initializing base value to 1, i.e 2^0
            int base = 1;

            int len = num.length();
            for (int i = len - 1; i >= 0; i--) {
                if (num[i] == '1')
                dec_value += base;
                base = base * 2;
            }

            return dec_value;
        }

        int convert_value(int value)
        {

            string value_s = stob(value, d*order);

            string segmentation_bits[d];

            int init = 0;
            for(int i = 0; i < this->d; i++, init+= order) // iteration by dimention
                segmentation_bits[i] = value_s.substr(init, order);
                    
            string new_value;

            for(int i = order -1; i >= 0; i--) // iteration by bit
                for(int j = this->d - 1; j >= 0; j--) // iteration by dimention
                    new_value = segmentation_bits[j].substr(i,1) + new_value;
            return btod(new_value);
        }

        void generate_z_order_curve(int *matrix_n, int n_m)
        {
            cout << "[!] Generating Z Order Curve...\n"; 
            
            for(int i = 0; i < n_m; i++)
                zorder.push_back(convert_value(matrix_n[i]));
            cout << "[+] Z Order Curve Generated...\n"; 
        }

        void get_close2d(int i, int j){
            cout << endl;
            //cout << "n " <<n*n << endl;
            //for(int i = 0; i < n*n; i++){cout << zorder[i] << " ";}
            cout << endl;
            cout << "your query is:" << endl;
            //cout << zorder;
            if(i >= 1)
                cout << zorder[(i-1) * n + j] << endl;
            else
                cout << "no close data minimun reached!" << endl;
            if (i < n)
                cout << zorder[(i+1) * n + j] << endl;
            else
                cout << "no close data minimun reached!" << endl;
            if (j >=1) 
                cout << zorder[i * n + (j-1)] << endl;
            else
                cout << "no close data minimun reached!" << endl;
            if (j < n)
                cout << zorder[i * n + (1+ j)] << endl;
            else
                cout << "no close data minimun reached!" << endl;
        }

        void query2d(int a, int b)
        {
            cout << "\n[+] Querying..."<< "\n";

            int x0, x1, y0, y1;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    if(zorder[i * n + j] == a)
                    {
                        x0 = i;
                        y0 = j;
                    }
                    if(zorder[i * n + j] == b)
                    {
                        x1 = i;
                        y1 = j;
                    }
                }
            }

            for(int i = x0; i <= x1; i++)
            {
                for(int j = y0; j <= y1; j++)
                    cout << "\t" <<zorder[i*n + j] ;
                cout << "\n";
            }
            cout << endl;
        }

        void query_min_max(int a, int b)
        {
            
            cout << "\n[+] Querying..."<< "\n";

            for(int i = 0; i < pow(n, d); i++)
                if(zorder[i] >=a and zorder[i]<=b)
                    cout << zorder[i] << " ";
            cout << endl;
        }

        void print_z_order()
        {
            cout << "\n" << "[+] --- Z-ORDER-CURVE --- " << endl;

            cout << "y";
            for(int i = 0; i < n; i ++)
                cout << '\t' << i;
            cout << endl<< "x" <<  endl;
            
            for(int i = 0; i < n; i ++)
            {   
                cout << i;
                for(int j = 0; j < n; j++)
                    cout << '\t' << zorder[i * n + j];
                cout << endl;
            }
            cout << endl;
        }

        void print_n_d()
        {
            for(int i = 0; i < pow(n, d); i++)   
                cout <<  zorder[i] << " ";
            cout << endl;
        }
};

int main()
{
    int n = 8;

    int array1[n*n];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            array1[i * n +j] = i * n +j; 

    Z_order zo1(3, 2);
    zo1.generate_z_order_curve(array1, pow(n, 2));
    zo1.print_z_order();

    zo1.query_min_max(41,57);
    zo1.query2d(15,63);
    zo1.get_close2d(3,5);
    // int m = 2;
    // int s = pow(m, 3);
    // int array2[s];

    // for(int i = 0; i < pow(m, 3); i++)
    //     array2[i] = i;

    // Z_order zo2(1, 3); 
    // zo2.generate_z_order_curve(array2, pow(m,3));
    // zo2.print_z_order();
    // zo2.print_n_d();
}