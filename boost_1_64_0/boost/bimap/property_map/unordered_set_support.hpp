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
t/321bRI+paLmzPNOt32ok91kLCssq68cJJYxdaRdbXFQffG7j7Wc59rr8c2ayx6qV9Llp7Jk6Fid6uuuzb3wf5WVHC9bKU5t3ccfnZJnmS73prlWdh7Z3wOljA6OI1IQ5aYRYy/vX43z5bxeLa4rSU89JbfdKf2mNa4pliyoahuuk7Xk9ekdVDMc6LIh+pm1nOYetRgPMpfd45t/ca/e53GChkH+02zPQfueOVPuz+duSf19QGDlhx5/cbmYN3W575e8+EOzcx2ui7zVHg67AGX6577NbAP/DrMg9fDvvAm2E/X1/WH98IB8H54OnwIDoU/goWwqe6dbw6LYBo8F2apnKfO8Dxdj7q24ZqQCOtBNsTG4WJX7IpdsSt2xa7YFbti10m6TkL/v+pEyv+Pt/r/hY10jxmJyFUO96//P8/0/6siyv/X/r/2+9R9B99E53E3zZb573fkyYBXd618D7N76BTt919wvowVhPf51d8c469K/KVr33DcGMw4dfpl5wBSAfPdSHttVea/+n80bhyn2e7x0cfF/ALMh0gY1cQFd15cpM9ff4QzAH4t4b3rZjg/seT9631UZv4qo38x7mr3audHvs+jytvPU7dBGf1rLL9BOfuNVc5+mjNc+/KU+FiRnydmLbQuDhOzczGTOJh8murODN9rrOs3dsu9vsa9zJ5bkbedrmMusySMYrfASWB9RaLK7SbNJXJ/N+BOy4STwVNZCzKGk5LTVL53iri70M3AbQNZ+0ZWXw/x+xx7lJ+W8NIxe1LSssHNc3z0pR83e5cP+uNLWQ5y4tjnhjxzca/lp7IBK6zy9OSm6zkUKq/wJQnntrgwOfia7usl3lucMJnyGr9r/fbEy5bLbo9xPSrxn2LGTz6Q+1Xo86D5Qp3OdTpSj3Bj1esPnKwwmetpGq8fSLib3DeIW5qOQ70nYb/gXui21/gH098CPW7s/LDLmXCD+V0q9x7rDmGs5mot54WEnSPxHKDlEoxj67hm7PoocR6hnHFn0lPipuA2IC9BZacfw979oKz0tRJHT195vic7Pe98Iye9n6NmXTyzfCPr/PxwGetp54fLWE8+P1zGuu/8cBnrh0vCZax/XBIuYz1+rDHrZ/yOCZenvt8zM/F72zMz8fvtmHB56i95ZiZ+P/HMTPwe98w0fqmp0yOMj81R2ekNx8eqooyP1UeRn74qgvz0NRHkoq/6D5SL/pCMo516VqfLb5j6wV23bC99sHFexhNHHkfLCbYr2m7Www5ynq23DyoXZqpc9Cx4HszWcbM28FY1fxi2hdt0/O1plc34GcyBf4Md4HzCzoULYSd4O+wGt6hMxldhd9iEB68nPAX2gpmwNxwL+8BJal4F82Ctyk/fo/LT34ED4cfwNHgIFsBmzBcMgr1Unnoflad+CxwC71K56o/CYbBnUC75MYzhbYuN4cWu2BW7Ylfs+i+6TkL/f+HsmSdu/79r9f9/nOjItY72Ok1Z1pFvjnNN/597m+5/tPP/1H17I1vpTNH3jIt0/l+xcd/GrBcYIvrecd4c/oK6+TMramvUTzocJG76xelcsYaRGXWtQIVxk+cG57hLRvn1Ob4U5wGXfracBaRmkc4QtNcDaFh6lp/Rl8RFGyP4qdhf5GvtDPLZ/Xw7nM2h4WifbHHIGoE0iZ/PydI1Ai+I+6t852L2J7eJ8znK8zt/Rs28PCdL++e14vZuXzcnkXs35lstLvRcPc2n6XKPB6gal0XMK3sMQvoBjDcE9478Xdx96LzoJMg4xDw9vz6hGHOkOgXcYmjldUvnesxxi3m8Zd7FudU15whGOOtsIsG8JGm6wTfP2Sll6M/T98XsWl9oPvQVP3M=
*/