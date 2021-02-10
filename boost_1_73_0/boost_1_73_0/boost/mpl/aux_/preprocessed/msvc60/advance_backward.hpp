
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
1Wm92qS8kdrzweDavqeYpnce4tyhLfMLXC8AMvdowRcI1xeBQjr4RdTQcYXxHSbONy0Z1NZ4o8wxYdNJCs8QeLQ8YDPjfAz/eAL2Q3fuj/YUTw082SPv7iab7Xy1DNhIKaxpu8d7AQsI8xUj+DObv37LH1BLAwQKAAAACAAtZ0pSzoYhcCUDAADvCQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMzNVVUBQABtkgkYO1WXW/TMBR9t9T/cAnaC6JN0rWli7KKChCb+Fi1FvbsOjeNRWoX21kpv56buG1giCGkSfCAWjW2c318zvU9V00dWie4xQl7DO+0deUOOGTVppSCOwSdQx0Rj8YslSrXE5Z+wt1Wm8xO2MViMWt+4PWrhR9sjP6y+24IL+WK9gOvXOGXf1qoRyAVfLh+y9KwRU9DfyARm6O5RdO1MkOWGtyUu2bZFdICfQ26yijMIJeGoK1UAmGLsEIHSnsi3ebANOOOe+Jh3IthED2DKb3QRn7lTmoF1/i5koaw3H4jrBHWO8iQG7BbK0ptkc0ayHonKtdkKjkIM8jL9XmwRWky3UyCp8SCKJ0Hcf90MAwYm6oMdroCW+iqzECuFEV6OTXBHmn3RBuRqH5Welej9RlqRcZRFP0g
*/