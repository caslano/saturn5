
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
I6h23ctr0pc3gG6XW55KrY2zsUiXqy1RT5v6Ni+vq7uWzo3aZPdRkrseg1q80hjXt6RRmWZx9W2or23hljbql0aQmlO5nj611EhzbG3f1/dn7Tioz5uGs9zKj++NLtAFZ7XOuNAuwH/Nzz9u/ZxtFN/k3eRt8rtZ2qz1nBWLgzO7QJpu6/ngs6hLzqZo86LynweOszXvdmiUd6G0ZnUsFG9453zKvMi8F/tqVLeJa8bbja5aWjSiTe34kuem/cW4LhbsiwVnsbBmRT2Pn6tsbX4DYwFeFfONZdVC9Szqmm/MMwanBepbsG7Z+L2uTBM50wx2LV6N8KmNry1bm9asrnOlmctV+WyfxUYXtHT2Qt4XM24blle4YJwOzfLWxjVKs2Gl4hbZ5oWuxeZbTH5Mq6XRQm2l93kaCQ3pVJtem5ZXdeWb9MuC9NnfnM7NyryYvBf7chq0eTG83ehaFH/W0PJc/HoxroXG2/lcFxPHxeBUy6+2PFioTG35xdD4EoXPZRZel1wEujWCYctZG6dPW3nPRR+bjxI/84V5eaG4Orxq5gJ4ndVl1zapB/PU8fdFkK3pa3BRuTI1vw82hPBsKuY+E19Uz/ssOIPCS6U9AiGZ+p8V77LiUZbWqgVFk7P+Qlu5/Qvv5PqA+cVvxQYw7jPw7bp0yUGK+TeF0zfo933ilVKXTZda6Co2yTXSND9ayvm90Vt9rYzbfam0
*/