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
AUp9Up0GuXqZev0ZwnBez0V80PFq6Hf9Zr4PIra3Vxlt6/jbjnpMgrTgWaRFZQdofrOwnO97sO4f3UpxwK/q3ykodLV3XmTnjCoZ42R8Bj7LXDyxqvQJ2tqNvWkuncOX5xZObLWvPblF39cjp6mG+6C3S+nrFOO/Xdhey/QhfGHf5X3Ue7dZ0sdzJxVy+mq5jxphcTtllvUSdX+rhmmM9po/KfH+5rzdvn81I0mfjJTTZ84IBU6L9r7z/ava+87rONMKu3qoGmuS1GUZcqnacuv+19erzlh3SWesu731M9rJXKXbphuwKXUjaK17p4UNbkb+fbVW+Mt3VdAdY6v4G/jD+P2Io7YjNCbnffEd27/OWF65/se9UbXG3MVrzLP1uTdv/YzBd5tCNM3Seh77+FDMxRFvW/VcnKSXP/z1FWVatv879TUyDvb3+Ztb+IP7gda57bNv2Oek+ul20EsPNPWmX4Tj6Hwo8Fr28RGr2v5Z6se8WvR1S6T7euS+2JGddlv4SyLskpxG6z5dh/NvFVJaQ/3betAGtIP9A+Uj4lDm4+Fd3mcCRMLl6vZwv1ca84vGiCQ6Sh/4Rfp+8V9uBa0+/quAzmdDpkcbgLZ+FMThsWct5ht/sZThQZz2kN32/ZbjkHa3d9onFBTTQtd8XC0hKnSVNtT1OgYYR+HUU9tGST8pAfIftKK/dwS6Wf6moZ+o+NrrJsUsF9yXO2+/+s7hw7vt31S+Bk2KrCuxHzxwXU/Z7/y+15T9Act/te57NW35+j32+p2H/E/zThP2i/JZUCLTA6cvTUpfeID8Tatl+sI5D63pW/CWPX0TkD6PLX28yK4a6fNI6YsMkD5PLdMXKdJn+f7ztqUN4r5KmSV9JYWegqKcwGkqM+uZ6K8wqzpdoPdugwbWoA2Kl/sbUnxyOzTyHauN5nGUnE7rPmEH7S34Lf0z2megHk/VMg8pfRy+1514ey1llNO2XUqbvK/XSb9zuy1dU3KKfI2jAqfLwT3uCN/aj36vat13ENwGLpsVlnSNzlbfZXCU6F7RbgT3HPV8NsJy3r8GraV/TfOcYr3pWfK/HjEFa/389MMHfwA6jBYv4Hnsrsi/Ae8ac8eRQZg7jtTnjuvZ546Zdhpoy/BOn9m9Piw4eKAxxWub441l+sVMHxU5wEZjfld7jNfuFwC9xwTVn/sI1P8/8Z69HZwIm1r+gZSviv3NTvq/CEPkUZ7/PhNoA5Zbv+nLE30iy90q+yzp4/pYqUwf7492kDbwW8oqcarnvGuZNso7Dl/Ou67vW84/5W967gNy2qQhm7gPyXcf76oDvvfOIlzrujU9zGL1/ADTi+96Ej1/LDP3X8QRXaqWjFCU69sOyO2Ss3nqwN/zWBbb9zxZRsv83351u+Wx6JtbrIBlyHPAeXvlOfB3lCF7e7XgA94fwOm6Ge6lxuiLSGnysx9T2NF7iX6Y1suHbS+V0nqMePXgquaTy8i/H3Qdpko/+NV7rmJ5D9AD5D8Uq12jieZ70lLuaI1p4oGLiOYKrKeuI+TAzHq+fN/lI0TTH2sAXTX+FndMf+b00X34B7zvw3/1gHr97JoD9vFbURL+HPTKi+J8T3p2rrDEvutyyEHf4zWEKfQ5knizc9W2mWl5vPYkysuIA3/feG0kvaO4STcxB9XjtXkH1X3jZItuCkucrY0Cn6XuEasy/Uwr7M+gGvSLveohxyWnr/yQwdyUA2kCF6SvYZTSJ/ap+rj/sBfRNlalF+E4tzWgFXY+yPv7jyhbQ4gmUmWvwf/32SpznWuQ5duNbMPWfGgtG2yXFbrj/dEBy4fHpi/iU9tmS/kYXOvyQXF52YYFh+3jihJ9f7oqjbw=
*/