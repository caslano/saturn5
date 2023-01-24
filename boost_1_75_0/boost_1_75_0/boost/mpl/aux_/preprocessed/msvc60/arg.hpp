
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
9dji828yWLtsZKAolfrr0CUZzJkMwl6xozmbEk2+Xet/i23T9xpR8jszTZBirXA/qSBeGuvs8ag83gxXML6jfD9vzKMbbEgOEmZeeryoaoJBYz6M8e+jWWXdLW0J+lerRdroethmHZnQky8CsMSeN0NAotSW0SmVsRajd6NMZh0No9pO1QRlNjXlA2ukRbNUWJ0JjlJbBdYcnnMEZrnrw7hLmaOGQ1bCphAiDf7CKx5FojbVhuFLJ87nWPBiq6KWoIITL7Ts7wx0pN6pXvoerawbHjwYbOjJ91b/eVN2BiYmfBD46XqpG+o7aCMKCzx91+3C9OY41be9ctr0+mPeKey1+x5APpMGZSm5h6N/8/J0euhlT4DBNUC9azIyvgSSFrR8CezlqlNtyYc14p54JeoeR0OZQEoIQPRu9d8wxwt1lOduVgPaueOX0HUEfwsY9pMRyH/al8lZ4Dqzr+adYnqwKKim6N1z9Qtp6ZzRmhfj3On5BfMvhIyZIWib8jw0APlvolhuckqg92958s//TRRT/mdeuYSJmwWrl43DpbaBvbrkh3wWMZZxJXj4Q2kpJMYF1jcYzo+tyx65Fei6g9wfqFlXim1egVf2V9hTtRz38DsfRwn3EZPOQ+fDEoOIjNiXpSnlIcGZ1gC4r+9xgdcT5UtuV5sOcozteh9Vhjqe7mdmO9xmcgXcLGcCYFvZzJR5O+5p04X+5jgd
*/