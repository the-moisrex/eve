//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var minabs
  //!
  //! @brief Callable object computing the minabs operation.
  //!
  //! **Required header:** `#include <eve/function/minabs.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the minabs operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value ...Ts> auto operator()( T x,Ts... args ) const noexcept
  //!                                       requires (compatible_values< T, Ts > && ...);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `args`:   [values](../../concepts.html#value)
  //!
  //! **Return value**
  //!
  //!the greatest absolute value is returned.
  //!
  //!For instance for two elemnts:
  //!
  //!  * If `|x| <   |y|`,  `|x|` is returned.
  //!  * If `|x| >   |y|`,  `|y|` is returned.
  //!  * Otherwise `min(|x|, |y|)` is returned.
  //!
  //!For n parameters the result is computed as if this scheme was recursively used.
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the parameters.
  //!
  //!@warning
  //!   If any element of the inputs is a `Nan`, the corresponding output element is system-dependent.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::minabs
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `minabs[cond](x, ...)` is equivalent to `if_else(cond,minabs(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/minabs.hpp>`
  //!
  //!     The behaviour is the same except that if  `|x| == |y|`, `pedantic(max)` is used.
  //!
  //!  * `numeric`
  //!
  //!     **Required header:** `#include <eve/function/numeric/minabs.hpp>`
  //!
  //!      The behaviour is the same except that if  `|x| == |y|`, `numeric(max)` is used.
  //!
  //!  * `diff`
  //!
  //!     **Required header:** `#include <eve/function/diff/minabs.hpp>`
  //!
  //!     The expression `diff< N >(minabs)(x,args,...)` computes the partial
  //!      derivative relative to the Nth parameter. If the parameters are \f$x_1, ..., x_n\f$ and
  //!      their minabs is \f$m\f$, the value returned is elementwise \f$\mathrm{sign}(x_N)\f$ if \f$m\f$ is equal to \f$|x_N|\f$ else 0.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/minabs.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minabs_, minabs);
}

#include <eve/module/real/core/function/regular/generic/minabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/minabs.hpp>
#endif
