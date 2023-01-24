
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
template< bool C_ > struct and_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : false_
    {
    };
};

template<> struct and_impl<true>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : and_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,true_ >
    {
    };
};

template<>
struct and_impl<true>
    ::result_< true_,true_,true_,true_ >
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
        >::template result_< T2,T3,T4,T5 >

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
Tdmto2VQNrN5RbI/s7sBkuIL2rVKjBNhAUUP048ZJrS3vAoyls0+3UmqXb73jxgIvUMXPnlOutySD/iqWqMYq1xlaKfwb6+qIs0aaJQx3FcSrm/6T487MjzgOZh9BVqTWsVlgkOlLVare/GoTRAt63eN9NO7odaZ1m7JDQCL1GFL6YV7MNkOiwtm1Fhrl/4VXqXhOE/BaOUCc+uP/hx4IS+59V8F1ov7zbgOzOaUiKINRT8vY317zLrTgvCzHdM20ZdIdLFWjcYj2AWPRaWhacS3onkPRvOwM/tPYgVg0KRfElT7yInwNlBpQmxepyRWXUdWxIDRq/I12lWyklMjrVLxV4kt+t3K4GEns4ukLVNaxRvaI+TbOlzc4wk+gE850RBVpP0Pq81IIjORM+FINsfinvI+8qa1jzt1EvZzQdr7f2yJe9l2r8zZnbL3YKnIED5DVFGe7+b1TmksvwPpC1JAc16nvhD/6Vkl8X2LyeIdehMU5J6wtfMCY1Z+m1zUo2yugWYXOiCqZUjHvT71JFPXTKsVw0a+zayrvy8rsGnnqSzObUAfhy3NQQmRbR8eedY+rhyHtH+eSiVOe+mLvDarwxqm8ksCOsh1Qq6ldSMcl6lcdgkd3sFFX4ORYFDm/B0Fo18p0zCCCqutZE3rIhJRmcTV3qFrrmRQzgidCm0D40gzaZDafr8JRWWzwcqgqoMvG4qW/WziuapS
*/