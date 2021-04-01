// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file property_map/set_support.hpp
/// \brief Support for the property map concept.

#ifndef BOOST_BIMAP_PROPERTY_MAP_SET_SUPPORT_HPP
#define BOOST_BIMAP_PROPERTY_MAP_SET_SUPPORT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/property_map/property_map.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/support/data_type_by.hpp>
#include <boost/bimap/support/key_type_by.hpp>

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {

template< class Tag, class Bimap >
struct property_traits< ::boost::bimaps::views::map_view<Tag,Bimap> >
{
    typedef BOOST_DEDUCED_TYPENAME
        ::boost::bimaps::support::data_type_by<Tag,Bimap>::type value_type;
    typedef BOOST_DEDUCED_TYPENAME
        ::boost::bimaps::support:: key_type_by<Tag,Bimap>::type   key_type;

    typedef readable_property_map_tag category;
};


template< class Tag, class Bimap >
const BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::data_type_by<Tag,Bimap>::type &
    get(const ::boost::bimaps::views::map_view<Tag,Bimap> & m,
        const BOOST_DEDUCED_TYPENAME
            ::boost::bimaps::support::key_type_by<Tag,Bimap>::type & key)
{
    return m.at(key);
}

} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_PROPERTY_MAP_SET_SUPPORT_HPP

/* set_support.hpp
zqT8gWZQI2Hbs+qIrrmP4wch/biQoSPjqUqNlso09HpS/CFPel4MnJmro2+ELLBVng7eiLGdbYtrLIbs+CLXeHZcJb0NirMLOi8WHDuURIuTpzUi5Oz4uXWnRd6FxX6U/LQDnYzVfWFSeZis26LeqZflH4pdwMGzjN0fPo6adsAR1Lb4E7d9inDNefeXWvtLWHo7mKvXiy/asSk7EOF44VD+3bSyhvbOFkQpgi5lHiJbiMD1irJFupKuHr6uFRAnViBmukYU4hhPM+RCkoUyMZqBz7NTNRyjGnMNr8AW6Rjd3LNdM8eGMeN1Pvu5xziHVAFlfKxLZrmObjogQlvUL1DcaB40blhXGsVlONLSaSkB527wZLr8WmljMpa0LF5aWvFo/5LAYlxV6FPwCeGlT1iLgGxX0DwoUyK8/PRREh0BfoAyNliokms6At9yxeHilNOdy2A6fGi9W14TYKtuf76184EMEqe2nbb+Bm4972zPJZQlLWzSVdLOKSAmY5h6QIFXQ+qF8586aE4IX2QNEXfHiE82ICYgpem7JfHgKfgOZe6JNcZb3LhK3A==
*/