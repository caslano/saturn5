
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
VudwkVywKOnPG4mfs/8CR/vnFDrT168B/cU/O872nKKpCcYJqcmmPo1OpU3OryXPmvthZijth0jrWD4/dIy4VXlD2T5Wjsu8bgbrdmPel0o6bK+RrKtcl3aFjq9LiIx97y/XpTFhTSvOS6HNeRlt5KsbV+7rYvvd97H97pPG7ySNa1tZp3GzpLGFpLE5Ia8V//vGksa7BkzoP2rshJhk4yzX8o6pz6+kcQNxJiRZ55uxVWUcrEoyDhYq+zY43LeScVwrH+z3L+MAyNgRqdOMExgTwnR+Lnxbcn4KbK6hQca7HyPlw0jCm8SVccIujakpN1B+pRJiKBzUfYyN3XTWfYyDSvJxJOfN36skb+Yq6dAo45Tj2iLL99oc11I5rtZy3VsS9rFOkd1xTUqJi3PtunNcVvu6IvtqIPvyJexnXwEnbffFaA1OlE/quFOlENkpcX9CWNWKdNjFnRI3PS71unHbHodyDjOJS/39Lpb2oetM/X0zX33xi+8+MRge/mRkesKTq8+6/v5brX60I03rXzvyof7v8x7OGXzocnTC+DaF1GWb5g+6O6bxibHFnaoZ/Qsf6nHlA+3+x/RdYf6+Oft3/n7p6eJZC5s3fDObdl+a/Yaps2V+0R3D/NMCn8p+36/vU9UKf/vB1Lab+Y23zc2+1mrse4+lD9m04J8bd7vef9rVfs/HTceV2vjxSw8PX3Lvox3GLPcJrnZSux82bZiZv/alVQPme1b+7Y6YXuuSvu0VTdsjb2V+358D2426PPex9YPv9TvrtfAh6q5N81/ZtGTbvl0PXJlTd4tvR/3Pd1EemdJzNjvgxc7bk649fGHlu4+sbP46bWhM/aSNBdMWXCpqt3P/s/39O50I+UCrn7Tr7/utfp8yf/92jzNxXrUab2k7PSGhT30q/2nnyvyX7/nYs+aCXze03Pxly8DlQ27T6tfuej/vkvbVch8q96dU31m3r9ZJ+2qsj79gE7yKzfFX7IzXcCH+ji9gpUq040APlPZO3ANKeyfZj7q9099lPy9ia1yKBlyG3ZG0EQ9xEPIlnjclnhoYK/G8IvGswn64Gsfgq3gfrsEpuBbTcB0uwNdwEb6O63EDbsSNst8QndxfYSvZryfKcAcsp34ee2NtvAVbYB/ZPosNC2T7KLZVtu/Cv+fKb4PbJN395PwOxlC8EwfiEByGEXg/DsdYHIGpOBKfxlH4PN6Di3EsrsV75XgicTvej7twAn6HUfgTRuMVjMXfMAG9lPZaWA2nYj1MxPo4DZtiEoZgMvbDB3AwpuJoTMN4nIGP4Ux8Bmfh33E25uEc3Ipz8SA+iN/gPPwve3cCV0W1B3D8qphoaKioqKio5Io7Ki4pKu64o6KhLIJKIqDgVqaYuOOaW26h4ZaWpOSeomHuRYlFakWJ5SveC31U1KN8v7n3fy8D3MviUm+Z+fj/fO+MnDnnzsxdZv5nzv0V5+LvuBCV/jiLsSEuxTa4DNvjcnTHFdgfV6I3rkLT/cLyHclB9qf6/s9XZX+uxRq4znQcyHclqGvmODgo5Q7JcRCPdfBdKd+ohHzfke9BSvl6ShuM/ankODgux8EJOf5PYkdMwBF4BkPwLE7DD3AenseleEH2/0XchJdwO17Gt/AKnsZP8CJew2t4HX/AT+V4+Ayz8XPZzzewAd7ELngLe+JXGIDfYBim4Sy8gyvwW9yA3+EbeBd3YzoexL/jRfwRP8QMvK8/fuW7F46U7W2NHrK9S5dge+FT6Ihl0A2tsReWxX5YDoegDQ7D8mjcnxmyficz+7O17M82sj9dsB62NR1H8r0Gq5o5jppJ+eZohy3Q2E/LTcpdlHLqflp2Uq4KlsWqWBlroSs=
*/