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
xBud9E3MEk0s2GBP2M5aARc8jqJ3KwD8FSoG6no0XncLp294dtWecNHd4ibyt5cpHKi9aDZ46qlyqS3d0vyS4PSnqp1a8sfYZpeMhpIHLoiSTzfRZhxMj6VI0pXKlsFGQFAJjUbhQDbEVT61qk+bACKKkQZ4Iqp6N0zgqim4U0Xr5Jfo9c7AH8B/FkCT0p+2Mpt4sGLyunThPJFyVtUUo2jmocabsRacwg6+SGsbhMfrEouyjtZ4qhJLjfO4ZyTmIBMZFo6c9XmTweAZIzgB4wBYG7EceOMv3mUgvF0WThzyAHFIioQGH6LZB0fhu8+bdN/xopdgL6pFuQ4GSY2bKqSGKPKaFxhvzJr/wznCjFR9D6Hlhu7/Afazle6dGAIYsVso8O/XI4yaDyxrfgGvPZuzEM85QRe9uzVNF3C+UDVP5cJfX9rknJuXxYpU30v5n2lG/mzIfxXlT2sifyeWf1wkrQ3I3M4x+anqzb9Fl9Z2bbx8IvGba2x6fmPNVvnNWMZw2Io5D1bMqmGsWms0LV/WK2h/wPZ6FJiObewocCD0wMxXVMrDRBkYeggiVmWGOgqBqcuHxdoPssCUu/iKQCuq+y6+ItRw0rJqiz9SS7VZfg2Xa33kN53/3mdI6oD93y7a/xlQttbiCt2rOb544BLhfjTrEhJzcjvS8+sYem6PQQ/Wj/DX9/PnF/zzx/T5XZ5cxJ838WzzYjS/
*/