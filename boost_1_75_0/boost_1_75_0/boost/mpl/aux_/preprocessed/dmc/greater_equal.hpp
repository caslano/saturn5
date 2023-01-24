
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

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
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
teBbQyYIuPQ5u9jPmfDqxookq7+0UW0XO3VCNHzjBvuwAZaZyVTLHpvJbOlCTX3I/oLVfpBAxh6+CxG3nuYHcjwwQuOzzR/i8oTitOTcON32ZDsLBNsS5JZGKOn+6kmJMH3oGjthTRkyc4FQJ8lOp928r1OQYPkJlLLIa/ThwX2WJwtZSRUqUIxDVUdopGkQMqmVdI2uu3P+mbazs5O9NNEQgtjT8/Xr2RH0ksx9eNjKew5HbENGQql7aw1hTuEVL0Pt9KJYuBf5xv9LZHc1ITR7EYejCXcsqG9EUcCZn4IDs4HXgV781T3g846yudjL/njdt0mrXTB6QsQXla95iaNHiA4ODPqBDMiSgfkBrK9ByTuBF/eUpokFyT+IFJz5lE0YXhBOQgFmCC+C09zKo36sK+poPuGW9MbEfy0kYkSzHGoK15TC2VbvQttARzVhcWuiuyWor9csJeq1qScOJNL+ItLyBTKKxXQd0KmD0hLEUENTMxLTnG/ho1SiXeFhc7kOsEZp4y05ghp32IjYTugdtplnnGR9pErwWfSzk6NFb0vgGp/2AVbh9nMig2ehYTKoynxyN1+I3j4Qe6TK0EOguljXf/bAcncbhCgP73l4RNvXAF4q3uFTsFxGXVZcuuyogX/aYttPmPBeCFlkmcRJ37bv1IJxTp+7Odjm4+E9vt3kZgdjv0vuRo2DMHmGjNKrN5B3c6cPTsJf
*/