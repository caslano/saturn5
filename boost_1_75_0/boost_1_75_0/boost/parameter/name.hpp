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
M91wgkahSM/7GpLM8p0+ShmlrGnX980HsXWFG4loVGbI75goeocvKmuWwatWw9o/i/JSDARCpGHQF8nelCSeERn0FwwLSIFZcVHl0X0Lb+y2Y9fsSyNQOcOSQGfpUYo7wFi8b3OXGj76EplBfMtUcugzIXK+aBT6bqn67xMJ5UBxHrTLMdh4s9DVUaMoOhFZP09IUGOErPRcZ0JIdzDH+WWJzTY8+czzGDNLlo6Kp/R7pXh2J12zxez8kofylUrixDCCzGSd/AKtsbixwYBiVwGFhF7Q3lWjapfPIB+595gEGa758j/zKIbpNpoYreqido9hFH77KPCjNpQj04DD4q8havRIZD9xwg1lX1kx9UAZoT50vE6mN11gR+uYhZY88hwAUN9dBU+/B/XYwoEmk7NeXmUVjD6rZsgA8wmDJuNnj+u40R8Xob2bI/E1QBOUDYGkwwzhmWGnlI2N4+KEt+9Q4q6Os2koMNEcsv2HxE4t2OBisWLZQUHC9VnlSCDGihaUvOv9jeiEsj73R1WnQCxTLG3DvBQX7ZmKyQMBnvUrTMI1GKBaWtgY1+Q9X2gXSyU4mpNX0wa9/ivlzmquHbDkZyzi/fz8i09IX+tgI67jkOI+OGp22xaSkvdrq2gGrhJ0yPRS3nBr8TmKZdGgu63fh8iFch9gPQaXCEKPut+w+F4ZL1L/6edOn6MPWwxEzlB/cLz79RjC2MIz
*/