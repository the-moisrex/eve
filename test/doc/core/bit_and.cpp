#include <eve/function/bit_and.hpp>
#include <eve/literals.hpp>
#include <eve/wide.hpp>

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 4}, qi = {4, 1, 1, ~0};
  std::uint32_t z = 5;
  std::cout << "---- simd" << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " <- z               = " << z  << '\n'
            << " -> bit_and(pi, qi) = " << eve::bit_and(pi, qi) << '\n'
            << " -> bit_and(z,  qi) = " << eve::bit_and(z,  qi) << '\n'
            << " -> bit_and(pi, z ) = " << eve::bit_and(pi, z) << '\n';

  std::uint32_t mask = 1 >> 31;
  float xi = -3.4565;

  std::cout << "---- scalar" << '\n'
            << " <- xi                = " << xi << '\n'
            << " <- mask              = " << mask << '\n'
            << " -> bit_and(xi, mask) = " << eve::bit_and(xi, mask) << '\n';
  return 0;
}