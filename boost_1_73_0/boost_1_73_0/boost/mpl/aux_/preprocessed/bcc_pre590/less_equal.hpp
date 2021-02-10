
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
pYfZcGpad+yEklekkkPxjbiBDbYHbGNvChSqxabqOF9o0kNDOb2fwsNkAus38V0TJpDt8Q4mT/DuDpyYTmD6mDw+JQx5/ZmJZ2cJLcU/0O6oTGB2iWRdw9WER5Il1ZUQJVaVYy7DMCVPw3tWz5UJNQOrvD8wZIua9i2yAtOwurOwa1j5Xs1clERN3IOUPMdAWV3jICsO9gSf4MtQOVgEvsHcbA0WsPfG7iBgYruvsTW5rkAXBQ/x3EcOjUDlrq61LeYi3kF8hFEYm0g5Xq432WyVJuMwa5auP7IRnHJMpQtPi7XjbRrCe+4iH2bfmOqlH/+eRPd2fDKFbQfBKdBbwhaoRAiXAUrt4TeihZEvHY2EOvRYbsGiyOWumoug87/j4bzuSCydpwT+DY3ELzY0XuyYXQL5vq3k+PPlY7Nav0dikefYcPhW3kYiDabGvH6LORlnE3hDbOJFZQ4YiYg1XhkqeaEtr3f8L1BLAwQKAAAACAAtZ0pS7yrcgugBAAA5AwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI2NFVUBQABtkgkYIVTwW7aQBC9r+R/GKXiktYsRggp1gqVpmkSpQ0ouBxy264HbMV4rd0xxv36jjGEHir1Yu/uvHl+b/ZZEXoy
*/