
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
6BAAR4n4twgDHGlEsNF5I8f7Rzrf2+tG2fNPMtWbBFGkJckmdZ8fkve9PI4OckRruq+f0h1GNunAzb9/Ms8yiMVbZhObB4RhKjXtvxVU/WdBWKt+mlX0fK+7Oz3FN0p2GNHQ6h7GP/nXL01oYwLrsLIFSMIzfazZegRsMT70BuKFY7LH2KOl7R58rv36hncNsHByx1Q7awhxXGUzW5bWC9KKMT9E1B5g1S9/++ojOplwgHBe76rZ3+jqOVbPC5skjMSuHBJ2as+qSTU2IDdANZ0oVRSOaWJMoX1Ri+4lFCenivTmhmKrcp0J9QHu3KG/7pYrbnkWtTl8920wTVvNq7j9WPedtjH1i8yp59dolku6j1yWETkh9zJACE6n4fzgyVn7hRq9g4DrtbEGqgSgkFg8SJ5y54C1rMKc4iiiO8fhewRfq7O8dPx24v8NBALR7icSsDOUOlD1eXorJMRUkl5QfmE71VePzxj4bGeERoChfDRX64De59L5nIYR0ya4eIouLpQUkWp5thxDXxqP3GkrfXYNYFcz+09jHev5XzqAKEwdQfg4yaHyrw==
*/