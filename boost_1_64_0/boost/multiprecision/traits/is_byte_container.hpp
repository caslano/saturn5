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
kaDf9G1pawC3k2/ooo1N0WBKYil7IY/zUFdP0diNNwlCSkCERVE4FzRWeXMIaWOt8X33fNhHWrRNZN2BtfhcIh/am+FIA0w8hB7LDKSELGPwi9KgkdFs6m5IzeMjr9yQXdbsHe9MHOfG6JQnzvsOsjrhtGexdkgcWBUexyYB4BYfm6/188iqtVg9nsc5zu/q6cNqmVT/UDaqVg3L8gIKe8J09lr0ZdOTkkkLzkNryO37uce2h9tzOVPEkps3tuC/yF+K1yB+0Ixebv27EtYdXLBknNuZqLcohkyPERTmzWn3lyr3hZ1AU9haw6ona2frOV0FO5JFqeA6Hr0jlsqCEyCcVK5jOoKDSsSngN9VEbEVBl0C9RE+MkscCbZRtaV6wQo+aZPeWi7V3u2XzAVZhwyzrwE8r43SiWN9YqCsmcXyLpNHLJqa/XjFpzhzcFXNqgbXY0nsoCLefPZsEt8W3owNx1zf21EK+0hXrzd+nZx+Z7n/tBV8nei09rlID5rrIhDO/vDRGhMI7MWaT/nGMyYcINuOHgcJMK57rnh++iPhxvL7yom/Z90oAw==
*/