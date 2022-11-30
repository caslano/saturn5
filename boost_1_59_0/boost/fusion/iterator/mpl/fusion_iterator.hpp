/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FUSION_ITERATOR_10012005_1551)
#define FUSION_FUSION_ITERATOR_10012005_1551

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion { namespace detail
{

template<class Category>
struct to_mpl_category {
    typedef typename mpl::eval_if<
        is_base_of<random_access_traversal_tag, Category>,
        mpl::random_access_iterator_tag,
        mpl::eval_if<
            is_base_of<bidirectional_traversal_tag, Category>,
            mpl::bidirectional_iterator_tag,
            mpl::forward_iterator_tag
        >
    >::type type;
};

}}}

namespace boost { namespace mpl
{
    template <typename Iterator>
    struct fusion_iterator
    {
        typedef typename fusion::result_of::value_of<Iterator>::type type;
        typedef typename fusion::traits::category_of<Iterator>::type fusion_category;
        typedef typename fusion::detail::to_mpl_category<fusion_category>::type category;
        typedef Iterator iterator;
    };

    template <typename Iterator>
    struct next<fusion_iterator<Iterator> >
    {
        typedef fusion_iterator<typename fusion::result_of::next<Iterator>::type> type;
    };

    template <typename Iterator>
    struct prior<fusion_iterator<Iterator> >
    {
        typedef fusion_iterator<typename fusion::result_of::prior<Iterator>::type> type;
    };

    template <typename Iterator, typename N>
    struct advance<fusion_iterator<Iterator>, N>
    {
        typedef fusion_iterator<typename fusion::result_of::advance<Iterator, N>::type> type;
    };

    template <typename First, typename Last>
    struct distance<fusion_iterator<First>, fusion_iterator<Last> >
        : fusion::result_of::distance<First, Last>
    {};

}}

#endif



/* fusion_iterator.hpp
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
*/