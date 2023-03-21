#include <cassert>
#include "../include/NonNullOwningPointer.hpp"

namespace dmut::test
{

namespace
{

template <typename PointerType>
struct TestSmartPointerInputs
{
    using NNOP = dmut::NonNullOwningPointer<PointerType>;

    static_assert(!std::is_constructible_v<NNOP, PointerType>);

    static_assert(!std::is_constructible_v<NNOP, std::nullptr_t>);
        
    static_assert(
        std::is_constructible_v<
            NNOP, NNOP::ConstructorAccessToken, PointerType>);

    static_assert(
        !std::is_constructible_v<NNOP::ConstructorAccessToken>);
};

} // namespace

void TestNonNullOwningPointer()
{
    TestSmartPointerInputs<std::unique_ptr<int>>{};
    TestSmartPointerInputs<std::shared_ptr<std::optional<double>>>{};

    using PointerType = std::unique_ptr<int>;
    using NNOP = dmut::NonNullOwningPointer<PointerType>;

    auto testVal = NNOP::MakeOptional(nullptr);
    assert(!testVal.has_value());
    testVal = NNOP::MakeOptional(std::make_unique<int>(123));
    assert(testVal.has_value());
    auto& nnPtr = *testVal;
    auto ptr = PointerType(std::move(nnPtr));
    assert(*ptr == 123);
}

} // namespace dmut::test
