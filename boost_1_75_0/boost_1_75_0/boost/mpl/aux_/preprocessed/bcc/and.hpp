
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
2dXh5qhSb7HbLwrXkaBS8Lt4elWLyhr7SAVz6E1ve1M7SRzLRmmwW1CWlfLhtHfc0MJseJw3JSphuZYQY2EFh9OClFjkTo8ihGa3IBqxtfzq2FZSYnmyAQEAsKF1GKct+NakwBvtWsipUWtp9GqZlVg91MYByTscjKzF0IortWIZrxYKRptmrFUt1hpqkLBL6cbK2hGphTkq0ST+avpYN5fbZwF3u9RySyWpVWwFNOlxsyzKukcYvYiXsJYBIQpDw4vaSlmBjvLMpmqPX65MMsnhBZisEE6n1g7JTrtlpQhob6oaxQHo8TNmO4LpOxaT9aNigOIiMY6rRcYe+LjDY1qNUD2EdtrGAYAqxsaRXYyFA2tGbxOzbYxrPm1iyocgY3D17J8qq1VSNulTQrXkZpWpbDw4hQZkmMh8s6omRSGeiUETIkcDs/9SjXUfYn2e8iYa0fQLS7XFrXWzXvZmkc0pe0J9VudU7UwsNsAYrFkDp2LF7Ixm19TuTs3Gzv3uA5YFgxwlkBrQbS+LDaqnytsytJN2IdaivAbAG2k9flxhPcn4ySQj27Y9pNkPWhYWpszoNPQkGUCMAQuNCm4Is7kdK6C6yH1DG8OYjyeAR0pGJKTRa9ZCS9khmirJrgvnaVMAbRaLNl8RGJIyvaWpIApLqK0vRndM4ZVbgPJKdFg2bD+pCaYUNpY2lseNckcBS0G24dgryWawE7Nv
*/