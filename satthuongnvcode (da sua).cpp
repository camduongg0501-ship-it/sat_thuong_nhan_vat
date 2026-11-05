// ============================================================
//  DE TAI 10: HE THONG SAT THUONG NHAN VAT
//  Mon hoc : Lap trinh Huong doi tuong (COMP1017)
//
//  Lop co so  : VuKhi
//  Lop ke thua: Sung, Kiem, PhepThuat
//  Da hinh    : TanCong(), SatThuong(int t), Nhap(), HienThiThongTin()
// ============================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

// ============================================================
//  HAM HO TRO GIAO DIEN
// ============================================================

// Mau chu tren Console
const int MAU_MAC_DINH = 7;
const int MAU_XAM = 8;
const int MAU_XANH_LA = 10;
const int MAU_XANH_DUONG = 11;
const int MAU_DO = 12;
const int MAU_TIM = 13;
const int MAU_VANG = 14;
const int MAU_TRANG = 15;

const int DO_RONG_MENU = 50;
const int DO_RONG_NHAN = 20;

void setColor(int mau) {
    cout.flush();   // in het chu dang cho truoc khi doi mau
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mau);
}

void inThongBaoLoi(string thongBao) {
    setColor(MAU_DO);
    cout << thongBao << endl;
    setColor(MAU_MAC_DINH);
}

void inDuongKe(int doRong, char kyTu, int mau) {
    setColor(mau);
    cout << setfill(kyTu) << setw(doRong) << "" << setfill(' ') << endl;
    setColor(MAU_MAC_DINH);
}

void inGiuaDong(int doRong, string noiDung, int mau) {
    int leTrai = (doRong - (int)noiDung.length()) / 2;
    if (leTrai < 0) {
        leTrai = 0;
    }

    setColor(mau);
    cout << setw(leTrai) << "" << noiDung << endl;
    setColor(MAU_MAC_DINH);
}

void inTieuDe(string tieuDe, int mau) {
    system("cls");
    inDuongKe(DO_RONG_MENU, '=', mau);
    inGiuaDong(DO_RONG_MENU, tieuDe, mau);
    inDuongKe(DO_RONG_MENU, '=', mau);
}

// In mot muc menu: so mau vang, noi dung theo mau truyen vao
void inMucMenu(int so, string noiDung, int mau) {
    setColor(MAU_VANG);
    cout << " [" << so << "] ";
    setColor(mau);
    cout << noiDung << endl;
    setColor(MAU_MAC_DINH);
}

// In loi nhac mau xanh, phan nguoi dung go se co mau trang
void inLoiNhac(string loiNhac) {
    setColor(MAU_XANH_DUONG);
    cout << loiNhac;
    setColor(MAU_TRANG);
}

// In nhan cua mot dong thong tin, phan gia tri phia sau co mau trang
void inNhan(ostream& os, string nhan) {
    setColor(MAU_XANH_DUONG);
    os << left << setw(DO_RONG_NHAN) << nhan << ": ";
    setColor(MAU_TRANG);
}

// In gia tri ket qua mau vang, sau do tro lai mau xanh la
void inGiaTri(double giaTri) {
    setColor(MAU_VANG);
    cout << giaTri;
    setColor(MAU_XANH_LA);
}

// ============================================================
//  HAM NHAP DU LIEU HOP LE
//  Moi ham deu doc het dong hien tai de lan nhap sau khong bi loi.
// ============================================================

string nhapChuoi(istream& is, string loiNhac) {
    string s;
    while (true) {
        inLoiNhac(loiNhac);
        getline(is, s);
        if (s != "") {
            return s;
        }
        inThongBaoLoi("Noi dung khong duoc de trong.");
    }
}

double nhapSoThuc(istream& is, string loiNhac) {
    double x;
    while (true) {
        inLoiNhac(loiNhac);
        if (is >> x && x > 0 && is.peek() == '\n') {
            is.ignore(1000, '\n');
            return x;
        }
        is.clear();
        is.ignore(1000, '\n');
        inThongBaoLoi("Gia tri khong hop le, vui long nhap so lon hon 0.");
    }
}

int nhapSoNguyen(istream& is, string loiNhac) {
    int x;
    while (true) {
        inLoiNhac(loiNhac);
        if (is >> x && x > 0 && is.peek() == '\n') {
            is.ignore(1000, '\n');
            return x;
        }
        is.clear();
        is.ignore(1000, '\n');
        inThongBaoLoi("Gia tri khong hop le, vui long nhap so nguyen lon hon 0.");
    }
}

int nhapLuaChon(int nhoNhat, int lonNhat) {
    int x;
    while (true) {
        inLoiNhac("Lua chon: ");
        if (cin >> x && x >= nhoNhat && x <= lonNhat && cin.peek() == '\n') {
            cin.ignore(1000, '\n');
            return x;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(MAU_DO);
        cout << "Vui long nhap so tu " << nhoNhat << " den " << lonNhat << "." << endl;
        setColor(MAU_MAC_DINH);
    }
}

// ============================================================
//  LOP CO SO: VUKHI (lop truu tuong)
// ============================================================
class VuKhi {
private:
    string tenVuKhi;
    double satThuongCoBan;
    double tocDoRaDon;      // so don danh moi giay

public:
    // ----- Ham khoi tao va ham huy -----
    VuKhi() {
        tenVuKhi = "Chua dat ten";
        satThuongCoBan = 1;
        tocDoRaDon = 1;
    }

    VuKhi(string ten, double satThuong, double tocDo) {
        tenVuKhi = ten;
        satThuongCoBan = (satThuong > 0) ? satThuong : 1;
        tocDoRaDon = (tocDo > 0) ? tocDo : 1;
    }

    VuKhi(const VuKhi& other) {
        tenVuKhi = other.tenVuKhi;
        satThuongCoBan = other.satThuongCoBan;
        tocDoRaDon = other.tocDoRaDon;
    }

    virtual ~VuKhi() {
    }

    // ----- Getter -----
    string getTenVuKhi() const { return tenVuKhi; }
    double getSatThuongCoBan() const { return satThuongCoBan; }
    double getTocDoRaDon() const { return tocDoRaDon; }

    // ----- Setter -----
    void setTenVuKhi(string ten) {
        if (ten != "") tenVuKhi = ten;
        else inThongBaoLoi("Ten vu khi khong duoc de trong.");
    }

    void setSatThuongCoBan(double giaTri) {
        if (giaTri > 0) satThuongCoBan = giaTri;
        else inThongBaoLoi("Sat thuong co ban phai lon hon 0.");
    }

    void setTocDoRaDon(double giaTri) {
        if (giaTri > 0) tocDoRaDon = giaTri;
        else inThongBaoLoi("Toc do ra don phai lon hon 0.");
    }

    // ----- Phuong thuc ao thuan tuy: lop con bat buoc cai dat -----
    virtual void TanCong() const = 0;
    virtual double SatThuong(int t) const = 0;

    // ----- Phuong thuc ao: lop con co the dinh nghia lai -----
    virtual bool CoDungMana() const {
        return false;
    }

    virtual double ManaTieuThu(int t) const {
        return 0;
    }

    virtual void Nhap(istream& is) {
        setTenVuKhi(nhapChuoi(is, "Nhap ten vu khi: "));
        setSatThuongCoBan(nhapSoThuc(is, "Nhap sat thuong co ban: "));
        setTocDoRaDon(nhapSoThuc(is, "Nhap toc do ra don (don/giay): "));
    }

    virtual void HienThiThongTin(ostream& os) const {
        inNhan(os, "Ten vu khi");
        os << tenVuKhi << endl;
        inNhan(os, "Sat thuong co ban");
        os << satThuongCoBan << endl;
        inNhan(os, "Toc do ra don");
        os << tocDoRaDon << " don/giay" << endl;
    }

    // Cong them 0.000000001 de tranh sai so lam tron cua so thuc
    long long TinhSoDon(double soGiay) const {
        return (long long)(soGiay * tocDoRaDon + 0.000000001);
    }

    // ----- Qua tai toan tu nhap/xuat (dung duoc cho moi lop con) -----
    friend istream& operator>>(istream& is, VuKhi& vk) {
        vk.Nhap(is);
        return is;
    }

    friend ostream& operator<<(ostream& os, const VuKhi& vk) {
        inDuongKe(DO_RONG_MENU, '-', MAU_TIM);
        vk.HienThiThongTin(os);
        inDuongKe(DO_RONG_MENU, '-', MAU_TIM);
        return os;
    }
};

// ============================================================
//  LOP KE THUA: SUNG
// ============================================================
class Sung : public VuKhi {
private:
    int soLuongDanTrongOng; // so vien dan trong mot bang
    double tocDoThayBang;   // so giay de thay mot bang dan

public:
    // ----- Ham khoi tao -----
    Sung() : VuKhi() {
        soLuongDanTrongOng = 1;
        tocDoThayBang = 1;
    }

    Sung(string ten, double satThuong, double tocDo, int soDan, double thayBang)
        : VuKhi(ten, satThuong, tocDo) {
        soLuongDanTrongOng = (soDan > 0) ? soDan : 1;
        tocDoThayBang = (thayBang > 0) ? thayBang : 1;
    }

    Sung(const Sung& other) : VuKhi(other) {
        soLuongDanTrongOng = other.soLuongDanTrongOng;
        tocDoThayBang = other.tocDoThayBang;
    }

    // ----- Getter -----
    int getSoLuongDanTrongOng() const { return soLuongDanTrongOng; }
    double getTocDoThayBang() const { return tocDoThayBang; }

    // ----- Setter -----
    void setSoLuongDanTrongOng(int giaTri) {
        if (giaTri > 0) soLuongDanTrongOng = giaTri;
        else inThongBaoLoi("So luong dan trong ong phai lon hon 0.");
    }

    void setTocDoThayBang(double giaTri) {
        if (giaTri > 0) tocDoThayBang = giaTri;
        else inThongBaoLoi("Toc do thay bang phai lon hon 0.");
    }

    // ----- Da hinh -----
    virtual void TanCong() const {
        cout << "Nhan vat no sung " << getTenVuKhi() << ": ban "
             << getTocDoRaDon() << " vien/giay, het " << soLuongDanTrongOng
             << " vien thi mat " << tocDoThayBang << " giay de thay bang." << endl;
    }

    // Moi chu ky = thoi gian ban het bang + thoi gian thay bang
    virtual double SatThuong(int t) const {
        if (t <= 0) {
            return 0;
        }

        double thoiGianBan = soLuongDanTrongOng / getTocDoRaDon();
        double chuKy = thoiGianBan + tocDoThayBang;

        int soChuKy = (int)(t / chuKy);
        double thoiGianConLai = t - soChuKy * chuKy;

        long long soVien = (long long)soChuKy * soLuongDanTrongOng;
        if (thoiGianConLai >= thoiGianBan) {
            soVien += soLuongDanTrongOng;
        } else {
            soVien += TinhSoDon(thoiGianConLai);
        }

        return soVien * getSatThuongCoBan();
    }

    virtual void Nhap(istream& is) {
        VuKhi::Nhap(is);
        setSoLuongDanTrongOng(nhapSoNguyen(is, "Nhap so luong dan trong ong: "));
        setTocDoThayBang(nhapSoThuc(is, "Nhap toc do thay bang (giay): "));
    }

    virtual void HienThiThongTin(ostream& os) const {
        VuKhi::HienThiThongTin(os);
        inNhan(os, "Loai vu khi");
        os << "Sung" << endl;
        inNhan(os, "So dan trong ong");
        os << soLuongDanTrongOng << " vien" << endl;
        inNhan(os, "Toc do thay bang");
        os << tocDoThayBang << " giay" << endl;
    }
};

// ============================================================
//  LOP KE THUA: KIEM
// ============================================================
class Kiem : public VuKhi {
private:
    int doBen;              // moi don chem lam giam 1 do ben

public:
    // ----- Ham khoi tao -----
    Kiem() : VuKhi() {
        doBen = 1;
    }

    Kiem(string ten, double satThuong, double tocDo, int ben)
        : VuKhi(ten, satThuong, tocDo) {
        doBen = (ben > 0) ? ben : 1;
    }

    Kiem(const Kiem& other) : VuKhi(other) {
        doBen = other.doBen;
    }

    // ----- Getter -----
    int getDoBen() const { return doBen; }

    // ----- Setter -----
    void setDoBen(int giaTri) {
        if (giaTri > 0) doBen = giaTri;
        else inThongBaoLoi("Do ben phai lon hon 0.");
    }

    // ----- Da hinh -----
    virtual void TanCong() const {
        cout << "Nhan vat vung kiem " << getTenVuKhi() << ": chem "
             << getTocDoRaDon() << " don/giay, moi don lam giam 1 do ben (hien co "
             << doBen << ")." << endl;
    }

    // So don chem bi gioi han boi do ben
    virtual double SatThuong(int t) const {
        if (t <= 0) {
            return 0;
        }

        long long soDon = TinhSoDon(t);
        if (soDon > doBen) {
            soDon = doBen;
        }

        return soDon * getSatThuongCoBan();
    }

    virtual void Nhap(istream& is) {
        VuKhi::Nhap(is);
        setDoBen(nhapSoNguyen(is, "Nhap do ben: "));
    }

    virtual void HienThiThongTin(ostream& os) const {
        VuKhi::HienThiThongTin(os);
        inNhan(os, "Loai vu khi");
        os << "Kiem" << endl;
        inNhan(os, "Do ben");
        os << doBen << endl;
    }
};

// ============================================================
//  LOP KE THUA: PHEPTHUAT
// ============================================================
class PhepThuat : public VuKhi {
private:
    string loaiPhep;
    double manaTieuThuTrenGiay;

public:
    // ----- Ham khoi tao -----
    PhepThuat() : VuKhi() {
        loaiPhep = "Chua xac dinh";
        manaTieuThuTrenGiay = 1;
    }

    PhepThuat(string ten, double satThuong, double tocDo, string loai, double mana)
        : VuKhi(ten, satThuong, tocDo) {
        loaiPhep = loai;
        manaTieuThuTrenGiay = (mana > 0) ? mana : 1;
    }

    PhepThuat(const PhepThuat& other) : VuKhi(other) {
        loaiPhep = other.loaiPhep;
        manaTieuThuTrenGiay = other.manaTieuThuTrenGiay;
    }

    // ----- Getter -----
    string getLoaiPhep() const { return loaiPhep; }
    double getManaTieuThuTrenGiay() const { return manaTieuThuTrenGiay; }

    // ----- Setter -----
    void setLoaiPhep(string loai) {
        if (loai != "") loaiPhep = loai;
        else inThongBaoLoi("Loai phep khong duoc de trong.");
    }

    void setManaTieuThuTrenGiay(double giaTri) {
        if (giaTri > 0) manaTieuThuTrenGiay = giaTri;
        else inThongBaoLoi("Mana tieu thu phai lon hon 0.");
    }

    // ----- Da hinh -----
    virtual void TanCong() const {
        cout << "Nhan vat niem phep " << loaiPhep << " (" << getTenVuKhi()
             << "): tung " << getTocDoRaDon() << " don/giay, tieu ton "
             << manaTieuThuTrenGiay << " mana moi giay." << endl;
    }

    virtual double SatThuong(int t) const {
        if (t <= 0) {
            return 0;
        }
        return TinhSoDon(t) * getSatThuongCoBan();
    }

    virtual bool CoDungMana() const {
        return true;
    }

    virtual double ManaTieuThu(int t) const {
        if (t <= 0) {
            return 0;
        }
        return t * manaTieuThuTrenGiay;
    }

    virtual void Nhap(istream& is) {
        VuKhi::Nhap(is);
        setLoaiPhep(nhapChuoi(is, "Nhap loai phep (lua, bang, set...): "));
        setManaTieuThuTrenGiay(nhapSoThuc(is, "Nhap mana tieu thu tren giay: "));
    }

    virtual void HienThiThongTin(ostream& os) const {
        VuKhi::HienThiThongTin(os);
        inNhan(os, "Loai vu khi");
        os << "Phep thuat" << endl;
        inNhan(os, "Loai phep");
        os << loaiPhep << endl;
        inNhan(os, "Mana tieu thu");
        os << manaTieuThuTrenGiay << " mana/giay" << endl;
    }
};

// ============================================================
//  MENU VU KHI
// ============================================================
void inMenuVuKhi() {
    inTieuDe("MENU VU KHI", MAU_VANG);
    inMucMenu(1, "Xem thong tin vu khi", MAU_TRANG);
    inMucMenu(2, "Tan cong", MAU_TRANG);
    inMucMenu(3, "Tinh sat thuong sau t giay", MAU_TRANG);
    inMucMenu(4, "Tinh mana tieu thu (chi phep thuat)", MAU_TRANG);
    inDuongKe(DO_RONG_MENU, '-', MAU_XAM);
    inMucMenu(0, "Quay lai menu chinh", MAU_DO);
}

void menuVuKhi(VuKhi* vk) {
    int luaChon;
    int t;

    do {
        inMenuVuKhi();
        luaChon = nhapLuaChon(0, 4);

        switch (luaChon) {
        case 1:
            cout << *vk;
            break;

        case 2:
            setColor(MAU_XANH_LA);
            vk->TanCong();
            setColor(MAU_MAC_DINH);
            break;

        case 3:
            t = nhapSoNguyen(cin, "Nhap so giay t: ");
            setColor(MAU_XANH_LA);
            cout << "Sau " << t << " giay, " << vk->getTenVuKhi() << " gay tong sat thuong: ";
            inGiaTri(vk->SatThuong(t));
            cout << endl;
            setColor(MAU_MAC_DINH);
            break;

        case 4:
            if (vk->CoDungMana()) {
                t = nhapSoNguyen(cin, "Nhap so giay t: ");
                setColor(MAU_XANH_LA);
                cout << "Sau " << t << " giay, tieu thu ";
                inGiaTri(vk->ManaTieuThu(t));
                cout << " mana." << endl;
                setColor(MAU_MAC_DINH);
            } else {
                inThongBaoLoi("Vu khi nay khong tieu thu mana.");
            }
            break;
        }

        if (luaChon != 0) {
            system("pause");
        }
    } while (luaChon != 0);
}

// ============================================================
//  MENU CHINH
// ============================================================
void inMenuChinh() {
    inTieuDe("HE THONG SAT THUONG NHAN VAT", MAU_XANH_DUONG);
    inMucMenu(1, "Sung", MAU_XANH_LA);
    inMucMenu(2, "Kiem", MAU_XANH_DUONG);
    inMucMenu(3, "Phep thuat", MAU_TIM);
    inDuongKe(DO_RONG_MENU, '-', MAU_XAM);
    inMucMenu(0, "Thoat chuong trinh", MAU_DO);
}

int main() {
    cout << fixed << setprecision(2);

    int luaChon;
    do {
        inMenuChinh();
        luaChon = nhapLuaChon(0, 3);

        if (luaChon != 0) {
            VuKhi* vk;

            if (luaChon == 1) {
                vk = new Sung();
            } else if (luaChon == 2) {
                vk = new Kiem();
            } else {
                vk = new PhepThuat();
            }

            cin >> *vk;
            menuVuKhi(vk);
            delete vk;
        }
    } while (luaChon != 0);

    inDuongKe(DO_RONG_MENU, '=', MAU_XANH_LA);
    inGiuaDong(DO_RONG_MENU, "Cam on ban da su dung chuong trinh!", MAU_XANH_LA);
    inDuongKe(DO_RONG_MENU, '=', MAU_XANH_LA);

    return 0;
}
