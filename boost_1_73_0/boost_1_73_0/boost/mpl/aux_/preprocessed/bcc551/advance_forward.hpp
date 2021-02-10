
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
AdvGWEKyTNzte0nv1JVgxq54PeBM5Z+PAtFdA8k+n/ZEK3Lm7EZSlfcupKognhvP1S1aqTYMHbT40dNiURPUvAByJVSMkyL4M4n49P5e7oyNT9O+o+MI48W7ST9gh0jxV7f1vaYhDAVK8Nyyd5TVxe7SKnvRz6TckefVTlaC6eBQsfes2EC72b6wnA7ZRFHXsTgWBZzLW0oRHI38eIkSLYV6dXdA2KznjSDWuax5Jo88eyYwWrse01yZYqF2ZaHn5/0O8OqcMMN+ZkXTbWzWJGbrlOhpQ3FHDGPTBFKuNjkbAsFV2WZG2bBSxutaomzkSOAoa6Hpvba1cEyo8m6p67OE3zcjGZ5xsgSMHRC+PboiqSMhYdIhFFYGvjuzglMlda7UpS4nwBs8dRvn64pTDTxJz07lpDwjWla9Uptjju1w00m4kBdoi5tPwsbSdHwV6jjUsPJFGopLnLO2fMZY5Zw4Iqewbnpnt7KFCmx3BfPF1zgQTLZi1uzq4iLHYmqG2Vp0uNZUW/k8Rs21geRbLnhXrMkthi9uFHXPuXIasmaauySJY2FoeL9WM1ng2ENOsw4/dY1v3PMNNnPp8RQFinBug8NxOq1myCO5+y1T1B3jWgCfIhGRLX7w7syh770tI2XY2pbkPr0fhynN
*/