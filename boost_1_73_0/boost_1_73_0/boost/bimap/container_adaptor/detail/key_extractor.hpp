// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/key_extractor.hpp
/// \brief Key extractor for a pair<Key,Data>.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Key Extractor

template < class T >
struct key_from_pair_extractor 
{
    typedef T argument_type;
    typedef BOOST_DEDUCED_TYPENAME T::first_type result_type;

    result_type operator()( const T & p ) { return p.first; }
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP



/* key_extractor.hpp
KbvI/slidrWzjT+q5NofnQ5wPbsulrvz5O6dwj0s3EfCfSOcy21GekG36cJ7wnUZu4bCFdel6zZhY26j1GM6eJq8PjGjg7/ErW2qlgJ3Z3Twpm8n+9bzp86dMW1hWp+e3n/3lcVsvV1kBJ9vo48LmnNZmYwXc/num/ZI5VH347fJelD0V/RPLsdEygL5VFnhh5bo6YhGpeZMnTpX9qVcyd7Pt2fCSzdruKsd8yZYviuobrfSB125zrpxL2ZGuyc=
*/