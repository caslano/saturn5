/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_EXCEPTION_HPP
#define BOOST_POLY_COLLECTION_EXCEPTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <stdexcept>
#include <typeinfo>

namespace boost{

namespace poly_collection{

struct unregistered_type:std::logic_error
{
  unregistered_type(const std::type_info& info):
    std::logic_error{"type not registered"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

struct not_copy_constructible:std::logic_error
{
  not_copy_constructible(const std::type_info& info):
    std::logic_error{"type is not copy constructible"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

struct not_equality_comparable:std::logic_error
{
  not_equality_comparable(const std::type_info& info):
    std::logic_error{"type does not support equality comparison"},
    pinfo{&info}
  {}

  const std::type_info* pinfo;
};

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* exception.hpp
G9AKy3mKA58yOK1xcHyubppBPdozEuU67AnqeiT64TCKhe/hRdPLn1YSTwcwIBgmHsDBLNKHTo8xmsnqK0iX117v3+DTUsCSJ5/qYtdTmhNluEvnQCOUEx/KDWSWXbJ/3AowGA5ztV1pdw2h4GZwHAS83795ySfxQZvkNY+OMQv1U49Yh3CPNB4FTqTadA0X3cZj4nKTxwhuN2tz8xoejtcoM9bHu5gEuHa67LoOLEZ1/1sgBNW4o6siF2JQIaftXBKUdWnjK+6uc2gzvKZ00hCbrIJjEII/aOw+YuEAD+24OuQBfvuIKPckADhmY1T6hwJU4+VwQ0DIiRI6Zlthve+daHicDxXxB81plbPjO1tUUSP92C1qQoqKE4PcMBVITT7zsCOPpHAdzPZxUJ5nqVzTwb1GAH1XxdLzt6JDo0hmDdzYs5DIDzwYb3oXMb6tf3pYhTk7S+yAJCNYIprteUuVHmGfuqFCdrwnYfXy0K+r1Btp+ZDPzD+2dNKAfr6uUkXkuLgwog1NcvpWdtFOg0M+YL4rpwb+v2R5VSBneziduS7GbyxaDiNeqg==
*/