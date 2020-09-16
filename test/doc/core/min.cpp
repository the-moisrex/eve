#include <eve/function/min.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using eve::pedantic_;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f, eve::nan(eve::as<float>()),
                -0.0f, eve::nan(eve::as<float>()), -2.0f};


  std::cout << "---- simd" << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> min(pf, qf)            = " << eve::min(pf, qf) << '\n'
            << "-> pedantic_(min)(pf, qf) = " << eve::pedantic_(eve::min)(pf, qf) << '\n'
            << "-> numeric_(min)(pf, qf)  = " << eve::numeric_(eve::min)(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                     = " << xf << '\n'
            << "<- yf                     = " << yf << '\n'
            << "-> min(xf, yf) =          = " << eve::min(xf, yf) << '\n'
            << "-> pedantic_(min)(xf, yf) = " << eve::pedantic_(eve::min)(xf, yf) << '\n'
            << "-> numeric_(min)(xf, yf)  = " << eve::numeric_(eve::min)(xf, yf) << '\n';
  return 0;
}
