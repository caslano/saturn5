
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct divides_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct divides_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct divides2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , divides2< N1,N2 >
        , divides<
              divides2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct divides2
    : aux::msvc_eti_base< typename apply_wrap2<
          divides_impl<
              typename divides_tag<N1>::type
            , typename divides_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, divides2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct divides_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 / n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::divides_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* divides.hpp
h4dGYiFnh9Hdsd6Zoawd7iyeQSgXjmVwAYszyQs71QxSWzIPOkYyDzQmiQfOL3qwdcMQ5Tog930GVfhbIVz3+wwOQPxA/o5ZOpfe42VoXRfYRnr+erT7Ft89qzTRm8vKVnFpp5hEjcEnTH/o/qrntDV23NL8qe2edjCKOeJ7z/TJOv9lVf2BwjOTb4H/2HVffmD0B5G1x9l1UP2PbVNhk8BpIYvAwUZZiQIZS+BLUgr5G4rywTitvw4O5MW7hOGE+jOOjqLm5SFehtztHftskeTC1EljBiNlLqdl48GR+IorNJOXsQbIEaBmuclNeTMDpn+Ivet0PW3IIPW5PI4g8QUXjhrcFI7qDsRXgwC6uzAoKU7GIBzLK1m9d/FgtixovjqL1UVGX6bWrZi9KKfDTlKOcLXWGkdyYw85OunZqXjOKoOMSrzrl/MZ1G7dzwAVTICky1dmmzfK8Aqu+o1/coPPJXfgnIjba17XVgouBZPiOnzLYMJYP1Z4KMANCf94OtD9O8rbPcBDSC1zOK3tJvFRb9/ayWGkrtLiVdG8qu/tg+3Ntw8u1GTY/prybWd42m7h9xxygSI3JlhQvh5xbmz+0nqhhHVWEIPGxepH0VqK+xMNsjL/UNhkxzPEsAL2TdhWNDD7NFALiBrXRuj4EFm+5ovmETk88CcyCc0Ei9n5oMTV/ZkUCA2NGAANCmPUcJ0vL/r0wjPNd25I
*/