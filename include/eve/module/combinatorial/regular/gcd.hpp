//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup combinatorial
  //! @{
  //! @var gcd
  //!
  //! @brief Callable object computing least common multiple.
  //!
  //! **Required header:** `#include <eve/function/gcd.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | least common multiple operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T p, U n ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`p`, `n`:   [real values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //!@warning
  //!    `p` and `n` can be of any [real values](@ref eve::value) type, but when the types are not integral
  //!    the greatest common divisor is defined only if `p` and `n` element are [flint](@ref eve::is_flint). If any
  //!    of the arguments is not flint the result is undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::gcd
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `gcd[cond](x, ...)` is equivalent to `if_else(cond,gcd(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Type conversion
  //!
  //!If the input types are integral, the result is succeptible to overflow, but will never be greater than the product of the two
  //!input values which will be representable in the upgraded integral type:
  //!
  //!The call `upgrade(gcd)(a,b)` will then return a correct result in the upgraded type (see example below).
  //!
  //! #### Example
  //!
  //! @godbolt{doc/combinatorial/gcd.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct gcd_; }

  template<>
  struct supports_optimized_conversion<tag::gcd_> : std::true_type {};

  EVE_MAKE_CALLABLE(gcd_, gcd);
}

#include <eve/module/combinatorial/regular/impl/gcd.hpp>
