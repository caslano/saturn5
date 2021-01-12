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
kzvUaBzMU4opwsUF2JzcEf7Yep+FT/sG/+tBIX5IzLdEBj0iRsYqKt0TP7d0s+CW/nsFvCZU1gYzuINOCLhH7G8iSc2vuPElrWnTh+2U7dsKnU1ohVGkOQ6OxYrQcr/itQwXHtbLgHsPUFBn3TaFN/HNsMydjbEiCKSjzKEtP+ZbOlL4ovkPYId7LrHo63VLc6WzM43EfCJRkhrkJR5IJ1YzsQiv09X/9y8z5e3olaVlUktw
*/