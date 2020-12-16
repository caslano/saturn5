
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
Sh2/vK99Ke29raa9Z9m8z357b6tp7/mq99lv76RMWa609l7Cci3V9Z3p2H6Rn+nYfuG71Ln9ImqpY/tF1lLH9ov8pc7tF77LnNsvopY5tl9kLXNuv8hf5th+4bvcsf0iarlz+0XWcuf2i/zlzu0Xvisc2y+iVji2X2StKH2/yCDly3KRspz6PsGT5fMyEuthFDbAaLwNp2IXjMFeGIuBGIcDcBqG4XSMwASciDNU+UettJ//Ssl/leS/WvJfI/nfLfmvlfzXSf7rJf97JP8Nkv8myX+zuvwl5O8v+XeR/LtK/t0k/+6Sfw/Jv6fk30vy7y35B0j+gZJ/H+zl7prT9r9pTlv3VzwqdF5b7vfnmtvWibltW7MdQkkppC2kY6R8kvur3POPNJqURtpByiWdJ7m/xjy4pDBSBimLdIp0leTzOq+T0kjbSSdJl0heb3B/QNIkUiZpJ+kUqYDkdcrDFEiKJa0m5ZDOkq6RfN/0MA0mJZI2kg6RzpHc36L9kCJImaRdpDMk09sepnakSaRM0k5SHukGqXUeZSWlkbJIx0jn8lxz4bgersd/++N3/f1/cow5ZdKcrpGKFXT/vwQ6J+iDsbn/337p73iS9AUnSEFmS38Ht3Gz5ByZlJwUE2dy5N5/HnWe4b0290iTftJotPaBnCePFPnttSfP5Z5w09Pii+//14kIk808l36S3d68hxfUfUg3JP5QiX8w6Srrzk+1xJ/QJVYVfxn6kLTxXpF4JRaJzbbvaLv85j9Y+vgGkK4r77PGkhrJBoyLSXOgT6+uxLGY9zPsJD45VmKR2JITYqUv27bfz8t6/62kWJt6CnQzjs1TFZtST9Ex6WnJ06Y5FV9dVXyymjLFeENi/FMltiX2RCXGzBTbGGNSExNiHdqWHnUOz7a2xdLrNCGp9Hit2//NtrQPTX/mTtZhc886qeOsNJv4aYsx8fRHlruOZT02MSenp7GMTcxxSWm2cYbKaccgiTNY4gzSxck+42RbVccp63E4zgCJ019+W+8l7cFT2kOuJk5zXOqchJi4xOSYwlhrltIm3kr/fdqE5bmU8yrPzawzOrb4ePa2QZvZYXAPwtrk41tYxuLtYLmrYunbQn380uZ1rYq+fe4gxrxUbV7cUdGB7a5e9+qq+nU/ybqzC8th7pJQ/rZv3S57eS0mLaNouyj/M8v9DgdIPASgq9evvKnXOdb7HfYfODBk1KjI4JBRA8PvDBt954jhyk0ey3LfxS+95T6Pkq91XgDtfRYv8iSohHwLb7hY9nzt3W8xrwLHDhiPEbA/puBTy+sn3o24uDuxyYXfNmcFf9Tq4BXGk9dSXs/+bHyLv0Ttqb6yxqlK9f/1+JE/bqyB8ZgCe2MQ7I81ON5Ied3jaoOfZo2In/xR9bbrUzYtrV1x8wH/p41NeMMyNqFvwSezj9V64JmjfxnV/Ile0/bbG5tQsWMQsk1yXirnqxGsox7ulL0kR67xHUXl9WexBR7D9vgcdsLnsTMex66Yi3/CF3EMnsBx+BLG4is4A1/FVHwN5+IpXIVv4r34Fu7Ft/FJzMMrGGaS81EMlbirYrDE/ZTEvU/izsZGuB+74QEciIdwMB5WrTdF1htssN4HVH0GLfBBbIMPYW98GPtgFg7AR1Tr9SxhvZtkvZtlvffKerfIeu+T9W6V9W6T9V4wybmcnOMp623M3+dkvSlSD7OlHlKxCZplvWnYF9NxNM7B8TgXUzAD03E+LsYFuAMX4iO4CHNwMR7FJfgOZvLfaVyG53A5XscVeANXYj3ivQu9cRX64WrsiHdjd1yHPXF9UR+CnPthdalHdR/C51KPX6DluK6q/yB53yCD+v9Q3veR1P8=
*/