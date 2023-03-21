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
    dmut::test::TestNonNullOwningPointer();
    std::cout << "Done.\n";
    return 0;
}
