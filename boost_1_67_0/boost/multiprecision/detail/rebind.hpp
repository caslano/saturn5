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
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
*/