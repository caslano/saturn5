
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
f2vtQVn0VCON/trxFZTQ9RD7fZo+fH7n9jUL5XgQfL6eWlwhtwCS1APEKQQ0qOXVKJ42zAItvfPLilTyb2iy6KWy6F2ejAErotPq/HOfktc9Kjyud8su/eOfAuo4YAg47F66t9veu+ehb1/YgTkIXRQ5ICWUTz6zk27nS8i2oypLIbhu18elW5ea8Sx/TBQYsdu2FpbNeD5FN5DpseF+dgbutMGLT9tdwTSpmx9juEGnpwDvH54T+Z347h0F8j498i4R+y77LitkkaZ8UFszIARxdUJnnI16DF1swWMiFyntHI/o2vy35+xfdo2uCAXyZEnHP1geeyigRi0Vsng8dr4d+Ru1nm3Ua7npA5iFHJe4X89Ifv+GUE177ubWaNVCz6AJA9uP6i91fBc00WPw79+OylVsIxta85ftDB1aMuSHLOYTKQptFolmOBYJi7wcyreWi569dn8F9KS5NCFopS0dYufbhW/oqEm/zJ1MM1g01SEjs2l0SBKeHOWgZnXcAnEVs66MFkNgfLy9YQ/u9DWZww24kkcwKRZGJMaXVCoaS2GHKNSqLlfyPAkWcIaqX3UylXkeRUrydYmM0b5meLGYfn0PLQlm0d34DGcqN6zQFKglIg+f/4VVsVz6iyusLvvirJve0Cvdo7Vhb65BgGU0T/PNARoY+8X/5YelPw6B2WGotQnOfVYq8P1ZZgu/ui4qmLkFVhPBVM0G
*/