
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
B92MslRTDww3f916UXEtwNidATIx5VBDR1QAl+brc2KnQ3yGDbK1SumzOtrqOgMyKk1MqiLOKirUUZbl+s5bZ0b4uiF3Raeb5dE9ETQZVB0Pejo4vu+4fVIAb/PKVbEAwgOdJcWxFTxf/8ot3z6dv2B48l9HGU9kWsvV6GnbLFVXKnGx54xbYI/juzDgYJHvEw21gKHo0RVmt35GhGi2FX+u/3biQjLuqSBZ+aFjKia7/cMIgblB9jc1QBSb6h4xPilp/sNix/DZSfsJvk+A0o5Geh/E0285XzUOdT4tVRmaDSOjz1Sd+nla+RbUXOJ17mQr2GsyNQ6HlQisEddsLc2HlHNR/fr1h+hMasYFkIk+iyeO8RJ9adc/7qvqN3HuAKoTKZUzhdyVRdtljSpd0xGlW/vy65u2bV/IUr6THbZDHre8UOb+n7gnDyjv8FRjWU0wsx178c6ykksX18+Nog/PwHhUG2Ddn1TZs+8JiihKs54HJ5zBYI4yF0aNWQVid/Ld/mUM556K9k+O3cTb3V9ov+zq62D3Bi/tUvz1yKwdaqeG2MkwhMxr60g/ymYiVFF72nwbNkIttTPqdi48l8JAdiRY2E29WeDbKPVRT3/FVhaclmfHhrcS+Lfl5BoJmiy6oXuo8cOwLzE52k0IrwoOzng9XQAD5DWJMxV+S22iJe/DgW5oE0UpW/aeDkXHMKoafe/mF3PVgsQ2
*/