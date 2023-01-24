
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
1+kL7+L8UT54MFOfL9tRz57T5jEWkELZiqp+kx3G+GOBNPIj8nR9qetxVN044ViMEnrU3KJtN0bUSvQmVv7FYsL264uYQdQ64eYc7ITH3iSzDyopy96xmQVvuRerWUTpPMjWd274hc69fn/pwOe6Pd+QM2mrX9pz8fMDB0jKj0nKKysr14/VleTVz6flYNWkcebS81FEwoa8MQ/Wrmw4xdfo/H6AqQis4YLyHfXGjfzY59YEVouTLTQn55KAyoLGoBlK8g6NWyc3Ya29QjkQebv7nb36UtJGfPUGN+Ors7MfjZ2bNstaEOWHrFcGQb7xpSLZUdmFBryHsTAMNDjxkGCAX+yXqWxpu8FRiVc4Q/L2BtSePSP22ZmqKTvjPSrUeCh3blMAxW5e8+t4fk08xkZhyzY3zHS+sD170wnWnpxK8rZ25wlhrWwX0azsr0em3zx9tuapbCUudshP3cKwBpdLo3LMIf5Mrxybeuf4qQiaMOQLx7DDxiNVm3lZ1t/+OEl011qGfZrM/0slvCPkL5VwK0pBuXm+woG3rHYtiq3h8oBbTaVSej4FtbfCmdl28vyJDh9XbkXkOHSmYrZyyArpmR2sxUUtvnc8aNNRJYyujq/curK03B0GfVhYsLY6EvMap0rLs3gdGrKwsHu9zOL74bmdP0Insfh5S2HT9tpA7tKGzmJ1c1xg1Pgmp5DKLU7BqPfzLNV0iZpa
*/