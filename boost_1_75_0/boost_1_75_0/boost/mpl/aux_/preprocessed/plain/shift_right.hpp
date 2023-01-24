
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
i9SNV3kEqucCxevH+VxYl+QC9PI6y4S21PnX2hFBwV3v+1qFG3TfVf+X3j+/lS3k97E3A9t6PMxvBi0JrbvliHb0UbwLwkEBLXF8hs1s+or+aTofHNF015Tr23nbRCOVTp/yTIAbLd1+5l4+RvqtUhS0sX+FdU1eCYZQuJeacaip17K2O3gR4AcLwF5N3DaRIpwWoBGia9m5iLxGs42DS6zxTZnZkwzdy4DKz363fh1dp9tH7jd+st1iOQGctSLvXntL6KYDh2HUZGjYdO6Y4RsVGyuVrtKlJ4KSiaagvEwTFOD1WdlHX+VrxKEqA9TivUmHTXcl4NDNFWgXEvL0jKL3p2EWsU4smCkkT/snPrauTU+5iHSsVWu3+uNsN3hlc9Fyo84pIKHNJ8BCvXBjc7mx17YWXp8Vp0ol+HOpxtHWEFIHzg29zuEPTshhd3S7qaDt5rYkt9Y3qxPqgS1b4IJzjKPGqCiPszidy2qd/3BwOLrEWFgcJGufg+kZnYiF5hKW55pUX2Yc2I4cJ7sJuZ0d5Jh4bkoN2y0o+3kHoNU6BwVYlw4VPm41/hmamGaj6dls3W1VZDffm08I6Wpvd7NX97NRL53bhR/1j69C6jw9Agi3zg81I7MTxP2RrQyAqA8MU/K5seJvBSE3zxtmCR3CrojNpGHcO4DnEqFUAN/l4HBWfYKcKQ4hzmjGMNVX9T3/JgZfdXezJgZX
*/