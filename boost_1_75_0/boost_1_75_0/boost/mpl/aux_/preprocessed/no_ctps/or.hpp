
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
template< bool C_ > struct or_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : true_
    {
    };
};

template<> struct or_impl<false>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : or_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,false_ >
    {
    };
};

template<>
struct or_impl<false>
    ::result_< false_,false_,false_,false_ >
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
        >::template result_< T2,T3,T4,T5 >

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
ksYr6QgA5E1QeEwLfLxplEjAqTpQXE1+o5BSgaiIHjQk32bHvdQsf08K2ZDVpi1s3VYTTFH0td6c/CbC+LYdo35DZEij1CajJ8OCjVh190umOLoj2I5NU0hbaaZEAvZR3cMygmf0j57E6+DYiulKyivNAr6FjYz9grC7Ax1sAxQDDANv9HaltPtVjbEpr8s3K2kv9Q05FmLVyFJI1qxLNXDtiekHzaTabUZEngvVSu6XvVsGWNefuUuwx5TAF+JQde4HSfa595lZ+QuE9YW78K2uiQCw7IM3sXROvFpJq/Lmc5vGxeZQgd7Njoh2xA3LitxsZpXGeUnvJO+UnZn/2TV/NME+5DzSoO8teVdR41NXg+yDXdJ23yOH5HG1GfPUxUemB+flsASX0Lcghlqsg25Cx9Ewf/LdHSFZMm+9rYQARmfwTEZ3LVoNJl9lE9jokH1ws9WP8ES9ThyfEc39Uy26pzL6wt2GMuIPm6h/UO2hxw6U7CGCkaFq14TSHGwBS3v0sdOrlxj5Ji2HLdOWr5lSRk9c23tzAdrLmg9wimkhKNOd6S3G4HAnk11p855MPuAXh7tdKG9nI9Fe1vug2s21Xg6+TYqAIpsNBb8LQ3/SrvDKz7/ysGyw5G7qtkXdawvb49flw6GBc89i/uNe+QB86Y2YS2CSktmAT6DE3L6Aw8CieKk2lBlGA8u7+J4X+iic3B+xEdJiA+N7
*/