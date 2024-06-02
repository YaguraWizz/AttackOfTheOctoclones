#pragma once
#include "ptrvector.h"
#include "scopedptr.h"
// ��� ����� ���������� scopedptr.h � ptrvector.h, 
// ���� ��� ��� �����������.

#include <new> // ��� ���������� bad_alloc
#include <vector>
#include <iostream>
// ��������
class Tentacle {
public:
    explicit Tentacle(int id) noexcept
        : id_(id) {
    }

    int GetId() const noexcept {
        return id_;
    }

    Tentacle* GetLinkedTentacle() const noexcept {
        return linked_tentacle_;
    }
    void LinkTo(Tentacle& tentacle) noexcept {
        linked_tentacle_ = &tentacle;
    }
    void Unlink() noexcept {
        linked_tentacle_ = nullptr;
    }

private:
    int id_ = 0;
    Tentacle* linked_tentacle_ = nullptr;
};

#define LOG_LIFECYCLE(action, object_type, object_name) \
    std::cout << action << " " << object_type << " " << object_name << std::endl;

// ��������
class Octopus {
public:
    Octopus()
        : Octopus(8) {}

    explicit Octopus(int num_tentacles) {
        LOG_LIFECYCLE("Creating", "Octopus object with num_tentacles =", num_tentacles)
            PtrVector<Tentacle> tentaclePtrs;
        try {
            for (int i = 1; i <= num_tentacles; ++i) {
                ScopedPtr<Tentacle> t(new Tentacle(i)); // ScopedPtr ��������� �������
                tentaclePtrs.GetItems().push_back(t.Release()); // �������� ��������� �� PtrVector, �� ���������� ��� ����������
                LOG_LIFECYCLE("Creating", "Tentacle", i)
                    LOG_LIFECYCLE("Adding", "Tentacle", i)
            }
            tentacles_ = std::move(tentaclePtrs); // ���������� tentaclePtrs � tentacles_
            LOG_LIFECYCLE("Moving", "tentaclePtrs to tentacles_", "")
        }
        catch (std::exception e) {
            // � ������ ���������� ������� ��� ��������� ��������
            std::cerr << "Exception \"Octopus\": " << e.what() << std::endl;
            tentaclePtrs.GetItems().clear();
            LOG_LIFECYCLE("Exception", "Octopus:", e.what())
                throw;
        }
    }


    ~Octopus() = default;

    Tentacle& AddTentacle() {
        ScopedPtr<Tentacle> t(new Tentacle(GetTentacleCount() + 1));
        tentacles_.GetItems().push_back(t.Release());
        return *tentacles_.GetItems().back();
    }

    int GetTentacleCount() const noexcept {
        return static_cast<int>(tentacles_.GetItems().size());
    }

    const Tentacle& GetTentacle(size_t index) const {
        return *tentacles_.GetItems().at(index);
    }
    Tentacle& GetTentacle(size_t index) {
        return *tentacles_.GetItems().at(index);
    }

private:
    PtrVector<Tentacle> tentacles_;
};