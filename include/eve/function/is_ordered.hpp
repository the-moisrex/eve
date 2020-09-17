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

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(is_ordered_, is_ordered);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/generic/is_ordered.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/is_ordered.hpp>
#endif
