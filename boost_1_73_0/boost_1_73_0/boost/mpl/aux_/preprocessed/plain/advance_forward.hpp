
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
xA4Sql1IhD4OLI9gW/feRimlJbNrorprTVMoXR9uKrkpcOzjYeMmdf04P1BLAwQKAAAACAAtZ0pSWXJ1W2oCAADdBAAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDYyVVQFAAG2SCRgvVRNT9tAED17Jf+HaSouiHiTEEFxTSpEA0FtCSKGa7VZj2M3tjfa3WD87ztrh0/10F56Scbe92bezLx1ZNFYKQxOWJRXqaK/NTa10omZsFkc37Q/cDmNu0DjphASE8hQJKgNk0qtczQss3ajqqJhEX9JEPEuJ/sIC9QPqPsmT5BFLktDx4mwoivDh8EARoMBzL+BqY0slEGffRUWQ4i3eACDE7hWDwQZDmA4DscnIYEvf8Q+O1eVxcr242ZDYIuPlme2LHzms6VSpKGrEvFdVRJzXuSO0YmR7QMBTCtx0rZC8KdHiCpRYifzAAxWCeyahjrDCrYmr1Ygt8aqEmbK2JAovONAJFVZiirpsoac783mi/jqJtxz6W7mtzGvkdeisvxoBH+B+ZKpFZ6m25WA/hIKteK/hD4aBfbRQn8GvVYA1HUdZBQFqVIBSehRP89KojQvEJzA096bBL0JzeYarZFig9Du+7ztFC6IQWdOnyGBcquLwCBPlDTcvezv
*/