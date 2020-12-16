
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
ArPxC1yJlbgBq7AAv8ZdeA334HXrftJI7tXIPZw8Qk8+hzVybAO4DfW4HTtgIXbFndgHd+N4fAgn48NoxD24Bn+EubgXH8Z9uA8fwUfxAB7Hg/gzLMK38FF8Fw+jkskj6IdHsSM+jiF4HKPwCZyKT6IBn8Il+BNchj/DI/g0voAn8SV8Dt/B03gZn8eP8AX8C76E3+HL2JwyegV98Ry2w/P4l+rjRe6zUFayf3XmcxMpz9ekPC+gHl+X8nxDyvMtHIpv4xT8JcbguxiHl3A+vo/L8VdSvh/iXvwID+HH+DxewZfwN/g6/hZL8Sr+HsvwO/xUyrccW+Nn2Bk/x574JynXL3A6folzsApN+DWuxG8wD7/FLXgN5XjlHo3r43WnHK+70B93287jct8EgzTO46ESbxh2w+HYB8NwAI6Q5XC+lPsg7DuyXZTy9pft0ka2iz/qsZNslwAchl0wHLviTOyOcdgD52NPXIi9MBv74Hbsiz/GfngMA2U/H4DP4j14HoPwQxyIv8FgLMUQ/BoH498wFNuQ52HYF4djII7AKByJCXgfJuJozMQxuA4jZPuMx90YiUU4AQ/hRJTfJXKPg3sfGr9LJkt5TUU9TpfyisGuOBP74SycjrE4F2djAs7BxTgXV+A83IUP4D40YDHG4zM4H89gIr6IRnwVk6XcUvATTMUqfBC/wXT0Is8ZUm4m7ICLMAizcBDm4DxcgkZcjktwBW7AVbgRV6v2Z59a9ucC2S+3oT9uR2u8wlp+z9wu8e7AVthU4p3Vyb0F9Jbt0YbPJyXecfneegpb40+wNxbjQPwZ3osnMQKfwbn4LCbhc5iGz+NaPIN78AXciy/haTyLP8eX8SN8Ba/gObyKr+IX+AuswguofOe+bl9/rvVdr3+4rP8oWf/RqnjRtZTb36Xt83Vshf9QPdtgWuP6d8seKbd9Ul77MRwfkXI6iDOxSMrrUXt+uF52/bvlsKzHEfTFoxjHiSst18utdzYFrKOt6iTa0RKs7ZHPr1O1SZ5M21NlnKC0T46YbG+fbK4kLtNyCda2yqFfNdEdYzyN+Qoc2i0T1tdsuxyI4YQq/uazgfiEKqbHMy2Fz0sJK/lcgFrtm4s32Ns4lynzYgXj+mjmz2X9COEEI+Ew4SwhNprlElLIa1EYy8b9jFfmktcdtMsmFDP9BNMuod9G2gozj7q9dFEl6eFa/hbCtGNYQmgy1d6OuvtU5mGabpO977KoqaSHeqYdxhB0bl8dw7QTqnbWJaTlw+dcppcyfo1QRn4qyKe1/XXJJuJhGV4nLOWzfjPLKGxMm2zS4XMY7lGWw+c4PpsJh/l8nmBtr13B5yZ59jbbvfnszw0UddvtFKadYN6LhDjGqzCceZzbc5uYdph5zxCuVZIW0yv43J085U5nnNAkn/SxnOAdU93uO4y/hynT+RyLgUw3YSnju9FVe/Az/G0lRsWQB4zH3Bhrn2wYwzyo20J+CbGES+GkyfQLhLWMVzJ+Cr1Hse5fki+mlyjjMyhXDEKzUqb8PWZG7W3J9TOZnxC4lbSU6TPt7coL8SThEiGSdKK3OrY1957l2N58/1Z7m/NTfD5xmnQp3wo++xRUt0HvjVrt0KOYXsD088x/Ai8SKgiu2qcHMM1MnCrmr2J8txJf2SZM9/+6ie4M47HSfv0aYa30J+e/jX0Zw1Hdpv0S0+Iwl+km3I/XY5kXywh+s9kPtju2efdn/BRGYAh/T8HLjBdgHOPFuBJ3S5v4UsZP8vki4RrjfjuYl3PgMcJZQhmh2UYvXRAhmmAiFBJOEEoIFQTvTV663oRIQgohl3CYcJZwhXCN4L/Z01beM3gGz+AZPINn8Aye4f8=
*/