
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
PZzM9nG87qvwK1s9pNYUS92w9rmgdOgWHJ1GXXoVmzGF+EPBmINYveYLqVGQKk7k/e1V1/oRB1V2utELZ3P7D/qIH9+GfrsAiEnXe2gdz37QAd4LGwu+3d7+D2KBkNLr6+UXfxjToI+8H+43Pgd0RNkonx+UDCD43PJAkhihInRwlIaYeSc+xlRBUekpt4qNKIP30y8kwVI3Ut4p1thO3KCmY2fjriPyce87fz4t8jrdJOpJBRg3z1G1vVbixZ2Q6BRUTOSJ0JomSLoWNSyQJAQPUpqDd5Lpwvxpe3SYsXoFlVUCiP+X4beqNckJJtFXAiy9cQ2XlNQmebf6Wi4d9ZCGcs++8EXEa4BCiAJE+Y+jMgVAjjbTmWj1oFn0t5DW7prsiJ/dcsVcf4gVQ9VqpBonUjk+e+AdiXzxq6EO/byvar23pzEweGBcxOQ7ELmgwa2mq3pVc6Fqt89kyd/kkjdKkBq0XR5jTVAfAHFNCTc3zouwb4285BvKeS8rFHeng2848j9MeBkLq6jCOWuJ4eoDW4tRov42TLABR1YINKZSUGCmFLlLVwls/Q==
*/