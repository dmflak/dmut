// dmut.cpp : Defines the entry point for the application.
//

#include "../include/dmut.hpp"
#include "../include/ConstrainedType.hpp"
#include "../include/NonNullOwningPointer.hpp"

namespace dmut::test
{

void TestNonNullOwningPointer();

} // namespace dmut::test
int main()
{

    using HourOfDay = dmut::ConstrainedType<int, [](const int i)
    {
        return 0 <= i && i <= 23;
    }>;

    using NoughtToFiftyNine = dmut::ConstrainedType<int, [](const int i)
    {
        return 0 <= i && i <= 59;
    }>;

    using MinuteOfHour = NoughtToFiftyNine;
    using SecondOfMinute = NoughtToFiftyNine;

    struct TimeOfDay
    {
        HourOfDay hourOfDay;
        MinuteOfHour minuteOfHour;
        SecondOfMinute secondOfMinute;
    };

    auto bob1 = dmut::NonNullOwningPointer<std::unique_ptr<int>>::MakeOptional(
        std::make_unique<int>());
    auto bob2 = dmut::NonNullOwningPointer<std::unique_ptr<int>>::MakeOptional(
        nullptr);
    if (bob2.has_value())
    {

    }
    //struct 
    dmut::test::TestNonNullOwningPointer();
    std::cout << "Done.\n";
    return 0;
}
