/* Copyright 2017-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/has_equal_to.hpp>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T>
using is_equality_comparable=std::integral_constant<
  bool,
  has_equal_to<T,T,bool>::value
>;

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_equality_comparable.hpp
auvb84NwjBrQFEsvWu3xgEsucAc1duB3ccoBQEiUV/tnpRElTxvo5EDjvjXdbn96yMLedwi6gfUV0PUR30DevrWNc+bC8gBhB+o/ADOmDPU+sF+9CSzRtkPbsMpGntDjHste0Gubi5x2u4wL1wEBD+5YATxitXOvRwiwokQYGmwijsVDWF+IV9DDAJ936pse6ndSLL4FDhe0EJ7IcPguf7YSxQszmmHw4kapm/WqeXrOLOWogVXJspnglbepyN2Uwhs+0j7i3M1rHOPdDKPExhLHS0/uuQBdfKnj1ms+7cJKBIb0g0gIxzFb/3rSmNE6apLoM3oVwrT0nZahdo/JSec9364fYCLqc7RmmS2C76kQ5cKhCMfMkpjSbSyp5dOmj9svGtwnmvxIEicWVX1r2dgXDxOYSvFGXfLbU+h+NsjtoCjc48qy65Pg4mP0YY1ThtcFW1DCXNcvQBrgGt8rGSL0+5Z0sOuvXnojYqByJ0DVCAuzB6/zeqJ72QL4dKUWbvW/s4zHYMIuU1A4uCdBdyz0p5RCUWexqyMUiyfEqtgM/eokfnm2H3THrQ==
*/