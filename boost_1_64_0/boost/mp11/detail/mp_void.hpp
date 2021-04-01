#ifndef BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost
{
namespace mp11
{

// mp_void<T...>
namespace detail
{

template<class... T> struct mp_void_impl
{
    using type = void;
};

} // namespace detail

template<class... T> using mp_void = typename detail::mp_void_impl<T...>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED

/* mp_void.hpp
R7il8uZOrm2ozhcOazbK2SF//r+0vCBQCq3A/j2piZiROZpxV1v7qfgGIOnL3Npip9ov8zaPdZyt2kNKJCd+MdHi6xCLGueZ6T6EIU93kmzpGqRcNEnnAyQypwJig53JVFlxp/sdHU8L4yr+VAtwL/sNXSxPbI2EHMbwb2hazs1bW1k6z/+fhdSMDtz3rriv0ZZFoHC+26Pf0Klw6wC+fav1TkBd9xiU7AgV143Q4SxHykXmpnL2BOPboFsY1akF7XYBk+T26A3PO3PSr9aNg9HBbyXK3HbOUz89gb9avup/FzRupiGvHWQ4f5t0oq5UzYlBwoO6UQW9CcO5kQARweOTHp5CTUxQSkHbUAAnoT6onU7kzlKVhqNLYXRhlHJo3ixIJVRtLe48sOvxHYs32RaQZlExw/Ie0qIjgJ0DfiLDztDxYt4eaJPymhEYVwD/h5ECCQ+dP+O6b7Etxlp3QwkGV5gdQGQr36gq0C5tUf5p0tkM7ZRu+Ud7sYsSv+GMss5bx/guXCsE5qVDIh/mP1MKrgAx1LFpR8+pNPHtXZoW2OheuvpyozKtNA==
*/