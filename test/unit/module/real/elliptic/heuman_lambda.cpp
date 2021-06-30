//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/heuman_lambda.hpp>
#include <boost/math/special_functions/heuman_lambda.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ellint_1"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::heuman_lambda(T(), T())  , T);
  TTS_EXPR_IS( eve::heuman_lambda(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::heuman_lambda(T(), v_t()), T);
  TTS_EXPR_IS( eve::heuman_lambda(v_t(), T()), T);
};

//==================================================================================================
// heuman_lambda  tests
//==================================================================================================
EVE_TEST( "Check behavior of heuman_lambda on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0, 1.0)
                             , eve::test::randoms(0, eve::pio_2))
        )
<typename T>(T const& k, T const& phi)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::heuman_lambda(phi, k) , map([](auto e, auto f) -> v_t { return boost::math::heuman_lambda(e, f); }, k, phi), 10);
};
