/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2009-2011 Christopher Schmidt
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base_attr_filler.hpp>
#include <boost/fusion/adapted/struct/detail/at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_view_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_sequence_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/category_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/size_impl.hpp>
#include <boost/fusion/adapted/struct/detail/begin_impl.hpp>
#include <boost/fusion/adapted/struct/detail/end_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/deref_impl.hpp>

#define BOOST_FUSION_ADAPT_STRUCT_C(                                            \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, IS_VIEW, I, ATTRIBUTE)                       \
        BOOST_FUSION_ADAPT_STRUCT_C_BASE(                                       \
            TEMPLATE_PARAMS_SEQ,                                                \
            NAME_SEQ,                                                           \
            IS_VIEW,                                                            \
            I,                                                                  \
            BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),   \
            BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR(ATTRIBUTE),                   \
            BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE),              \
            BOOST_PP_LESS(                                                      \
                BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE), 2))



#if BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_TPL_STRUCT(TEMPLATE_PARAMS_SEQ,NAME_SEQ, ...)     \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (1)TEMPLATE_PARAMS_SEQ,                                             \
            (1)NAME_SEQ,                                                        \
            struct_tag,                                                         \
            0,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER(                        \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)),                         \
            BOOST_FUSION_ADAPT_STRUCT_C)

#   define BOOST_FUSION_ADAPT_STRUCT(...)                                       \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (0),                                                                \
            (0)(BOOST_PP_SEQ_HEAD(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))),      \
            struct_tag,                                                         \
            0,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER(                        \
              BOOST_PP_SEQ_TAIL(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))),        \
            BOOST_FUSION_ADAPT_STRUCT_C)

#   define BOOST_FUSION_ADAPT_STRUCT_AS_VIEW(...)                               \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (0),                                                                \
            (0)(BOOST_PP_SEQ_HEAD(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))),      \
            struct_tag,                                                         \
            1,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER(                        \
              BOOST_PP_SEQ_TAIL(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))),        \
            BOOST_FUSION_ADAPT_STRUCT_C)

#else // BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_TPL_STRUCT(                                       \
        TEMPLATE_PARAMS_SEQ,NAME_SEQ, ATTRIBUTES)                               \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (1)TEMPLATE_PARAMS_SEQ,                                             \
            (1)NAME_SEQ,                                                        \
            struct_tag,                                                         \
            0,                                                                  \
            BOOST_PP_CAT(                                                       \
                BOOST_FUSION_ADAPT_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),        \
            BOOST_FUSION_ADAPT_STRUCT_C)

#   define BOOST_FUSION_ADAPT_STRUCT(NAME, ATTRIBUTES)                          \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (0),                                                                \
            (0)(NAME),                                                          \
            struct_tag,                                                         \
            0,                                                                  \
            BOOST_PP_CAT(                                                       \
                BOOST_FUSION_ADAPT_STRUCT_FILLER_0(0,0)ATTRIBUTES,              \
                _END),                                                          \
            BOOST_FUSION_ADAPT_STRUCT_C)

#   define BOOST_FUSION_ADAPT_STRUCT_AS_VIEW(NAME, ATTRIBUTES)                  \
        BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
            (0),                                                                \
            (0)(NAME),                                                          \
            struct_tag,                                                         \
            1,                                                                  \
            BOOST_PP_CAT(                                                       \
                BOOST_FUSION_ADAPT_STRUCT_FILLER_0(0,0)ATTRIBUTES,              \
                _END),                                                          \
            BOOST_FUSION_ADAPT_STRUCT_C)


#endif // BOOST_PP_VARIADICS

#endif

/* adapt_struct.hpp
AjJm3+Bo4k+xzhXsAUw/V/AYgRWVyCvJgfUUmDqUkLFejOFlxLM3YbQ5sZr2Jlbl5ZerO3ORPscSXz1YXsaDvTKcpn0Yj0o8v3jqlPyynIr8POb6gtMvs/DvTdY4XAXH7/QDPim/mFwq4m1L3jv9wRWW5uTlleWXl+O7DrDxquJcL/4DiZtFXOm0yeLoSHbneGDqsmfpTnYA51f4nUHg/Iue4fdgG9fOdR5CXJg4uuyDAiWSNZeupq6gvbjSzaEeX14YLmks88vlMA2nbjN3dHPnNES9+8SGO/gEwnMCc0jXCYUVetqOMLgppaCYOxGc9R05D4/UOXyYwlPy8yoK6dsgrqMcMrr7o3W+MGeYzo0B58onY3WueGpREfBxwLX8yOEYDzxw0SDSJ0fn+e6HnAlF+ZiTdnLmPYW5ukx5/slT84tz86tyiqfD/TyTr2AKXL7OVQwfBJc5PhN1jhNW4pMMfHppPtwq0PGpSDTUOYUGV1xIUwTl3tfw984bMhW57CW4ySY3cYR8leNfpHPTCssLVQpxeZvi85yfOTzFHjaVjmIpK6yYzhuSUCzgZ0lAhhR80FWVelwq2aDKJuadwU2gwpArrjKhwORQcpTje5VJno+4KZxYmEuZmnflFeaXs9vlHk+Xnuc2xJJUngq9c9crNK4sUhOJxpNl8joCzEEr3j+vdprE+FiEPHGvZGmJCA1/yx+ByyvAJaP4xpU+vlASSJPpHl5YRtm7pGy6TGh+5xSfKy8typleQdv8GT8VuPJbujUjgHPVytxpHqfff4/0Oz3AmXVclZNXd73OVLyqOhHvasVBoyvfmRXA2UPmagIce8bfI6xx5YUynSIK89KW8Vrg+bmQRnhn+3jp5FKlv2NujuI0RnJRxakkRBqd4eD0c4znKl5PQg5nnc8huninXuEqicDFApz6Hg0el0etZVnFdL19jXtcebk8EgpjmHkaXlhePjW/rKqcZh1zvL2+jYoXKVlMeZTf9+KfAM9HUeTRngsRpKnlOZPyZZiS4M02X3IpB1cObj44igl1hyOJhGwkmVtgcxOr6RouqQtYaHOy8VXngNs8s5gzlRynA8VTK0/Yiw6ebkUrz80pzZcJiYYC8V1sy5SXTs7JldyPHVwhvs/Z4OR5omX5ExHec4CX5JaXyopQXOOAfegax2FBnXqujcvbDuQ+dIMrKyrMw5ypjpcUUwhOZrfO13ECRe3upeUFFjeVWguPu9DkyksnUD1WLrmLbC4vpyIH6bDU5hCni22cWoN8b+5U57D3Rw/nJTpPuXsapXBRSS5zyzSOMzhfXyffu9TkiicV5QufOZzLPa6iIL+MMzXmToGXTsgfzPP2wFcoXMLAL/fxyXkT8QbPnwLny5AHY/7UwCg3TJLt3EoTn5KTWyVSlLkrTa48Z2I+vYe94wan+sNXG7iqg6/R8BOQttfqGJWYSVoeuM7gqIyUTS+t8OZILY7bd6pCiJd7xi1+Gn2xUvTlbjA41Fo5xXmoueS+cUOG2tjC0io9T9yo8/zh8/P8udEgV8Yvg78pwKsA8tyoznOyYm5UxzlZpXu3aPgIsxlh/lY3L1xgfrXOi87tNK6FOcQ8P5qeF36wzJr0MuQPzgHXZbR43aHjWrzu9HC/TagqpS9Ukof37pI8jlIQXuF+YwM/eWpOkeR6E3e3x5WVVE5HS0akOgoJ3/ceXQ4ueePGdeDQ6Mr94AamysJ9Bq7O3rgfuD3OfCCAq/7NrwKccu/X4Owx6IPAyxz9t/WKc/bfHlK8s//2sOI1bzGfaXNWv+ZRF4/zfx9TXFVJTn6pXMBUztxvNK60vBwUzvJWnNFn3BDAVZo+EeBUmj4JzrsH3vs=
*/