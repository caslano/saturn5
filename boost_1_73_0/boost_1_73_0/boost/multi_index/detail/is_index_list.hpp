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
MTEuY1VUBQABtkgkYM1UbW/bNhD+rl9xy4DBDrTICdCgrdthnq20whQpsOQVAQIQtERbHCRSIKk4RtP/viMtx2nRzhiQD6NfKB7vnufu4YnB6csND07h6CDuR3Dg7CJulPybFeb73oQ8wu6DUXc4HyMJ4BDySIZwPOQRBi6E9Czv7DMhx4jubG72L7CRd8Q+ogXDbORUtlvF15WBwXQI52/evIZf4WJ0MfJhRgVnNWSGiSVTax/elc7ye0UfHs40+80HZoDWZz1UXnENWq7MhioG+FzzggnNSqAaSqYLxZe44AJMxWDFawbT9OY2Sj74sKl4UVmQrexAV7KrS6joPQPFCsbvdxgtVQbkCsMRvOTaIGBnuBRnyM3AMNVoi2Hpaa0l0HvKa7pEImqgMqbVb4Og6FSN2QelLHRQ7Ms/q0zzVMktJtHQLcjWgJHQaeaD9fShkSVf2RkFQWPbLWuuK/+QDVKJMpAKNKtri4VxnOld2gyyXh7fukGLGXNjJy2FtlSbSjZfOaKOFmXVKYFEqAM6lRJl9qETJVPO2VW+p+g1dQL/8GgO+ZYgBSYDJ5MMouwEllRz7cOnKP+YLnL4NJnPJ0l+C+kVTJJbC/ZnlMzw6DmSKWAPrWIayRXwpq05K3vOlxuB9zMXRd2V
*/