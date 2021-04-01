
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
HOJfioXoeYegq2sWEbka4WhaDNHcW5MM545wZn/ovSXIz6d87Fhxs3KPtwKVK9jQRc6xaC4yGDDUP9Ztnc7qbY6NlHel8ecwLr3aJcl8Q5PYPbgLHkTqSAf7taFK41KsjuSDcO2dlzHr5kX56nkaAIgeRn25XlvB1XXJBFsVLgj7V3a7opPHkqkCG4NoZwIef3qDKvcS8X0z81I5S39qfc27cXgUOwmoyCfvDWnzxZt3+8BsKyHMvOD1QK796/JD0m8Tg2Th/2bqTGzkNqay+1Dkydks1sDBO96nl5IZgB9Ug9FemUtcx/d78kUKXkKgWFiVEPgKSQt6IfhTw3cB7W2M7sTfcjmKYao9brLXFA6mqaL1xc+zcsv1JsxNjonR3XN00xxOirnoE+cD3uvIdL+FgWcVba4FhbkIgjURHQ8iseI9sgyk1wkkqlMdChymd6fgqXgHlk2duS20zSqZEnFWnpw69beaB/RSs/oU1nkg/+Nx5pTbJ9b//Ypqa4d/tMpKDB3j/GXraudqKC6Zud4OEywIkzi7p3j3u+/EzIhVybBhIWj+uASd5g==
*/