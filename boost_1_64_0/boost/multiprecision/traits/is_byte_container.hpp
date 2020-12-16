///////////////////////////////////////////////////////////////////////////////
//  Copyright 2015 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_IS_BYTE_CONTAINER_HPP
#define BOOST_IS_BYTE_CONTAINER_HPP

#include <iterator>
#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_cv.hpp>

namespace boost { namespace multiprecision { namespace detail {

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_member_const_iterator, const_iterator, false)

template <class C, bool b>
struct is_byte_container_imp
{
   // Note: Don't use C::value_type as this is a rather widespread typedef, even for non-range types
   typedef typename boost::remove_cv<typename std::iterator_traits<typename C::const_iterator>::value_type>::type container_value_type;
   static const bool                                                                                              value = boost::is_integral<container_value_type>::value && (sizeof(container_value_type) == 1);
};

template <class C>
struct is_byte_container_imp<C, false> : public boost::false_type
{};

template <class C>
struct is_byte_container : public is_byte_container_imp<C, has_member_const_iterator<C>::value>
{};

}}} // namespace boost::multiprecision::detail

#endif // BOOST_IS_BYTE_CONTAINER_HPP

/* is_byte_container.hpp
YyMSf20Tp8dGcD339YAj6ERl6MnrVas9WG+A8MofpXXUyqSus01d9PAJyrxJyni1BO9//mtIuln5OMwsh9qat4+04p3p0DpQt2/0bUYeZZdHeTWY0xhjHDNLKQ/uYnmaCCf0yjCO7rg/qc5al7o+LxRumkeWlzvteap5HKKG1+/Su2y6HtcXQeLmflIm/1PPwpkO6tHv+vk3+VQ+SkB+3DlMGHMi31OGvcmBfvUyAa1ZDHPcfJlAxeMq8TJX6aD7UUcYxuRpXYE4kIJ6p7Uez8VRDa8/43qZuUU4fO5r+RO4wben3bMypnFqHYpD6/FbkFNFslYDV5xoa7I6fhrfMdDe8tmKmHFsrd7D8dFH4n1xmOcvmV9YXVxZXgZxzX+fQ1EZN8LpPCTstwAMJqtmB2FvlWHVeJLmIGQY7XUa3MO73biHN3NK3/bvuJ3Huv/huh3JXGxD+FzSiIx/9XYujQi1PILlwAYnwhQQB88ic44+kiVbY20c1KTtnd+CnO4yzgjQyBu/iXVevG5cvhU1P3sAskEL/5gKn5iYBITCf07hU0/Rw+/aXocfPMT4oQqfOjAhw7W9M6My7mh7kP+voPDKtr5v8CphlX2J0XwaYRgHJvcawqp46Gdsr0kMexwyjPbjjNbl7IH0hhSFoWUKf/sgHDWTjl1bMJyXyzUKkwmj8G9SeJUomu/dqsIxQZpNCgeTWvjYNgynck/hZ7VwsEDhe8cH4aCJ6mcq83h1YQWeFDjwlP2sfn4J7UhfEk5pfiKe0zXq59tlGPmB7o0YY/Gs7O6UdnE/Cd+PegV+tqBNCFZ7bO6n0gD6txg234Jhhs2bGNZi8+o2tIl3utXlX7O5tbY5p+XrHtCz1bB3FsMMezdkGNkj356r7U11qM4x326rbU5V9YK1fduMcnrXCISZ/sYwIy67RjGsmfbnU1wwGjzt4yoeQzzt4y1pH29J+3iLvb21vckWe9tre5OGve0t9ra32Nve0t7/eqsx5+ynaZa4d9zHVnM/13V9U24K+mzXEjPPLT3sqNLbf3o/8J6YLtnlPjSBPXP6llf7dgn3njshSfo3YP+IjuMH/wCcGltbZXskNuF0Try0k0cu8dZGN+cVdky8ybHNefhyG/UzGE+dY0amNieyhXGws4EEsnWrgbOoE+8tW02eHnVtHXBbO29ueX1pTSsXF1i5SERpW2UROHc8p4nl+ltPhDon9+6snOjJYzZVXf82hB8bQzsn1hcW1xaWOoDX5z2uAaYNKsinP8f5rmFCZKcrMubwF0c0DtrDLNLKzNNGW3A5ZCYd8C3TObT1ndqh1zG8WhzcTXmqYehibW1z31bEtLVNTPMEux8CcDk9iJ1DdNjcGt1rj+0D4iij5jKr8A+w8MbyJsmX4zUPafrZHBnOR3J1sogzs73JMdc7r7Rw2vZqztyjyTP3al5t4fB1TtxPxctpUNqZkwd3vE5xlN5S5W/KZLmThHZht4+1Fs0h+PJJPLEyd+SwgO610vnYMa7Tt8ogTErnNs6/NHTqd4ffa5iP0usrPFFm8C7AcJOHzxXBYTI4o8bHRe9q4arhFd3VPdLk1Pf20hmWRyt9LVw10wMTo6RzzyjnNXaxAYfm9Tbh1vFUdKrHO8eafBgXUxxf2Y6rl0SJd7Odp9xIvMUtTR4OppVCuve4hVdPNRNnZmuTU28XJt9dbuPA6tAp7BFgQjXu07a1cPvtfr7Sym36mfbyjHO+ebLp0TTH386r00W817Tx1np9pZDuXb4H51Wzo2vL1QS2dn7A4Ol1hdr8e3KOGfe3mjiWO7RX+Zl47g6Dhzdm414VaU6Lk8HTyx3t27wX52hlieL9LoOD5UiPz64=
*/