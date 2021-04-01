
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
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
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_equal_impl<
              typename greater_equal_tag<N1>::type
            , typename greater_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
xloV/Y/8Wb+VRDE38FsjghlYdrWH6nG3mdCA3+YDYScl4vXWsXuzogoNNemx4DsvLCkRRpK0uz07wCY9TYw9YMhkWCNgJJ5ipNg30TDqDJdQbsoO3kzf4r/thXxxy/B0IR0CttVxvdcm0HvPrbNvIrzIWiwfy+nsMVRuLee+/wkVvNV43WCTsIx00UiO0zP3oUqF85/Y6Uu11hnUmwxKOeCVZMz3QwcEbV+l/tNDWHun2K2qvqoMKHnVmiT8yuDjmodLM+qiRTSePcLApMo9gy/r/h4PjlOdzmDxiJ3u8HRc7AGUuSYTcxlafGCAyr1bL4La+ABw5ImzvEu1Ne9ebwhBSjfxqQXyIT/67CP6hVpYMy/khc0YH50kLWLp4PqrQqNmF3ToT+MMPYA4icSsk2+lh8+GjrS+2j/qKE4tByidbeBEAe1zJwe8Zg41ibHJMIYoP9MajWZ42jf9JqJY5ejfuP2gjnpldDJdRQ9J9/F94W35CMYLEwxsb69oJdb/bk3beAKfELBj17o5f3FSVhieuw3bn02m4hEC1Tt+fTdFd2NHINRnSlYaeg==
*/