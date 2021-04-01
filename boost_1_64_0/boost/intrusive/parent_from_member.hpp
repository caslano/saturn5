/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2010-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP
#define BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/parent_from_member.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Given a pointer to a member and its corresponding pointer to data member,
//! this function returns the pointer of the parent containing that member.
//! Note: this function does not work with pointer to members that rely on
//! virtual inheritance.
template<class Parent, class Member>
BOOST_INTRUSIVE_FORCEINLINE Parent *get_parent_from_member(Member *member, const Member Parent::* ptr_to_member)
{  return ::boost::intrusive::detail::parent_from_member(member, ptr_to_member);  }

//! Given a const pointer to a member and its corresponding const pointer to data member,
//! this function returns the const pointer of the parent containing that member.
//! Note: this function does not work with pointer to members that rely on
//! virtual inheritance.
template<class Parent, class Member>
BOOST_INTRUSIVE_FORCEINLINE const Parent *get_parent_from_member(const Member *member, const Member Parent::* ptr_to_member)
{  return ::boost::intrusive::detail::parent_from_member(member, ptr_to_member);  }

}  //namespace intrusive {
}  //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP

/* parent_from_member.hpp
fwwNkt2PQmDgM5mEntjGppREcjbDP4IcjUcvfWg0mOWd1CEozLovmko5Frs1rh/ept5MHT6iM3PHKHFk+oYskihKoP7WKLH3fak97qjS8D/kGvn8Vt8Gd+N0KxOF7uwQdYZzuZtEM5yVdJHCO/JNAKZnTBCOncHi5wGpTVl0lc01nLmPZ6w9wS2NupPMT6IR+wIQ5zq3GGe6Pnb85cqlCSR8c4ss36TM3uEr54DYf0sHi+4eHk0XkZbz1RsJN59zmM9LeDvhN+pj9a1l5C0pqaUe4IpDF83BiB6U3+5ZNcr4Zguxc6mvGWSoNmKe7DvLztNedzugN4kXwazEn7k0TR1mT04dyR63nhqYQ9vahfxW9Byn9ORdahO9MBj+sUgK5k0zvn2Jx4OqO+mpuPXwreHoIju3v4MIjMMIVDItJaQq7DYB/D0FYd48PhDmIIOV4h1sV3WclXmxNrd+IllekVV+tCARQox943Suh5Jse5eNTjc6Kscorja8Cspe0GWbVCjwpUutU0YLWz6z/7lCqmFIdcH6aFl6IpHzB3DSy/rhcJhcmTNW493BNA==
*/