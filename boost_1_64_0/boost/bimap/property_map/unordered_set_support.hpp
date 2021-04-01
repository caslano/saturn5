// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file property_map/unordered_set_support.hpp
/// \brief Support for the property map concept.

#ifndef BOOST_BIMAP_PROPERTY_MAP_UNORDERED_SET_SUPPORT_HPP
#define BOOST_BIMAP_PROPERTY_MAP_UNORDERED_SET_SUPPORT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/property_map/property_map.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/support/data_type_by.hpp>
#include <boost/bimap/support/key_type_by.hpp>

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {

template< class Tag, class Bimap >
struct property_traits< ::boost::bimaps::views::unordered_map_view<Tag,Bimap> >
{
    typedef BOOST_DEDUCED_TYPENAME
        ::boost::bimaps::support::data_type_by<Tag,Bimap>::type value_type;
    typedef BOOST_DEDUCED_TYPENAME
        ::boost::bimaps::support:: key_type_by<Tag,Bimap>::type   key_type;

    typedef readable_property_map_tag category;
};


template< class Tag, class Bimap >
const BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::data_type_by<Tag,Bimap>::type &
    get(const ::boost::bimaps::views::unordered_map_view<Tag,Bimap> & m,
        const BOOST_DEDUCED_TYPENAME
            ::boost::bimaps::support::key_type_by<Tag,Bimap>::type & key)
{
    return m.at(key);
}

} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_PROPERTY_MAP_UNORDERED_SET_SUPPORT_HPP

/* unordered_set_support.hpp
D0x/okdCGnzX5FnGULqF1J+/ewsHCqd9iwXnrojefxjb4RaOKLD/gWV/3hZk1AFDkoLY8Lupp4ZVX4LrBtc3UDFcJCrcdeJd20Jepw5z5LciJOWlTt1FzW5bwfUug6riWWm0+q9pXf/sFBsXU6+c+P/WXH6PLJOFcm0Ksbbn+z6elSy+0saDhJV1LDTOYKKf4JW7DwTeuiY1zPrXXvzNwz5IWJ275pc0qkfRTjvXres2fVyC0zsA+KbJ5vd3CWY/1hj5O/5nXuq9Z7VJ7LvxtbZa0hmSmc/oyg5HgkqjF81pVpjv7mOt8NA+x1YYqK+Jce/kQEkM6RzAPwnbu8HuRwr6j+8IQSZIRuVt6AORfKO2OGoQ6zJcpWNYn0V3t4q7YEIumIUI1u/8VCD4lT1QKqAVosOgo+/q/1EFXy/dIWkHG0Rfwesvc3Kzb02AQiDkTpou+6ukee5npHuHCu4z+ibm8rqzu4fMFncUAKAK5DGf2fZ/uS17+nyPMKdSEDXHlcAHOwd8p5FV7ecmOyboH0zmnJpMX8mDyvMb0vih6GNYfigOcbqjjNbndA==
*/