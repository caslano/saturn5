
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_HPP_

#include <boost/local_function/aux_/symbol.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_returns.hpp>
#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id) \
    /* symbol (not internal) also gives error if missing result type */ \
    BOOST_PP_CAT( \
  ERROR_missing_result_type_before_the_local_function_parameter_macro_id, \
            id)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_PARAMS_(id) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (deduce_result_params)(id) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE_(id) \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL( (result_type)(id) )

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_INDEX_ \
    /* this does not have to be an integral index because ScopeExit uses */ \
    /* just as a symbol to concatenate go generate unique symbols (but */ \
    /* if it'd ever needed to became integral, the number of function */ \
    /* params + 1 as in the macro CONFIG_ARITY_MAX could be used) */ \
    result

// User did not explicitly specified result type, deduce it (using Typeof).
#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DEDUCE_( \
        id, typename01, decl_traits) \
    /* user specified result type here */ \
    BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DECL(id) \
    /* tagging, wrapping, etc as from ScopeExit type deduction are */ \
    /* necessary within templates (at least on GCC) to work around an */ \
    /* compiler internal errors) */ \
    BOOST_SCOPE_EXIT_DETAIL_TAG_DECL(0, /* no recursive step r */ \
            id, BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_INDEX_, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id)) \
    BOOST_SCOPE_EXIT_DETAIL_CAPTURE_DECL(0, /* no recursive step r */ \
            ( id, BOOST_PP_EXPR_IIF(typename01, typename) ), \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_INDEX_, \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id)) \
    /* extra struct to workaround GCC and other compiler's issues */ \
    struct BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_PARAMS_(id) { \
        typedef \
            BOOST_PP_EXPR_IIF(typename01, typename) \
            ::boost::function_traits< \
                BOOST_PP_EXPR_IIF(typename01, typename) \
                ::boost::remove_pointer< \
                    BOOST_SCOPE_EXIT_DETAIL_CAPTURE_T(id, \
                            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_INDEX_, \
                            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id)) \
                >::type \
            >::result_type \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE_(id) \
        ; \
    };

// Use result type as explicitly specified by user (no type deduction needed).
// Precondition: RETURNS(decl_traits) != NIL
#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPED_( \
        id, typename01, decl_traits) \
    /* user specified result type here */ \
    struct BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_PARAMS_(id) { \
        typedef \
            BOOST_PP_LIST_FIRST( \
                    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS( \
                            decl_traits)) \
            BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE_(id) \
        ; \
    };

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE(id, typename01) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_PARAMS_(id) :: \
    BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPE_(id)

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DECL(id) \
    /* result type here */ (*BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_FUNC_(id))();

#define BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT(id, typename01, decl_traits) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits)), \
        BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_TYPED_ \
    , \
        BOOST_LOCAL_FUNCTION_AUX_CODE_RESULT_DEDUCE_ \
    )(id, typename01, decl_traits)

#endif // #include guard


/* result.hpp
uemDLAzgj+xp4w9joBZJ+u4z8qgUQpz2d5b+c4RyU9t4n2l5f+Z+f2V5W2xgvc8z4Vrqhxj12lPZT6RdFLb+/b7PUi/EeDe7V9l72U7ovnznW0TSSogqbTbr3/n7rPUMysvvWG9l39bmq3mrdz4/m7cWibjUndG2Jyj3lW1f6X58g+1n2d8OXY0bUhEgcay3+yHs8lIOmrKfrQ/FjUa/3lSvyr4YIUb/rKn8eBt7/32v/HfT7VVUUm9k2o9JbeusFJ3CZF/g95XbwXoHLZAU1WEfhNW4xw7Tl1W8d9HT9lHvm1fon79U7p/QrfZS+x77Gcq+gi0rn+MMfZkDKrwgfll4v5XfjhnKLFLy4oizqPF+m5mXnab9w9DdipW9jSXcXcqPv6rPq/hx3cctvEymPs55xN73lxcx9gg07RMYmI935bzq54RiZk9Xppmk32U/7ur8tV+bqM5icJ3sF1g/3fHsieKOxdjK7nXAKru7gYQYxBtHWX5XSxjP0d9UGIv0ZuzqYvEcEoelXo9Rb/uUfW96r5pWzyH+3e0tKO9+yr6H/iM1H8pz0EC33O+ScCyfPaOeZ6xyfi+JV/c+RltJVf576a7PYnl5Fjsr+zv1MOJvKfvzpvJ/0/6Dhm7aLOW2rf4lOfSj/6jstBfmWGPfxAeUu0uMyKZp62nHpyhR12cjUtzGKLdT9dtx/YaGAz2ap9Rbm4A49iIcIG7M+5nRho09CGm3UPYgLIA9LvOqg9TmP1AH6f2uOublGi1/3L/L+b4vel87eax7pcl/vg7S/5uuUUHrFMWtc69T1FJ0g1pBH4cOhrhLEn9b5b44slD87ZL9rPbAcnAvrAiPwqrwKVgb7oc94DOwPzwEZ8Dn4Gxxfxc8DOfDI3C1mD8IM+BmuRddJ+YG3Os6LcadnUugP1wGA+EqGARXSjhbdBlXyvg9DTZAVst8XjXJXz3JX31YBzaADWBD2BgugE1hFOwLo+EC2BymwTlwk7jbAlvBHWL+LJwPM8T+BdgOvgzbw1dhR3gK9oTvwV7wHOwNvxTz72A/+CMcCEPs+7jB0nAojID28CPhGFgFzoe1xLwOHA8bwUTYEU6AvcXdAHE3CE6G8TAZThT7VLGfCqfCRXAaXAGnw9VwBnxA3D0IZ8JH4Cy4F86Gz0p4GeKOeqIyZSwC+0p9F5M+UxPdHh0Ohn5wCPSHY2AAHAbLwFhYQcwj4HBYHY6AzWACbAtHwm5wNIwR95IOGTeQ9+zpMHS22sNSsAMsCzvBSrAzrAa7wCawq8TbFzaHPWFf2AvGwd5wPIyBk8XdZRhok3dmGTekwdaIt3wzNl7ynwRDRccoDH4p+U+GNWEqbAqnwE5wBuwCZ8E+8E44Ac6Dd8H5ENEWwCVwIbwXLoEb4FK4E6bDJ+Aq+Cy8Hx6Da+Ar8AF4Dq6FX4pu4AW4Dl6C6+EPcBP8GW6BxcjsQzACboOV4HZYE+6C9eBjsAl8EjaF++Ao+AxMhM/CJHgIJsPn4Wx4GM6HR+BCeBTeDV+E98Pj8En4GtwP34YZ8DR8GZ6Br8KP4Bl4Fn4CP4GfwU/hFzAdXoGPwGvwPPShzj6HAfALWBaqeoIHYF04FUaJeTQ8ATvCkzBGzEV3U97nKDs9u+7mBdHB+17a5yVp/5dhNPwRtoQ/S3u4CnvBa9Iuf4Hj4K8wGd6AUyARKh04b3gfLAwfgn7wUVhE+rdgeAKWlP3HQuA7MBSehaWk/yoNr8Fw2X+sAgyEEbAs9IWV4XXibwB/k3qvjHlzWAa2h2FwgJgPgZFwFKwEJ4v5FFgMLoQB8B5YHKaL/QPwB8JfJ/djbLApumTRvrnqyq2+xXtVFZRunItO3B/WhzM=
*/