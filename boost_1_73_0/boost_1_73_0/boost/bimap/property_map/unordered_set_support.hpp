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
xT2TvZ0vbqj0ksQ04FOp0ZC4BpmXmcS41fx2h+c43hDGNzN/es36q+XqBekKkkNOB1XA1pFHqqBetXUmBBVQZqF6gvBAmZIfKoT5DcPHXsdExN/LIsqqGGFsbCzVKL0+meJOadqFptlDnUb6CjCyVu9cVEYWj2Qk5NU/msZiJEoRykxarv+Jz6YrzlntSrdQ1FM2FbZp+05R44dKUuY7UfhldPlydMF1EKHa1ZWn+GRhmb3o75SMB85HB2C6Xd/CkDFX7VWkYiY08Ka+nAXLt1cO3at539RDgMIcAllI2x8wTCZ9nh4AM9JmNgSf9gJ6UHQhcmyaWxizVzpmH7zmSGPQ0pNVE7i14nK1Cbb+bL2YvJu50GOaXi1zFrWa+P7dck392DMYabSM6yx15XpftQ1CvDvq2ToBX2dqfUvMpSpf0MZBw6hN/yhS+akSB88C2/nNLdU2zzkBXycx3fqb5bv17K/tzN+QGFOcUq9QJ0o3m0JEgdD+wLVHCqkVaCp3lCkbRFOgI9E0xehvoDuAWittOjiVkhm+OxZ/4DRvjqTU1D9Jnx4NgpC3LzUGkFDvYvwafjAPRc91Pn/3nMRudS3LWoMTV5NsLw4GogxFUZVf5qy90QUD8ImhVGjaEKFP9gZEeOV8cv4BUEsD
*/