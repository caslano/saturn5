
#ifndef BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/less.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(max_element)

namespace aux {

template< typename Predicate >
struct select_max
{
    template< typename OldIterator, typename Iterator >
    struct apply
    {
        typedef typename apply2<
              Predicate
            , typename deref<OldIterator>::type
            , typename deref<Iterator>::type
            >::type condition_;

        typedef typename if_<
              condition_
            , Iterator
            , OldIterator
            >::type type;
    };
};

} // namespace aux 


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct max_element
    : iter_fold<
          Sequence
        , typename begin<Sequence>::type
        , protect< aux::select_max<Predicate> >
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, max_element)

}}

#endif // BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED

/* max_element.hpp
I9YkPITNyuKQkCXKY0Tl9tj9NsLDzcIWwyCvC05FAjnNDG1CWaBsEEpjAgUmWvNeqfMuOzqPITOoN7mLBLVuSl0T3XsnICDoI9Mb4g6M929DhjkmxpIhspa/1sfI07NyYUrLnPm63oDDSTj9UxGpG+JLcVW1auBP1NFfyPoyWenOjXn7PY89ID4UjZ8vBF7mzcncf8RR1xNinEjjsjqgsIdOYrLZ37Igovnhc9j7PhkJOvqghQVuCaB1RYDIsL+73pDwGzWW2/4K69x0oA0TsVWgHyei7+fYmek3ixUxRLlHLN8VL0qFMLJluIf39q7ZqaTvn2z3oG119UFt7YefA3YgfilAGEMOySleQhioWpVk5y1hipOMuBghp+qdCR37ZhAz9jlxUAz6PCtQS0WQ3RL27bA6yViitKIdxdtaK7QnRX5ri8/41WJzHU+k3QwdgyejkCrKDnmBhTPNvkIoMkvMEBnC/OD2eH2BSENqx1cCrTuvH8K/9bxV23TAiwTm6oIdJh0g1lI6hp6g0+qaWMxsHvooeHJ0CqOYqfrfw7avYT6YCdO5/19EWw==
*/