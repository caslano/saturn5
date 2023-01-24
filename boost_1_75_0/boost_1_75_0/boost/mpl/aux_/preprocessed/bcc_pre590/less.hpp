
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
7V0gSmV+NLIFnJTzlCD/zyYpurwE4xtDIl9OopkVtdHyAADmwtWxj1jGdmx30fVpvy0nQQ7OtAvwo/FY18pA/qPT0E1vNdXCUWr+/szUH+V94o5BBLf8wmVCVp/Z8y7Gnpw8lJ+cxqj5sY94y9px7XrYAJBZJqsf9aNXFDOYUGLuukPimMWOReEEvtnXaxh2qC2hZgXmBd8LXqmHzPNIEhUozg4W+H17ldtVuPCtk6j9txTeTDqJp4f4kZOQjKhHyrRWCjvt/R9uwLFMKKWoGqAi3q5vDj0+dGdVrt7MyIigPoZ/KOWhqf39Fv4K7Vn1rn3RT+50w6Ks5QXiNVX/YyTUyrB49a/U5cke4Xll1mN02Zo8qsicTG+TpfAVNPebzETt9sSvnbjeTakFeH2PPy9yhC13xGd0aohhQ1Fm5kkNZU/11pTvbeushJRNo4s3MANwTLqaNrIGRcUYiYNmQsPWeoIKDIiW5t93pt/NBmKoE7RoMIrKMh4R5hbH8MjQp7yLCGRanpXtjPBaoF+UoPVLEaqIiV9IhhIaFkiSl2n8UO8aHVU6ZLYIWFyo2y0eSugV0JeuqxdlyuP4s+n0aoJH+mKOJriq0ZjoHwI1bsmaqB2eerYr8vu9lgVOw/zD268v3F87iPa6TCWI6//0DltSG799CN1fdju+q77FEi7DXNl95OoQLuYhymeeJK3gMGCZlIBMhWzRh2ih
*/