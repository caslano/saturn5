
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
dMJcWigunSiXFopLC8WlheLRQvEMGoVm2aPvwx59H/acX/eOTCXbc8lkex6NUqNR/J01XqPTVTNIFdZMUoW1fZVdox9ha1vfOXZ5nanRiqm9fON45djotTvd1im9Iq2uGq0un06Xr9Kl+h2rlnddK7/80QBe9q5KZ61Ov13Sl5+G71u2a3k1r5T3qEqrHhW6bvS9SoPe9duuyusNj5rvmo8eTkm1Rt92Mauu4Xs1f+lil552EZXrLgtZpbyRvVdwZknO+esLPN+78TQsY+d1Vq+1JdUw3UyezBZQdD2WKq9UKqScfFqivqU9g4UhHm0sOsJCyjIMaOdDxafPXd+hI6bfMn3vecQ0Jv0w4vur9tIKtKGv+k6NIRICqunXPBzzkf4jyJyqewgTHuGIasUeqm7gJZMiDKYM8m5i0euFM3TFOdUsE3VdD2fZuCKYHvFQ6GqwvJRrJW/mfoCB6pHm680DASOWsizAmoDbBYyTW+V+AO0okRBIWPBZBqq/mCXirqJp7xb3e6S9t7DfLeu9RL2vpN8j6HfIuaGrnKpm6LqrqT/+U/N/UEsDBAoAAAAIAC1nSlJZdc2z+gAAAKQBAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTA3VVQFAAG2SCRg
*/