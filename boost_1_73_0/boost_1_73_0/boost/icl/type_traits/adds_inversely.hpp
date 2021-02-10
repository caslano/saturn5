/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829

#include <boost/icl/type_traits/has_inverse.hpp>
#include <boost/icl/functors.hpp>

namespace boost{ namespace icl
{

template<class Type, class Combiner>
struct adds_inversely
{
    typedef adds_inversely type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (mpl::and_<has_inverse<Type>, is_negative<Combiner> >::value)); 
};

}} // namespace boost icl

#endif // BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829



/* adds_inversely.hpp
85AiPn4LXRRjFyEu3MV73lghaBUdett+CdFgYvtjiPrFOJte7LqAoZjx8g3tFDFzPu4kaEAn1m9gDvuQhkTsq3KVUNh/Ar5NnyxsH43X6kvxf9zSD+2v06oU0SNjDxI68TzkKfHIOG8O2D3bSXo8mgsvuSQdmCmS929hNqJgQBN+X+QSK9rAgkTQK7KW5hgkwl3py4LtLbQ7mmK12vaCGbsIpGx2pKigMbOMX51BjPeG2PTWEGBI7EwX6SmtPGR3SIiZJ1B/bu5ZbW/Qu6ghboyK5ZkFjpkFpia3rNqbrGOJ2F1OffQ3Qz6d5eS81+/e5HK6Rw4sq2l0W9adZpAfP5L/Pj49xp/X5I9/JHtM/YYIdKd+fi3VTaulGlfapbgvQTLWqq49d/w094a9EJSVqM4T/QMnWk4fJmkQ+T+Wk7jaI4X6qfQ7AWNUPS94TPNP9+euF6OBFSTw9k2l8ylAJmxg5wBLbGBJpcj/+IFv0evFwDfi3ahnouqjyY/yhuwV2rLM94qhUc7b8tENDd03TBApGUadVeoN8lrnbUfCJpSOeQTOwf0nKGv+eqeVGL9YCrwuRckFOcoCzaZ8RjqF42a0yDq7/wNQSwMECgAAAAgALWdKUil7VE87DgAAhSgAACkACQBjdXJsLW1h
*/