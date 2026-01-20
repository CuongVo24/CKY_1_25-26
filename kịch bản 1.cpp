// Phân tích nhanh trong đầu:
•	"Team chứa Dev, Tester và Team con"  Cấu trúc Cây (Composite Pattern).
•	"Dev, Tester"  Đây là Leaf.
•	"Team" Đây là Composite.
•	"Lương" Đây là hàm execute().
•	"Hệ thống duy nhất"  Singleton.
📝 Điền vào bảng Mapping (trong đầu):
•	IComponent  Đổi tên thành: NhanSu (Abstract Class).
•	execute() Đổi tên thành: tinhLuong().
•	Leaf  Đổi tên thành: Dev, Tester.
•	Composite  Đổi tên thành: Team.
// [Cheatsheet]: class Component { virtual int execute() = 0; virtual ~Component() {} };
// [Bài làm]:
class NhanSu {
public:
    virtual long tinhLuong() = 0; // Thay execute bằng tinhLuong
    virtual ~NhanSu() {}          // Chép y nguyên (Sống còn!)
};
// [Cheatsheet]: class Leaf : public Component { ... };
// [Bài làm]:
class Dev : public NhanSu {
private:
    long luongCB;
public:
    Dev(long l) : luongCB(l) {}
    long tinhLuong() override { return luongCB; }
};

// Tester y hệt Dev (Copy paste logic)
class Tester : public NhanSu {
private:
    long luongCB;
public:
    Tester(long l) : luongCB(l) {}
    long tinhLuong() override { return luongCB; } // Có thể thêm logic * hệ số nếu thích
};
// [Cheatsheet]: class Composite : public Component { vector<Component*> children; ... };
// [Bài làm]:
class Team : public NhanSu { // Team kế thừa NhanSu (Team cũng là 1 đơn vị nhân sự)
private:
    vector<NhanSu*> members; // Thay children bằng members, Component bằng NhanSu
public:
    // Hàm add
    void add(NhanSu* ns) {
        members.push_back(ns);
    }

    // Hàm execute -> tinhLuong (Duyệt đệ quy)
    long tinhLuong() override {
        long total = 0;
        for (int i = 0; i < members.size(); i++) {
            total += members[i]->tinhLuong(); // Đa hình
        }
        return total;
    }

    // Destructor (Chép y nguyên Cheatsheet - Ăn điểm quản lý bộ nhớ)
    ~Team() {
        for (int i = 0; i < members.size(); i++) {
            delete members[i];
        }
        members.clear();
    }
};
// [Bài làm]:
class PayrollSystem {
private:
    static PayrollSystem* instance; // Static
    Team* rootTeam;                 // Quản lý cái Team to nhất
    
    // Private Constructor
    PayrollSystem() { 
        rootTeam = new Team(); // Khởi tạo team gốc
    } 

public:
    // Xóa copy (cho ngầu, không viết cũng không sao nếu đề không gắt)
    PayrollSystem(const PayrollSystem&) = delete;
    void operator=(const PayrollSystem&) = delete;

    // Hàm lấy instance
    static PayrollSystem* getInstance() {
        if (!instance) instance = new PayrollSystem();
        return instance;
    }

    Team* getRoot() { return rootTeam; }
};
// Init bên ngoài
PayrollSystem* PayrollSystem::instance = nullptr;
