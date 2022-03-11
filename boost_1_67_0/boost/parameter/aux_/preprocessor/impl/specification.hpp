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
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
*/