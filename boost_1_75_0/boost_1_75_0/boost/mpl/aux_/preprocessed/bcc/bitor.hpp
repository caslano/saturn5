
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
JoJfHPPzeeuTE8AqSqniLQdU8ag29XEwnLMHgjGjfDc6P5P6rm6YGD4KwZiqPrGj5qoRTvLWh2O9o6mvUC3mWzfpScF2tCGDaWpeoBU3YBIBeV7Wz8XaFau5xf5arC3/NNE0mkBw/iBxUzu5zkkr7bQI0UmuEjPJaSteeulJG1DdQzyVfFJCfeibReNDDQuW0NS8fTczo3usn/6wh5ZDZmFqrUe5h8yKlMcyt97sIdW0QOU5Vp6Isnlff9Gowd9MUKfH+Q9/6K0A83EOOliOel+1xLOu5aGhx4gug97aXXVH4/RHtpN5CjtXfehBFY1T9YVWPJrtrDRlD6KWK7iKpWJeMmMqt6VaskyuScOS78azcznrkurjzLG7qWtgYJOmWjdoa5hu/WRuwvNK+Bc9zI5eo3Z4iY+oPU8OctYa78mGABg7JEmRzg3TgynCqzdTKjHwW2yiXWMTt1N70vy/gseY2cJMttkqyXIjWWngN1QxxlqLkJzlj+vrEy8VHrljsXL5sr/gZg6vu11oc6YVUBwUywVmeZZLyrTF3Y+QtDAYq0XNe5F/Owr/bhn+3Tb8m1T/E//+H/7tvAv9+3/49ynxb82dz9//wz+DdjH//h/+PcH7INyv2vIAPF+r3h+EZxbCGIQchDwEH8K4Sn85LkH9vgH6nf/SZwv08lLgiFXQkyvFe4A/HLkW/v9VCFJ8GOKvBF5xgDcc4A1+
*/