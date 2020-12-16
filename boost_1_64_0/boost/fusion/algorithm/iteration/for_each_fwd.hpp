/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each;
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f);

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f);
}}

#endif

/* for_each_fwd.hpp
b5azvHj231c42tGsY/XeznbsSh3TXOoYz957P+Wf3MrZht3I3x/KP4H7cnCuzLGVU97Kve1SQmMxgXtyRcfIdjPL29DK2W7dqdeKUL3ivh/LT718/ic3Q3fYGh5MvnXkKx/hWqIGgqCA4pKsEqOs6Os0Y5/3g2vtPgozzLFInpHxKGblF0zNj5injJlBPnzNv+XonKF13VRc4jN9yPYYYp1/7deyX7758RVDeuoNe5K+/Dr3Ohfl5+EnMXp9Y62f3lG46WjGmpCOmRrH4w19SV9f4dAxtECKeuZW9yCLfiozIi5ArsrMUpnZ1zvKVJuUyj97w2WmOMo0+6J2H/d61jnKtN2cd7quGfvKH5Teg92LHEa5GX9wlEtggFLu19HPNO9rLzPwPT38fYr9ulP5qap3H6T1IL7f4CiflxcFuTl4V/fnlOXHMh+GrovmKXpvorE1SmXPk//9Mr3PKkZ6G3NkA2WX5AUffbNoinh0+HH/4BjP0bpicLg95Cveti7KKSwsnhUaXDlFU/Ns/mDnahY19jE7wn6wD3onLwzoHVCYlzpllGW8E4rqKzwUU+XRwFrNz6N6EWportHfDd15xld9QvOPX2sYdLf+jTranx2nBr731HfSRPhDnRpeb/Wy/I28bc9M2W2DSp+4d7C/hsIjqHfVjap35CChBcvySopCa9jZUdawG263rmF1fts+frSGc/ZnRUR/mv757bF1Btvbk9HFvG1b/6rX+R++RrRbgfzxhmJ1zNa7W3ueJbkFgTwHOPI0/ifoo/f+m4Nr0v0GBb+feYv9+9aI75ffav9+xW327z0q7d8PW2z/3u52+/dV5nfbWmxbW+eZgVRjXXRn+MyA+dwdx3PRkTtxVqDiAKdO/civwtTJse6NZ03aIwHdQvN3r3ZO3QaSX527bqWxzFkhvfonoFc/6bXKoRdCfql3WfSKsw8HJaBPaM7MkM//tdLnJeQ48isP6sNFW5IztcyYhoxpJ/o9TuWZay6Lzc60iPVahvk3sraP99r2znMoQw297g6dQ0lsvKNXlPMnWut0cJZ/AuXXhMvfubGt/QgPPcxxvNFFjzT08C0J6ZH4OGZedtchYsxmdnTqcJIx94R1iH/M8swU0zmgXC0eTzaeO+AJcJgxDkJll7j0Qwz39tAzxC3JKlf3oXzn3ozOn5j3DErjn5H+088tne7cs9GaLxz7KLAHMplGzKZeU6nA6HvMPZD0iOuGdrCd+0mVT/6r9Q76cmQt6dPOd22L0lh88us+6RqnJN0af8S8Zh1tlunRNr3c1vWqy6rOzjNMI4xniWWhM0zWbeRg+KB4zk5x39c5Ju3zmzra27SL8/xWOnpUuegRfc8mxXbGbLVizJxrLB0jznAtcSl3DOXWupbLwbEYyg3VfdQQ93NjfQ90xpkYS1pftVuZ/pml+bGXaW1vXdMay/6yyBgtVQc6655hzCeuepQWl5Qlpoe1zF5dneNtHGX63coMHpqLucxRQ6KfmQvpUdnV/bzgiupf7rxgz4PczwvWVe+a84L9pEfFQc66v92dHO+1xTmh1rGXv667yo9Y17Tr5qzzBtJm2MsyahvXvLKue/T6htq9U4p8ke4ZrOto+IoRt22Wzkc61qDR3ykYe2ZDLuL3lrORKzzm71UuZyNrHGcjdS+0zdWK4RVxXjLfZc/Nb91z0/uGTt2C7eRvgR9to65KO8bM72jrPUZ/62e9p+pv/UN/m+CyB5hmPb/pvBeVah8yoFM79KlFDkeZqgut77rMezN9F45VNvmCYJrTjiId3x+N+H7JHPv3J8zvMZ0ZdT+T98ufJW0s+2P3M6n/PWdM3c9oNt7Z03jPjLqfVY3/zOg=
*/