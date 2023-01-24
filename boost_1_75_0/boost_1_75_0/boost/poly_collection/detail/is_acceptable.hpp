/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_ACCEPTABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_ACCEPTABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

/* This can be further specialized by Model when the std type trait classes
 * fail to give the right info (as it can happen with class templates whose
 * nominally existing operators do not compile for certain instantiations).
 */

template<typename T,typename Model,typename=void>
struct is_acceptable:std::integral_constant<
  bool,
  Model::template is_implementation<T>::value&&
  std::is_move_constructible<typename std::decay<T>::type>::value&&
  (std::is_move_assignable<typename std::decay<T>::type>::value||
   std::is_nothrow_move_constructible<typename std::decay<T>::type>::value)
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_acceptable.hpp
RHaAgbz+Ou5yWeV1RRbYkj5tyMukjdISpyMy6LklWtq75AWsAddto2xf7daXFKAcZUs0m0lLt/c5CCXbFn525avSYoZtn3TNEQ8iiPKnjX7s7DjnZ/iW9s6Oh120SXYM4+Y4V7+fm7x0asReN0Qxf7aOVmLCoaW+a8fVK6qaVPP2RNT57l5UVBeFEK8pMRw649AYfvossZf59xYxz9dPXmtJogrIh1Pb3/nPlJZ2cmqItfvJ6nbtGPXHvyz6aI86WHPaEf1m+i38eVyZscdXQhXUTiCugwIC95JfXVg/U/r0J1IFxsH56DlJF0BTciAUlBDS+exRFRW4K5yq50NIhqaNNl9nacd6IUBmIiJjQ6Ef/Et/kdiD19bMv9EwcX6rmSj4w3hjdUV5nL35HK6D5XQjYypA/IMZqxHvUiZ7cy7zsuTyTeB4ebb9s/AtCgMhT0ayiYPplzWMUF6P9+Wy0brOtOTs+IAkKopOQZfX89CtPs8fKRPWxvDhXE0tQLtQisCc36PtY0eZUgLU4VH8jFxhfVhM6orgjCfe0xtE7w2CisV7+syprO/y83h7kpteIc7eJEA9oG+8wZ5fhx/aw1N3AtKGH7oG09pIgPHDvpITBUmjV4uPP9XbH6nZOao+1K7a9+cLeR6xHfHTxEM7Ho3OS5IUKHnaZ1TlOPUJ06R5fEOMUQ+vmvI9b7P/jIWvCD7H0+LvTDzgIS7i
*/