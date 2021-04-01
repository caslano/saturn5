
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_right.hpp" header
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
8WvJ7HxzOcYWmNJcFbbh+DPFGFWY7I0s7SOYm1uOSqkADvgQ6vWP74UF56mXmAl8u4n56zPVgCe/tHazQY7uLe0dNdNlgZQN4OqO6vd+LGOYbyV0mD5wPLQrWQMoervBVNJg7GCxNOim7xegZBEloVYMyzB46oVRmKMXQFWaHrU8xIWNiCQP5/ZrntzCaXWC9eOYRcbuUim9xdq3mTQcd9HG0bMtNRbVNUVKnsBu+2wF3G/spYBef5/ygY+RVtM0m4kiMg5LxQk/EJBcjHMYa4ckb9T715Pqws4n8IOZO/h90jTXbCAP8GhX7Eli/u6+E+gXRDlqZDAqU7lD9zOe7CekLi0i6YBxvLEP27kMCI2dDZqCcfvdoJMIUzHKmiAVYTy+mzmPsRcig2LDGATdvok9k2ecDCNjTm+jvjItsxL8JGl2scClEGa+dOyAKUdufSJ1VyYdMWLP0DOTsnXbN+oLiXnmtKLrYXFJQf5wU/KVMB5EIASQP1uZyTt/ODbWcnjVKdRZzr7OLoWRBQwb2y3ZCzPXP/eVVFixKU66TZW9vKTwOaKZK1+5lA==
*/