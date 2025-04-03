#include "Ionosphere.h"
#include "PlasmaField.h"
// Constants not directly used in this implementation file

namespace Archimedes {

void Ionosphere::addPlasmaField(std::shared_ptr<PlasmaField> field) {
    m_plasmaFields.push_back(field);
}

std::vector<std::shared_ptr<PlasmaField>> Ionosphere::getPlasmaFields() const {
    return m_plasmaFields;
}

void Ionosphere::update(float deltaTime) {
    for (auto& field : m_plasmaFields) {
        field->update(deltaTime);
    }
}

} // namespace Archimedes