
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_

namespace boost { namespace local_function { namespace aux {

// Metafunction to add const to pointed type `T` (i.e. converts
// `T* [const]` to `T const* [const]`). `boost::add_const<>` cannot be used 
// instead because only adds outer const.

template<typename T> struct add_pointed_const { typedef T type; };

template<typename T> struct add_pointed_const<T*> { typedef T const* type; };

template<typename T> struct add_pointed_const<T const*>
    { typedef T const* type; };

template<typename T> struct add_pointed_const<T* const>
    { typedef T const* const type; };

template<typename T> struct add_pointed_const<T const* const>
    { typedef T const* const type; };

} } } // namespace

#endif //#include guard


/* add_pointed_const.hpp
l1gsbvLAlLCDvot8IBENL8cz6zi6sP34Fs2l0IGV3tzzz+vtTNpePoH8IzhCYvV3cIzIqLfrv2bOa3myTcgm30mUyxoQY6+Akin2kQtbv594ObpLoEgvB+JBA6S2E9//uqmNM9/fxdZN5ZUACRfF/52+1UOsrR2affEWNaOhTa4m8DQCK9sZA8vgiiygBzuYd3ArKtF7OoKFRZ1rhljxLs0cOTyBxFPtVvc6AU1a7+Oh24MK
*/