/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_IS_INDEX_LIST_HPP
#define BOOST_MULTI_INDEX_DETAIL_IS_INDEX_LIST_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/empty.hpp>
#include <boost/mpl/is_sequence.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename T>
struct is_index_list
{
  BOOST_STATIC_CONSTANT(bool,mpl_sequence=mpl::is_sequence<T>::value);
  BOOST_STATIC_CONSTANT(bool,non_empty=!mpl::empty<T>::value);
  BOOST_STATIC_CONSTANT(bool,value=mpl_sequence&&non_empty);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* is_index_list.hpp
umT3CIlQvbbGQApK2Pdzej7u5+NSZe6DhJGowPcDiLz3M/5M3572ScB8G9F0McKlIX0rLyZPIdjUY0XRIh7miYMXf4oi12l7g+6ZEmrEWuxEV0XjfiRa2vRGubKDgDVV4SaLxUhfCnzPOlr8EFSz4FO69pMDhMUbI5uhiaJfOYTUdsfTeVZpcmjdm8md0q19CRAgjBsW1y5gbQBziKkssDjJ8YfLk2inl5lTlv7a1v9vsjAbSOEAIhT2zp97Wh7vgxLOtOrSnNxXAFEmPs35ClMedRRB5QA1tC+u9BVZdXU41XBV8quBuAOXTJHPPbc9HL5Q3y3q0PYv/1MhJE3WhO51xrrXkSBI0bUhdoqyWJZmihaRlHpxd413JX7H4hr0CR1a2RHc13xG54RHczrsqFor30FpaYgiHw615L0eiqohY0a4BDf3P0ai3KA8s1I1GnMAWidg126ttPDMXBpynBa+T5WlWtkJVXX4uOTGIIx4qDJruR5LKRVauNDviPqikPmTp6sqNtRS2v+CJrH8bJJfK30s/OKhIeRkI2ib+nhwtlJdyGB+Cf18LQ==
*/