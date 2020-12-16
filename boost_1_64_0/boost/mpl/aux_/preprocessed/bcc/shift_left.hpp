
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_left.hpp" header
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
PAcLBEjCbziLDIe1zM4Wh/NRGJhTqPRzxf3hWx3X08ZnprRMqc4TMdFXLs0RiOBAO4ZgpWQ6lAMzB0OmqbGzSzik9QF+TMshzGmcwFGtwBWJklI6PqVt4se0TS0dXa3jW5tgvKntk1ubWluCA+Y0Rq38aFBd05TGpvjZAw7yEwCmY075sjmFeD0i3NFhdzo3ZnCR4wuD8MFqshU7qCA1zV98h2JwRjiM0IUDgEwTuhjr+lbsu/x6FBD6KxAqkrFwCEGfKqclsGA+14z9WtQBKgeWrsGB2RHpYPeAhShZLA0FrGDbFCjake/JF4YqHcFBZ8gZkcZC29KKBNaEB4NIY6P1KhoZADD6oQATxLpPys8LbjFhjNTOEtRayIk5fDtGtlI5sFUNTiBtaBbkwv4p/FnZcmEBgn12ICNb7FsgH+IXyC+VC31o1oLywPdmeTUyROV949XK4kVtTcuQnxXWAiG1+AuQXwHX77zafG4nb4EZ8OASy9hULYIWoAE1WAjsnoegnVJ0gY3HEV/g4J392XI+F7lMKRei0CgcPwXEBI6V/ZxxsyWcNzeVMQBTwiVkVqRlTaYHOlvBTChxJePJXDS/PuL6Cit8JCUsfCCcikK/agAL5GByG5FpglTcM+9BFAkuqXsxD+aeXQIDiwdfRMDmXOjD5SAQFTlRjvrJ7/UUWOxx8OqleMNx1MIpXgsILk7IFNkrooPlJ/Z9A1i74mFvjKtABYubbFnkwGIDQ5g9ArPk4E1xojrpxFQ474AQIzYPQzwdx3oF5JZROVF+XNvgoT+J8J4XQmdvrKfvbOIg8jjOnYWDkb9wIB9OgV3h4Es6cKJcJcFO7VzgQed6nETvVilsg9D0ShY3bQI7eOAqNScHh5cQBVgqjSxxAl5T1SUCECICr8lWKuVUMLxZWJOHq9A1eZW5QkU4Fs5X8nJV/C5mijjw0vKLmqmsBUhCnw4HPQqPhw8N1CGJw8uko4NMsw3gBVgH3AXYB9wFWAjcdBuBUcNKCje9TG0twaytpGqtaHjxJPel9in8JI5TkBE+jhIxDI4gF1/EgogjTXDvJcCwf0ZQSiIQEDzs8ilJ3Hy8GoZU2/jgyTMO/BNUL+IZiEhHpFC4Pr4Di5Hei7UIHs1wbvh8idPYv/nTQQjw+3+gceM/uGDHD5JUOEiqOBqkothulasdrnL85atUwEuv1VPkFEvZHE/5RuJUbKSwNFw1oGtqFVVTg+HBoNi294uYX5WKRLbnMNwxzho+wcPTZfgb6MQF5sjLYjy8VNjUMTnT3Iod3dT2+EqQAmLWkiF4JLCZU7vaM3j9Lnx9TkWgUS6JyrnkPF0TO1oam+M7XHBpTEsiD0MAzcTFNalQ8o5XKjNVGiyfzgA2K7SGiqP1EowgmavyZHx4MINzXVmKl64OrKbKCK+5JBiIOqWBQg9cL24mtvywZ7QaEFHM9CLaM+CjWZidI1JpFfVJXD3hvJqSgdYuAYPL2WGMwmwJw0PhEIleJ62PxEr42DRcVY0f+YsIOq4I08ZgpSwVVlGfHNnAeZ5kOxWNgjPncWkqqpbAc4XokXQE+S1JptP4wIK7LxHYp/Q8EFV7jqa0FzxVe47WLBFGOQkEJsvA4JKQMuZ7XHziqOo2fZLbCDeFJAgVSGYBjssE1TPT6jloxBgQfANZgpsPnMbmMEGhmyIKdci1o/UV1Vk4R3UYlQ8DKyUX5Dilnu6ww0UkirAyihM2NHFuElbVBZqiClC1lwHKvQxI6mUgSn8Ck/qzlDaspeEbHSVneyrD2WL1rrXEQW6EXRw4STiGi5SVd74KZnKlwfTs1abW5hSyRegkVY5VgQLNFytXfdkLfDa4sBiDtRw=
*/