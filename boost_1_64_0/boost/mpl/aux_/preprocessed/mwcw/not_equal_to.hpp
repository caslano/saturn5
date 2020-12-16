
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
ISYh/rkgzHfrbETIAaF36QTLAQFfoJ5wMaLcD8r74Mn34P+enOC5HpTjQfkdzJwO4edzCJS/wXzPTalvzgbla6idp2E7Mle5GfYiK7Y0dWxEqpCY13lfDZKNLEM2IjuQqDfIw4BMQoqRVUgFsg9JfJP8DchcZBWyBalCoivI7YBMRuYjq5HNSBUS9xZ/Q8Yjc5HlyAakEmmylTKRVMSFLEPKkAqkCol/u6ljCJKNLEbKkG3IXqT7NspE5iIrkM1IFRLzDvaQSUgxsgrZhjjeRQcZjmS+G8kvEdkiW2SLbJHtwGwHZf0/M9kNsf7fyvNv5ZlPqc7/X8hxwgVchXzInRsgvZXDO8eeqXXrX8A2cDs8Nsl6CPfORw+yXg0+vuDMrDma488NMce/tabh2QcoR7nZzXU0Cq/SWgIj37yxlqAoPdfl+55yreXUsTgjHioXmjn/3a+SVvkJWqvgeYd1V+2zuMW9vxZ/3THMKmONZ02F8b7/dVqrkqP91Z7PUIi1X6a/52UWsV/znoHCmdVlbmA/P9Ydb0aiA71zQJ8h2T1V942V2ajz0kVxAp2Q4zgvpQ96zos7vs45K819fkNaa22Wn3uIxtRU/lHI8+xU1JRfmJWeiQH1nBDK98QjOGlbKun7LnXlgI/W+x3ktU+u/ZlZhTlT5/jFoiiQL1nvoegME5OswakAfqbl5eTL15jGofbTwH5Tmta3+NYjxqYecb71cOvt+tW7Nqs6bzz7f+rotjPVu4aHY/dybEaO7znapbpfrPnYPCQpyZqE8Na9yLcP1J27XNeg6bt7fc6L7jK5ljrUxJGUNmAcSbi5mS93f/6ex25/YeurF++99Mh1Mcc3+2n0/+571v/b41GizrWO7/jKuTHllGXbo4cOiJ34y8p2geJRGjbupFljfV/pe6w7ggnHvkYad1fu2LM1bzoWHg3HwUQ4Hp4Cz4Ej4bnQBSdoHvk8uAqer/m/SXAtvAA+o3m5P8HJ8B3Nz32g+bnvYIZyLmfC1jALJsGpsBecBvvBbHgWzIHj4EXQBafDOTAP3gTz4QOwAD4CnfBNeDHcBgvhj7AI/gJdcB+cAQ+hbWbCw+BseAScA1vCS2BbeClsD+fCTvAyeBK8HA6EV8DhsNhqL3glnAjnwwvh1XAyvAZmw2vhRXABdMLr4NVwIbwBLoK3wsXwNngDvBcugffDErgG3gifhTfBl+Ey+A68GW6Ht3jjJ/Q9qe9P+oPP/F6C5hM7KX6iM4zXvG0neDT0zpOonI4qxxwHTFI5J8CjYA/pLXDo+0nfW+j5xDP0Vn/sB5Nhf9gXngwHwVPgmXCA5nVPVXzDQHgHTIE74GD4MxwCm2FnKIyHw2BneAbU+Ki+M+gjqoc5Phqr+d82sBWMkz/t5Ed7mKd57uHGOKfzvaYh5dVdbfsuczOvbsO9v7yud5f3q0c+3QORS7ch8ujGjQs/l+5/Oo9ufXLohjPe+lvNn7uYa2UNsgWpQuK2R8Ys/5u2g/L8z1NyQzz/d+D5/wTry+kE6/vK/ZjgYuU8b55xaV1HVMsBrYlbSzb/zmNUEVm79C7ADONdgKn6HTVYz4qnI6ehX3pf9XPI2LFpuQU8g6mknPwQ1tjqGYNYjkDPGIF+Kwf6zdpwvynD/S1u/+wR+BnjNPdv5Ywetz90YuMfR1csGnBj5UN3rA/8zFD9Ha721nmocug73C+2+hHYAT6q2MAyOAA+AU+Ha2F3Ctn4A/NDSIC5SH0X+34HRxnftfp+9ZlfLEMc+u5c5feduBlJ1Hefe24Q8Z8HnIx45v7i9b20wm8uT981/t8x3nk7J+L57thm951hfCeUQbv5N6fm2ZrsidyjI1tki2w=
*/