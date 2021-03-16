//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// TODO: C++20: deprecate and replace with std::std_remove_cvref
template <typename T>
struct remove_const_and_reference
    : std::remove_const<typename std::remove_reference<T>::type>
{
};

}}} // namespace boost::gil::detail

#endif

/* type_traits.hpp
QUfNaIzE3qX0KBOFOBI/UF81EJrmBRpxa+qptUAxdEhYGDsANqUo9k6o9W1s2jJX3CKBUSHTgpdkDLNt0qrcsBqqkOpwGwsm42PkCXUhzQ5Sue5RuQ7Q0W5MiKIpq5u1TeZb2wnY2IToGDTsGQ9a4Cuqi+R2A4Wpx1gkLNRQmJumx94KrSnM7RBr3P95h9Ca63LT6xYF9jd7QmsiuRkhGNVBFbWzwOAsDOiCSbqGGozcLOzX1aOw35b5yjC+drE=
*/