#pragma once

#include <concepts>
#include <optional>

namespace dmut
{

template <auto Constraint, typename T>
concept IsAConstraintFunction = requires (const T& t)
{
    { std::invoke(Constraint, t) } -> std::same_as<bool>;
};

template <typename T, auto Constraint, typename CRTP>
requires IsAConstraintFunction<Constraint, T>
class BasicConstrainedType
{
public:
    static std::optional<CRTP> MakeOptional(T&& t) noexcept(
        std::is_nothrow_move_constructible_v<T> &&
        noexcept(std::invoke(Constraint, std::declval<T>())))
    {
        if (std::invoke(Constraint, t))
        {
            return CRTP(ConstructorAccessToken{}, std::move(t));
        }
        return std::nullopt;
    }

    class ConstructorAccessToken
    {
    private:
        friend class BasicConstrainedType;
        ConstructorAccessToken() = default;
    };
protected:
    using SpecialisedBasicConstrainedType = BasicConstrainedType;

    inline BasicConstrainedType(ConstructorAccessToken, T&& t) noexcept(
            std::is_nothrow_move_constructible_v<T>)
        : value{ std::move(t) }
    { }
    T value;
};

template <typename T, auto Constraint>
requires IsAConstraintFunction<Constraint, T>
struct ConstrainedType
    : public BasicConstrainedType<T, Constraint, ConstrainedType<T, Constraint>>
{ };

} // namespace dmut
