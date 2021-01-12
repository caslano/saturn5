//  boost lockfree: allocator rebind helper
//
//  Copyright (C) 2017 Minmin Gong
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED
#define BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED

#include <memory>

namespace boost    {
namespace lockfree {
namespace detail   {

template <class allocator_type, class value_type>
struct allocator_rebind_helper
{
#if !defined( BOOST_NO_CXX11_ALLOCATOR )
    typedef typename std::allocator_traits<allocator_type>::template rebind_alloc<value_type> type;
#else
    typedef typename allocator_type::template rebind<value_type>::other type;
#endif
};

} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED */

/* allocator_rebind_helper.hpp
NjIQrSbyIOi1Gq3wH9HoUjgn95yGE41fUqLSlJ+KRfVVTiuRFkGvXUsk0Q+pfvmh+RLV/QmiFfcu0OvA1vgbH1HoHKLJQqUV95dxlQzSW6LxaSCllukabczAy4sopUyLiVLKkTyqZUedl1pe67R6zMuCKKVc1hOllMXDRCn5X87C+b9Bpft4uRCl5NsmopS8sqh0OejNKi2ArlDpc8irSu03HTQlVs3bLUQp+UljbzU/qdDV
*/