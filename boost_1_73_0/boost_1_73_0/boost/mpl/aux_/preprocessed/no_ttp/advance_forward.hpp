
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
YDJN+p8+0HKvyzfwg0Y0UsqUGyFLqAqkwkFv9FzWZfpbGUMr4/n52Z108SRp54RCXqxHjvWxGTqnUEpiGzmBH54P/UEwGDg9ZmulWHe2rSjW4Hfj5WZdvIM050qjGQkt3cvL8MoNOvADlkuTR+DbUmKvtbBxMnhlJfkBE3j6+Ef9b8p/bvPL1U5CsNOQ5piu/rf0DS39Zy3ctS72dqeTDu11ISy+PbRpMyGAbuSMWW5MRfCf03iB3NQK6eCnalsZSd+6pSMwUhYgNGxybmgCNTVFlNogz0Au4CStVXHCYgsbs0LMw4srYminDOKSr+lC0mteFFRcXa4wg/09RKzC5JB1F1EfeJlBpeSS0mtIKWzO0xUReS0TxKlcrwnUFhJ53vEdMd0n0bGlTZ4+zzySAIVceqJqxewjaLhzo7ncvqISiy1YF4EvDCqgHQR2r0DONcwRS3B0Lo3D4pcGa+0SBYLVMnL2OZwxS36V3Ayo2KbCLw/gg6yNdcz/O/byAGwwPAB8dgh4GBwCfsVMG4hMsnbvXfO6n9MPUEsDBAoAAAAIAC1nSlI+sqiprwEAAMUCAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NThVVAUAAbZIJGBlUsFq4zAQvQv8D0MWX8q6
*/