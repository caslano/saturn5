
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
xOZtBcEfnOoKzOzb6EW9A0E3dYS42+vZuFUjwFfJV5pEig/EvawuXEA2/bMKMrQd3sSu1eJ6K9it1zrqfEw5e/YXl3W+4lJ+uRDmJ4kHjo/KFhicBc5csZQcfbpXCUfLb1806BnkR921jjjZew2i33mrePxiQxqi7CGwpKCzbaSQw1lVsTJf1fWfpNp+iPU8Ym/E2bumIC5/GtLWOve6LI0tMIEv3xhIK78UR2sC4wtZuexRnwycDosJw3gDyggoQf23yLJVJFxA/mQiFgzzfraMkaNkJAvMFjqAFG7+1SJqusrlQ+52WWcErjLFVKyuJZqbk7SdP5KJfvW09H/6gckWG/arcp22svM5SPN4hVni7xzEVqUOmiBU35uNcceitwdjJikeBnreLX5RIg7Ez0eYSYfphRBvEUlzIHE++/SvfO6QACOcFJJHp/ruH1Sad/0/fSTIJn0+n1gX9VRN75EtT4PDt+8veZvB/xvBXJtbLMHz5lgbXGSXZDZiJs+3bgOLOVdiW0+GhVAL11tkwfl5A6QptsPNkrFjp9hhF12vhut+YBnoODt6vQ==
*/