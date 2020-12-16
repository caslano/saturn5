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
j9np3F2ZlFaUIzGPrxwjOsxbP3UeqJ6r7/WxEcC7/K1zL9fx1VIaed+u8n7ptUS3W+uFv5PV3zYRlvMxBmi9xxiW9TUbyH8QvqMGWccXgqbOIRetm2sFmnjdfiIfn/zIXPviigoOZRvKfgc+MteizHW0FoXPTJXGDOD/L44bzLxK/cRgXsX9oBfMvSqHRF6JfpAqr7YR3eNaFnKlWL2uEWH5338Uj7TrdO2q7vZGemu2B0m1t6j9h1I7LaU9+YgRWAcONMW8Cx30nPYSD+rgaGGnLWc1El19PgvF5Gsipx3vfN8XupL8Ggp7s6UG39Is91N670P6t8G4A47uj+H1L+VS+opylOfOKfexHSS+Teh1obbALVHXTYTP4wWxJsYreDGX8AXRLddSIfUj6vUHIiyuN2JfaUEN1g8kymtcLDLJ5eIY662OAfDh8+8Om3pzfoZD+WFndtbf2RczPlXvx6qokufWzLHF+jb90QWFxt0nTvpOFdWULVKxL9n9mXqvtPaRJNuE4oB60j4KKEvA8yJmVhiEu9iWodzT/mO3JAsmB9AbUbc7zYnuFdqnuVBpyzgstmU73X73aILW+R5N90f/uz2aO90126P5DsmIq6nEHs36xr6WzzmD2M7047Vh7o9J71l5OZmF0vFZyjVhDYm2l1rn8DPXp85GHrf8nNd5XehnnRfTpjFtVFikz3VeYi1ZDfaC0Bov1sOBLw1CRAtZgeZeVdaDvnyjuDATWJBVpDcsRR58k8rhKwTVd7HdQbwPYk5ltLp/K3Qj9rMhNDOinGx5THw/0e7WtnnfySbyoOkn8EdpjOWzvj4n+gHYsxxF5fLWJOoXFcpruWcTzU7MI9cRd5xDKnGGis6XFGPKVTWGLyO+7dhHHUphT6awC4s80hlkc4jmdW0oZFiPEJVyoaifRTxb6N0jNNYJa0jxwR7m5cjrK48RTbxYX5mkpxdyX4z8j4D/fOT/AriFcI/DPQH3JD9PglsE9xSXkXC/8wmhMe0/8b2WA8+kG16P7lWGWn5dNRcIfqSS+ySfWMtQcR5lcw5dvaEuQ6zHR4m3D9b41ePz6jg8xNIAtVgqT3gfuDyZ5WUvlxcp30XfZonuh7Ct+R/N5WYj+TcV7frTrOtJNejjms8qfeYdNRgHsT4HmnuZbfqc3Dml26RLLSpV6vM08fbF3JJ6TqayGjpsf8TQYbQ4I5v264gyG0r+caLMXk7PQT71mgR/Wa+La6FXaltZj3uPGYRPMd8iuHv1vYtHTD3mF0xiU6bLNgN+GGsXFUt3OeYQ7QKtC/7epe47cngukT7ovTBLmvtbTP43IH+DlG0u+MWcx7WJOj8u5h6D09ZV7a4lvgdiWZ/Sd6Xl5J+GmzeCkQ45PynBfC4P32l5xLDVFyMlt8Hp82yeo9DdN7g7XG+DQqNtdzk2YxoN+n1Wp4noHhUcFeVqGxWKD1B1xJqpJfCDIx4z3JbgWUo8pbPleyRlmr4mTeQozUpDYXOfYpmjPQuhMceO2M9aQV6jvCCvpbkB5B3eIe+kPc7ID7wT+eHVhzj7rehr079QuMbwSfm3Wb48OYX5Y/EFZFKOOR8SJ+2RU5Ul8Iq8bUS0VDxV5UbQxlet/Zygb31OR/fHR9kBT8A+q9ccSpy5H07SUyP9HcuVKK+BtMQv18WUE7wWn/vbo1lXqUJXWL8/NqvYqZ5S1XoS/Ybe5J+pjcBf5TxjDXQHHuu4WNS5keTXi8aF0cKfzqUXde2fRNMPFEG4YTnYWn+F/RxDdGF+9/vn6zRkzVsa7/CUQe86Q78NjHtuUD7nfYf7VfW6VDfStv/CpFkPmud1mjrJgmanpb4tp/mNwPff/F3lxqw=
*/