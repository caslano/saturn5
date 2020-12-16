//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP
#define BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/stable_vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using stable_vector = boost::container::stable_vector<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a stable_vector
//! that uses a polymorphic allocator
template<class T>
struct stable_vector_of
{
   typedef boost::container::stable_vector
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP

/* stable_vector.hpp
Rn0cpZj7mkeZLzVfZ84xbzDvhMuz5jfNR8xfmvtGO6LTorOi86MLox+PfjX6D9GfRffuk9BnQp/pfbL65Pcp6VPV5zd9Pujz+b8uQX3j+k7qe2vfgr7FfZ/p29i3te/XfaMt4yzXWVyWByyPW163HLX0WPr3S+l3Y7+8ftv61fR7t9/Jft/2i+4/qv/0/vP6F/R/uH9d/7f7n+z/df/eMdExo2MmxdwckxfzQMzTMW/EHIn5OEZnjbEOszqt6dZF1kLrE9bfWA9aT1t7DRg0YPKAjAErBmwb8PyApgGfDOgda4v9SexPY/NjS2P3xB6M/STWODBhoHPgrQPXDCwd+NzA9wYeHfjVQJNttC3NdqVthu0q20zb1bZc22bbVtsvbW/Ymm1tto9tX9j+YesTFxd3aVxqXGacK25t3Oa4rXHlcU/FvRD3alxjXHvcp3FKvCXeET89fk78ovg18Q/FPx7/6/hD8R3xAYOiByUNun7QskFbB9UMenNQxyAlITxhRMKMhNsTNiXsSng94XDC1wlRgx2Drxl85+CiwU8O/u3gY4N7BvcbMn7IlUNuH7JpSMWQV4ccHPLBkK+G9B6aMPSKobcNLRh679DSodVweWVoy9DOoV8ODbMPtdvtw+zD7SPsifZUe6Y9x77c/pD9Bftr9vftXfYee/SwscMmD7tl2PJh9w/bPax+2PFhfx8WNXz08KuGZw9fN7x4+M7hjw1/avjzw18Z/tvh7w7/cPhfh6sjho5wjpg+4poRWSOWj9g+4skRDSM+GqFPjEt0Js5JXJ/4aOLLib9NPJz4VaJ+ZDBcwkb2G3nJyNkjl40sGfn8yHdHdo40jkoYNW7UdaNco4pHVY16c9TxUd+Nihk9YfQto1ePfmj0ntEHR38yupcjwXGFY55jmWOro8Zx0NHpCBpjHzN9zO1j7h6zY8xLY1rGfDEmcqxj7LVjF48tHvvM2P1jP4HVfci4qePmj9s4rmLca+OOjusZF5qUmHRV0qKkoqTdSQ1JHyXpk23JY5KvTs5KXp58378uDybvSH44uTL5Bbi8lXw4+ZPk08mfJn+XHDreMn7k+Knj08fPH79q/MbxmzUu94wvGr9t/PYfuOhgWxkC21oLXHXwtb/ST7HCVdyKawxc+8HZiwHie7j0Fz/B3kuFr+L7gXAbC7ehcBkI9/T3Pr4fRITD1XOBn6HVCLiq8DUO4kOgLRM82gq34qvncSKDVbGCWqEazwVqI5d+nlt4hEW69PXeRsMF6+gHewzxtQ9cQ8R953CJhmvQ9+0bRH68QLV4MUBLA+FRsBmCnsTBZZASCV/NSry4wk/xIh+MSF+4VaElGD+4il5FQ3wsfI2EcYgUtcItjD1cTN9fVfiqiiVCLmIMQsR9kMPTB1WMr3eMY8U9Qjz3e+71LANxgRr6it6IW/gKR3KecYIacSxViLCKsRWVgoeieG/xn0U4XAZCnXALX8XSFxdxG+W5lS6e5SLqEMtZ3BMOj4qAr+Hws5gBMZ4rXIK//xoGESbxnWhP1AYKcXDvAHIRKm6t4gqXgeKrR+ASB61bPEuJLEGYn2IWgISKMRZX+B6vZvjqfxH3R+Pcgu9NUIkK8X1hyQ0UV7EmwNeB8CjIDzlFHaIKm6jGU5GoU7pE4XdieYuvon/w2FioS2RV4OsAuA2C6mn9ohIVLB5UFQZfcWnjGhsnvheZxS1IiGL0XER/xVwUow0i5lUkVGIT/ZAunnZFX43iGA4ioQ+iRqGiUtFXuMUxF5WLntvEPXjxjo5JxMBjxBXbj8DvsEXxSPIT3hOLjxQ/o4qtCNQdRealAfpigNkjnk+YlWi4FaNlhlvP8gsRayp8NWCA9E8=
*/