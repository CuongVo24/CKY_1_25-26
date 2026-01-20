// 📄 ĐỀ BÀI MẪU: HỆ THỐNG TRÀ SỮA (Milk Tea System)
Mô tả: Cửa hàng trà sữa cần tính tiền cho khách.
1.	Món cơ bản là Trà Sữa Truyền Thống (giá gốc).
2.	Khách có thể gọi thêm (add-on) các loại Topping: Trân Châu (+10k), Pudding (+15k).
3.	Một ly trà sữa có thể thêm nhiều loại Topping chồng lên nhau (Ví dụ: Trà sữa + Trân Châu + Pudding).
4.	Cần tính Tổng tiền cuối cùng.
Yêu cầu:
1.	Vẽ sơ đồ lớp.
2.	Cài đặt các class. Đảm bảo nguyên lý Open/Closed (dễ dàng thêm loại Topping mới mà không sửa class cũ).

🕵️ BƯỚC 1: QUÉT ĐỀ & TRA CHEATSHEET (Mapping)
Em nhìn vào KHOANG 2 (Bảng Từ Điển) và nhận diện:
•	Dấu hiệu: "Thêm vào", "Cộng thêm giá", "Bao bọc".
o	Topping không phải là một món uống độc lập, nó phải đi kèm với ly trà sữa.
o	Topping cũng là một thành phần của ly nước (tính tiền được).
o	$\rightarrow$ Kịch bản 3 (Decorator).
•	Mapping (Ánh xạ):
o	IComponent (Interface)  Đổi tên thành: IMonUong.
o	execute() (Hàm ảo)  Đổi tên thành: tinhTien().
o	Leaf (Lõi)  Đổi tên thành: TraSuaTruyenThong.
o	Manager (Lớp bọc)  Đổi tên thành: Topping.
Nhìn vào KHOANG 1 (Code Khung Sườn). Quy tắc biến hình Kịch bản 3: GIỮ KẾ THỪA + BỎ VECTOR + THAY BẰNG 1 CON TRỎ.


// [Cheatsheet]: class Component { ... };
// [Bài làm]:
class IMonUong {
public:
    virtual int tinhTien() = 0;
    virtual ~IMonUong() {} 
};
// [Cheatsheet]: class Leaf : public Component { ... };
// [Bài làm]:
class TraSuaTruyenThong : public IMonUong {
public:
    int tinhTien() override {
        return 20000; // Giá gốc 20k
    }
};
// [Cheatsheet]: class Composite : public Component { vector<Component*> children; ... };
// [Bài làm]:
class Topping : public IMonUong { // <--- VẪN KẾ THỪA (Giống Kịch bản 1)
protected: 
    IMonUong* core; // <--- SỬA VECTOR THÀNH 1 CON TRỎ DUY NHẤT (Cái lõi bị bọc)

public:
    // Constructor nhận vào cái lõi để bọc lại
    Topping(IMonUong* m) : core(m) {}

    // Hàm execute (tinhTien)
    // Logic: Giá mình + Giá thằng bên trong
    int tinhTien() override {
        return core->tinhTien(); // Sẽ được cộng thêm ở lớp con
    }

    // Destructor (Dọn dẹp cái lõi bên trong)
    ~Topping() {
        if (core) delete core;
    }
};
class TranChau : public Topping {
public:
    // Nhận vào món uống để bọc lại, truyền lên cha
    TranChau(IMonUong* m) : Topping(m) {}

    int tinhTien() override {
        return 10000 + core->tinhTien(); // 10k giá trân châu + giá lõi
    }
};

class Pudding : public Topping {
public:
    Pudding(IMonUong* m) : Topping(m) {}

    int tinhTien() override {
        return 15000 + core->tinhTien(); // 15k giá pudding + giá lõi
    }
};
int main() {
    // 1. Tạo ly trà sữa gốc
    IMonUong* lyNuoc = new TraSuaTruyenThong(); 

    // 2. Thêm Trân Châu (Lấy Trân Châu bọc ly nước lại)
    lyNuoc = new TranChau(lyNuoc);

    // 3. Thêm Pudding (Lấy Pudding bọc cục (Trà+TrânChau) lại)
    lyNuoc = new Pudding(lyNuoc);

    // 4. Tính tiền
    cout << lyNuoc->tinhTien(); // Nó sẽ gọi đệ quy: Pudding -> TranChau -> TraSua

    // 5. Dọn dẹp
    delete lyNuoc; // Destructor sẽ tự động xóa dây chuyền vào trong
}
