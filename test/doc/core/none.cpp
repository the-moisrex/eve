#include <eve/function/none.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-0.0f, 0.0f, -0.0f, -0.0f};
  wide_it qi = {-1, 0, 30, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> none(pf) = " << eve::none(pf) << '\n'
            << "<- qi       = " << qi << '\n'
            << "-> none(qi) = " << eve::none(qi) << '\n';

  float        xf = -0.0f;
  float        yf = -3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> none(xf) = " << eve::none(xf) << '\n'
            << "<- yf       = " << yf << '\n'
            << "-> none(yf) = " << eve::none(yf) << '\n';
  return 0;
}
