
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
TI3BLV9fyssTGe+GQ9MxPSJu42lhd9juh5LnIpR8r0yen8gfUEsDBAoAAAAIAC1nSlISV1XEOwIAABIGAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjhVVAUAAbZIJGDVVVFP2zAQfrfU/3Bi6gtqcZKBNqKsE2IMkBitILBnz7k0Vl07sk1L/z2XuFCk8YSQpklRkrPPd999311SBPRBCo8TVihTW3oscLO2rvITdlGWs/4G52clK/hup+DR+RPcoluhG3tVISsctnpDu5UIIh7n6UEKn5MUykZ5oEvAGpWrLAR8DLBE78Ucwa+91NYj+yEC5lA+4AiSY7i2K8iSNIH0MD88zpMEzn+VLKbMoYM+9r3Ba7FAdmWlCMqaHIBbo5VBno7SL8dHo9+opV3iKEkOmrDUPPuaJEl2EB7Dd23n9iF8K2/uztipNQZlDBHxsB53TAJ9eV0RtXV9dmXmVJBXy1Yj7LLXVmu7pk1GREUuekqyV5xkVMzP3g8raNAh1IT3g4igOgKaML5CMw9NDkcZY5c1hK0GDiWqFVYjWkHQW9w72EAqL7B6Rp9t4csG5eIfyDpUNTSbFt0rgd+n7xC1/4A2GaKpVP1Wt/yP8m5lLfh2emmoT7Xq4sehlr1BDhHC
*/