/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_FACTORY_TAG_HPP
#define BOOST_FLYWEIGHT_FACTORY_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a factory specifier:
 *   1. Make it derived from factory_marker.
 *   2. Specialize is_factory to evaluate to boost::mpl::true_.
 *   3. Pass it as factory<T> when defining a flyweight type.
 */

struct factory_marker{};

template<typename T>
struct is_factory:is_base_and_derived<factory_marker,T>
{};

template<typename T=parameter::void_>
struct factory:parameter::template_keyword<factory<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* factory_tag.hpp
s6C0RqG0hSjdwihVGSldQJQOOpQKDNRhdcnaC6zGV+2qrWzrnVF8lCiexiiuNFJMI4p3OOgcaR37FvORwTqVwfl+JFeZQQlKfef59XzqKZ/gLMyn2pjPfbexfMY40NF/tWFp4e8sHbl6tE3X8ZMT79mVXHZfoZiFLXmMg2xXQQ4/rICs/S0HuVkFWfC8AjKnjoMsAxDD7XiyavMDVeuxFGskd3/8K0c6xW59qlTm1fi7YJgdcxwTmKlEf7aCil7E7SxxDUKkU6/hpD9CklskxpzNhOGzyo7ky0roZiyvpUCOx22AOH5aBf7j1vFe+T2/vofl5qG13vStZjnsfEUEu/1yBptM08apD+JuHN3BLhvMUAxSPwYD+5UsKJoKEbnoBoPRHZ2W+4YazEMzSV4zNJjfbhBS2nPr+NKprG2Tzi8/y/lvi3qUpn41fTRayrKGVYdRlEyet2zina66GCJQ32ajtGI9ux9XZYTodetYgdXsFPpYv0ytYvMFP2j5JI8WI5e3Us9+vSH7+CbdmVj29ngEtt1C2JQIrcjFD1w1av4P4mIVX6P+VPvfzUZ9f1+acW+8DxX4D7hYmd4/UyjwN+6MLhy00T8gq5RdraQ3RklvwPS22eMb8N+OQn8jprdtf1eVfx4wtE8sLLdeM7SSukDU/a5Y7WGLjuZ+7zb4CyyIUp+ro9RnfWvpgaqtlBwx/UFMj+L/6D7VtVqT4o/xhDW8miPTvw/pH4u/Sm/b/Uka6qeq9fq5EZOPxV+kZ1ds8rOP3aTxJ4MnYaknROtn+VIkDGkKhKfgNHrb7U23CazdwDn9RFqWklZnSKORUkneany9z/j6oAm53vTeYHpvNKLvNb6+boLeaHp/2/SuGdEPGpJbDONb3o6z8SuUuyu1GZhW5qtZjV0nRHWnTlYEzjQlhezWM38XA6oHffcJvNqU60BdhjFmvGwzXjZAeXW8QzAGYYwZL8uMlwVQHh3voWUsP48Zz23GcwNUto43ENYVGGPG85rxvABVoOMd+RXDKzDj+cx4PoAqDKWI9lZoVZkFZqQCQCrSM3sEhFSMMeMVmvEKAapYx5s2kOEVm/GKzHjYeUp0vLVTGV6JGa/YjIfdrEzHmwljHsZwvP4Cr8TczsDqjZ0iCHUWqKWVgEqR2mwQjrkb6Fw3AeCHJGWrK4HJt69Mk/Lt9VK+/cP1oGzNscsKPoEYCBTQNgMTqG7fTMaKoZ48zuuG6bO6sSPlCA2kJjeNlHp9ga9v6pzgy/B6WuRIIoWcCMJxvjKIrzFWfIVhAUY3kYssq8t62Upz5StaAd97E52XBTZyYOVlXM51I7F9PVisK3z2Ev1b8dlMMtyme4NhaXdKC4NhxOBNPgsGF1zH6WruO4/nnsovv9h/NNc9t5Gf6r6VxN5/ngo2tIcwJe5ii63IO1zsozacKj/qdfKj1qyh2xZivFQtL9J+6ChiiTY8XNijcLHNXlNX4jTHjIAPrFOMgEnrsoyY68+YuxKZ+51k7tMA012k2Bl6tpa0RTXpxWsrS09nO7DXt6RbRXRfmmpB90ai+xcbp7vtQU6Xrh1IFsa6aLzMovwT2LbJ679VsqG6raVsFrFsyozZDGfZhM6kg6F9lH6dbitNk69YM2DQixkZoXqZoIprfL2O+Yb8tv0i+JdNb93/7GoNRb9Y7M1+AC2Y4RLnDg/KVSl5tnajFBzD+SCj/1t6q02ZsJBNUl7xfttv2HtZzPZoRC9tVyT/p7cLS98lD5mW01+A0KCWZPX6GA5RRMjfFaW+62Oob/J/eZtUcvu011a3vPezs7ywxsu+xw13842hmPa7hhF5413aL10Zg39kVhwsTc1qWldFTlfXVfk=
*/