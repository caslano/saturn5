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
iNx0Avb7tQaD8Ns2PV3cwiBaTP0ZeDMKZkcjixPzqQiVqUvnuAPAtuhdD6tkjnJDw8/kPRxxSdsJJlIsdgthwybpppCQBbBLQlEnpaF1K0d22EBKu8DvIs0SboQeF04ns2gfamWVFjY9XAl8V7MrHg1XAFkrWTjUoXwqJAsFw5bdoTXSoZYwCEPAeTEcODX7ZQe8IBIYRpmMON3mANn5HjWxWRaZTRUdUpXYo6rDSjhCVdORf4lc5YzCKTJBDYM7RVtanTem7Xrnj98E+6EzhXBzkz1bQt5SxjdkwBF0qrxrjx7kpfn58aPzx398cHbMHH8eBp09kgPyfxnEGRGAA9II8rddzmExYVgptE/lAuzot2Vb0NRaZuhtXmM2W/3gCWz+0uQo8GeDyUf0ZQ50Zy1PezlUaK4v25g7ZIc8MCHSWeHaEC7lORYSNjgplOOyToA1b1cAewM6SC2twKXUxgYyTFVkh9qoQLQEUrJSlWWVTpU+Ev43u8UtZm3jldwyJTDEdVoVm71EvLpHNa5knZlvNRTRTkrSZgzGwprz6L5ULxCrT6bfadDbtmWHVEjKi/xcbUpz3zUPUbt+htiBFmARzzep7W8e7XnhiK7js2NsJ0616oD0VaIDXP0tHXGH02vLLMwJFq8wujJL
*/