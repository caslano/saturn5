
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C1, bool C2 >
struct inherit2_impl
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1, T2
    {
        typedef Derived type_;
    };
};

template<>
struct inherit2_impl< false,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1
    {
        typedef T1 type_;
    };
};

template<>
struct inherit2_impl< true,false >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T2
    {
        typedef T2 type_;
    };
};

template<>
struct inherit2_impl< true,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
    {
        typedef T1 type_;
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : aux::inherit2_impl<
          is_empty_base<T1>::value
        , is_empty_base<T2>::value
        >::template result_< inherit2< T1,T2 >,T1, T2 >
{
    typedef typename inherit2::type_ type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
gb/HmN+BFL4B3wNyExUp5momsNf9LatsVwDk/HDnWgAvBj9OWubzPxyc6+mu+KZMas96yg8/avEp8yk7OiY9P6br8+01CHrsBnHukZwiel1qB9E+E/hG6SeAGKo1k8f4ZbOmMsa6544prm4VOhVTo45N4jJjQGLVDT/WiG3q+dX6Oj+wmiPpVcBU+les/iIXFPMjSm91eHX2+lp561IthfTGwlbWTddCii0/8lmLld2K/JIOVzh4P0dQQ4DkslHDkI0UGaLblf5QlOs3rCTGikJckFLURtxV+hLlD173p+ycV7y6u6O/VtDr8LN7M/3HarUdMt8WInuFQQcuRH41XKfSR+rKfVa7Yd1j9ALX/fXpCO72v/APkecKyAU93b63ZbpT0tg70o7Cq6on0UzBof85X1OG4kVO2AeUtPkT1xzFNWirnQVSSO8DOgcNcFvfAKmaT9YsuXuqyqmbEwJi3u3hhMmj1uNwivHFYB4cYSf+xi5TkgaBSHL545bEscfwSwwelWU8RegZcKGqzkYhybeFEGWVuADIsRVW0WOPW9i1ZKD6b+0Qx7dGMvVCKssiwFa76w3Wnh3rqQHkG4yk5BRknXhdZvplknSvWjvBY/mRDCLerCa0FXFG4Ray8PgzyzeSpFS4MKEQxpJ3f+eVWtBHIxzl/EYgGJK0vFhQVJ0spJCwYMoGLJ6d09Z+WH9tw4H5YZr6ElFvevtE
*/