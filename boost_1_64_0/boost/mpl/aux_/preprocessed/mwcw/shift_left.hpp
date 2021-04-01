
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
40vNI1FBeCOEfL7B+57ZEl3e5k+mU+pwv6Z8eEDP2UvZEMqXATyqJFEijeKJifxGF3EG4o1Wdte2ueq7OD79WxCvtLpQXPO1/OE9sPDmXN46ZeWCZunBLei1z3BXQUPz3GL6vA4LZRBMkRf9Z9+a+AhHIs4SxV6MkdPf+SxY8PRiaxhQdaNavesH5lezNWiL+002bVE+zcUfIwGez1O6wXqGEuR+ogPI3ifHozCyI6McaV7OqT6fx4BbfpkEA7YN1IbZzF66GJD0sVMOLU0E9+atxi0yMOgeGFcRaB9M1W0xJ0i+8B3XAldReuf0xfnaJKJof3BbvqOvGYrOX5fOz45S8hqwJpa9P7xhUC6B7PQjO+sAz7PKUhxrnu3506+BCICZ3kzK+niNFE+accKCwfY9Hjn2mf5ykOEaT2idBLVQKw3uQrOrd9tAmSOdJmStHSgm5i+Q3gBLskagxEQy+k0FExnLHMW6D9uAXhkjAoYnRvt1nMU99mnNMFH1YD92lSmL8evs/WMPtB69GrGVKnXpTche79uy/TOm+Ri8Z+gIG1sDDXXdtrGqGA==
*/