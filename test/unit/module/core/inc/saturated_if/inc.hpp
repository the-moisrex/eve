//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inc.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check conditional saturated_(eve::inc) return type", EVE_TYPE)
{
  using eve::saturated_;
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS((saturated_(eve::inc[T()])(T()))                , T);
  TTS_EXPR_IS((saturated_(eve::inc[v_t()])(T()))              , T);
  TTS_EXPR_IS((saturated_(eve::inc[true])(T()))               , T);
  TTS_EXPR_IS((saturated_(eve::inc[eve::logical<T>()])(T()))  , T);
  TTS_EXPR_IS((saturated_(eve::inc[eve::logical<v_t>()])(T())), T);
}

TTS_CASE_TPL("Check conditional saturated_(eve::inc) behavior", EVE_TYPE)
{
  using eve::saturated_;

  T tv(2);
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(saturated_(eve::inc[ 1 ])(eve::valmax(eve::as<T>()))     , eve::valmax(eve::as<T>()));
  TTS_EQUAL(saturated_(eve::inc[ 1.0 ])(eve::valmax(eve::as<T>()))   , eve::valmax(eve::as<T>()));
  TTS_EQUAL(saturated_(eve::inc[ true ])(eve::valmax(eve::as<T>()))  , eve::valmax(eve::as<T>()));
  TTS_EQUAL(saturated_(eve::inc[ t ])(eve::valmax(eve::as<T>()))     , eve::valmax(eve::as<T>()));

  // All basic FALSE
  TTS_EQUAL(saturated_(eve::inc[ 0 ])(tv)     , tv);
  TTS_EQUAL(saturated_(eve::inc[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(saturated_(eve::inc[ false ])(tv) , tv);
  TTS_EQUAL(saturated_(eve::inc[ f ])(tv)     , tv);

  // Mixed case
  eve::as_logical_t<T> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(saturated_(eve::inc[ m ])(tv) , eve::if_else(m,saturated_(eve::inc)(tv), tv) );
}
