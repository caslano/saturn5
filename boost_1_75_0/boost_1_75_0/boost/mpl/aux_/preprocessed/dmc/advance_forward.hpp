
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
1WWWki5bPupSB92WzXyZqbnsM6+zAxFvOblhXkJaat+LUYtUUUeku/FBU4fJsj+pAqccYfMsn+V60oBAI9H3FOQERTk/kwdOPb62GVoFlu0NSdxr/xFE9rtKki6qPNfcLeNwYq5DjUSn3szqK5MSrO4AlSYM0Sa9mFvnlHHGaYDi+yzCDX5sZ52aZWxjRXQy97TPmngiMsT4/pIEACZ0iFb3u/GR2t1Zyz0j3Yg9WEVweTd7Q4mR/PKVauOeTd8qn9Or1ERk3emhU5TlComxSbyfaMBh51Q4psfEfJQHZb6a4jsgpovcfWw6zPMSyGSV7NkvZnxo2ybf+ICGRHcpNCbFEszXJBDMM6cLyfS1Zr2D+UJ3ceCyCDcE6f5uWt4lV/H0uVO6cexGz5hQgvAew9RNkO48npvJKljDn2wjhV8vrOPZILrd56SJL/zDozll3uwwDfA0UaCu7GlFEX+cLx4DpxawQXQjO0X0fm5nI4XxgNMGwD1QXLQTSqXpFj2lMEWKBMmkOuMZjziiLaLh8wjTWwb2kRrtpR+aVyxMBv2Mmp/6sE/iC+aeeB9Zc/jC8lY3VZ2qrBOiFDJaX/EFn6besSx0j3+pPXWwhOeHpN+J4Z8utq/BoxHhA55LAvojIx+xsnoo6znQBKkhz7u9VB+430u9cI86MFw2jdlLYijBe0OmxWUREZqBUUXCoyodV/OEhcag5UNqUphH
*/