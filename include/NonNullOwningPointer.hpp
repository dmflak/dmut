#pragma once

#include <memory>
#include "ConstrainedType.hpp"

namespace dmut
{

template <typename NotAnOwningPointer>
struct IsAnOwningPointerType : std::false_type {};

template <typename T, typename Deleter>
struct IsAnOwningPointerType<std::unique_ptr<T, Deleter>> : std::true_type {};

template <typename T>
struct IsAnOwningPointerType<std::shared_ptr<T>> : std::true_type {};

template <typename T>
constexpr bool IsAnOwningPointer = IsAnOwningPointerType<T>::value;

template <typename P>
requires IsAnOwningPointer<P>
class NonNullOwningPointer
    : public BasicConstrainedType<
        P,
        [](const P& p) { return p != nullptr; },
        NonNullOwningPointer<P>>
{
public:
    using Base = NonNullOwningPointer::SpecialisedBasicConstrainedType;
    NonNullOwningPointer(
        const typename Base::ConstructorAccessToken& t, P p) noexcept
        : Base{ t, std::move(p) }
    { }
    NonNullOwningPointer(NonNullOwningPointer&&) = default;
    NonNullOwningPointer& operator=(NonNullOwningPointer&&) = default;
    operator P() && noexcept
    {
        return std::move(this->value);
    }
};

} // namespace dmut
