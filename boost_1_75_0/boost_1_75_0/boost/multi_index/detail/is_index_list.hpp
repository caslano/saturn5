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
EBl7dijJ1J+iaPowxsrHj2tCjLaTKGArfuZOLQaOHnX6iV9NFMzUag19/mgkSvng6D9NEacp0ud2DjYFZ+t19pKvyGwazl8MMTUhOyPdXvI+Ur++zSoRkHQCIZOAclnsmwVJqQjmCFyBseYsuRINdICGuBE/yyyB5HautZci/7rKRuHkMTpngJGxggJF1ypck2yUdb0gKCdooTu0oNflSKuwr0WtGo1HOVEXhZ3/it4rSqJLfFjUVa+mfWrT4+SjG+GS96MAuG6toPiFCkl13B/DFP9+E+s6mxoljZDYgVF1OMJ6wfSs9XagNobE8tElAbw8wiIKin8pmqbYg1lJRRklSWiK7k2Es7QELjL4ePbGi7M1gxWMemep7eNtRdvU5E/iLpck85lypQYfR4UhU/AhBs5UKwEnwoMW2LdS+R2ZszqTQRfejB/nukNRmh8nSZOOqY6YtiRNyoanrzspDZwdZyiLGJq4bzcSYfXXJuLI1/+Tkv/ZlWw3Bf23w3kdwxkd7MpBoJey5GfQy8WlVmT56QoOb98qcjjxtpMCL5GzRX/ANEFA90+RfReFuJSfYuMvxyL4kHJIQqLgpfRIppADOV2UZZ2JatBU4JI8oosaD/fMd2GKuBGqcugTpBZGoDfyfiWmHTmcriokIzVynoxx+/powhDfuyhYRcHvfXPIxfIQpWNbn33SROns3urNLPUn6Ne9qpaIde8R
*/