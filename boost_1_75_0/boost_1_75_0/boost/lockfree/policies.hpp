// boost lockfree
//
// Copyright (C) 2011 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_POLICIES_HPP_INCLUDED
#define BOOST_LOCKFREE_POLICIES_HPP_INCLUDED

#include <boost/parameter/template_keyword.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost {
namespace lockfree {

#ifndef BOOST_DOXYGEN_INVOKED
namespace tag { struct allocator ; }
namespace tag { struct fixed_sized; }
namespace tag { struct capacity; }

#endif

/** Configures a data structure as \b fixed-sized.
 *
 *  The internal nodes are stored inside an array and they are addressed by array indexing. This limits the possible size of the
 *  queue to the number of elements that can be addressed by the index type (usually 2**16-2), but on platforms that lack
 *  double-width compare-and-exchange instructions, this is the best way to achieve lock-freedom.
 *  This implies that a data structure is bounded.
 * */
template <bool IsFixedSized>
struct fixed_sized:
    boost::parameter::template_keyword<tag::fixed_sized, boost::mpl::bool_<IsFixedSized> >
{};

/** Sets the \b capacity of a data structure at compile-time.
 *
 * This implies that a data structure is bounded and fixed-sized.
 * */
template <size_t Size>
struct capacity:
    boost::parameter::template_keyword<tag::capacity, boost::mpl::size_t<Size> >
{};

/** Defines the \b allocator type of a data structure.
 * */
template <class Alloc>
struct allocator:
    boost::parameter::template_keyword<tag::allocator, Alloc>
{};

}
}

#endif /* BOOST_LOCKFREE_POLICIES_HPP_INCLUDED */

/* policies.hpp
okdlclX+YvX+HKjymELZbrXKXnp/aCnz5tuiu7v8dwD1MUuWYsT4G19+/r+VHdz8/6Ls4Pgnf1rZ6wwmX3J5aiSYxNkYWhvtUIs19WJOZsbTfawY7iDaTb1aqYu+GFGfa3Q2/JseY6OWhSwFu1by2/co2QlTlR9MpX2rlKOqS6vGkWVxrGVfgPWrlO3Jcr98GaXWJo2sxWRNmDkMHZXcttPKZ/u5ys4xy+aKu7xeHJ4zLueLKbl8YPvHVsXdPhdZ+vUdM0NyKwxpcmqXIwgoFJZEjmEQhjSFoampV1bvsr5sbDay5jtHsvErRUAX6g//EinVj2o0ZdhWWG5Ul3hsPUvUS6NtjY9d8kMwAhHyXaxIGk0FQ3GC/ubRoZvUAJN+JLWUzNsDZELLMg+oYB7fwUGmyP0egJIWiiZX+qoXrz5EzTIaEs9d1Y6m7YCkbXxDFklMFMuaD2R2mtR2QrW4JZZaodsj3yVcRxZwe3INRQPXc6lyEc5s5LR+L4HS7n00PbOzy7zlRa5CVK/oPoGqqG+P3Xd3+nAToQvN3wf2VOGv5JgiPrtRK6Ucg+wyUUQaON/ErAifVHOfmTpq1pZg0gby5qlgl+1GsXzw1pQmbClPqxbubl5LUzfIN7r2vMvybPscSP8ZV4iQRUkQ0MhcA6yWFL3YPkBtSE1EV2+DVh/bYJ/BkAY2w6LDFMO8sLLFraVnGroxHUQlxIX8
*/