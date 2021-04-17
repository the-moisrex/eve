//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <boost/math/special_functions/legendre.hpp>
#include <eve/function/legendre.hpp>
#include <eve/function/diff/legendre.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of legendre on wide"
        , eve::test::simd::ieee_reals

        )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::legendre(i_t(), T())  , T);
  TTS_EXPR_IS( eve::legendre(wi_t(), T())  , T);
  TTS_EXPR_IS( eve::legendre(i_t(), v_t())  , v_t);
  TTS_EXPR_IS( eve::legendre(wi_t(), v_t())  , T);

};

//==================================================================================================
//== legendre tests
//==================================================================================================
EVE_TEST( "Check behavior of legendre on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(-1, 1), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__legendrev  =  [](auto n, auto x) { return eve::legendre(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_p(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
  }
  auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_p(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(eve__legendrev(i0    , a0), T(boost_legendrev), 100);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_legendre2 =  [&](auto i, auto) { return boost::math::legendre_p(i0.get(i), a0.get(j)); };
    TTS_ULP_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2), 100);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_ULP_EQUAL(eve__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_p(i0.get(j), a0.get(n))), 100);
    }
  }
};


EVE_TEST( "Check behavior of diff(legendre) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(-1, 1), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__legendrev  =  [](auto n, auto x) { return eve::diff(eve::legendre)(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_p_prime(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
  }
  auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_p_prime(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(eve__legendrev(i0    , a0), T(boost_legendrev), 100);
   std::cout <<" a0 " << a0 << std::endl;
   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_legendre2 =  [i0, a0, j](auto i, auto) { return boost::math::legendre_p_prime(i0.get(i), a0.get(j)); };
    TTS_ULP_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2), 100);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_ULP_EQUAL(eve__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_p_prime(i0.get(j), a0.get(n))), 100);
    }
  }
};