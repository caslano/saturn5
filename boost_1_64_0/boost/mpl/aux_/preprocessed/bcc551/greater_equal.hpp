
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
tzRzF81Ng6cAYiSwO/C7f7tV+SncjUOPcy103veOjkvmPeXmIEr625cFJD33OMr1J3gTbJ8rEJzgaZ7huKWOOai7rQwvm2MXl41+KOXfM4Td875VraBen9a6CkxDXqvVAJEuyPT3zgSJh9xhoA7bT5TYufgoLSPAVUAcgCaaDA2vi4VXXYODlk423cXU6JzhpZtq2KwaUH0pvd/kvBeaYqH3wGhClmTeQof0DAbDedfzvUXSjzlG3IGwvQaUMr9qoTQCFn6nAGl0iqNusonFO0eSOkHrK4DfVa7GIGOhEmMwuH1GUS63nd0KNET1pduXNJdj+rk1LouRedl4T2/0R5uhBdNgpUCnMr5HO0+/fRv5o4cYNoR+094JU+uUMR+txzJMQj0pMBJ5pwHoPUk+GnihsMZWl00CQMf59nxQGnffdah5io+4EErAoFQ2phpwduEF4UqHUzFR0XaM5/g01ZMrI1lMIznEnuXxoWQpk2EyI8kExG3G9ZtgJGQoIPmGhi7X6Oq6YDYPN1W9oz5ERvX0gz7/gwhGkyjtqmHD5JgsAheyPQU+ca53qA==
*/