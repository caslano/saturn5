
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
aU9PRjGFBaxhGwc5zhVuke6C6ysy8DKlaEQ7ujGYySxkPbs4yl+kuai28iolqUFLejCSGaxjPye5wV2X5B95KUtd2tKXcczlew5zkqvcJO1l1yM8z2uUpTbN6UIPhjKa6SxkDTs4wmVSrphjMpOdgpSkAg1ox0f0YQjjmMMyNvMTZ7nObVddZ/A0r1CM8tSmJZ3pzQimspTtHOUKqf9Q18hBSerQmp6MZCrrOcCvXCX80/iRiQJUoBEf8DnTWMsBLpHyl3VMXirQiB5MYQUHuUbaa3KAHJSmPl2ZwEJ28Cs3uf+6nKUoTejEAKaxhoNcIs3fcpM8vMW7dGUkU1nCZg5zhqsE/zhfk4kCVOZdejCCGaxgBz9zhuiGfXiKHJSiKk3oQG9GM5ctHOUKyb/6wrMUoBIf0p+vmct37OMEl7nFHTfVGIrQlAGMYzYbOcQlkluu63mc7BShCu/wAZPYzO88GGQMClKN9/iAQYxnIZvYzxmukjbMGDxEdvJThoa05iMGMIqpLGETB7lCKjfwPUpOSlGPDgxmMmvZw3mCOGNwLy9RkPLUpgO9+YZN7Oc0UZIxeIrC1OR9BjKR+ezjAqlSMgb38BJvUItO9GAsc1nPfs4TptJfslGcunTkc+ayjUvc7T/QZaYw1enE50xgDqvYxmF+4xb3pc4YZKEQVWhBd0Yxj22cJu3tGYPnKEIdWtOT8cxlFfu5zsNpMgavU4EWdGcks1nPQS5xW9qMQQbyUovO9GEUs1nFTo5zndvczPwIL1OGGrSiF2OYxwZ+4iKp0mUMHiMnJajJ+/RiJPPYyCEukepO25OdktSlPf0Zx3y28AuXCe/KGNzPS7xODTrRl5HMYi07Oc110t+dMXia7BSlEo1oR38msJhtHOcat6U3TuSjAi3oyhfM5juOcJO77zFPFKEWrejOMObyPT/zNw/faywpTxO6MZpv2cJh/uS2+zIGj/Mab1Kf9vRnCqv5meh+a4uCVKQlfZjMak6Qyn9IeYL81KMVfRnPHJaxhZ85zy3ufjBj8CTZKEh56tGOnnzJNL5lPfs5xXXSPWRfslOcmrSiB8OZxlI2c4Cz/MNdD4uTlylKDZrxEYMYywxWsZ1jXCH1I+aK13iT2jSnK4MYy2y2coLr3PmonCAP5WhJfyYwjx2c4gbpH8sYPEt+KtCaQUxiIWvZziHOcIM7/icmslOAUlSnKR3oyzjmsJZDXCHd4/bjNSrRkp4MYxqbOMaf3PFExiAjr1COd+jOMGaxhj2c4ybpn5SnFKYi79KVL5nDZo4TZ1CDeZqXKUhVWtGV4cxgDT/wK7e4O2PGIBN5KUlVmtKZwXzFAjayn7PcIv1T8ozXqUFbBjCDxWziMBeJn84YPMBzFKYGrenLRJazl/OkesZYkosKNGMA37CUPZwjyqQG8QrlaMzHjGQuWzhByrPaIz+lqMP79GEs37KFE/zDHZmtYXJQjIa0ZwAjmckyvucAZ7jJA8/Zh8KUpSbN+ZhBjGEmGznOFRL/yfBBMpOLElSjKR3py1hmsZLtHOEy8Qvmm6fIQREq0pBO9GUiq9jBUa6QvOhcxtPkpCiVaERn+vEFE5jJYjayl3OEWdRDslKU6rxHd0Ywl40c4hKpXlLryE5J6tCWvoxlBsvZzH5O8g+3ZRUnGclKXopTiUZ0oB+jmclKdnKUy0TZXDvwOC+QizLUpy1dGcIYpjGPpWxkN4c4x9+kyi4WnuRFclKQ8jSgM334gknMYxU/cJCTXOQfUr2sLV7kdarTgPfpwRdMYTHf8xN/cVcOdZZsFKEOHRjAOOazmA3s4QSXCHLKEx4nM69QmNLUpCWfMJDxzGQt+zjKGW6S/pU=
*/