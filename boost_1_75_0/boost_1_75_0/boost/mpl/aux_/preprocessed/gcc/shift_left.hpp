
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
H/VLGgNW5A266PIzYfOGxwVs7Zo7G7hxA0zcVPqGiCBM8A3JYyHoOF5pw6bW5g5GCgYvRf+6b964cjShAlqY9As2fkLkGLPXPQAn6/ual25/nKRbg+y0nrpavPaZB75tmxDMknGnInkDtT83Pji5S2217HQcTiSISS8wQIEMIVJDToIY8XuVff5wJG5wGt1OxBlSj6SSfpOrM95UogczOA79O7YgiT1KC1YTsXZILDn4KEBKBr+HYLMD/5Py5R96uIPX0T3Q/bDviOdJhLFz0PHR49CfsLOxs3HuSBpYV6ugktLORPf2aM6Z+XH5ud0fN99esn4G+d5oUtF76y84CGfoNBd8X6VlFC57VJ954u/ZQbfGniy/S5hpE4oZROqIWr34vi5nMn2KTdgfUsxiit4Xsm7OWCxGFUsYIW7VIEX8Jgqjt+AOAGjtKwj6A5ko45/zf8SUYh6PFqZ0grtCaCEf6u70OYkPY4bGbZp9ePf54vTFv97RJLzITJK2mSbFJk+qo2F8w3Lcx7iVSB592ySPudOnTaRQts+IVvaDhYj3yXxrWP+CcV+/5CUlw98kudWKbx1DkQWQF/GlvkpqbSYdHeovFa8Sd+CO7LhHvpo/z6U5bVZ3/IMU+K30xPcxGGlUdNblSiEvym2L0ePvMpNYXSS/hWLuDOb78BPFtfSS/Qye0/8F6C/cCClwZnJjbkUNoZeBhfISYbdt
*/