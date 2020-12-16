
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
isAv43VOVYGSnhMMbMxwPAq8RMMnF1cWI5YQlokSr1DbpNJAX03b/VQUV03lBWcoLhijtzlkhCwO6pryAM9lU7Lc8rOTfGw0FZIC7xgh8lQ+RU2leH8FcN5KqXhMcQFldF6NWVxU6YetMuBMrIwWpJJZKmvFynkFVSpeEa+LJ9LZChz3wWP2Kl6bCJ6bDD1vq1HonS9bXsY+Q14/3scLx4mDh6GfIvVzBID9EgJ9cQVl/7KKqXqZP0HileUl+VOraFsI/10nAlP8wW5Os/WiSoabJwV4Zb6MeuGfk52YrBujbrzeH6s4RcGDqhX+rVEwWKX5mVpb772QsTobC9ZBx1SMlkP48RJX9Ihr1tf7+qICPCH83CD15RPKA7sjY9MlJhGENSExJRqxv4GFIRqBz7BwRCPC0ChxBFu8s8nSs6OMJS1MpksqwAqpxa2omsoZQmDpAKusFNuTSbv3TBUrrqysLqqIVtIIbH6JwJtVnGK0lPIuu4HnM8DFdiaFtG7G81Z1Zf7YIn53FrjRd2As58JQv8zyMQoNdbXjmQwaWbx3toWPqaHj8+b6+BwLR0OOd8+1cEb52dOAcXxQeJVyxvXT6T5OJxxWFuSXF4lIRSMjwj3P4lSWT8gvYOwMF1Ys8sWZPib2yq0oGiP8e5avLyuoLBcVp3dECmPzVYz9ItN3gYWJk0T8fHi2jleUFBeym+do+rLSImFSYGyhhhHgtQ7AzjWxampxgJ1nYJXlo6m+q2TsfAsrzK/Kxxiyhcl25gILo9akCGPIGoZ1XexXgV+o4l6un0wxXlJW4Lu9WMU58/PxlPzsRQZWOrakiBME8XpxgFeNK6rgTC/Gkn19+eiiQTzHAWegK3pWww+XSv2EwjF4wh9LBiYOVR8kxpJ1HeWUsUGbudTAJuYXREUs4xx0A6/MH1NEz4s9CHQs6H9fZejr08Jvy1T9MOx3r+moVI2VeeNqHaNyVDG1vAp7DpgY9xmouqnCngMmPplSsbyIv8Ov0zHUcPmlhajlgjPQdR611cXlUSVf36DhnBmKCv0xYgdWwQ9jjNjGA08GY8Qah6OX9Tdreo5edvMWVT/caoLEWHEIh1wRY8Ua7nWkJ3PtjWBz/N3eAgfvYrdWtMCj94n98TWODOOdmp7Y8P9KqffblGg5pVpZoXhuFXBs1cHe5rPRdf2k6vwSD+Pw3B1gFWVTpqI1JFBuxyXS+x6NB5dQ7lYDQyMs9hPQdUH5uA96s29zP/Tmt+4aWx/0lR6wscC9B4GZ38EP+foKuy/4sMScfcFHJO7sC/5SxeVrxXiujcFpjOdaOJwG/riCR8vyi8p5Qpg8h/tXKl5eWQlY7HUvMa0f+qStD+L2KQuTafU0MD6Xv4T6AsgHv4ZenHWMNf+aTrZTz/r6Knmmr489JzH1PFExNuvG2N+81t+NB/XwCxLnUQHe/17XBXn1RV0fhH+dohdtHNbzG3rVlvOSidWLeeMvK3rlTDPG1gNTzyvy88PvHJh6rs4rFi7rnVeBKWcQiLPZoWebH/z9mqLD/s9iz3pbH+TFN1RM7i3M7m3UseopeOZNVR/sGSz88JaOUVCE/ve6vqIEbr1t6jn0AvuDiXGkYezTwuR+8++omKwcxV71bizoU76r4typx1nsph57uvnvfE/B5bQmrJeXmDa+9YGpV8L+oYXJsP/ZwmTYP9Iw9Bvhj49VzGvKof9E1Xvz/aH/i6pXzgDerOqVeu9TTx9vbuZhd4yQZZQ98P/q4YlBNQ7bJeOfAQ+zAW8B7rIB/01i0l4H7HOJSfswwvJ3gdVKey7OZ4fe1ZZ9Acxln/1SYLEw++xXwF322W0Sc9pn/wHcZZ/9WmJO++w=
*/