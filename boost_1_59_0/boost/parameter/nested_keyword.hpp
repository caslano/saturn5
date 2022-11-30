// Copyright Eric Niebler 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_NESTED_KEYWORD_HPP
#define BOOST_PARAMETER_NESTED_KEYWORD_HPP

#include <boost/parameter/aux_/name.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/parameter/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_NESTED_KEYWORD_AUX(tag_namespace, q, name, alias)    \
    namespace tag_namespace                                                  \
    {                                                                        \
        template <int Dummy = 0>                                             \
        struct BOOST_PP_CAT(name, _)                                         \
        {                                                                    \
            static BOOST_CONSTEXPR char const* keyword_name()                \
            {                                                                \
                return BOOST_PP_STRINGIZE(name);                             \
            }                                                                \
            using _ = BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                  \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            );                                                               \
            using _1 = BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                 \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            );                                                               \
            BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_BINDING(                    \
                binding_fn                                                   \
              , BOOST_PP_CAT(name, _)<Dummy>                                 \
            );                                                               \
            BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_VALUE(                      \
                fn                                                           \
              , BOOST_PP_CAT(name, _)<Dummy>                                 \
            );                                                               \
            using qualifier = ::boost::parameter::q;                         \
            static ::boost::parameter::keyword<                              \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            > const& alias;                                                  \
        };                                                                   \
        template <int Dummy>                                                 \
        ::boost::parameter::keyword<                                         \
            BOOST_PP_CAT(name, _)<Dummy>                                     \
        > const& BOOST_PP_CAT(name, _)<Dummy>::alias                         \
            = ::boost::parameter::keyword<                                   \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            >::instance;                                                     \
        typedef BOOST_PP_CAT(name, _)<> name;                                \
    }                                                                        \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::name> const& name         \
            = ::boost::parameter::keyword<tag_namespace::name>::instance;    \
    }
/**/
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_NESTED_KEYWORD_AUX(tag_namespace, q, name, alias)    \
    namespace tag_namespace                                                  \
    {                                                                        \
        template <int Dummy = 0>                                             \
        struct BOOST_PP_CAT(name, _)                                         \
        {                                                                    \
            static BOOST_CONSTEXPR char const* keyword_name()                \
            {                                                                \
                return BOOST_PP_STRINGIZE(name);                             \
            }                                                                \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                    \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            ) _;                                                             \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                    \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            ) _1;                                                            \
            typedef ::boost::parameter::q qualifier;                         \
            static ::boost::parameter::keyword<                              \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            > const& alias;                                                  \
        };                                                                   \
        template <int Dummy>                                                 \
        ::boost::parameter::keyword<                                         \
            BOOST_PP_CAT(name, _)<Dummy>                                     \
        > const& BOOST_PP_CAT(name, _)<Dummy>::alias                         \
            = ::boost::parameter::keyword<                                   \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            >::instance;                                                     \
        typedef BOOST_PP_CAT(name, _)<> name;                                \
    }                                                                        \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::name> const& name         \
            = ::boost::parameter::keyword<tag_namespace::name>::instance;    \
    }
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/parameter/aux_/preprocessor/qualifier.hpp>

#define BOOST_PARAMETER_NESTED_KEYWORD(tag_namespace, name, alias)           \
    BOOST_PARAMETER_NESTED_KEYWORD_AUX(                                      \
        tag_namespace                                                        \
      , BOOST_PARAMETER_GET_QUALIFIER(name)                                  \
      , BOOST_PARAMETER_UNQUALIFIED(name)                                    \
      , alias                                                                \
    )
/**/

#endif  // include guard


/* nested_keyword.hpp
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
*/