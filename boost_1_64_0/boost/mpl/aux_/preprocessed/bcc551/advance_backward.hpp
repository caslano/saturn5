
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
/zK90jb5PnqzRok/mDfEo08L2mB6EuAT3PfqsReIu5GiG3NvIfD1o4FAd+65EdU0f0QNorLXi87YmchBfIuZ4NjLWY9Mt6QXxhrKVtmUg0vGpF3djc6ofoN6uAoJhyNoSSMKPblM7oc8XLP6JiO54SqShZcmFqz2oHpb6BEMo++vh9YzC5DQIzuqatMfqHWKU+AsjXyDex6CoZSQ79RzINO4fnxY4lIPqACrXhdSshq/iLpEv62Z34diP529ZtoseXN/Opz14wYNjP9ayJjLVSkj+L94q7nMARiG5NnRicQsADPvbVN2z1n+YgfibF8zMWEDuklBuAt0ZLO43k0bRsmqXUKWxOGd7HZNTS4wxm05niuwuNlqoQW677gBe1Zqa2ETd0hEvqavbKYnyPxZj/1VHmUXz10JnEzxLIqnSQzGgIqS7BOn52ab4eq9l+shzB6sqZzV5CqKJSyBPPMHY9ZtSsJfpWOHvl4KzgLU1E2+hQYpMD4fdE7FDCp6M0kx3lpPN4GWnD0SvmMSkNqOJRwrQF7wBKloLFvsM7Qrl61aPVo6RnK4uUy8ng==
*/