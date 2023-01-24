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
u0ExjNQYzE//qMpLKB6gF3BwvpqFhnuMnm8vBkSNGEXbkHHanm5c8iKSlj60NBLr84pRiGGK+znKjPO4wALBfmEhH5tWND5uIlvWc1BYiGblrVewRR7Hlwa6Lcxan+1sV4uB9lmbLmXdc8lW7saXzfeddv9tyWngQVjTCz6bZTY4Cmqthd0tKiwLsqATL9Zxf6ETlQf7hDXa6EddRKPDm9VoV9Hov81qo7FZ4Fqjl7MdmxK+m0e0A+Oj/f0WwZLttDq+JkAOJjQOiFcFZHPX5gDy/J0ckGs0QF5i7/otgtXbPa3fIljM062O8zwc10QlqwkQSjoLEAY2C4RoAcKKSBWEDnfCAIzMphZ/urLxFhd1Ei3u6tKcFheN5C26tBbfHAmeRVdYNDQUjyQivDpSkF8ahH5vDJBDMQKQIc0CxCYA2WNSm+1EgERpgJg5IF+Ymg1IfxWQdZ2bA8gzmRyQLA2Q4kwEJFoDZGYmAZLSfECe7ygAub5ZgIQLQA5HaP3PxNmYoc7GffGN08PFS0SjpZ2a0+i8O3ijk7RGn7sDG81SG72/iUYfURsd1qxGO4lGI7RGL6VGs9VGT/VuvNHvbaLRfTHNafTt23mjL4WrjS69HRsdpzb6ZBON3qo2en+zGr1aNHql1mgSezfWuw7Wbb9nArX72OWNtzu/g2i3qmNz2l05grcLqnPe7poRqPXM513IUBZBVVLRazxe
*/