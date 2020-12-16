//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_ALGORITHM_HPP
#define BOOST_MOVE_ALGORITHM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/move/iterator.hpp>
#include <boost/move/algo/move.hpp>
#include <boost/core/no_exceptions_support.hpp>

#include <algorithm> //copy, copy_backward
#include <memory>    //uninitialized_copy

namespace boost {

//////////////////////////////////////////////////////////////////////////////
//
//                            uninitialized_copy_or_move
//
//////////////////////////////////////////////////////////////////////////////

namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_move_move_iterator(I f, I l, F r
//                             ,typename ::boost::move_detail::enable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0
)
{
   return ::boost::uninitialized_move(f, l, r);
}
/*
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
F uninitialized_move_move_iterator(I f, I l, F r,
                                   typename ::boost::move_detail::disable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0)
{
   return std::uninitialized_copy(f.base(), l.base(), r);
}
*/
}  //namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_copy_or_move(I f, I l, F r,
                             typename ::boost::move_detail::enable_if< move_detail::is_move_iterator<I> >::type* = 0)
{
   return ::boost::move_detail::uninitialized_move_move_iterator(f, l, r);
}

//////////////////////////////////////////////////////////////////////////////
//
//                            copy_or_move
//
//////////////////////////////////////////////////////////////////////////////

namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F move_move_iterator(I f, I l, F r
//                             ,typename ::boost::move_detail::enable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0
)
{
   return ::boost::move(f, l, r);
}
/*
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
F move_move_iterator(I f, I l, F r,
                                   typename ::boost::move_detail::disable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0)
{
   return std::copy(f.base(), l.base(), r);
}
*/

}  //namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F copy_or_move(I f, I l, F r,
                             typename ::boost::move_detail::enable_if< move_detail::is_move_iterator<I> >::type* = 0)
{
   return ::boost::move_detail::move_move_iterator(f, l, r);
}

/// @endcond

//! <b>Effects</b>:
//!   \code
//!   for (; first != last; ++result, ++first)
//!      new (static_cast<void*>(&*result))
//!         typename iterator_traits<ForwardIterator>::value_type(*first);
//!   \endcode
//!
//! <b>Returns</b>: result
//!
//! <b>Note</b>: This function is provided because
//!   <i>std::uninitialized_copy</i> from some STL implementations
//!    is not compatible with <i>move_iterator</i>
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_copy_or_move(I f, I l, F r
   /// @cond
   ,typename ::boost::move_detail::disable_if< move_detail::is_move_iterator<I> >::type* = 0
   /// @endcond
   )
{
   return std::uninitialized_copy(f, l, r);
}

//! <b>Effects</b>:
//!   \code
//!   for (; first != last; ++result, ++first)
//!      *result = *first;
//!   \endcode
//!
//! <b>Returns</b>: result
//!
//! <b>Note</b>: This function is provided because
//!   <i>std::uninitialized_copy</i> from some STL implementations
//!    is not compatible with <i>move_iterator</i>
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F copy_or_move(I f, I l, F r
   /// @cond
   ,typename ::boost::move_detail::disable_if< move_detail::is_move_iterator<I> >::type* = 0
   /// @endcond
   )
{
   return std::copy(f, l, r);
}

}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_ALGORITHM_HPP

/* algorithm.hpp
4rsPp/8oc232J7XbTpwS0l9kZrIyiILd7Yk63mNkzOhSKv7naL38SnkO4F3e+Ia6zFphZzH2JcPcljwwkUm4kECrjh21BEr5v9A+rld5EDeK9jO/X0HblOrKzSuNeHKMTkUp1y5LnfiIAvjpqdwpPLLcMYhNL1fiGux4ecECX5uibnt8lLTpzoOzXk9bvv9AxlU49qeG/Zl71LB4JHkStvE/zNtkvQt44FvfqhwTo0clwgYuycV5LTc7vq0x/9bm10wYHlyLjoS32lyf3ymWydbkjJYtx5l5wQVzMVSGHe0mapBmCpTbIFKumagFOE/DbgZU89vpnfHvsTqa6rGi0hK5Uota6aRUpb/Abwbk2962IJQpcUu7t5Nk8wsZgf4TzO4AaVKniLQO4ydE+aOR8KOmcFnwEhnx51TEv52gIb4fiMUuE9QkyoJXypDrVcgfpCCDgOSHERrB785qb2l4cfBqGfoBFbpZhuaf4Qn00MYsE19L6X6LwyJulwd6mW2RKnMJ6STesQJvGfAi7KnaV9a4OPgpGe+XVLwzFbz+sjoVL3BJqxS8CJYO9Mt4f5+j4X3KQgaV1AVmV2JgdH8RSLoVTl+ga2kLTw7WoynUbBDtbCvRettg4eTYYQZfMdWwBih/usZS/tyMuEdeZ2HGOGZcjeu6kX1ukTGeGX5RxSYyPMxYiCrwImNcQm7kTUEekFvcKJqJyhTjSlGpXGRjUSF+O+XfHF/h3GVYWfxVQMvaP3T2c97f0zilYt8duA/Q7BD6i7A3rIiwsuFmzBhXtQkFOKvlC+PUuniOPR8ozECL6JN3xYZNDcUrox1OfNwtCAatP0Jj0EdBA9oFZupUT7V3R/08lcMiGu26ISDjZgZ4vjEMz7IUnnHAwz7lC3w78FkjfMBFXWT8Oovt5mvwsRYssE4sMEyRqK8Dq7ZsltmduADBcbtwg5EZn2XGXEzNbT2wdZjTw5wKLnQuFQT5BWafCAy6+7PSZ2C1gg4A38NV9IxCJoA6oJLqpNpyRdDyczWm+hNdT3t/j+0sg/zwMfe/C24Ftg/r3O3j1c4lqsAeBPRhN0tuPy6iAh+3ejueI0GPg1dtdWkz81XIBlQFP2S53TmDclucHT97jNldPNPsvhz/T8b/9+H//gqz+2n8+wX+TQJ3XqkwzpHfb0rpPxj9NICE55jLi/boGmwPhWFpgb3LbbX5UF7hlP9/qoKPWzzio0ZUP7cIVKvNugiatNxBtmZBrUO3pmvPl729kqztocA9vOBwKbSNksIR6H1oisZv6PIAsaM5/q2V82dqJ6IcCRh5DKRxj64lzX84N4WfWNCPUWHR6u+fLM7Xmm7iZvEoMACY6CNJFi/k5+2Ek82BPVhZyHY4ByIa/of0+K+S8QPdlQ0FeN7WpJwvno8f80XWpWrWafgxW2RVqVnlgo7xJC8wtIGf4Fu0jzTaIbxkkFGHrqX6X6ofn2ASu+jHjlav1Foto1oMaf5P4JO3GpWo1Rx2Q9dC56DjMBxhL/JsmnPNjkZpOPL7PagHQAsBTwMV2CLgb0vJ0xHrEbYlM7lvGErPxGfVYDg549BDRGAjguVoABtQ/CkruUti82lXM91wu2TLt2fNz8iEFWyDFZw4uVV/M/FqbSLTWg6LQ9Yz0T0c3KF7qM5dCJBwv1IKu4BBAYh38aTuGjblQAglHPGfwbofBbM/gJQaf1ij3DxzbCgH9plDE4Sb93dD7BWn/xgeUu49oAJYFIAJ+9MB9isAMJlcYsaLQ7qe18lClttCY5vDdgoAlBDuXYwmQMqFAVXMsiTK6F3BUcBbOC7z6Q63C3gMxIvcHwx/tP3y/gnsPx0kMOawV0Qz0AnoII8=
*/