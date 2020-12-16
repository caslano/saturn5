
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

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
OBgTcAjm4AW4HONwAw7FHTgM9+JwPMTOPRLrN6QesGMjfuvhoAi2O07miBuPczhQEvAq9tNJuDaS33r4FE7Fd3AaHsYkjGrGbz08Fy/BRLwUC3A63oTVanDNgvXwbqyP32IDHBXF/oK3YCPcjxHIkIewxngtNsH3sSn2YjtG4RBsjuOwBUYbY3z4rbeDwG9L12/KXfx7XZz7t+Ge0O/A0BSaQlNoCk2hKTSFptD0PzSFE2aeruv/wuz0U3Hfv3F9P810Xz99TEzEpb7NmoQhXBekuK/vJySMGD95cnxydkFBhrNwVnZ6MPeXe64xdxDs+wV/ff1/H7muYZ/N2DL5wrqLJ+wOW37D/e3L0zz3V6g+VE+bwqzj5c9Ue39LrImtMMXTzn6a2tiPhK6lQlNoCk2hKTSFptAUmkJTaApNoekXm07r+/8Ls/kvudCZfWre/z/d1Me/XG0A2zTm+HHC9nZcvzdwtQFMGZM8JXFMfHJ+Bq9kcywI/tlKDipkZmGmxhx75zMrvnutIPvyDPMz0Yw/OPLJrVPPRNNy8zPyszMXhvm9n8wzLnkjeS7Mtr5bMEvjF64mNCcsIDzNciUN7cqWXODMp6rUxlHfvW7Q9zdYyqs884y/Wc4sldembJE2ZTt0zPu8N/c4bOafaae6M7WvRFcL1If/62tfWVLf+PyPD//+2bdenXdkUZOtkd1qHx4XqH2o6mMQLmhvfL7spbWdlkxpeGXLTpvWH908gH58PbdA+zL7uNq8zM8tiNZ4y/YYiZ2wJXbGDtgFz8GzMQa74iQ8By/DbrgMu+NK7IG3Y0/ciDF4P/bGR7APPo59vc+L0P6IVyt/5udFNNXzBZrjDGyp8bCtcAG2xuW4yfPOl6X+4zv7JwTX/tRistEGhYnhtu1QD2zzb4vqzrL9CfGEnMRQu1RoCk2hKTSFptAUmkJTaPr/mE7r8//d1/9a+OTH/kcx9v854/n6Vxh92QWp8wuyZ5Ft1+cdMKXY+NzpXJicl89fvJ+nez/nGbBafmMk19nez3lruunzHF88hU59buhwfZ5dkJyazB+5puHzEvKzYbTxua+kLOr62/P8zeleh2fdJ5NbbifX/QrJpmcYlNq8p2An666v6bnen0DEDGkIchyD59n0i9UWcJninU64l3ij3fGm5eQV8Nb2PDZ4TpWewa82C9czrzu74iLeSPd8rOZfa+eeH1Xh78nev1vfpRCue/KHKa9xymuJO68ZaVl5yurxn6Fvl899Svd15etjzX8Yaa2z1QHyEXGG+1ndeeacnGCdDTnDmpcRzCsvljrJClcbl/LypPISE+7Ki7G3nVSdTA13p/sX5SMv3LqtloVb83mt5t/S/JoKy/+pQny7vX+3Pg+9tZ7pv17lupNwgNw73HXMQ5M5VIKqW/Kouvub0ryzwvzWCvNvVpj/osJ8zVqeeWueS5XnrcrzE8pzXC13nnm4MpkOLs9ja1nTzKowf02F+Q0V5p+tMP+Bd966/+zUu/23V9O7InAzyxRXc+XZaD9U42Hw7aO+/UfthY2N+QK1Z5raN8nX2650eMak8nmwwnz16tZzxYjq1r9PqfD3LRXmz6rhmbc+F7t2HY0P4/hpjt+zwd41jpvaFcvNiT+XLxbta2efEVzbqfH+hvvqudLOyM/Pyw8Lon7MbcfGKQTCokxtqUZ+HMm5OZ7P93xPXWrZ5Iw877s2DujzualFRhO0K53y763tyoeYd3ieG6LvriLX95CjgH9a2mfzMwoKc5y6r4zyp1OIVyhY4zq+56scIT7je5QH+Bt151q2NsulEH7g87NNyx5l2feId4EiNr8foaWW26ftN7SO9fwyWvP/0PwRzQ8=
*/