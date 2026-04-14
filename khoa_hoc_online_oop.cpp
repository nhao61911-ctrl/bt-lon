#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ====================== CLASS HOC VIEN ======================
class HocVien {
private:
    static int dem;
    int maHocVien;
    string ten, tenDangNhap, matKhau;

public:
    HocVien() { maHocVien = ++dem; }

    int getMa() const { return maHocVien; }
    string getTen() const { return ten; }

    bool dangNhap(string user, string pass) {
        return user == tenDangNhap && pass == matKhau;
    }

    void nhap() {
        cout << "Nhap ten: ";
        getline(cin, ten);
        cout << "Nhap username: ";
        getline(cin, tenDangNhap);
        cout << "Nhap password: ";
        getline(cin, matKhau);
    }

    void xuat() const {
        cout << "Ma: " << maHocVien << " | Ten: " << ten << endl;
    }
};
int HocVien::dem = 0;

// ====================== CLASS KHOA HOC ======================
class KhoaHoc {
private:
    static int dem;
    int maKhoaHoc;
    string tenKhoaHoc, giangVien;
    double hocPhi;

public:
    KhoaHoc() { maKhoaHoc = ++dem; }

    int getMa() const { return maKhoaHoc; }
    string getTen() const { return tenKhoaHoc; }
    double getHocPhi() const { return hocPhi; }

    void nhap() {
        cout << "Nhap ten khoa hoc: ";
        getline(cin, tenKhoaHoc);
        cout << "Nhap giang vien: ";
        getline(cin, giangVien);
        cout << "Nhap hoc phi: ";
        cin >> hocPhi;
        cin.ignore();
    }

    void xuat() const {
        cout << "Ma: " << maKhoaHoc
             << " | Ten: " << tenKhoaHoc
             << " | Hoc phi: " << hocPhi << endl;
    }
};
int KhoaHoc::dem = 0;

// ====================== CLASS PHIEU DANG KY ======================
class PhieuDangKy {
private:
    static int dem;
    int maPhieu;
    HocVien hocVien;
    vector<KhoaHoc> dsKhoaHoc;
    double tongHocPhi;

public:
    PhieuDangKy(HocVien hv) : hocVien(hv) {
        maPhieu = ++dem;
        tongHocPhi = 0;
    }

    bool daTonTai(int ma) {
        for (auto &kh : dsKhoaHoc)
            if (kh.getMa() == ma) return true;
        return false;
    }

    // ⭐ HÀM QUAN TRỌNG NHẤT
    bool themKhoaHoc(KhoaHoc kh) {
        if (daTonTai(kh.getMa())) return false;
        dsKhoaHoc.push_back(kh);
        tongHocPhi += kh.getHocPhi();
        return true;
    }

    void xuat() const {
        cout << "\nPhieu: " << maPhieu << endl;
        cout << "Hoc vien: " << hocVien.getTen() << endl;
        cout << "Danh sach khoa hoc:\n";
        for (auto &kh : dsKhoaHoc) {
            cout << "- " << kh.getTen()
                 << " (" << kh.getHocPhi() << ")\n";
        }
        cout << "Tong hoc phi: " << tongHocPhi << endl;
    }
};
int PhieuDangKy::dem = 0;

// ====================== CLASS QUAN LY ======================
class QuanLy {
private:
    vector<HocVien> dsHocVien;
    vector<KhoaHoc> dsKhoaHoc;
    vector<PhieuDangKy> dsPhieu;

public:
    void themHocVien() {
        HocVien hv;
        hv.nhap();
        dsHocVien.push_back(hv);
    }

    void hienThiHocVien() {
        for (auto &hv : dsHocVien) hv.xuat();
    }

    void themKhoaHoc() {
        KhoaHoc kh;
        kh.nhap();
        dsKhoaHoc.push_back(kh);
    }

    void hienThiKhoaHoc() {
        for (auto &kh : dsKhoaHoc) kh.xuat();
    }

    void taoPhieu() {
        int ma;
        cout << "Nhap ma hoc vien: ";
        cin >> ma;
        cin.ignore();

        for (auto &hv : dsHocVien) {
            if (hv.getMa() == ma) {
                PhieuDangKy phieu(hv);
                int maKH;

                do {
                    hienThiKhoaHoc();
                    cout << "Nhap ma khoa hoc (0 de dung): ";
                    cin >> maKH;
                    cin.ignore();

                    for (auto &kh : dsKhoaHoc) {
                        if (kh.getMa() == maKH) {
                            if (phieu.themKhoaHoc(kh))
                                cout << "Them thanh cong\n";
                            else
                                cout << "Da ton tai\n";
                        }
                    }

                } while (maKH != 0);

                dsPhieu.push_back(phieu);
                return;
            }
        }

        cout << "Khong tim thay hoc vien\n";
    }

    void hienThiPhieu() {
        for (auto &p : dsPhieu) p.xuat();
    }
};

// ====================== CLASS UNG DUNG ======================
class UngDung {
private:
    QuanLy ql;

public:
    void menu() {
        int chon;
        do {
            cout << "\n===== MENU =====\n";
            cout << "1. Them hoc vien\n";
            cout << "2. Hien thi hoc vien\n";
            cout << "3. Them khoa hoc\n";
            cout << "4. Hien thi khoa hoc\n";
            cout << "5. Tao phieu\n";
            cout << "6. Hien thi phieu\n";
            cout << "0. Thoat\n";
            cout << "Chon: ";

            cin >> chon;
            cin.ignore();

            if (chon == 1) ql.themHocVien();
            else if (chon == 2) ql.hienThiHocVien();
            else if (chon == 3) ql.themKhoaHoc();
            else if (chon == 4) ql.hienThiKhoaHoc();
            else if (chon == 5) ql.taoPhieu();
            else if (chon == 6) ql.hienThiPhieu();

        } while (chon != 0);
    }
};

// ====================== MAIN ======================
int main() {
    UngDung app;
    app.menu();
    return 0;
}