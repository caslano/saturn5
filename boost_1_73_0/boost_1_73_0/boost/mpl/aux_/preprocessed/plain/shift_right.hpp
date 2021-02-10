
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
JptZdhKMB5PLYHAxOAt67fqnvXaxYfAkeBKOxeaL2Bxm8UwEvY1Il1u1QflEb3G6jMU6L7eY6m/kJpl+3UmQrfJUvqD6tpcnyfIkWMZ3z5/9LH9efBuEvXW0EsUBhV/jfB6K9TSZiVk4f3wQ4SpeiXAW5VE4Tda5fINMvqJdvCTsTZPVKlrPivc6brefng/Hk4vL46dqb5fD0aRdvJfZTj4tD1N/gBuxie+3xf6j+1xswnwuQlW3cB5l4Z0Q6/Agmyf5QdD7ordVny/fxGkabeROsvbfh87Hn9HhP53DF3/91HZvox5tuZu75HE9izbbVz/e2Q83LfYpC18fZy/dJHkyVQU/O/8wDGVVWsHg9cWHsD8aDo57WbISd8ls+6v4Fq3SpTiSBTtpBaPTy0k4GRa/T9bC+vXb15PXreDq+mLSkm9Xv0XvMV0mkaz2aXHKDifbVByHq8dlHqvjaa/ib2L2MvxPn0Qep2yBQ3mmsjhZH4fdo04raAXfL2nLvPXbOEuTLM71a6M8j6bzlfz5y/A+XgrVRq8OVlv1/Ohz+nDQsg45XkUPov05FQ/gN5tond3LP4wz1afx+uE4vJN/ZM9/UYd1dd1/U493p1cLM95edT6aMTqD/276o2szfhstbvWQ9VfPOrPzeswv
*/