
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
zi6HN18YwP+gsTb9l1gNDu/NS2UOHLoAK5HDLZigEINhduSPRztUSbFgdi6RgRCmerHnBWmk9ehqjax+/2zNkc2zsKOJYJ0hzjP75Fox1ntI3BMb61+ucOtt+wCyDv9gvB/Pcxv6I3yWGkBAHBJIAvjgMju/WF5vizqoHygoteDO2GiSDadV6NGgi0Vyu4LcCP2j429PrJuqXRvWjHPmXe03j8qzUy1x8AgRt7IcuWe4ZRJCyDG1wbfD4kNRXFES1fx4UvzowCgMdJJ+jS/1fKAeBCSkCNJJJsEt575aQNpNFO984LjeyI1qG25OpcoNISdmiTiIOFkRMxwdgsXYcppli8yPtfm7bdvJwbBn3BoQOzyEvvjwMd8a3Fgi+pKstSkHkN8Gphn+2tuKVwkc129ZrFqInmyfJPMz8XgkSHWgv/2TapxLaOhbN1UfYEW/B3H4El0usOyse/+C1FSmRKE9c9I4C/eVy3TmSOjaI0X+wjQH+V6gAA/7Ax1HDpTre2WXF/qqfgHLsXPyqmwQHHgb0jEe6UQ+sAnuJrgGlt8kanJaIR9qOhIxXg==
*/