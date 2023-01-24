
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
P32ucB0tmr+Nc2mjD8z46I+k//hD85S8hDHU+GID+y2RTEHeG97h7x0AHFRqkemfCbvLnjigLAzAheLuVmQp7u7uri2wxd3dfYrT4u7u7u7uDFLcncFdh5mV7Ga/7GZzk5vc+w+enJz3bTrZjJxu+6zHneHkEmBdVeZR4xByPuoxq8ylYKZv1qvqmAzl3TVVvN1ZF7Z0chU+yuaFMpz3kawmLwPOl6VU8w62WdSEllWHEI7m8q6Jv+31fXqJtoCFHpuczCweiFl8+PgKiI1Ak2LxHewc4tZzXavbWGzIGuqyE/Hu88V2KKZOR8f6ftEH1Ja+sLXunBN5knuqxghpHHE/7GQP5OXt+DPeNGVjTsRcQPVXflDrf8pEP1TqkByX5E5rV4k8ThJGJdjvQfLGnRDo+7vK29HKP1f9XOo/6s8Kavtk95Mpss6hUKtfT8vI7qYWfhnmH0EJ6OJMzjmFE8OtzBakbfn+TPXwqyjNMJfiiHMV65tBbXaS70ZjzUNbZheeFDfEG59z64HO3lu94itXvYZD5DdhfmAMqj/ED0+Z2z/7WpLELmH6xqa4hEKCDKmsn7buc7t6yJs2LLy7Ome0F9F8MUNVqJo3+O1biR25SLkFr1B8o/NXdizu37YGekUcjYh6nh8QwOE7F9bonmF+8djSoH2HXPflPXSSHMu/rK7cqhY5lW1chCNZsu8mFXqW18WSGZ9y+vec
*/