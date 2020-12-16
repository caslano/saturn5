
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {
template< int N > struct arity_tag
{
    typedef char (&type)[N + 1];
};

template<
      int C1, int C2, int C3, int C4, int C5, int C6
    >
struct max_arity
{
    BOOST_STATIC_CONSTANT(int, value =
          ( C6 > 0 ? C6 : ( C5 > 0 ? C5 : ( C4 > 0 ? C4 : ( C3 > 0 ? C3 : ( C2 > 0 ? C2 : ( C1 > 0 ? C1 : -1 ) ) ) ) ) )
        );
};

arity_tag<0>::type arity_helper(...);

template<
      template< typename P1 > class F
    , typename T1
    >
typename arity_tag<1>::type
arity_helper(type_wrapper< F<T1> >, arity_tag<1>);

template<
      template< typename P1, typename P2 > class F
    , typename T1, typename T2
    >
typename arity_tag<2>::type
arity_helper(type_wrapper< F< T1,T2 > >, arity_tag<2>);

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename T1, typename T2, typename T3
    >
typename arity_tag<3>::type
arity_helper(type_wrapper< F< T1,T2,T3 > >, arity_tag<3>);

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename T1, typename T2, typename T3, typename T4
    >
typename arity_tag<4>::type
arity_helper(type_wrapper< F< T1,T2,T3,T4 > >, arity_tag<4>);

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename T1, typename T2, typename T3, typename T4, typename T5
    >
typename arity_tag<5>::type
arity_helper(type_wrapper< F< T1,T2,T3,T4,T5 > >, arity_tag<5>);

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5, typename P6
        >
      class F
    , typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6
    >
typename arity_tag<6>::type
arity_helper(type_wrapper< F< T1,T2,T3,T4,T5,T6 > >, arity_tag<6>);
template< typename F, int N >
struct template_arity_impl
{
    BOOST_STATIC_CONSTANT(int, value =
          sizeof(::boost::mpl::aux::arity_helper(type_wrapper<F>(), arity_tag<N>())) - 1
        );
};

template< typename F >
struct template_arity
{
    BOOST_STATIC_CONSTANT(int, value  = (
          max_arity< template_arity_impl< F,1 >::value, template_arity_impl< F,2 >::value, template_arity_impl< F,3 >::value, template_arity_impl< F,4 >::value, template_arity_impl< F,5 >::value, template_arity_impl< F,6 >::value >::value
        ));
    typedef mpl::int_<value> type;
};

}}}

/* template_arity.hpp
nWB/3UdOg8lwoMn+mVP939c+kH4fSp+PTPmXK14fi/w7K/8usn9X2T8O9oLdoNoX77+qR4v2dUT5fyP7fAtbwu9gJDwqvb6Hp8Ef4HD4o/RcG6Z3Xvio0o+Aq5X+n2TvJ5Tek7ATfAr2gE/DRLgdToU7YDp8Bl4An4O5cCcshM/DEvgCvB3u0v3yJbgZvgy3wlfg2sa01xENz0/Vup5a07N+3c5VyFokz1irE7rW6zyE1HDeagrxNId1+RTPeawZWp9zB+Ka0xqVWj+WbrdpbuuuVPKDaUg2UoKs1li7asS8rmbYaPSFEbCvaf5rGRI7zTUPFk4jzJvhrvmw5rmwWhOTPGAm3AhXwh3I1jEQ2Y+0SiRNZDCSjGQjy73mzG5DzHNmjTUsByCxSfXrVmrNSubTYnfkqBFmpnNurR2uhGsR1zqVu2GdxhC61qicjCxABnOejGgOrnsdykpYhdQgCZTbNR93lNacNI9BzEDsmpe7VnNzH0X2IMYakgfhESSDdMqRSmQHUouEv8V8XWQCsgBZjWxBapA6JGIP6zMiaUgJsg7ZhuxDwt5mXVkk8e3QfN7QETpCR+gI5vhl/f9FdkNsS+YtOx7+f2Mv/CuN74FnGe97c4YOLsmak5fjXPfvVkrg+mY5WOMCZuubZQayk3ipCY7viNOnpdpmjk2aPs7h3gjie+2zpLFkjte3efnAa/Sb9mn4Qjzn3nmxtt1A25xltlI8j8pzsHWel5InNhnp+NYYTW6Gn6yst4+fTPrUj1GwU5kkzzfSfPfaYrtIo5Jwjmx1bTfXpvECmp07v9h1rYZriRRgbklZievawfpwS7x9Eo829vWPGeWO6+Nbblexg1nDqqGymb9RD9CjfxeKnAR3wheJn+itixZY87W9r1/yrv7+7d3RpNOSnKLcebk5RbZ5NFHpvx+75TvWc3Pa8RDnyXFOvy7RHWWq03dkMigsYmhKdo4z7kFdz1W4Ws6NfPKyHDvrZeeUOa/v4/pL6GMUbn6KjZ5Q/336eq7PT3GGO2yqf5t9aTbJur9rfxdFGeyEw1+9jfrsG659BvpRdoXbQ7g18eRPgtjcw+5bZfem+i7WCL4cb1SIp93lDm5w7E20YWfZtTgnJ9vGAnNm36Hs7+GfOSqf9PvUeXv4KqwhXOpAtw5zmYTE4BNXTTn1qI4MvO89Obi+LbSVjm0iPPtUK12zZxW7+1QENGxcnMVqfSpflK65tVH5YhQ/ReexOp+vtDJoRLcb9WqbU+BKP13XUkzXSrj2Ktdoa4NceU7m2pNRznAab+DII1PXi5VnHueONj3PGW+C/n2+V7wFur5E8Yb/3Z2nQ4dUpZOdM29+Sm6241oy1zACaRfnXpjj1DVR4dzrGXLNrnDsS+5ol4/y7ztOcNrl94Pq22X2ofp2Tntwhz1C2AmEmWnUmcqfpnzQz+aqC+J43M9S5Uharfv4xXA36Q8Y6q8d2camqE3vaRF4W1ow7Ke3pdfifdoS16zbEu3C3JY4V1vyrK9BrjgD/u6s0zKFGaxzIz9Xvfbl2hvEozXwmHCGS+AaCqkOPfc6rZZNz9EzYgKynfhxw1025dYV4Lgf173hbuITaW7W3AXE8vQfLlc99FAdRsM3CV/ukR83I8eDIPi6u2iE6Zlgqru5C3z7QWvZS23ZbVNDfzSg2Xrqbpc//RH5Ph9E9hC2boRZd3te1twcemPDa4267HWbl71am55d6O3j0zT6UTk2GYU+AznvN5L8YVs9Swz9XYmhvzt8HuHHcC3TFJ5njE95zWWOaCmFVeaLkXcIv39kfZl5e0B9XiByswP29xp1QnB3XzKek3pG+o5DkZ66l3iOlZF+RWq/dmQ=
*/