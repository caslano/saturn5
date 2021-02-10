
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
11e/LWQicOdHw80Ze7F/wNYsO+DcgFpGTKE491CpAAWig2GofByKfN37cnJiaxpmMhdB/jH66vNRjf4cj05+35df9+FHEkzhV65UbXf2MNiDrgmTqrbjuUdyi3Swvmp0wrTEyVaFXyOlvKZPgMkUio6OD8vW14B05A68pqK26DRyhWk3oW059ECM4kqg2pHL0capBtWyNPpwhS870Emj4QBuiQAyzE9H+5PpCzg7g+PxJrDFEETetD56zaLhywq4irDtp4E4J61k8K9aD8TPWmNDS/tyf9cTb9F9ilUGx7PxPxul1yBnSJLK6hHL4BS+K7/cWd+u6i7WaxNI3SY17L1ALOKzYUBXsraHp73E0yR3g4nTQz3kQOWqrrtHC7jtLJ77AfDbQ/TQd+d4tGytitrEHpsT92iwvk6k7xeBJ9k6jJ854hfu2MYq45hLYVUF/HqIEFN6REkfzZ6ypEFZulKdimb998z2izyE6f8C/+8JPJe7+zuXd7+bcvdv9S9QSwMECgAAAAgALWdKUlId7NHxAQAA0wMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NDRVVAUAAbZIJGCNU2Fr2zAQ/S7IfzgSSreAqzaEwlw1kKSBlKU0tN5gjC0o9nkWcSQj
*/