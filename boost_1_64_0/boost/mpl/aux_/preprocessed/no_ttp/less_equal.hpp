
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
XIUb8Q68B9fhJrwH78P78SGp74/ge7gVv8ZHsQi34SV8HGuT5+3YCJ/Efvg0DsKXcCruxjh8GRfiK7gZX8U8fB234178At/A0/gmfotvYWOlnLAJvoP98CCG4/t4PR7CeDyCGfgBzsajuACP4VL8EFfgcXwQP8LH8WPchZ/g63gC38BPnfNGyW8daKXzfbBIvg8WY0tcgilVy9ePvjTDx5g7qpz3+/0/zx31MOfJHsIJwkWCOdPH1IUQlWn0DxuLsRiLsRiLsRiLsRiLsRiLsRjLf365LP3/Svd8JfT/K/37j6v697tIu9xqQh3CCsKBENq1dzr69+0pxyWV495/R19yVRr2yDLNda4+uHWsQD+d+1x5knZPQjVCD8JB0g58zj3tGVkWmgDL7oN1pE9akr708Ul6ZhlzcKWk50N4V9lXTXrJFltwXILVGpeUYEvwIl3XfrvPu7esaskxFO+RrlUv3YyEdMufSFP2lYRK7uv7pLmwZJpxiRlx6ZlJcZZca8XTdeyrTSfdQ6S7tmS60rn+59M8rZPmYdLM00szLSE524vy5VzSTTO2uv5+5uukyW7avDl/Pe3nIQ9p7tFJ034/vxfP7PCU5rAaJdM8EkK6OmnKSVThNB3n7m6dND8gzcKSaTrnCaiM8g2+omS6R0n3rE66DAb4U2k69nWbTprHSNO0Sy9NGYBQCfU0oGbJdP9GuvVLpiujiyqepuO7Jl/SvFW+axYTPlQ+7zVpZljmlPu75ipyJB+ZbmO6pJ477/H39J0QIROQNJRyUN78SDm/NXnKruB3gitd17iqauyYY1Pa43JC8jNTyiiZ8IlyDpbMT4/i74qy5+womRcpK235SVlZ2RgzQyhvu5VVmk/JsvpU+U55XpO3Cn6n6JXVDrbv2pZ7WV3Qyc9J1s/T5qcC3zV6ZfUM25btuOVjfu2S+fhM+VzW5uNPfv+UPL/d81H9Sv3yKNTmowLfSZ7KQ7bjlo9VHvJhKtDkowLfU57yIdtxy4fZt2Q+vmDdQG0+KvDdpZePp9i2bMet3jysk48vWTdCm48Kfp/p1Zvn2L5jW9rj06VOyfx8zfrx2vxU4HtOr1weYduyHffveZ18fMO6C7X5qOB3n165bJO8yLbcf+vULZmf71g/T5ufCnwn6pXLE2xbtuMc35dSxftxcN6O/9If3+dpfJn349o8jY/TH5/oeTyj/rhC78f9rc5Q3p9zqHvT527o+mJYzZUF5+t9zhhjmW9DrnVZjxBdxX2+jR4yLioEW2Eotsde2Bf74ARUzxMdj/0xGwfiMhyEKzACz9mV61zsKenWwFBJt6OMt+iEPtgZW2AX7IHdXOM25Pq1ON/RmnEbibKd6bKdJFU8q8SrrRNvqMQbhrVwuCrewlLS2yrxHpX0tqnirS0l3isS71WJt0f9PLNS4k2SeJMl3hRVvPxS4j0r8XZKvOdU8faUEu+4xPtI4n2sineolHgbJN7dEm+jKl5hKfHekXgHJd67qnhnS4mXIfEyJZ7VGY9ll+d48yTefIm3QBWvfinxlkm85RJvBTrqV6DEu1WnfjWW+uWPrbCp1K9mGIzNMRJbYDS2xInYClMwCBdiW1yM7dAxju2QpNuQEK0Zx5Ys+U1BX0zFq/AG1fzoZyX+TEK0Zn70SMn3KGyDo7EjRuFgHIPDMRqn4jhMxAmYjDGufPL72XM+n5R8PiX5fFryma+Kn1dK/L0Sf5/Ef0Piv6mKv6eU+LES/zqJf73Ej1PFLywlfoHEf0HivyjxX3LFZyXP8T+V+H+X+CclfqEqfmAp8e+T+PdL/DyJ/4AqfkQp8Y9I/A8k/lGJf0wVP76U+DaJnyPxZ0v8Oerjrxc=
*/