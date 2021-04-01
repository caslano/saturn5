
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
QnbdabJ/FfzlzFJ5cQOBIcGty2Rn0h6SREDsRs67uzcc3ruhGaXw7x6aznCP6Kz51mMmZN3cL35XfNFAdrEHCDxj+I9USwuIBzml17gF7O0RKeQBB/WOAY4/g/V4dsKTtGWKacSN1qx612PCVJr6Ji6YaRAOKaEs73sBVE0VXwE02llKK7GZNwAq0NZub7KjK2Whh1+xtSbeRfRbC+rHRi0Nz6sIzU72DbjHsNL0qbxQaAi1ei729ZYoHdpmeNCnn2mL/OtIkMgcvwN1SFUs3bDy+uMrY9POlVoIFbQY8dKQSDnR4JzYKLXp0MLB4/jg5L3k1IpZ3kvMHt2qfvArs+TQdI3nwAoZ56Pdwpt9ytSnmwhmsNtBOaIGfn34ExRFGWFx0c6QKyfFqJOW6Lhb0JRWWBwga80RYqwV+UmXCIqVnP7F1u3mKKhgigQe7ixumE2d23EeGYcAFNVJdWV1/IdI3l2Uv8wBFtrN9Ia9R9IkFyvfr/gf+TcV3S4eLa0ILKlb6YRd2HCvjj+mk9whQrdjNjUHPBBHusEa4WRPXx7emd6cIyTNw52XxA==
*/