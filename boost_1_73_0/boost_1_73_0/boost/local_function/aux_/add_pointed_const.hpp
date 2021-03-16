
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
Que3gei0sDPA6cB3KF3ge5Qu8H1KF/gBsIUqBUof+Be/mKX4CAgnm31M+QCiq2/RyPRnwH8DfuEXHaIv/aJD9A3wXeBZIA0zfEv5AQbQRI5GWeF3ymcv4oARYDxwNjCBmlRgInApsA9wDTApIDpE/YE7ganAR4ADgY8B04A0pDgUSD/T4cAjwJFA+g2EZdNMZSVaJQoJB1lwQ3w2N1Zx4xWXr7hCxZUrbo7iFituueLqFdegOEtx2xTnS/GxlBI=
*/