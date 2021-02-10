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
CAAAJQAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvcG9wMy11aWRsLmNVVAUAAbZIJGCtVVuP2kYUfvevOKWqCsjF242UNlmyKmJpi7IBikGrlVayxvbxelLb48yMYVE2/73n+FKI0oo8xFzGHs93ORePveG3OxwYwtkjqH8BHTTWiJVW7zGy/706CJ6h+RDqgcZzIh4cIc/BAM5DnqFfQ4JWZcznQXBO6IG98Z/HyIeAT2mGYIycqvKg5WNqoT8dwM+vXv0KP8HlxeWFCzeikJiBb7EIUT+6MI7rmd9S8fQ0MnjtAloQ2ail2qTSgFGJ3QuNQOeZjLAwGIMwEKOJtAzpQhZgU4REZgjT5ep+vvjDhX0qo5RJDqoCk6oqiyEVOwSNEcpdw1EKbUElBCfyWBpLhJWVqhiRNoJFnRvmYHmRGQViJ2QmQhISFlJrS/Pa86JKZ+Tei1VkvKgLf5Ta/N9I7slELg6gSgtWQWXQBV7pQq5imfBICaHJsgozaVL36IakithTGgxmGXMRTqJpbCP4bXpcXgYlOZaWB6MKw1L7VOWfLaQ8MktS6YKEKA+0KFaUZheqIkZdL64j7yTanNYJ/t/SHP3GoAoyA72JD3O/B6Ew0rhwN9/8udxu4G6yXk8Wm3tY/g6T
*/