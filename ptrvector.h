#pragma once

#include <vector>
#include <iostream>

template <typename T>
class PtrVector {
public:
    PtrVector() = default;

    // ������ ������ ���������� �� ����� �������� �� other
    PtrVector(const PtrVector& other) {
        // ����������� ����� � vector-� ��� �������� ������� ���������� ���������
        // ��������� ����� ��� push_back �� ����� ������������� ����������
        items_.reserve(other.items_.size());

        try {
            for (auto p : other.items_) {
                // �������� ������, ���� ��������� �� ���� ���������
                auto p_copy = p ? new T(*p) : nullptr;  // new ����� ��������� ����������

                // �� �������� ����������, �. �. � vector ������ ��� ���������������
                items_.push_back(p_copy);
            }
        }
        catch (std::exception e) {
            std::cerr << "Exception \"PtrVector\": " << e.what() << std::endl;
            // ������� �������� � ������� � ��������������� ��������� ����������
            DeleteItems();
            throw;
        }
    }

    // ���������� ������� ������� � ����, �� ������� ��������� ���������,
    // � ������� items_
    ~PtrVector() {
        DeleteItems();
    }

    // ���������� ������ �� ������ ����������
    std::vector<T*>& GetItems() noexcept {
        return items_;
    }

    // ���������� ����������� ������ �� ������ ����������
    std::vector<T*> const& GetItems() const noexcept {
        return items_;
    }

private:
    void DeleteItems() noexcept {
        for (auto p : items_) {
            delete p;
        }
        items_.clear();
    }

    std::vector<T*> items_;
};