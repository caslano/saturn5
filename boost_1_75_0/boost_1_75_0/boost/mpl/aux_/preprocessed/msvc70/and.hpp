
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

    template<> struct result_< true_,true_,true_,true_ >
        : true_
    {
    };
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
LLdiM3B3LCElLRWMWqhz4tmkpAhG6L53YEg9Ihx6lt46qPPMtVyvrG+fY+uDTskzP5MQtSbd61S/XF1g2ZDph9H88Bc+mcnUiwBp3V9L5vBYF2f3NCSX46/69l7zbYR/rjEecKHp3cYBnx4DJlgfLHvIo9Oh6dMyAPX2dRCRMMGNMTPcd6tw7uroNn7xU+Gd/Hd9EGc0dZUmyOgI4etwQvlT+Pg5hqRmG+Fn8lW37b4ORPAu++hX0pabjOXppemVWMT8i8KuqoeKsW2xF7OEZVslg6inkh0yQSd9v5y9HphcTMlFtn3yUhXYI7sT+WXGyA7ybh7Dj3P3As9BmnwbiQkQn6POdPWQvD7+7ahMdre0NrBblaZ56tjHIo0nVtwXS83zFsrlo1xqOVrnUZe+YKPoubM1zDkymnqzzliqWtA/bcV5dcbzBKxyp2UuabkeQ8tFmoICdCnHRNLzMsKaF5e5L07VQ1b1ti5U76OZ230L4EZjPfqyDo7OHchRSb68Ns+SaxtLB/gK3EVkQ2qpRwAV44fZm2yiN6Y3at2s3qJnfp681rFg+OJc4jZHhRjfOABYJtvtsOj/K1p6Uy2y1Ejli9ctg/ZKVofjVWoU8pLHIMe43bccUD7iXMvN0QDhHuGoo7biGW3kM2u3+uI8WbjrWAEWcwiJshWQTQveOnPzuHtYYsbtom1akqeWSpWfm2o9mpdrLWidfz9y
*/