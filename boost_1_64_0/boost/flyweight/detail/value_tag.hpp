/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_VALUE_TAG_HPP
#define BOOST_FLYWEIGHT_DETAIL_VALUE_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

namespace detail{

/* Three ways to indicate that a given class T is a value policy:
 *   1. Make it derived from value_marker.
 *   2. Specialize is_value to evaluate to boost::mpl::true_.
 *   3. Pass it as value<T> when defining a flyweight type.
 *
 * For the time being the interface of value policies is not public.
 */

struct value_marker{};

template<typename T>
struct is_value:is_base_and_derived<value_marker,T>
{};

template<typename T=parameter::void_>
struct value:parameter::template_keyword<value<>,T>
{};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif

/* value_tag.hpp
JWiuuHnQRqNHHPHoGL3dh2qrb6pDqIHk+iR/zCNZWksL7gFhik6Du/Pu1zGuz5OB39/luIa6t6a1rd4UrU/U/LcuQ1nEYqNdOFAjsPO0LAepEEJ8OHlXu5DjQDqY+lOuFGsO+q6KvOTLM5aMuJvAh/LGlkTiQAGcq0Y3Ntmp64U3nRYIhzUk3jHj3BS/24CgxHPiFaZgvRuzGskdJIhenJR8Xngte8uBPvcP9uDSiC3VmTXCkqxnmLrhcT1QV/DXS2RHYOnZxYPSZECugCvO4TAf2D7hH6T/NkNiGrdGFyiG2H5ZFEjNhf2bxXa2a7I31wNwl6L6QmNoTWqX2U2yk99V3FfFclyzMAMUYUAYjJy+OuqnyTTEVZ36paXtHpp6uRgqowKB+S2eJnipWu3H96JpUk8WPw2OJMyy/E9fP850APHahIJw/v4LOI5EZMoGTsI/TkHvxqBqe+UHMyt5sqXf5AprW0FZatupZWYCqljWSIQFcgWwGUXz/0XBTpyDFsGrb0GE3o95edpIBvKkXLiXo+dg8HYODxURnSGtf9aPt1sZNAVD6wctfA==
*/