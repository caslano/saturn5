
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
G7AAqhXXEUseK8NpyJXUcmtq4/HSPqk3vj7NP8Kw00IMd281kVtwmpkyxxFVQOUmg9YlvBeQ0Kp+wLK1byjQFfj1j67yFV3lR81/c83//0toVzaOvZ/OT0m/bBW7oV31DRCoutCZFRiTgvh+C3NHygjzJNMgjpszKwo3J51TkKq2zlYwaGoCjgaYJtZyObGeLJezseWJTeZb1bHCsQ9ixElYLM4eHjWwrVZZloewKk8nGEDV4qCMvMNhhTh2pU/AbYDjFv2EEbiVCmahzBSReUICCeMR5V4gV3B0gcqDOGJ2LcqWiWcl2PGgYtMTqYAbNNH+28Xk/flwNQIfLuh02OOZitBa9RWjih0epZnJ4P1sMZy8oQMSgHPwsW05yBkpoyebLIw86yDVezZ7N7ABQvy+XYeFxh3aR2frWmJ8+7iIw2UcQ4ZVzHRtG9XqSsTSiLq4Y3EaiTrI2CkzgQ20kJ3cM3R/POs+Q5BnbxarMmDwWnVxgTMEOLm37qRK7JKFB9d7b8h96I59EAC1XdoAIpdChdui4optDYK8BzdgGkYejLljHUhzbDm3pWz5MWkkx+Qpif7S0PYFCaUJPnXJZxSOLMq5SEHguf18388e9sg/hEhrNApvxSOl/+unhcrSNMI2CKr2XS3P8xok
*/