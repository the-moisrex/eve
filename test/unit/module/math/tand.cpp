//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/function/tand.hpp>
#include <eve/function/diff/tand.hpp>
#include <eve/function/cscd.hpp>
#include <eve/function/cosd.hpp>
#include <eve/function/sind.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/deginrad.hpp>
#include <cmath>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of tand"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::tand(T())  , T);
  TTS_EXPR_IS( eve::tand(v_t()), v_t);
};

//==================================================================================================
// tand  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & ){  return T(-45); };
auto quarter_c   = []<typename T>(eve::as<T> const & ){  return T( 45); };
auto mhalf_c = []<typename T>(eve::as<T> const & ){  return T(-90 ); };
auto half_c  = []<typename T>(eve::as<T> const & ){  return T( 90 ); };
auto mmed   = []<typename T>(eve::as<T> const & ){  return -5000; };
auto med    = []<typename T>(eve::as<T> const & ){  return  5000; };

EVE_TEST( "Check behavior of tand on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::tand;
  using eve::diff;
  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { auto d = eve::cosd(e); return d ? eve::sind(e)/d: eve::nan(eve::as(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(tand)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(tand)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(tand)(a1)           , map(ref, a1), 50);
  TTS_ULP_EQUAL(tand(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(tand(a1)                       , map(ref, a1), 50);
  TTS_ULP_EQUAL(tand(a2)                       , map(ref, a2), 1024);
  TTS_ULP_EQUAL(tand(a3)                       , map(ref, a3), 2);
  auto dinr = 1.7453292519943295769236907684886127134428718885417e-2l;

  TTS_ULP_EQUAL(diff(tand)(a0), map([dinr](auto e) -> v_t { return  dinr*eve::sqr(eve::secd(e)); }, a0), 2);
};
