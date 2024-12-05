/*
thanh vien nhom:
Le Minh Sang - 072205001900
Nguyen Chi Thanh - 072205000038
Nguyen Hoai Linh - 082205014590
*/
// test

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

struct toa_do
{
    int x;
    int y;
};

void docdulieu(vector<vector<int> > &Mecung, int n, int m)
{
    ifstream ifs;
    ifs.open("input.txt");
    Mecung.resize(n);
    for (int i = 0; i < n; i++)
    {
        Mecung[i].resize(m);
        for (int j = 0; j < m; j++)
        {
            ifs >> Mecung[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << Mecung[i][j] << " ";
        }
        cout << endl;
    }
    ifs.close();
}

void nhap(vector<vector<int> > &Mecung, int n, int m)
{
    srand(time(NULL));
    Mecung.resize(n);
    for (int i = 0; i < n; i++)
    {
        Mecung[i].resize(m);
        for (int j = 0; j < m; j++)
        {
            Mecung[i][j] = rand() % 1000 + 1;
        }
    }
}

void hien_thi(vector<vector<int> > &Mecung, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << Mecung[i][j] << " ";
        }
        cout << endl;
    }
}

void mo_phong(vector<vector<int> > &Mecung, const vector<int> &duong_di, toa_do &start, int n, int m)
{
    vector<vector<bool> > Danh_dau(n, vector<bool>(m, false));

    toa_do robot;
    robot.x = start.x;
    robot.y = start.y;

    cout << "\nMap:" << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bool robot_visited = false;

            for (int k = 0; k < duong_di.size(); k++)
            {
                if (i == start.x && j == start.y && k == 0)
                {
                    cout << " S "<<" ";
                    robot_visited = true;
                    break;
                }
                if (Mecung[i][j] == duong_di[k])
                {
                    cout << " X "<<" ";
                    robot_visited = true;
                    break;
                }
            }
            if (!robot_visited)
            {
				if(Mecung[i][j]<10)
                {
					cout<<" "<<Mecung[i][j]<<"  ";
                }
				else if(Mecung[i][j]<100)
                {
					cout<<Mecung[i][j]<<"  ";
                }
				else
                {
					cout<<Mecung[i][j]<<"  ";
                }
            }
        }
        cout << endl;
    }
}

void mo_phong_2(vector<vector<int> > &Mecung,vector<vector<bool> > &Danh_dau, const vector<int> &duong_di_1,const vector<int> &duong_di_2,toa_do &start1,toa_do &start2, int n, int m)
{
    toa_do robot1,robot2;
    robot1.x = start1.x;
    robot1.y = start1.y;
    robot2.x = start2.x;
    robot2.y = start2.y;

    for(int i=0; i<n; i++)
    {
		for(int j=0; j<m; j++)
        {
			if(Danh_dau[i][j]==true)
            {
				for(int h=0; h< duong_di_1.size(); h++)
                {
                    if(i == start1.x && j == start1.y && h == 0)
                    {
                        cout << " S1 ";
                        break;
                    }
					if(Mecung[i][j]==duong_di_1[h])
                    {
						cout<<" X "<<" ";
						break;						
					}
				}
				for(int k=0; k<duong_di_2.size(); k++)
                {
                    if(i == start2.x && j == start2.y && k == 0)
                    {
                        cout << " S2 ";
                        break;
                    }
					if(Mecung[i][j]==duong_di_2[k])
                    {
						cout<<" O "<<" ";
						break;						
					}
				}
			}
			else
            {
				if(Mecung[i][j]<10)
                {
					cout<<" "<<Mecung[i][j]<<"  ";
                }
				else if(Mecung[i][j]<100)
                {
					cout<<Mecung[i][j]<<"  ";
                }
				else
                {
					cout<<Mecung[i][j]<<" ";
                }
			}
		}
		cout<<endl;
	}
	cout<<endl;
}

void tim_duong_lon_nhat(vector<vector<int> > &Mecung, vector<vector<bool> > &Danh_dau, vector<int> &duong_di, toa_do start)
{
    if (start.x < 0 || start.x >= Mecung.size() || start.y < 0 || start.y >= Mecung[0].size() || Danh_dau[start.x][start.y])
    {
        return;
    }

    Danh_dau[start.x][start.y] = true;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    int duong_lon_nhat = 0;
    toa_do diem_ke_tiep = {-1, -1};

    for (int i = 0; i < 4; i++)
    {
        int nx = start.x + dx[i];
        int ny = start.y + dy[i];

        if (nx >= 0 && nx < Mecung.size() && ny >= 0 && ny < Mecung[0].size() && Danh_dau[nx][ny] == false && Mecung[nx][ny] > duong_lon_nhat)
        {
            duong_lon_nhat = Mecung[nx][ny];
            diem_ke_tiep.x = nx;
            diem_ke_tiep.y = ny;
        }
    }

    if (diem_ke_tiep.x != -1 && diem_ke_tiep.y != -1)
    {
        duong_di.push_back(duong_lon_nhat);
        tim_duong_lon_nhat(Mecung, Danh_dau, duong_di, diem_ke_tiep);
    }
}

void che_do_don(vector<vector<int> > &Mecung, int n, int m, toa_do start)
{
    vector<vector<bool> > Danh_dau(n, vector<bool>(m, false));
    vector<int> duong_di;
    vector<toa_do> duong_di_mp;
    ofstream ifs;

    ifs.open("output.txt");

    cout << "\nNhap toa xuat phat cua robot: ";
    cin >> start.x >> start.y;

    duong_di.push_back(Mecung[start.x][start.y]);

    tim_duong_lon_nhat(Mecung, Danh_dau, duong_di, start);
    cout << "\nDuong di cua robot la: " << endl;

    for (int i = 0; i < duong_di.size(); i++)
    {
        cout << duong_di[i] << " ";
    }
    mo_phong(Mecung,duong_di,start,n,m);
    cout << endl;
    for (int i = 0; i < duong_di.size(); i++)
    {
        ifs << duong_di[i] << " ";
    }
    cout << endl;
    ifs.close();
}

void che_do_may_vs_may(vector<vector<int> > &Mecung, int n, int m)
{
    vector<vector<bool> > Danh_dau(n, vector<bool>(m, false));
    toa_do start1;
    toa_do start2;
    vector<int> duong_di_1;
    vector<int> duong_di_2;
    ofstream ifs;

    ifs.open("output.txt");

    cout << "\nNhap toa xuat phat cua robot 1: ";
    cin >> start1.x >> start1.y;

    ifs << start1.x << start1.y << endl;

    cout << "\nNhap toa xuat phat cua robot 2: ";
    cin >> start2.x >> start2.y;

    ifs << start2.x << start2.y << endl;

    duong_di_1.push_back(Mecung[start1.x][start1.y]);
    tim_duong_lon_nhat(Mecung, Danh_dau, duong_di_1, start1);

    Danh_dau.assign(n, vector<bool>(m, false));

    duong_di_2.push_back(Mecung[start2.x][start2.y]);
    tim_duong_lon_nhat(Mecung, Danh_dau, duong_di_2, start2);

    int diem_1 = 0;
    int diem_2 = 0;

    cout << "duong di cua robot 1: " << endl;
    for (int i = 0; i < duong_di_1.size(); i++)
    {
        diem_1 += duong_di_1[i];
        cout << duong_di_1[i] << " ";
    }
    mo_phong(Mecung,duong_di_1,start1,n,m);

    cout << endl;

    cout << "duong di cua robot 2: " << endl;
    for (int j = 0; j < duong_di_1.size(); j++)
    {
        diem_2 += duong_di_2[j];
        cout << duong_di_2[j] << " ";
    }
    mo_phong(Mecung,duong_di_2,start2,n,m);

    cout << endl;

    cout << "tong diem cua robot 1: " << diem_1 << endl;
    ifs << "tong diem cua robot 1: " << diem_1 << endl;
    cout << "tong diem cua robot 2: " << diem_2 << endl;
    ifs << "tong diem cua robot 2: " << diem_2 << endl;

    if (diem_1 > diem_2)
    {
        cout << "robot 1 win !" << endl;
        ifs << "robot 1 win !" << endl;
    }
    else if (diem_1 < diem_2)
    {
        cout << "robot 2 win !" << endl;
        ifs << "robot 2 win !" << endl;
    }
    cout << "\nToa do cac o ma 2 robot di trung nhau la: ";
    ifs << "\nToa do cac o ma 2 robot di trung nhau la: ";

    for (int k = 0; k < m; k++)
    {
        for (int h = 0; h < n; h++)
        {
            for (int i = 0; i < duong_di_1.size(); i++)
            {
                for (int j = 0; j < duong_di_2.size(); j++)
                {
                    if((Mecung[k][h] == duong_di_1[i])&&(Mecung[k][h] == duong_di_2[j]))
                    {
                        cout << "(" << h << "," << k << ")"<< " ";
                    }
                }
            }
        }
    }
    cout << endl;
    for (int k = 0; k < m; k++)
    {
        for (int h = 0; h < n; h++)
        {
            for (int i = 0; i < duong_di_1.size(); i++)
            {
                for (int j = 0; j < duong_di_2.size(); j++)
                {
                    if((Mecung[k][h] == duong_di_1[i])&&(Mecung[k][h] == duong_di_2[j]))
                    {
                        ifs << "(" << h << "," << k << ")"<< " ";
                    }
                }
            }
        }
    }
    cout << endl;
    ifs.close();
}
// Hàm di chuyển robot
void di_chuyen_robot(vector<vector<int> > &Mecung, vector<vector<bool> > &Danh_dau, vector<int> &duong_di_1, vector<int> &duong_di_2, toa_do &start1, toa_do &start2, bool &luot)
{
    if (luot == true)
    {
        if (start1.x < 0 || start1.x >= Mecung.size() || start1.y < 0 || start1.y >= Mecung[0].size() || Danh_dau[start1.x][start1.y])
        {
            return;
        }
        // Đến lượt của Robot 1
        luot = false;
        Danh_dau[start1.x][start1.y] = true;

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        int duong_lon_nhat_1 = 0;
        toa_do diem_ke_tiep_1 = {-1, -1};

        // Duyệt qua các hướng để tìm đường đi tốt nhất cho Robot 1
        for (int i = 0; i < 4; i++)
        {
            int nx_1 = start1.x + dx[i];
            int ny_1 = start1.y + dy[i];

            if (nx_1 == start2.x && ny_1 == start2.y)
                continue;
            if (nx_1 >= 0 && nx_1 < Mecung.size() && ny_1 >= 0 && ny_1 < Mecung[0].size() && !Danh_dau[nx_1][ny_1] && Mecung[nx_1][ny_1] > duong_lon_nhat_1)
            {
                duong_lon_nhat_1 = Mecung[nx_1][ny_1];
                diem_ke_tiep_1.x = nx_1;
                diem_ke_tiep_1.y = ny_1;
            }
        }
        if (diem_ke_tiep_1.x != -1 && diem_ke_tiep_1.y != -1)
        {
            duong_di_1.push_back(duong_lon_nhat_1);
            di_chuyen_robot(Mecung, Danh_dau, duong_di_1, duong_di_2, diem_ke_tiep_1, start2, luot);
        }
        else
        {
            tim_duong_lon_nhat(Mecung, Danh_dau, duong_di_2, start2);
        }
    }
    else
    {
        if (start2.x < 0 || start2.x >= Mecung.size() || start2.y < 0 || start2.y >= Mecung[0].size() || Danh_dau[start2.x][start2.y])
        {
            return;
        }
        // Đến lượt của Robot 2
        luot = true;
        Danh_dau[start2.x][start2.y] = true;

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        int duong_lon_nhat_2 = 0;
        toa_do diem_ke_tiep_2 = {-1, -1};

        // Duyệt qua các hướng để tìm đường đi tốt nhất cho Robot 2
        for (int i = 0; i < 4; i++)
        {
            int nx_2 = start2.x + dx[i];
            int ny_2 = start2.y + dy[i];

            if (nx_2 == start1.x && ny_2 == start1.y)
                continue;

            if (nx_2 >= 0 && nx_2 < Mecung.size() && ny_2 >= 0 && ny_2 < Mecung[0].size() && !Danh_dau[nx_2][ny_2] && Mecung[nx_2][ny_2] > duong_lon_nhat_2)
            {
                duong_lon_nhat_2 = Mecung[nx_2][ny_2];
                diem_ke_tiep_2.x = nx_2;
                diem_ke_tiep_2.y = ny_2;
            }
        }
        // Nếu có đường đi cho Robot 2, cập nhật thông tin và tiếp tục di chuyển
        if (diem_ke_tiep_2.x != -1 && diem_ke_tiep_2.y != -1)
        {
            duong_di_2.push_back(duong_lon_nhat_2);
            di_chuyen_robot(Mecung, Danh_dau, duong_di_1, duong_di_2, start1, diem_ke_tiep_2, luot);
        }
        else
        {
           tim_duong_lon_nhat(Mecung, Danh_dau, duong_di_1, start1);
        }
    }
}


void che_do_lan_luot(vector<vector<int> > &Mecung, int n, int m, toa_do start1, toa_do start2, vector<int> duong_di_1, vector<int> duong_di_2)
{
    vector<vector<bool> > Danh_dau(n, vector<bool>(m, false));
    int diem_1 = 0, diem_2 = 0;
    int lua_chon;
    bool luot;
    ofstream ifs;

    ifs.open("output.txt");

    cout << "\nNhap toa xuat phat cua robot 1: ";
    cin >> start1.x >> start1.y;

    ifs << start1.x << start1.y << endl; // xuat toa do vao file

    cout << "\nNhap toa xuat phat cua robot 2: ";
    cin >> start2.x >> start2.y;

    ifs << start2.x << start2.y << endl; // xuat toa do vao file

    cout << "\nChon robot nao xuat phat truoc (1 hoac 2): ";
    cin >> lua_chon;

    luot = (lua_chon == 1) ? true : false;

    duong_di_1.push_back(Mecung[start1.x][start1.y]);
    duong_di_2.push_back(Mecung[start2.x][start2.y]);

    di_chuyen_robot(Mecung, Danh_dau, duong_di_1, duong_di_2, start1, start2, luot);

    cout << "Duong di cua robot 1: " << endl;
    for (int i = 0; i < duong_di_1.size(); i++)
    {
        diem_1 += duong_di_1[i];
        cout << duong_di_1[i] << " ";
    }
    cout << endl;

    //xuat ket qua vao file
    for (int i = 0; i < duong_di_1.size(); i++)
    {
        ifs << duong_di_1[i] << " ";
    }

    ifs << endl;

    cout << "Duong di cua robot 2: " << endl;
    for (int j = 0; j < duong_di_2.size(); j++)
    {
        diem_2 += duong_di_2[j];
        cout << duong_di_2[j] << " ";
    }
    cout << endl;

    //xuat ket qua vao file
    for (int j = 0; j < duong_di_2.size(); j++)
    {
        ifs << duong_di_2[j] << " ";
    }

    ifs << endl;

    cout << "tong diem cua robot 1: " << diem_1 << endl;

    //xuat ket qua vao file
    ifs << "tong diem cua robot 1: " << diem_1 << endl;

    cout << "tong diem cua robot 2: " << diem_2 << endl;

    //xuat ket qua vao file
    ifs << "tong diem cua robot 2: " << diem_2 << endl;

    if (diem_1 > diem_2)
    {
        cout << "robot 1 win !" << endl;
        ifs << "robot 1 win !" << endl; //xuat ket qua vao file
    }
    else if (diem_1 < diem_2)
    {
        cout << "robot 2 win !" << endl;
        ifs << "robot 2 win !" << endl; //xuat ket qua vao file
    }
    else
    {
        cout << "Hai robot hoa nhau !" << endl;
        ifs << "Hai robot hoa nhau !" << endl; //xuat ket qua vao file
    }
    cout <<"               chu y !                    "<<endl;
    cout <<" S1: la vi tri xuat phat qua cua robot 1: "<<endl;
    cout <<" S2: la vi tri xuat phat qua cua robot 1: "<<endl;
    cout <<" X: la vi tri di qua cua robot 1:         "<<endl;
    cout <<" O: la vi tri di qua cua robot 2:         "<<endl;
    cout << endl;
    cout << " map: "<<endl;
    mo_phong_2(Mecung,Danh_dau,duong_di_1,duong_di_2,start1,start2,n,m);
}

void menu1()
{
    cout << "================= MENU ===================" << endl;
    cout << "| 1. Che do choi don                      |" << endl;
    cout << "| 2. Che do may voi may                   |" << endl;
    cout << "| 3. Che do choi lan luot                 |" << endl;
    cout << "| 4. Luat choi                            |" << endl;
    cout << "| 5. Thoat                                |" << endl;
    cout << "==========================================" << endl;
}

void menu2()
{
    cout << "==============LUA CHON================" << endl;
    cout << "| 1. chon file input                  |" << endl;
    cout << "| 2. nhap du lieu tu ban phim         |" << endl;
    cout << "=======================================" << endl;
}

void luat()
{
    cout << "==================================LUAT CHOI=======================================" << endl;
    cout << "| 1. Robot chi co the di theo 4 huong (tren, duoi, trai, phai)                    |" << endl;
    cout << "| 2. Robot se chon lua so lon nhat de di, o nao robot di roi thi khong duoc di lai|" << endl;
    cout << "| 3. Rieng che do choi lan luot thi co 2 robot hay chon 1 trong 2 di truoc va moi |" << endl;
    cout << "===================================================================================" << endl;
}

int main()
{
    int n, m, chon;
    vector<vector<int> > Mecung;
    toa_do start;
    toa_do start1;
    toa_do start2;
    vector<int> duong_di;
    vector<int> duong_di_1;
    vector<int> duong_di_2;

    cout << "Nhap so dong: ";
    cin >> n;
    cout << "Nhap so cot: ";
    cin >> m;

    menu2();

    cout << "hay nhap lua chon cua ban: ";
    cin >> chon;

    switch (chon)
    {
    case 1:
        docdulieu(Mecung, n, m);
        break;
    case 2:
        nhap(Mecung, n, m);
        break;
    default:
        cout << "hay nhap dung thong tin trong bang !";
    }

    cout << "Me cung da nhap:" << endl;
    hien_thi(Mecung, n, m);

    while (true)
    {
        int luachon;
        menu1();
        cout << "Hay nhap lua chon cua ban: ";
        cin >> luachon;
        switch (luachon)
        {
        case 1:
            che_do_don(Mecung, n, m, start);
            break;
        case 2:
            che_do_may_vs_may(Mecung, n, m);
            break;
        case 3:
            che_do_lan_luot(Mecung, n, m, start1, start2, duong_di_1, duong_di_2);
            break;
        case 4:
            luat();
            break;
        case 5:
            return 0;
        }
    }
    return 0;
}