
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
GHPsUfcYP3RKyQf2mEEyvJ6suPdNmCmtIRt5RxuyAMlPx0pr+ZlTxWi8+1lHMFquqIStzYbakZ4p2LHxMfq7JOqgIfJk8Y4acyXrGwGp1gSa5eFQT/bEKiVptZUBA4HEuG8oy3KFdPesaDPJbwtRSI2ohg/qjcC+Uh0UI0ozbelfMdxtKAkZembAtpPDyc8nZTJayi5yy6zB/oy7HYS/eBPpplQG8aEpPKeqk54zrinvcSeRzpHAOa+hjIEuSFC0ZPaDBTVGZlOdMUd2/UFW/O+4e9tByN4qvftCoDScBtrTv3IJ3ZDHDGikvoToetHhur7ATwjvC1/VekSKMgI5cHs+bHH63NtT+aNf2COBqOy+QzYgs1BI4CHmFu71xYAQSDYwB20tMJNik8cIZcSv8k1uHVtSaA3SS+crIzCSPw+5dT71W7tX+q8El4DNON60mLVwmqZsB8lzYHOK4RiZLsrqJ7XVi/XIX6XfOpaptCB39XJovF9sVmkqcXNk2FNTx5sPoohvJAVlOlBqo+frM3tNHzFYDTrwMbUbN7MMA2yCMKy7gxyCzzW3VCYcLdGXbHu5e8/Smjg0o+aUVrj9iTLsKYzPqgdT16R/MKPdD8F3Y8/7zruqsUGUPkb+/djIUkO+Bg7PSiDpIR/WL/56jcYHV05tctztq+tAko3Ir8U7ZkQkKSOtb0rbNtqaPFfwvCgrzJmXmYobYu05
*/