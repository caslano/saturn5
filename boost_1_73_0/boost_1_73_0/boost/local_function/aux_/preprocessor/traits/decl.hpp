
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/sign.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/nil.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/adt.hpp>

// PUBLIC //

// Expand: decl_traits (see DECL_TRAITS macros to inspect these traits).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS(declarations) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_NIL(declarations), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN \
    )(declarations)

#endif // #include guard


/* decl.hpp
UwSZkoD3Hk2z3pTpHBbDvhhP2eX0CzYXVtkj9tPl7OLm44z9NL67G1/PPrGbd2x8/QmZ/Xh5/RaOXsFkhsmHwkgLkxum1kWmZBrm/Os+pwfPVJ5kZSrZF07rjFvpyuJk9UUPnsokswMDa+lEpvL7gSFQhmWm5wMjC23WoHFW4tiB2xUSvZjMyzX77wFjk7s7fn1zPTkKv99cXo/vPvHZ5O4D/Lpi3zMwodNDNle5MDs8NjwleMjAFhz4EZA8bM0TX42ns4M/Gaoml8ZoMzo4gAMqwdu8h9WJ7FznC7VsoFMnQNVwHQGwlE6Xjh0Ch1ynctSMgDNFHuxQ5bjToREgsghPVsKwQ+CDuhNB0HRgggUYfxqByyLTIkVchJW5VcscdpXpfAlWjnAQ1giFAN/gQlBDiTMZFRF7EbRJy2LEkChgkKNIdJmD/NgWtA4ciGAWdyMrnCVtY4AVSCMsYaW3YNP5jingI9BrWO9IAicQBngcSzMwI/KlBMPb/5EuGZowU6ODP5tjuinCXP786MDmoFzg1tbaSe7UWjbyhFlTveaVQD1QLtMOBNyREUuZuwaUaH2v5KgdYA6rrWUYW2lftpCJgmNMmaewfg8xk1+FGbWYbA1IjPQXpUWn0SOiBcZERuLJGXJmA1Qic3aT
*/