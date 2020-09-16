//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(valmin_, valmin);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto valmin_(EVE_SUPPORTS(cpu_),eve::as_<T> const &) noexcept
    {
      using t_t = detail::value_type_t<T>;
      return T(std::numeric_limits<t_t>::lowest());
    }
  }
}
