///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_REBIND_HPP
#define BOOST_MP_DETAIL_REBIND_HPP

namespace boost { namespace multiprecision { namespace backends { namespace detail {
template <class value_type, class my_allocator>
struct rebind
{
#ifndef BOOST_NO_CXX11_ALLOCATOR
   typedef typename std::allocator_traits<my_allocator>::template rebind_alloc<value_type> type;
#else
   typedef typename my_allocator::template rebind<value_type>::other type;
#endif
};
}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_REBIND_HPP

/* rebind.hpp
40I5J/hgJHwuy+N0sI/xIY/nC4XcdLrgbf3uORbOd+LTHW8vuIXsFUd5vht6m5yGr284FJ/MoS0wp78XZ36hWMnP5tgWze0Rj4D7Ln+mK/Hxlc5OwJyt4HxBObC0X2x26qW1TgNbz6AdAGcbOD92HPcaDU5K63BtFzjsFfsxf7EYPG8BdNh2hBu9FWF+6coB3VnyDmCHDSYBee7+FZShS5F/3mK5ddbLvx6Xs93PTaBPS+VM
*/