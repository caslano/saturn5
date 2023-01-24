/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_TAG_HPP
#define BOOST_FLYWEIGHT_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

/* A type T can be used as a tag in the specification of a flyweight
 * by passing it wrapped in the form tag<T>.
 */

namespace boost{

namespace flyweights{

namespace detail{

struct tag_marker{};

template<typename T>
struct is_tag:is_base_and_derived<tag_marker,T>
{};

} /* namespace flyweights::detail */

template<typename T=parameter::void_>
struct tag:parameter::template_keyword<tag<>,T>,detail::tag_marker
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* tag.hpp
ZU9MOLmyIjq58k+MUa6sCC9XFu0Iliv37TDIlUk7opEr/ywJL1e6/YU9pONfmlwxnv8dEvn87/bMCHA9RZbl/aRybyLin2+PpnMMWBLi+Cx2jtmH9X3Y4OeG8k9Hp2W56rmgosYP2U6dQx/tlPWC6VK5nUsSDxoq5kiqYMjVBEPuypX6wYz71zNAJuS6L2Zpp0vauA9IyhLeQEzUwhl/sk04cxhWRgHOHNc/FYByYVOHdeWfyLTb/zToCwa+dS6JyLc+287GtwGcb6nbouHbg0+G49u6QxH5NnNwZL498U1ovg0I5NuA0Hz7KCLfBuj59tHZ+Bb/TTR8m/9EWL7V/4F8++8f4fl2+6CIfFvw9dn45uR8K/06Gr59+3g4viX/EZFvq4sj823/V6H55gzkmzM03z6OyDennm8fn41vxV9Fw7ctj4Xlm+l35Nvx38Lz7b/OiHz76suz8W0Q59vSL6Ph2wWPhePb8N8i8q2VMzLfLv4yNN8GBfJtUGi+fRKRb4P0fPvkbHx7ZGs0fGv3aFi+SQeRb/aD4fl2fEBk/Wfr2fhWwvnm3xIN3yY+Eo5vS1oi8m3IgMh8m7olNN9KAvlWEppvn0bkW4meb5+ejW/fb46Gb2MeDsu3ul+Rb95fw/PN7ojIt3Gbz8a3oZxvuZuj4du7D4Xj24/NEfn2hBSZbys2hebb0EC+DQ3Nt1UR+TZUz7dVZ+Nbt03R
*/