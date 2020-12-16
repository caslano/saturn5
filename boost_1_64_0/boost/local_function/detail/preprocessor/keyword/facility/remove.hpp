
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_HPP_

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

// From PP_EXPAND (my own reentrant version).
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC() && \
        ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_(x) \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_I_(x)
#else
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_(x) \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_OO_((x))
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_OO_( \
            par) \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_I_ ## par
#endif
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_I_(x) x

// PUBLIC //

// `is_front_macro(tokens)` is 1 if `tokens` start with keyword to remove.
// `removing_prefix ## <keyword-to-remove>` must expand to nothing, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT( \
        tokens, is_front_macro, removing_prefix) \
    /* without EXPAND doesn't expand on MSVC */ \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_EXPAND_( \
        BOOST_PP_IIF(is_front_macro(tokens), \
            BOOST_PP_CAT \
        , \
            tokens BOOST_PP_TUPLE_EAT(2) \
        )(removing_prefix, tokens) \
    )

// `is_back_macro(tokens)` is 1 iff `tokens` end with keyword to remove.
// `<keyword-to-remove> ## removing_postfix` must expand to nothing, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK( \
        tokens, is_back_macro, removing_prefix) \
    BOOST_PP_IIF(is_back_macro(tokens), \
        BOOST_PP_CAT \
    , \
        tokens BOOST_PP_TUPLE_EAT(2) \
    )(tokens, removing_postfix)

#endif // #include guard


/* remove.hpp
/CV/yV/yl/wlf8lf8pf8JX/J33/z+79rp47u5/8vWwMQ+f7fHfP9P0/f/ykPJb//k7/kL/lL/pK/5C/5S/6Sv/+wdx7gURRRAN7bSwCBhIDmiCFExAIoKARQVFQQC4ooNgQUk0ASiEASLgmCBRUbKiIWQBEFrAgWQJGiaARUFBR7L7EXLKioKLZ/595NNpe5cCcRy7ejw5/dmXm7OzO7Ozvv3RsveMELXvDCP/j9n9V1v7r7/t8Y8f1/qXz/p3nf/17wghe84AUveMELXvCCF7zgBS/8o9//WV3q7vv/y4jv/4ny/d/e+/73ghe84AUveMELXvCCF7zgBS94oSpsV///zvf/tn/7O9/5V2QiQ3zy7i4+6+rJtSQSv8LXZauQ//8jeuGTN3Ts7FH5ZcOL86yQr09zTYivYeYX3kZGb5yo2eI/1u3jfLY/lHk5MY24lLiW/P1eFD/AVccMOZ0eVT6SLJF+f7UP3RxV7i7WVPUb1hsQufwnPmH5K6j99JeotEKTH2B3OfEDnKt9so5VaV2snZFk8AtsKDuEdPGhq9LaW03ZY/DlK2XNaws0hxNV+omyjWdqtZ1i8lOOLLM/X85F5R2i0u/ES7bt8rXN8bLxfWtVrUFQoPLdbqXja5Y+ovzM/kD8UPuvDvWLhK34gOVca/UBmyw+YGkn9tFO1fy/5qrtFL09JKrf10dCx7F+7lS97z3PyTvhAel7C4nPkafHS1H6XunoYG19r58qN9sqMvc9kWvuezkq7XRT35Ny5r43XKW1of8Y+x5la+8/JSq9r+4/76ntFFNfRFbt/edElT7LGrWV/tNf5bu5Wv+5MjP+/vPeS9vWf5TvYEN/mfWSub9UyoOxhVXFC8lT8XyN/qJOAEflJeOkv8xvZ5EnL7+0rMp/9hpVLtnUV0Smz9XXSoNDpd12hKulrKG/6LINqV8f25MyY3lOh+rPOc9UOU/xwSx1yvHl2X2Y1McAWZ/COYgfpsCLqY+N0epD+XEvD47Jd9eJrFEh/bnrC07Z6dYOrEjdjng0sZBoqCOOE3lflOj7qYWS84Ghfkzlcg33jinfENN9IfnM/tabw59Uen1fwPKbnstS3nxfBeDPKr2eL9WyTWsg6Ptvi8qX6NuJf4+k7Tk37QP8qszQGiiThVcLpwivEV4LXesLSL+p/T7c8ELN+5C2jbwP5b4r+UvP8f+Tv+1Dh/vY/5nVfq+zDwvM2vuJwev6N2w3uO78bcfrV9vsn/v/4W+7oyXjV1jPsAZ4c1kT/hiYCPvoNeFlvASXG9aEHyf+fM+DXeCFsDucAE+Cl8Ch8DJYDifBS+FVcBKcDInWeHinpC+S9KWSLuch713GKYbzuFbOYxpsD2fI+dwEj4K3wP5wNhwO74Dj4J3wfHgXvBBOh7Mkfb6kL5R0qUd5r/BsNdTjcVKPx8NkeIKUI58839R7Qm2nEh+Ucv3J54eDYBN4GtwFlluyhjVsA3NgT5gLj4NDYC4cCotgnlxHvtRrAZwDh8H74HD4OCyE62AxrIQj4BYYlLXtS2FDWAZTYDnM8dY29Xz11qGv3i5LWJOUeC5xNnHNEk/H7gUveMELXvCCF7zgBS94wQte8MJ/KWwf/f+o4qI60v9fH4P+f8Hzbv0/x/4L+v+295n1/xNtWQdYCh0iOtiUKh2SHFN0sHn5Q4vz8iN1sEb9EDIi9a1GfVBKjPqgFLOex6gT0nnRw9iy1vPUOPRw26rHdNfxl35zHVesj1LH+UUx13HF+tjquGJ9bHVcsT72OiZvjTqe9g/V8USxJegVPpDYsVhR6ljsWGKqYyvGOrZirGNrfWx6TcvcFkYdpmVoi+l/U1vEqi8M66mXygM=
*/