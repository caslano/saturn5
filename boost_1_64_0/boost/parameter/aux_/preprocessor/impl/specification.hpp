// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPECIFICATION_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPECIFICATION_HPP

#include <boost/parameter/optional.hpp>

// Helper macros for BOOST_PARAMETER_SPECIFICATION_ELEM_R.
#define BOOST_PARAMETER_QUALIFIED_TAG_optional(tag)                          \
    optional<tag
/**/

#include <boost/parameter/required.hpp>

#define BOOST_PARAMETER_QUALIFIED_TAG_required(tag)                          \
    required<tag
/**/

#include <boost/parameter/deduced.hpp>

#define BOOST_PARAMETER_QUALIFIED_TAG_deduced_optional(tag)                  \
    optional< ::boost::parameter::deduced<tag>
/**/

#define BOOST_PARAMETER_QUALIFIED_TAG_deduced_required(tag)                  \
    required< ::boost::parameter::deduced<tag>
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/parameter/config.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#include <boost/parameter/aux_/use_default.hpp>

#define BOOST_PARAMETER_SPECIFICATION_ELEM_R(r, tag_namespace, i, elem)      \
    BOOST_PP_COMMA_IF(i) ::boost::parameter::BOOST_PP_CAT(                   \
        BOOST_PARAMETER_QUALIFIED_TAG_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)                               \
    )(tag_namespace::BOOST_PARAMETER_FN_ARG_NAME(elem))                      \
      , ::boost::parameter::aux::use_default                                 \
    >
/**/

#else   // !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#include <boost/parameter/aux_/pp_impl/unwrap_predicate.hpp>

// Expands to each boost::parameter::parameters<> element type.
#define BOOST_PARAMETER_SPECIFICATION_ELEM_R(r, tag_namespace, i, elem)      \
    BOOST_PP_COMMA_IF(i) ::boost::parameter::BOOST_PP_CAT(                   \
        BOOST_PARAMETER_QUALIFIED_TAG_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)                               \
    )(tag_namespace::BOOST_PARAMETER_FN_ARG_NAME(elem))                      \
      , typename ::boost::parameter::aux::unwrap_predicate<                  \
            void BOOST_PARAMETER_FN_ARG_PRED(elem)                           \
        >::type                                                              \
    >
/**/

#endif  // Borland workarounds needed.

#include <boost/parameter/parameters.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

// Expands to a boost::parameter::parameters<> specialization for the
// function named base.  Used by BOOST_PARAMETER_CONSTRUCTOR_AUX and
// BOOST_PARAMETER_FUNCTION_HEAD for their respective ParameterSpec models.
#define BOOST_PARAMETER_SPECIFICATION(tag_ns, base, split_args, is_const)    \
    template <typename BoostParameterDummy>                                  \
    struct BOOST_PP_CAT(                                                     \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_params_const_                                    \
              , boost_param_params_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    ) : ::boost::parameter::parameters<                                      \
            BOOST_PP_SEQ_FOR_EACH_I(                                         \
                BOOST_PARAMETER_SPECIFICATION_ELEM_R, tag_ns, split_args     \
            )                                                                \
        >                                                                    \
    {                                                                        \
    };                                                                       \
    typedef BOOST_PP_CAT(                                                    \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_params_const_                                    \
              , boost_param_params_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )<int>
/**/

#endif  // include guard


/* specification.hpp
zMNxkT2ZOFEiGM5L/9andZwKK6xHZEJuDzeF4XUNuTmbqmOw5/L3mwepvKQLILYULDuz+LJv5gv9ZoiSFofiUS2jEpf4FDylE8OZJpU7UTjvSuXms9cxc7eseubFhJiVgUkpT+401TmfqIxU2p7WZVvPkdl5BXFesw1R6aaRhuADyEI6SbR/wF1wdDUL3V6nAkNf7GtUXFrxMEpbv71Qv1962WgwTvSaD2m2wfsmBzMnt4GztAI5i4N3h+fW2up+JefKKxpBDMvexGFVB2K2XdDFXSpqM/EYKOkIXWG9DNfL7Wa/Oqzc9BRk3yKvCzfqxX7Hh+8O3kI6aiagucXujyLcec57x39chEbJBWFBEXfrx6rcho9yo+irTzGfIqiXOKtGwOb6UebHBBQPGR7ttSthvbG/yiBBGc6tGhVZEWnPlwOkSH3v68E+phYcL5WaqWTcrgzGwRnOOBN4dqOrLcnz7GM+QhfVy4QJXIm5RvSQJlrIBu0z3tFjf3VIjD/W3aC/wUas3dfer2s9L3Zo2JSs5jG4B/G7kKqmA0A3edkU6SI+87zmyprk1w==
*/