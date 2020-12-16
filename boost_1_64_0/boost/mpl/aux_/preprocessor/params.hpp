
#ifndef BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/preprocessor.hpp>

// BOOST_MPL_PP_PARAMS(0,T): <nothing>
// BOOST_MPL_PP_PARAMS(1,T): T1
// BOOST_MPL_PP_PARAMS(2,T): T1, T2
// BOOST_MPL_PP_PARAMS(n,T): T1, T2, .., Tn

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_PARAMS(n,p) \
    BOOST_PP_CAT(BOOST_MPL_PP_PARAMS_,n)(p) \
    /**/

#   define BOOST_MPL_PP_PARAMS_0(p)
#   define BOOST_MPL_PP_PARAMS_1(p) p##1
#   define BOOST_MPL_PP_PARAMS_2(p) p##1,p##2
#   define BOOST_MPL_PP_PARAMS_3(p) p##1,p##2,p##3
#   define BOOST_MPL_PP_PARAMS_4(p) p##1,p##2,p##3,p##4
#   define BOOST_MPL_PP_PARAMS_5(p) p##1,p##2,p##3,p##4,p##5
#   define BOOST_MPL_PP_PARAMS_6(p) p##1,p##2,p##3,p##4,p##5,p##6
#   define BOOST_MPL_PP_PARAMS_7(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7
#   define BOOST_MPL_PP_PARAMS_8(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8
#   define BOOST_MPL_PP_PARAMS_9(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9

#else

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_PARAM_FUNC(unused, i, param) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_CAT(param, BOOST_PP_INC(i)) \
    /**/

#   define BOOST_MPL_PP_PARAMS(n, param) \
    BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_PP_AUX_PARAM_FUNC \
        , param \
        ) \
    /**/

#endif 

#endif // BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

/* params.hpp
xe3YX+JwQXgQB0q5Z2vktw/nS7md0CDlzpRy75NyZ0m5D0q5X5NyH8I+eFiO+6M4EY/hJDyOenxLyvs2Po0n8dBfLD4T+GwFe4zGKkYzmm0yg7SWdIh0kZRHcltqj9f8P04Po/0fFlsy9/8/LO1/9bP760mbtQ7pY2Wceob5/D881qDVG4xr1zy4zVrgfJ93VJXzfQNJHhunOucnxemkjSN54gyGuEkF22YO0o6dKdco6PATpW22W8poeUxcpD6MQfWxEVpzW4UxpVaT7WsWIvYW3m6JSzBQRku7hU0xjhXwmup+BTyLjT/z63KFH7tJWr0+jJwu0l5LIMlrIea2jpulrWN8r/8v0occFxkHxvf68dp8TuBiEyaFTAwJT2J/GN/b8hdLu6iWXI8Q68I8uypukmSUMnWQ5UbGxWrNr7lJ/sjocexh02s+5HPnYJb1GJe7lnyJjU11ZCPnL1gpQ4CSn5Nhjt4C7cqtZQo/rvwzzftMp9cmRMb9J46rdlJGL2nz15AyVie97Us9Cyuj8r9xD45/WbV3Cz1uKEP+9TenHArfTin5ZVBW/nC3j3kfBpYtfPscs5TNsmGKuw9/Z9u0kecg+jzC/+RZe054FS+w/uxMua6kwPof/HwSczzNQDLtWau4ldVn2rRgqzFEkieH+YuURQrBa5bxGxFxCbFovN/Hnn2Ulb/Ja5yfst88L8eB1DWjnDzzUWJ1Z/Bz8gQdkLoa11K0ON3Ng5bvsarMl32NeWWXx+m52ihG4/Kb7aAs3GpbSJ2qFHIMOVsdQ65Wx1Bhz1W9yHw15vlF4j2WuJ18l+TH6mRdxjxX86830k+E/P3g7kCehCjjtVp+HCM7y5nO28dnWa7VyrWKC/7K5G5sB1qu1Wom295DAlpV5TivQvqmDseZcbuVosi/97l3L3Bs3eZ9IcG8Q/b/l8oy+PvbOupYla2YlK0YU/FjVYXHboofYyqp+6kWN1ZVeCyv5J75WdwYlo1Ylc3YVk9jDGv6Ny2+W9+upW/Zi8MvpjS4+qOtWJWtmJTtGNZdY6xFztOwntxnuAyavx8mSowmBuvgJGnj+pWScyc5p+J9xvd4oTK9LTGds+iHH2JX/Ie0tT/CCfgxxuGnOBMvSFv7Er6El/FlvIrH8Bpewi/xn3gDq7HOm+iKtyRm8hV2xtsYjF/jRPwG5+IdXIXf4g68i5n4HR7BXLyE9/A7/B7zME9iIj+iK/6EvvgztsX72A1/xdGoKUU9SwPqsDTKduc8xvZ2j5LtPk62+3g0v08n76tRyPsOyPuysDoeVL0v5XfWFybvC5f1Rajed+x31rdH3rcX5VoneQaI/MbKb2+21TNAJksMJB6bYgK2lJhYL0zEsZiEWpyBBrmWaRrOkVjM03JN0EK8iIvk2qAU/AGXY2WJdblIrKsZpmJXXIm9ME2Ok1UYg6tRh+txIb6Ii/ElTMeNuEnGDu3CLRJbexnfRWMsC1/Fq6oxQsTj5PeYz4Z8bnz4e6fqGj0nrIbO6Cwx0RpYH12xBdbEVmi575Llmr3RWFc+Z+6ox/q4CBvIGDoP3IWNcB82xnewCb6PzfECeuHP+LhsxyfQGb2xFvqhD7bFHtgO+2B7HIMdZDt2xCTshPOwMz6L/vg8dsE0DMCXsDtuxR74KvaUGGagbNde8vnsjU5sx74Ss+yHfhgkn7+BGI6DMBEHYwoG4wocgqtwGGbgCNyHo/EdHINncGz+50F+0+W3Ps/q8+BS2vR5qIFV0BW5Zvz3YnASp3t4sbiHGYczXHf4r4jFLSTmtpV0hnSbVGVZBY0nKYAUSkpcZo/J2Sf7ZJ/sk32yT/bJPtkn+2Sf7JN9KpnpIVz/T/c=
*/