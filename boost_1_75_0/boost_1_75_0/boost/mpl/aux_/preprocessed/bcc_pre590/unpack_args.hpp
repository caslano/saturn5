
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply
    {
        typedef typename aux::unpack_args_impl<
              size<Args>::value
            , F
            , Args
            >::type type;

    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
LT1CJi1qPakgO+VvLtVs4IwOoA70/oJGqXUgfzbmHy7VkoDvTmu1ACU2hSWq37QlcpoOqcGCyY2Gf0vO2ZjHAsvKR2u8K94VqA0lft2dovIWyG9fVi2OeuZYE/9j51kHlnnE8R/KR1CNYLBrPuWKyqq7TMBQGiwRp4wYePWGoVCatsDSf6zmrvl9tsYsjZhq/JQIUqyTyQyOgcSWVImftrmb3XxNEw9S61+nadMAFwPyJqeZvlEjsO5+QchJL9OgbtBz+ewHzrs4A7kPCBbS8Kv0+qmPEztsBqSXs1QZMeD0aLA//bUlhaKpdu3o4HzG02exRVDF9k9BdsaV/O380OhIorK7o/TowncUipL525VO7BuI7OjmXDtPIPCpS9djbpKDaCRe9WrURJNh/Kt1sYnaXIWOddiYMjvrDDHgabuASWLQNrqevSF1pXLFyCW1ycxpaqHWqyFMjxlDCEoXVchYMv6T7lPsCtFKQWxiFqdibNnpYseKtVGafhjZUYWvTnskq0oHEmkU71ts4ZQ/I4oIvUFJgrJRTO+uNi6k9jJsB9yyslEgEQcua8a8RxRAAgo5pLtpPuXKFdLUiyq/i325SeVVDIl/49e+TOE/d5uJOgxA3spPcxsBmUR5LRmRcenVPav7sffRheYE9/eMB4hsjpCn0nc5rLMo78H13MX9S6ZXTyi6Lm7273mTwwIH0MnFq09GuIhsV2VS
*/