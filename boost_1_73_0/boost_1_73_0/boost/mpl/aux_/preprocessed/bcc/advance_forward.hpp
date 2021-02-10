
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_forward.hpp" header
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
/w1QSwMECgAAAAgALWdKUqGSmn8ZAwAAzQcAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDY4VVQFAAG2SCRg5VVbb9s2FH4X4P/AKQgKFGUk+ip7sgGjKxBjbWPEXvNMU0cWF5kUSCqq9+t7KDlxsgxD1z3sYS+kSJ7Ld75zUerAOsEtLIJUqlzjdg/HRpvMLoLr7XbdLmR9s9l2X7/IPWoQXrsiSKOzbBp16sEF2YB5AEOtzCBIDVTlEZ8z7nhnMWJXjAxj1toA5aTgTmpFqhIQB7GN3elaCegFnaEZ+SSF0Vbnjq5Wm2h8FfeCu7s7ujzrw+wRmAFeHuahD6v9DN8RpdHaPGTxaDCOh2w4xDte7rWRrkDRzfWSjlif9kfjsBe818qhUbo9VmjUwVcXFe5Q/kxEwY0FN5dW0yQZTSk7C38EtXfFjCCwHjLRxdqGzOI4fhZ2P47Jktz8+rex/SsIAw9B359QdO47KKIAcf//SMF/xveJYzyd6h7b4X0pvULXDqI9LIKLILUtokVQOFehwuMxzYG72gD21E+bzXoVCHOsnEaJ80Oq+AEW59YklGYd9w0SSp7R+Y7UaLjgtpjnvMTccpW1V9RWIGQuISMvQyIF8AwM+uucXJBtIS3x2SR+
*/