/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_ITERATOR_05042005_0635)
#define FUSION_VECTOR_ITERATOR_05042005_0635

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/container/vector/detail/deref_impl.hpp>
#include <boost/fusion/container/vector/detail/value_of_impl.hpp>
#include <boost/fusion/container/vector/detail/next_impl.hpp>
#include <boost/fusion/container/vector/detail/prior_impl.hpp>
#include <boost/fusion/container/vector/detail/equal_to_impl.hpp>
#include <boost/fusion/container/vector/detail/distance_impl.hpp>
#include <boost/fusion/container/vector/detail/advance_impl.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    struct random_access_traversal_tag;

    template <typename Vector, int N>
    struct vector_iterator_identity;

    template <typename Vector, int N>
    struct vector_iterator : iterator_base<vector_iterator<Vector, N> >
    {
        typedef mpl::int_<N> index;
        typedef Vector vector;
        typedef vector_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;
        typedef vector_iterator_identity<
            typename add_const<Vector>::type, N> identity;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_iterator(Vector& in_vec)
            : vec(in_vec) {}

        Vector& vec;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(vector_iterator& operator= (vector_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Vector, int N>
    struct iterator_traits< ::boost::fusion::vector_iterator<Vector, N> >
    { };
}
#endif

#endif


/* vector_iterator.hpp
wZHowFFYivG4EsfiCzgOj+F4/Agn4C/Rin/ASdhGftOHYgJ2x4fwAZyKMTgNJ2IiJuB0nI0zMBNn4mJMwlKchY/ibKzAVKzENNyFWXgU5+JLOA/fwmx8F3PwA3RgG8psPrbFfIzEArwPnTgOC3ECFuFULMZZuBCX4SJci0vwEVyK38CHcQ8uw/24HO1f8+03fqDNYaDNYX3aHJbw22v3qkC7wsAUmAJTYApM/xnTTbj/59bzxu//Q6njnMaPZkcUdZyuIV2pwswozE1TxpTmbwXKeLn9dH/LT08pyMvlJ6M6RkBcKOm7x0DXvbu/hby7fz31Kcnqb/8RkyfbsvNS7DZ1TWTDh/cEuO9Rwxt4vxc1v9fyv97N33tU83tg/+8hze9Rvd9bUs3K/Bl9l27+zv6Dp/sfuFyZ0X8SnQjVMcCkvGU/NG3gOQZYrIxZOBx7YhxG4wgcifE4FkdLvVH0+maWBILh97n8Ntd+l//HvDvwq3hvoHN94PdnYApMgSkwBabAFJgCU2AKTP/P0024/7enO1wPAG7o/l+5hx8aatHGuKuQe/iX5H09Rwn5yrhr1dep//dhbDGpzzetD483qQ8Pcbe7V+vDU7KzU1PS5qnrSbTIO4eoJ7e5Xjsk7br1dfAyL0JXpx6o8w7UeV+vzruv67nKtFtXvJj3evaRZGduv24f/u0Zb8+RvNeFq2P/yzkj51KwYez/dvJuklCMwDAcgB1xMHbCeOyMVgzHGbr2l90xH+/ETXgXVmAEPok9cT/2wiPYG4/iPWitZ52sSX1soC7Wx7rYm10PezPrYCsCz78CU2AKTIEpMAWmwBSYXPf/c/+99/+ugcLVFgA31gZAeQYQo3vH/yF5BvAq92Ft8ZuYq7xf+aA8A1CT9qmd/Kbnje3kje9llXbyTfTvxda3X8/32g4+HrvpxqWONWkHH2XSDt5qaAevH/e+RPoLpJPptpiMyrZXVXlsu/rwo8C394NffcGzDKwmZZAoZWB8dmEcNz3cZHsi9ePJG7bHLuP4byEDYbgRHV0Jhz23R0bnrrNPubI9Hxzx3J5kw/ZIf3rTsfQdJtsZa9hOb/0XovXbGXiWE3iWc51nOamuZznjkxsknLjrcPLrvzs0etOoBybUr/9C9Nfk2ifXxGA+x/H/3miRfgVtcTh2xjiMwJE4AONxBI7GiTgGp+FYTMJxmIHjsRAn4BKciMvRio/gJHwcJ+NOTMDn8CE8g1PxQ5yGf8FEbC79CYZgEsbhLJyMszENk/FhTMFVmIrrMQ23oB2fxgx8F+fg+5iJn2AWfo5zsT1lMg97Yg6OxFycjXmYgQ6ch/OxAPOxDAtwBzrxKBbiy1iE38YF+C4W48e4ED/BRfg5lmAr9s8SbI9LsRM+jD2wlH/RuAzjcDnOxBU4C8uwEFdiCa7CpbgaV+IafAzX4U7cgHtxI1bhJnwJy/Gb+Ij0W7lMkO8PvlfU4yfU9V5OdWrLcgTtmWB7jMBQ7IthGIMdcSR2wgnYGadgOM7CLpiNXdGJ3XAh9sD1eCdux7vwXYzAj/FuDCJfPTEYe+Fd2BujsQ/GYiTGY1+cjPdhEkZhMrrff8uGyvcL3zuyveSda7U6bZW+5duwOz6G9+DXsT8+jkPxCRyL35Dt3I6JuANTcSfOxydxA1biI/gU7sZdeBSfxou4Gz/BPXgN92Iz8rcP2+ABjMODOBIPYQI+i+lYhTl4GAvxiJw31bgWj+FGfBEz6/mMNdDv5caftf4/9Hs5zTPX84RrgWevgSkw/cdNN6H+XxkG7Ibr/5U2/ult+Y3JoD98y8QXqTe2toL0+Tan0+L6+3v8/bT8vdjw91D+fjyE3zwvqX+XP6c=
*/