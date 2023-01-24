/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONCEPT_EQUIVALENT_HPP_JOFA_090830
#define BOOST_ICL_TYPE_TRAITS_IS_CONCEPT_EQUIVALENT_HPP_JOFA_090830

#include <boost/mpl/and.hpp> 

namespace boost{ namespace icl
{

    template<template<class>class IsConcept, class LeftT, class RightT>
    struct is_concept_equivalent
    {
        typedef is_concept_equivalent<IsConcept, LeftT, RightT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<IsConcept<LeftT>, IsConcept<RightT> >::value)
            );
    };

    template<template<class>class IsConcept, class LeftT, class RightT>
    struct has_same_concept
    {
        typedef has_same_concept<IsConcept, LeftT, RightT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<IsConcept<LeftT>, is_concept_equivalent<IsConcept, LeftT, RightT> >::value)
            );
    };

}} // namespace boost icl

#endif



/* is_concept_equivalent.hpp
o/KE92rp08W+LqZPl+xenj7dWHdrFJKni+tSQvL0QjMvT8SdL/Nq6bmNdSyeDLpA0NtibmadjydmzjB+94To3KOth7GkzMY6GkvIXC7y8ITMOo+W6Erk4YmUdR7hDmXjXSziL9SllGdaLzNPlFwg/TaSJA8T1i+x84aORyELcC7bbyEloy02ymVJYjtKkBcrWWyJUMfmfK95wlqjlmQ1T+C34ISkqzkyjiZczYtRFnGtR8trKtgyUorUPGPO1pOjFkrjyMi8OtJYp42ZGHVMbLqUYLQsNo+eoHOY8Y10y0y+UDfGDSuqXVn0BJvFUp3Km2X0Pifsx9HHmpDoslzvh/aJKPX3xEgyWSqW0ZREski3jeSEj0VCe4pvmmqDj5m0kXzPKTH47RIujo3Ba06iWCLXhVQJpca3WNIgSu0dIwGirs9MCQ6HizaEnL6Q0KT9AkbyQhualquwOPZzNFFhaQxaE09EVhhLJjGmh5vmSDGPn0melETQhkaLWWxDY7a7YZ+bUwfmm+cgtsVQtcYr2Zws8gtpA432MCUNjLG+bjGYmb8gHqEwiNQ2iJEBME/Aa1n/dN4mOdOfjjdl98vX8VI6PgMvZfLjsdMYGfwKNLyUtU+QI2Xr47aITfbD0Za6sLjwoi2gpfJj9o6eoY/bRjwzX67xPn0tOk/+RvqSXKlOmcNdYK5T7odna3g9qx7mt74hs/6NUCzZ9qTv
*/