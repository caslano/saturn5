
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
YHwDx+AmMVbyZozELZiAW9G0XpNtxW9e8RvYtF6J/DmNelPsEOv1ETbCT7ApfooeuBeD8DOMxM9xPu7Hk1iEDjznAUzCL3ArHsT38BDuxq/wKzyMp7EYa7IOR9AJv0YfPIaz8Rs8jcfxLH6LpXgCS7hn8Dv8Fb9HW463U9gAT6MnnsEo/AG7YQkOxLO4GX9CT46789gGf8Z5+AuW4AU8jxexN8dJKebjJXwff0cvjpPLeC+y7x7IQVuchXb4GNbE57EWbsUbcBfa40F0xGN4I57G2tiPz1sd3IB1cSvWw21YH3dgA/wUG2KgA9kjzsTGmItNcAG64DJsigXYDHegK+5HNzyO7vgDeuAF9MTzjlwLxIvojTac2/ywHrbATGyJB7AV/o6t0Z3jLABNx99iG/H7UPxu5H2b77PNxfJrm3WxEXqgExqxCf6InmjLsl7YCH2wKfqjD7ZCL1teV9yjGoBuYlyoZmJcKBcxLlQTMS6Ukz3rgA15n8FY31GMJc76h2Jt1j8MHflghKM9KxiBtVjZSLTjhBCFtpyJo/EGjMGaDcU9wryZWLQR40Jdxg54qTH3DuNF3lwc/uos5rPmpNEJz/PB64w/NaMNAn905Z5t/IETSFc8zYXbbniSL5AEPMEG647H2Ug34y/YC+3ZWH1wJ/bFL7AfnsT+aPrdPqD8+8FG/BYVv1FN+ydQM07ArWL/DEEPHIpGTMGOOAr7YSoOwrE4AsfhnTxHOt7O/hmPQ9g/E9B0fsjAW9k/mXgL+2ci9mf/ZGFf9s8k7O3A+uHN7J8p2JP9cw92r826Yjf2TzZ2YQXvw87sn/uxY33aFLArPsB/8eyfHOzE/pmGceyfB7GDE9/PGMt+mYEx7JeZGMV+mYUR7JfZGMZ+mYMh7JeH0Mh+eRjbuHEcYyD75RFszX6Ziy3ZUPPQj+25ADviQrwdF2EWPorKtf/l1s8bT4jv5yXojk9jW3wGS/BZcd5Yig1xGfricozA5zABV+BgfB7H4AvivPEiRuJKTMB8sV7+tuI3q/gNW4idKG7ivNFMrFdzbIRe6IU+GIC+OAP98DC2wEvYEm8Vn9+12Ao3YWvciQH4KQbiEQzCn7AN2oq5AEahEbMwGA9iCBZjKH6PYfiVmBPgW4zAnzESL2MU1rXj84ueGINtsR0uwlh8DtujPcdpHDbBjjgJO2ERxuOX2AUjOY674nzshmswAR04rrujC/bACdgTczARF+LN+Dz2wg3YG934HPTBHOyLs7AfPoL9cQEOwCV4C/6MA7GmA59bHIaDcCwOxgfwNlyAQ3AFDsVlfL7uwBdxGK7GJNyMyejJ524kzsDR+BKm4gc4Bmcb2A5/4T78P3MP/g76mxyj2L/sYPClxFGGviz7oMiQIUOGDBkyZMi4trju1/+TUqr1/v/fNP3/+4hr3dn8/HUWHiQRSg9Wx/RL0d3/P4jlrm3ev7LrDbtiLK8/rNI9ztU9TotRr0/4R5e3uUcobfN11Tqlbf5clFIXrlwnV+vCyuu2qXWhynVytS5EuU6u1gWX101U64zldU6R5XXhyvOVRih1yvMdU+uU59ut1inPt0mpC1OuWSxX66LK6x5S6yKV9VPrlO1yMKy8LlR5vnfUOrWvgFqnPF+eWqc83z1qnbKdh6t1ynZOUOuU7dJWrVO2y9uh+utPrItap2yX+aEVrz9lq3XK+xil1invo7dap7yPSLVOeR/eal1YVa7vZFKYX3JEamaGuc5Jf81H059Ac8nHvKxbJdd8PDXXfBqK6+rm19Qss5068brKddYb/Hj+0WI+Cd28loe081qKa/femuu0e8TyqeLxRt0clid0c1gWiuUnjOT1NdeFko0=
*/