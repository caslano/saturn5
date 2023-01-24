
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
4FSoxrYAdCFiY3Y4vd+p+MrrIKU/EXaWTW2waRgtVlr0xYu3UChSoLiT4u7uVtwdQnApTpGiwd3dtcU1uLtDgeDBQnbf3dmZ/bAz+/X5B2eu5z7HBx5PQYo9JOZF7c/U6PuWpzTwBaS89dQn9uC0T43gekGvDq/RJ0NI/oGIW9UNIbZVFFfPt0J+fRL3DdHX614E9uUX6qDDH16GIb/CrgBiyQBt4ZdMfSiOIXYOJlucoCrdPZsWog/tuW0NxHTRAK4ZCztHLP5wRrImcuYeuQ6BIkC6NShGmAa4a6/W3qxJuE46ffCRshevRGlBqQgUDFxEqkHXQrGLqHHIz+olD+JF8kKyC/LoXe8FmoScOOHuSG0ZbYls+ZsQXFhusURZsmLldzcFhjvptSA/qDQq2/kSPihtsW+5bK0GGfY6muB23U72TB7VThMIU3LG6cFH0vA4Ctjtaq3s+62bzEa2vYdlbpYPIsz1LlNEXhyaduD0yhQtVXh9noMbl5OC4/5WDGZpIeJK0btLB8eF5h+BMW5KmXgeic3TvuPnvPacIu+4dlV9TyW4UiSgfbRaaxGCXSx3Jq7v3oomszlCIZ/Eix1u+FOEF3wz2T2FTrBEUYeazdTmjH7+OUPti8AjV33oBBt1RfVZTRfdD98laH0Mc/90VUY1G0lq1MEzq8RnRP8NSyKpDtTMTQblNJOb6OyNJAjPenUYZw36QkrJ
*/