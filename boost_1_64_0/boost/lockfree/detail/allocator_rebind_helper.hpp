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
KDM2UoDTYcD1RV5G4U+94eF41CPrKJfmkmR9e7s3nuO0KtWCWucBxEVccy2HeiDL/1YbwmDlqVjkkjc8I0zavh+3RDXLBpMDRwr2xdvmR05pOZkqSHJBZnvRcfkppXbS6O0cCeQghi7NMyfdpjJ1xySYG/6FDAMo0mfF7RvOk/1ZfFl81Tnh0ekkH1QRninM558fyt3yKLiKVZSa+iek1rAX8yv3pHIcIkwTvRfZct/SqIhsvEIEQfygJfr+CTjHFvXaZTDAIfVYm7+thnjO12S2/lD/Vr7P8VzBBxXsQIT2CYrFydSHXwC/8PHQKMVZaK/4yKIlE5xz/WCun+gScu4nny1aHo4RdsfTr2VS1S1cxVlmtYCZI5MIpX+wA3BXdjjVlOCwtGwx79oMVtsHnHuGQ6za+vUAJdp8fPBgbwbgcDIoYFwENzzyL7ldtHeKzedlPjY2Swl20IzfVl6BOsIyZFp3iXCyNQ6ZsUEC2Yjm5ImBfOksdCrTxKWW4M9xaawO40Pg9pPjE7jEAwtTtBx+dZLG8kuDVatzRmA1VRGdPl72ogpOStCujQ==
*/