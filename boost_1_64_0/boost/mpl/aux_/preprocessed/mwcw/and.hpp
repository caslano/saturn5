
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
pw+p/cT3PjvrpkWT3v6xecDQEzl7Q37tfX/zafXekvJ7X84Daoht5DecEjKk/24ZdkQTRqEZh+FynIC5OAXzcBpacDbm4yIswHRcgSuxEDfjjXgvFuERXIMv4Fq5l846e/+u/J7HLlJObf/uY9J//Dh2wkOa1xXL67q6eN1T8rrD2AWPaF53TF7XwsXrbpD+5ERshgvxNG4mVsjrdsrrWhGL5HWDpT2HYzscge3xGhyE12IMjsSJeB3OwFG4GEdjBsbgUhyD2TgW1+E43IHjtfV/yX09Zko9Zkk9Zks9yoh75HV+cm+lDsSj8rpJUo9Y7IjTNffqnITxst9nYTrOxrWYgNtwDm7HuXgfzsMHcT7+Dhfgk3gD/gETsRwX4vu4CD/AZPw7puBXuBiVQqehDxrt93SV3614QtpBe0/XYKlPCPbBUIzE7hiHPTAee6IJw3AL9sJ7sDfuwT64H8PxEPbFP2I/fA774zs4AI+j3HMT5bcqRrrYT7EyvjMdwzEObfcIjZfXZcnrtPcI3SD1uhU74m0YhVtwGG7FCXgHTsFtOA2LcQ7eiWm4HZfgDk15qyTfVi7Ke70cV3PRH+eh7Af5fcfvPhf7IVrqORADcRiG4XDsi6MwGkfjNRiDE3EMzsSxmIzjcBWOx7U4AbfiRLwHJ+FOnIwP4BQpH/tEfs+xrRz3QcRyKd9n0p7V2Au/wFH4T2m3L9GMX2EBfo0bsRZvw29xF57BvXgWn8Bz+Dx+h+X4Pb6O5+U4/xGr8QJ+L+NP/pTvCmyLPtgLr8QovAqvRj8ci83sn0/y2xDXufh82iX1+yW2w/uxPZbgIHwQY/AhnIh7cQaW4hzch0vwYczDA7gSf4s34u9wNT6Cp5H9Lb/P2EbauycxTPp0jkp5nsVg/BNG4HM4Dp/HmfgCGvFFNOFLuAJflvZ/Be/AV/E+LMdSfA0fx9fx9/hn/ANWYBm+gRX4Jr6JlXgS38Yv8R1sQ1nfxY54HHvjezgU/4Kj8X0chx9gEv4VTfghrsIqXI8f4V34N9yNH2MJfoL78FNpt2MG+X2Hn8l+bE88JPuxpbyP2mIItsMoDMRh2AHHY0ecgUG4EDtjOnZBCwbjVuyKu7Eb7sUQPIih+Bj2wGexJ76NYfgu9sIq7I1/wz74CYZjOc5b6eI+vxcZQ4kcVX8cxUw6yv0JfBf5GXbjUadxlUqnsZWDztefJG4mjVJiGbGa6L+Ke94SE4gW4g7iYeIJoi+LcMOJMcREouVGfSxGD3rQgx70oAc96OH/Ifws4/+Mf6RY8pQpAD95/P98W4N9LGi8nGMtkH7j64mjlf7yY/XGzHLSjNZCsInX42a2cbwHOaFP14xnLAugv8Zs7csdK2U6L2VaJWUqII5RxmsbKFPS4swcb8Y2nMullCMn3+LQb88o4UXHnbXl3nGF67aMftZlufPzUpZI6S9Pe06UchX6yHifjIk0R6U991y0XEqrej5m4L5Npe/fac69tKnMd5e/k70xzXn8xHG8wJJjScl2Wp/h6+uy7ekkcK6jUjHvx309aW/bmOYGSXij0ieD66W9zS7KIo3s8diqmzb26D6Z3t4P0/XYyf/ufTJd35ey8e6f+ak6ZnP0489Mt7y5reTUgCMd7sodPc77MZvGGkOyzsmXz3p57+x0mpPfS/rewrEb9sUw7Ie9MQKvwUiciv3xeozC0xhPLJb0V0n6fjhe0k+Q9OdhP5yP8bgAb8Ab0IKJWIALUcrN56r7cg+UdIdIuYdKuYdJuYdLuUdIua+Wcl8j6Rcb5PNRPjd3Elsr721JP1nST8MumI4jcAkuwgzMxEzMwaVYiFm4DpfhejThrzAHD6EZn8bleBQ=
*/