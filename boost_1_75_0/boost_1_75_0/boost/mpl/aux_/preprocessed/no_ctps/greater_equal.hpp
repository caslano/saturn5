
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

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
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
nyI46v3IHWgvO5zxp9RVAdHgywHBWmoJoE4t9mGP7O3IFf4T0ytLtyrLq/IehKIkeu7x10/eDnX+WcT+rB2vC7nM0ModFRlmwdKeTDVkrX6SRxXyNGt20Klaf4vIYf6R96OK/7BfOahsE2PK6jplHsz0U/k0XOrCR7hcuNxaUfyeafUs7iTXJhvyLjHte9ggetm4C8opSS7Ce+T5ZrstAzbWhjdtRiPClC21wjUD9ysJI1whfNQuuH7Fo92G3dS5z5spj0aRn93IKYYtT8ofmY2Upm1qym1pwPIjmnMa8a0dhO2Wb8AKAm17b++oaIUs8dy5F2Xnbl8din3rBiPDczYj2R0Hik+G2PQjWD5C2DowKYfppZYHBBVRW3LdqXAt3Hl099yNvgqDB3t8cXHMUb136Y3Cxl35nAfIO1BxzDDFw/L0J35cI1RPtwcZNF+R/LmPJq7amb3kYNDLarH17Hnjd4WxyOTEP6uiV1Bcf/+r7GBIcao6JZdyYOS6BEPfIIu5gdNBn77FC7GrEXV6H1lUNWv5Cen0nje/uBtw45xSapzHih9sI27K3cVQIekzl6ei4pxTU/Kcjn/JnVJQVDHCqDuW9iPuoCesxzerb1CKrI+H1/SNRIh6gaWq10+XhWT1bUkuM/yrFYoxdQuJh7cmQfmgVWU3e8r4nVHvP7L7kNcjEu0j+G9YLwJT49I4PojTB/qDrtbm9EB0
*/