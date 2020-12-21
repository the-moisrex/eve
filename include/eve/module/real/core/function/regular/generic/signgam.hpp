//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SIGNGAM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SIGNGAM_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/minf.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/binarize_not.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_ngtz.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/oneminus.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T signgam_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto isleza0 = is_ngtz(a0);
      auto a       = if_else(is_flint(a0) || is_infinite(a0),
                       eve::allbits_,
                       oneminus(binarize(is_odd(floor(a0))) * T(2)));
      return if_else(is_nan(a0), a0, if_else(isleza0, a, eve::one_));
    }
    else
      return apply_over(signgam, a0);
  }
}

#endif