
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
RpTJFPQB0hUqwTigREq4rxzPslEzhd7ZUWH81DcSk3tjR/SAdPH7i7x1oWMZCcoC69hYhkwCUkA/GEyiD9cAPn5+tzT3A0p3YYoN2/6ktngfRusFQuZfVMUE7wxAcJ2hp21RYGaXttnrL6xw4CI5rFtYb9K04uYDdI5IjhcRhz0qZGBlmKbcNyiSNY7I778yBpFPSOVlw/uQgYnMX4XdebGjFDZ9HnBqfgcH6wFVPBr1bBeAawhpDgoosiU136IBrH2oa2FC942SxacUuOI4toqinchyhQDQqgoeQtuii0+R+QLR3DhFxQrPjg8Dxdek8jJh+S9Vk4GWYH0nUEf8AVSTbD9wcUuwF5zswTWflRH/P/AW5XmMvXBPPpnTgYtiqZfAy0DU+TKcZBZQ0x1AtupXjCMDB/nSnrqa7uZdB08Xt+yM7UjNB782BmFlEKWkctHhU9iHmAVHa/En5WZpAy220HBbedhJOgFIvhg8siDpL/xXIUgQcIijX6ykseGyOLdAp2izZG1TRpgH9v4PhbzH7OnDBcpd96XGI1EVBg7XyEXB6kyZOG3g9w==
*/