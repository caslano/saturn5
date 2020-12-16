
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/integral_c.hpp>
#   include <boost/mpl/aux_/largest_int.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#if !defined(AUX778076_OP_PREFIX)
#   define AUX778076_OP_PREFIX AUX778076_OP_NAME
#endif

#include <boost/mpl/aux_/numeric_op.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER AUX778076_OP_PREFIX.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/workaround.hpp>
#   include <boost/preprocessor/cat.hpp>


namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
namespace aux {
template< typename T, T n1, T n2 >
struct BOOST_PP_CAT(AUX778076_OP_PREFIX,_wknd)
{
    BOOST_STATIC_CONSTANT(T, value = (n1 AUX778076_OP_TOKEN n2));
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct AUX778076_OP_IMPL_NAME<integral_c_tag,integral_c_tag>
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  AUX778076_OP_TOKEN BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
#else
        : aux::BOOST_PP_CAT(AUX778076_OP_PREFIX,_wknd)<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type
#endif
    {
    };
};

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#undef AUX778076_OP_TAG_NAME
#undef AUX778076_OP_IMPL_NAME
#undef AUX778076_OP_ARITY
#undef AUX778076_OP_PREFIX
#undef AUX778076_OP_NAME
#undef AUX778076_OP_TOKEN

/* arithmetic_op.hpp
vmBoFkvf3sFzMVdwKhEaBcgggwmyq22PHi5niYBUozzGCt0HKpNUcZC2tRgB3WgpD/aEjpEdqReglwLefPUf4E9e7JfZD0ba421u9Nu7JPJ3UaPfBt7/xNx52H1/Z1+/d4BwNzDC3QEnSj5vO5/5ZZ5k+G4oL9tAFIUxI42ydiyDSexDVCxwvDl0pLTqrZ7YVFRfp/DVOuCrdXjtefKk7GJdVpVg7hIxCvaImUUZ2Bw7ifDm/teg/7qHxK7cCZT2GYhYDwujNwOrrBdlHMvFOu4Eh3N9RBlQ5w+KMh4qQ0QaroYHdZks2U5V4YqKwo3hoOG3FQtGFHNZxQqN+/T4b9TjPx3jR2VPkZG7XMNt9JTwUWDB/vQ10MT8/GSEta72Yg42V5SsLC9b6Qx66K8r2Dzso9HX0+YMN6UvngdF7c1F5tW95SqsKi/b6Mia/QdWmCvcViw7bWg9mpzn4TmxscJpTPy8E41lG/nUc+8XyZ60/G2CsszfOHOAeL/fnE30WtYbxFFeTgSgWCX6W7Z8ULDIeE6Nz1hBBdUQfzkCQ8SwPGMwRDntGKKAwlWkhpghh9idHo0MCgHaCBRjjewHcJrfjpE0945wjrGWs9AFTugnOre8bIewG3olehO+MhwQVq9xU9YwAgRk9EefOfmFmzXnTpzsjYRKNtOsbRhjXtJWmbYVGRv1qB+zjfpyblOCgVHLHUKj5kVuOUaN2t+bR91PALBZtQfq/emfoSd5sKo/qxfchzXFBKFaITzXMFdUIY0eZTqdflTkb6EnQlrhFqzYEnrTYsU48bV3nQ5qiL3qLWJheF7+KlrJ7XpMj9vGdPewQ1jJYb14TBcjetqSisLV5WWraf/dQUeCvvXKmv2BA99OJoH4y5QYyKii5cQYtshNiYVbzAMYWLhNaMFsYy+rhcZuvY5BBd+Xpx0CfMt7Mnzr8e5ZXFwFrRPbGm/9JVqDC9t90ZtmNndWPZ3qVw93qe0K8O1LsIVWR65YWslrYxovTv5reflbgpk8RjiepbGFo8fW+rRD2E8be/DYaAc75KaoIofn5gvn2db4y5hr/MzQQ0BIE2Q/tzmBkMhiqDuQTVEVhVsRattmvz1OZv5MKzS+iR7VaYfS2xcncW+Z1FtVyS5sW8JZxaJnsEVaH2utWH30in00hFdM6NTI4HGr3tybFr3y28+32nG5o9q5k9uBeWd4lOFxRw3LGHIIi9WWhxUeaGS67Sf/+VMiTn41sWbA8HmsjWL4uMLpNO5wd6OdqgjENZUrwioc87KyP65JehsX1vfbal5x1oF/vd+z/3/+Mz6CfpvRiJ7Lgf/7M6Q+wsHoVzNk4iP6WkEZ0l0cCArxnKr7KpsM8HsHZ2F/srNB5siBRjFdwY7hAUaTFe194kVn1CwV+9VHtDrUpH3hQcgTrymjnvJA+o2XeR0FR97K9yyT+QOQ72cZ2ABX1l2CmwtRtnL3jSg4cLoNH8esMjA9644XHOB3Za29e15GO19Dl3sN+sfIpYZBWq7wAFVWg4PYR3V3l0x9QKQOWyYHMFWmzhapE1QLl3Jq+HrDUNXPkUkXGUFVd7BMOsuYoSp25ySaqwWqYhuZ1BUDfQVD21tZhDBARcZKVeykfJx8ZmYIHuV+wUQVk7+fIq0SBbpBdftOUzRIc75NdfsCJ8GrIxpgQYi//C0XU9t7O9n5PBnVu3+wPWd6N2vnG0n/X0D/T6H/y+n/RfT/k/T/a/T/b+l/h9OV5jn8jzu9iedIPk23/A98hLz+8rHKHvwfp8Xyh5Ev8s23z41n/50N++8RLA9SER+8/E3Gt6j05bWcDm1WWOJ7wA3gp3uF4JqbMiKHNuAdRe7RLTlbUGw=
*/