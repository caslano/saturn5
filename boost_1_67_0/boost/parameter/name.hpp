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