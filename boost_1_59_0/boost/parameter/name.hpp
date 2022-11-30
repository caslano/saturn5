// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_NAME_060806_HPP
#define BOOST_PARAMETER_NAME_060806_HPP

#include <boost/parameter/aux_/name.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_NAME_TAG(tag_namespace, tag, q)                      \
    namespace tag_namespace                                                  \
    {                                                                        \
        struct tag                                                           \
        {                                                                    \
            static BOOST_CONSTEXPR char const* keyword_name()                \
            {                                                                \
                return BOOST_PP_STRINGIZE(tag);                              \
            }                                                                \
            using _ = BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(tag);             \
            using _1 = _;                                                    \
            BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_BINDING(binding_fn, tag);   \
            BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_VALUE(fn, tag);             \
            using qualifier = ::boost::parameter::q;                         \
        };                                                                   \
    }
/**/
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_NAME_TAG(tag_namespace, tag, q)                      \
    namespace tag_namespace                                                  \
    {                                                                        \
        struct tag                                                           \
        {                                                                    \
            static BOOST_CONSTEXPR char const* keyword_name()                \
            {                                                                \
                return BOOST_PP_STRINGIZE(tag);                              \
            }                                                                \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(tag) _;             \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(tag) _1;            \
            typedef ::boost::parameter::q qualifier;                         \
        };                                                                   \
    }
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/parameter/keyword.hpp>

#define BOOST_PARAMETER_NAME_KEYWORD(tag_namespace, tag, name)               \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::tag> const& name          \
            = ::boost::parameter::keyword<tag_namespace::tag>::instance;     \
    }
/**/

#define BOOST_PARAMETER_BASIC_NAME(tag_namespace, tag, qualifier, name)      \
    BOOST_PARAMETER_NAME_TAG(tag_namespace, tag, qualifier)                  \
    BOOST_PARAMETER_NAME_KEYWORD(tag_namespace, tag, name)
/**/

#define BOOST_PARAMETER_COMPLEX_NAME_TUPLE1(object, namespace)               \
    (object, namespace), ~
/**/

#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PARAMETER_COMPLEX_NAME_TUPLE(name)                             \
    BOOST_PP_TUPLE_ELEM(2, 0, (BOOST_PARAMETER_COMPLEX_NAME_TUPLE1 name))
/**/

#define BOOST_PARAMETER_COMPLEX_NAME_OBJECT(name)                            \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PARAMETER_COMPLEX_NAME_TUPLE(name))
/**/

#define BOOST_PARAMETER_COMPLEX_NAME_NAMESPACE(name)                         \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PARAMETER_COMPLEX_NAME_TUPLE(name))
/**/

#include <boost/parameter/aux_/preprocessor/qualifier.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_PARAMETER_COMPLEX_NAME(name)                                   \
    BOOST_PARAMETER_BASIC_NAME(                                              \
        BOOST_PARAMETER_COMPLEX_NAME_NAMESPACE(name)                         \
      , BOOST_PARAMETER_UNQUALIFIED(BOOST_PP_TUPLE_EAT(2) name)              \
      , BOOST_PARAMETER_GET_QUALIFIER(BOOST_PP_TUPLE_EAT(2) name)            \
      , BOOST_PARAMETER_COMPLEX_NAME_OBJECT(name)                            \
    )
/**/

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_SIMPLE_NAME(name)                                    \
    BOOST_PARAMETER_BASIC_NAME(                                              \
        tag                                                                  \
      , BOOST_PARAMETER_UNQUALIFIED(name)                                    \
      , BOOST_PARAMETER_GET_QUALIFIER(name)                                  \
      , BOOST_PP_CAT(_, BOOST_PARAMETER_UNQUALIFIED(name))                   \
    )
/**/

#include <boost/parameter/aux_/preprocessor/is_binary.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_PARAMETER_NAME(name)                                           \
    BOOST_PP_IIF(                                                            \
        BOOST_PARAMETER_IS_BINARY(name)                                      \
      , BOOST_PARAMETER_COMPLEX_NAME                                         \
      , BOOST_PARAMETER_SIMPLE_NAME                                          \
    )(name)
/**/

#include <boost/parameter/template_keyword.hpp>

#endif  // include guard


/* name.hpp
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
*/