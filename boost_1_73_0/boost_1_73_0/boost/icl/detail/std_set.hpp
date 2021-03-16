/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007
#define BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007

#include <set>
#include <boost/config.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>
#include <boost/icl/type_traits/is_set.hpp>


namespace boost{namespace icl
{

template <class Type>
struct is_set<std::set<Type> >
{ 
    typedef is_set<std::set<Type> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};


template <class Type>
struct type_to_string<std::set<Type> >
{
    static std::string apply()
    { return "set<"+ type_to_string<Type>::apply() +">"; }
};

template <class Type>
struct type_to_string<std::set<Type, std::greater<Type> > >
{
    static std::string apply()
    { return "set<"+ type_to_string<Type>::apply() +" g>"; }
};

}} // namespace icl boost

#endif // BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007


/* std_set.hpp
ly19fI7xauB5QDIBmQx8CIiPiZv0KcAPgdOA2Sit6UAy8sAHED8cWJ4uTTrqNt9wgaocp02hynTZqkeN5Av9ZqXLMvpsIBl5oM7FM6lpJr3AuUAq44V6OXqwbcoGc3O00dJeszSndVquvNZpQ5H1elHMpA3O4UrqbJXToEj7sTd9BpmZwY+HqoczXzsySfEC9hga3d5ryGgdDsAHOcY9AOc+zPMRaP7NfjlMe9jGjfW2BLG+Tu3UUsemN3sRrT4=
*/