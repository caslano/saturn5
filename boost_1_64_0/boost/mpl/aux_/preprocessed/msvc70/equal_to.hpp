
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          equal_to_impl<
              typename equal_to_tag<N1>::type
            , typename equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
36X+z0k7/hj74ScYjP+Q9eaQcmW9Xpb6R/5+Qtb7ndT/91L//8LO+CP2wGs4Cn/CCLyOy/Bn3I43pH5/kfr9FfPwN3wXyTjzSwX8CiujEowbVkZ3rIoeWBuroidWw6K+Lom/jkF9npZ6OYO34nvqPv1U+9tht7xvj2yHvar3ZZew/S7K+y7J+y6r+4DmFMVJu7Tts9mtWi5IlvO2s1w7D8f6FjJ+4rr2da75k6JIC0k7SLkkbb/DyaW2fQ9nleckdR9E4jKuQ5OsfRHx73qYova6mXYtM+qXIPF6Jv9ut3+Cf/dczrVvkrWvIp6/M0hKn8U6tMzpzjq0fRfZy4v7L84vt+3DqLaC69OkIFIsaScpl6Tt2yhYYdu/0XAl9UFe6n6OTMp4XnFlYX/HLjxFUvd7nOe56S59/4cXr+3EbqjuB/GlXlco779L3x+y4i59n8gpXrtAXKP7khd/3yBl8LfXqsI+km5o7SdZsaq4r2Qnf58kWftMLq0i7tXFfSftVhf3n8Sv1vehbKHsGf1Y5gk3274Ulj22Gnl+Ca39Ku5r9H0rgcprGIF+vJaC+Tzfgkb9LMfWFPe17CL/IPK23+dCYhnT3fw7ywVhBEndD5PJ8wKen2W5nLuL+2NOKX+PoS7vLnu/jN9a+30zrU+SP4atLbmPZsfa4n6aHP7OJP5L6LmusN+mHar7bgqI39p/E7rOuA/nEOsw6sc5w+u+vF7tNH0N6wr7dLZgIK9d5d+OrSvs38nHayRrP4/PetotBqFRf88KXk/BHXgjgmXxPEnp/3G/x7YPyIfnORiM3cZTNjzL83U4iefZqO4Xyue5tW/oGs8bbmAdxB9ImkTKIG0n5ZDOkq6RfM7w76RJpIWknWdcfSmuh+vhergerofr4Xq4Hq7HzXn8/v3/lq6TOdPmKQMAyt//n6K6f1+K9FlHusnvHfFzZe7QaEt/xYiBo8Iip0abE2Ii58SlJkwrmiewdSl9bGtiVX1sPN9c+HxapPKKLBMqyyTFFvdtfEbeU83F/YfZRBkTl5pmVvUf/txQ6e8xFfUftiRNS4yebkbltUv0tVneFx9N911x/9svDaXfSNVflxqXZnl+jucTeU9GUf+d9OfJOs/Lv5sTpifFUYL6vFYg+aQnpaWmm9PiKAavu9U5hL2o13n4pVKPso4LMm+jmR+Dym89i5ZPZPn8SjhVWb5w/fnWGJIS0pjFzyzvsfkt/1XpM5/N+2vhLPyKOsyMK9p+vHV2epw5TbZg4fbzKWX7fTJdtW14/sF0/ZiOL8mHdRtuq7o22yo5Nc5kuL2020K/raTefFl30qzibfMOFyinxyVZ1lmg3TbUaRr1cIy6mcR6100r3gbnjbaBLF/A8h8pdTqteBtcKmkbSJ9frPT7Dya5yTXb1cwLtzG+uF/V0usZGRuXGDc9mpZSav+ntY6lTdr0tfrJV90PZMzLadKltsSvyy8h1jpHj6cDfa3nWIeZMqaoxr18bdnG9NWr94nYmGTafFHd96IxpXF8oakY9oVfk2ViWEJdbzWlP/qGlOMa6RvyM83QlcNsTmfLSlm8HKg37XFEezy4ZG0zMdHamA3bVF0ph6qOpE6kbNEUTrOdzkr5MqV8C0kFvD9oZnH5pjGAILIwk1LHVlm30xoqIEXeI9vJpryeNvui/ePkDdsyFm2rlpQnVbOtsqV//01SA9Jx0hXyzDcuS6R5ZomfE8spD59ZAZYY6pOTlE0dd1HZiIc2R8xynFbm6mD3jY82x1uWOa9pb/nWY7nquBvubWmjynts2+At8nuXSpQLt+BVpVyJxeWaFZ0WEy9tkDgs5ZpUxnJNlHKZVOWSfUK2mXr/k88R6jw=
*/