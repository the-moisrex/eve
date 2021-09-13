//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/inclusive_scan.hpp>
#include <eve/algo/reduce.hpp>
#include <eve/algo/zip.hpp>

#include <algorithm>
#include <functional>
#include <vector>

#if 0  // FIX-#880, FIX-#896"
TTS_CASE("eve.algo.reduce sum complex numbers")
{
  std::vector<float> real = { 0.0,  0.1,  0.2,  0.3 };
  std::vector<float> img  = { 0.0, -0.1, -0.2, -0.3 };

  using cmplx = kumi::tuple<float, float>;

  auto plus = [](eve::same_value_type<cmplx> auto x,
                 eve::same_value_type<cmplx> auto y) {
    get<0>(x) += get<0>(y);
    get<1>(x) += get<1>(y);
    return x;
  };


  auto [re, im] = eve::algo::reduce(
    eve::algo::zip(real, img),
    std::pair{plus, cmplx{0.0, 0.0} },
    cmplx{1, -1}
  );

  TTS_EQUAL(re,  1.6);
  TTS_EQUAL(im, -1.6);
}

#endif

TTS_CASE("eve.algo.inclusive_scan a vector")
{
  std::vector<int> v        { 0, 1, 2, 3, 4 };

  std::vector<int> expected(v.size());
  std::inclusive_scan(v.begin(), v.end(), expected.begin(), std::plus<>{}, -1);

  eve::algo::inclusive_scan_inplace(v, -1);
  TTS_EQUAL(v, expected);
}

TTS_CASE("eve.algo.inclusive_scan complex numbers")
{
  std::vector<float> real = { 0.0,  0.1,  0.2,  0.3 };
  std::vector<float> img  = { 0.0, -0.1, -0.2, -0.3 };

  using cmplx = kumi::tuple<float, float>;

  auto plus = [](eve::same_value_type<cmplx> auto x,
                 eve::same_value_type<cmplx> auto y) {
    get<0>(x) += get<0>(y);
    get<1>(x) += get<1>(y);
    return x;
  };

  std::vector<float> real_copy = real;
  std::vector<float> img_copy  = img;

  eve::algo::inclusive_scan_to(
    eve::algo::zip(real, img),
    eve::algo::zip(real_copy, img_copy),
    std::pair{plus, eve::zero},
    eve::zero);

  eve::algo::inclusive_scan_inplace(eve::algo::zip(real, img), std::pair{plus, eve::zero}, eve::zero);

  std::vector<float> expected_real = { 0.0,  0.1,  0.3,  0.6 };
  std::vector<float> expected_img  = { 0.0, -0.1, -0.3, -0.6 };
  TTS_EQUAL(expected_real, real);
  TTS_EQUAL(expected_img,  img);

  TTS_EQUAL(expected_real, real_copy);
  TTS_EQUAL(expected_img,  img_copy);
}