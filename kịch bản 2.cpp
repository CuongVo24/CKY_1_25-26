// 📄 ĐỀ BÀI MẪU: HỆ THỐNG KHUYẾN MÃI (Promotion System)
Mô tả: Xây dựng hệ thống tính giảm giá cho Đơn hàng (Order).
1.	Có nhiều loại khuyến mãi: Giảm theo % (PercentageDiscount) và Giảm tiền trực tiếp (FixedDiscount).
2.	Một Đơn hàng có thể áp dụng nhiều mã khuyến mãi cùng lúc.
3.	Đơn hàng cần tính Tổng tiền được giảm.
//Yêu cầu:
1.	Vẽ sơ đồ lớp.
2.	Cài đặt các class. Đảm bảo tính đa hình và không rò rỉ bộ nhớ.
🕵️ BƯỚC 1: QUÉT ĐỀ & TRA CHEATSHEET (Mapping)
Em cầm tờ Cheatsheet ra, nhìn vào KHOANG 2 (Bảng Từ Điển) và nhận diện:
•	Dấu hiệu: "Đơn hàng áp dụng nhiều khuyến mãi". Đơn hàng bản thân nó không phải là một loại khuyến mãi. $\rightarrow$ Kịch bản 2 (Strategy).
•	Mapping (Ánh xạ):
o	IComponent (Interface) $\rightarrow$ Đổi tên thành: IPromotion.
o	execute() (Hàm ảo) $\rightarrow$ Đổi tên thành: calcDiscount(float price).
o	Leaf (Lá) $\rightarrow$ Đổi tên thành: PercentageDiscount, FixedDiscount.
o	Manager (Quản lý) $\rightarrow$ Đổi tên thành: Order.

// [Cheatsheet]: class Component { virtual int execute() = 0; virtual ~Component() {} };
// [Bài làm]:
class IPromotion {
public:
    // Sửa execute() thành calcDiscount()
    virtual float calcDiscount(float orderPrice) = 0; 
    virtual ~IPromotion() {} // Chép y nguyên (Quan trọng!)
};
// [Cheatsheet]: class Leaf : public Component { ... };
// [Bài làm]:
class PercentageDiscount : public IPromotion {
private:
    float percent;
public:
    PercentageDiscount(float p) : percent(p) {}
    
    // Logic cụ thể
    float calcDiscount(float orderPrice) override {
        return orderPrice * (percent / 100.0);
    }
};

class FixedDiscount : public IPromotion {
private:
    float amount;
public:
    FixedDiscount(float amt) : amount(amt) {}
    
    float calcDiscount(float orderPrice) override {
        return (amount > orderPrice) ? orderPrice : amount; // Không giảm quá giá trị đơn
    }
};
// [Cheatsheet]: class Composite : public Component { ... };
// [Bài làm]:
class Order { // <--- LƯU Ý: KHÔNG CÓ ": public IPromotion"
private:
    vector<IPromotion*> promos; // Vẫn dùng vector chứa Interface
    float originalPrice;

public:
    Order(float price) : originalPrice(price) {}

    void addPromotion(IPromotion* p) {
        promos.push_back(p);
    }

    // Hàm tính tổng (Thay vì execute thì đặt tên gì cũng được)
    float getTotalDiscount() {
        float total = 0;
        for (int i = 0; i < promos.size(); i++) {
            total += promos[i]->calcDiscount(originalPrice); // Đa hình
        }
        return total;
    }

    // Destructor (Vẫn phải chép y nguyên để dọn rác)
    ~Order() {
        for (int i = 0; i < promos.size(); i++) {
            delete promos[i];
        }
        promos.clear();
    }
};
