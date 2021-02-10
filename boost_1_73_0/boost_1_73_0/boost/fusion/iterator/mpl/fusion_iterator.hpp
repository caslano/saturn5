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
YzoS9asMveJllIjFaXm4ORNn5KRO1oRwGASP2Gt31L0za9r3BTzn0TDwwpj1/UEU/OWzbjSIVyDQShge/UohCP8BUEsDBAoAAAAIAC1nSlLPzwJtMAcAAB0UAAAYAAkAY3VybC1tYXN0ZXIvbGliL2RvdGRvdC5jVVQFAAG2SCRg3Vhtb9s2EP7uX3FzgcZ2ZCkv3bDWbbcs3UuwIR2SFEOxDgYtURY3WdRIqonb5L/vji+SnDjLCmxf5jaxRPLennuOPCaZ/HufAUzgwc/c/szxg99W4mclf+ep2b56Pr8G9w+l3uH3Q0YS6ESu52N4WOQaRlZk7q08p+f5/CFD78g3+pWQ5Ls5PeIIipHksazXSiwLA6PjMew/ffolTOFg72AvglesEryEc8OrBVfLCJ5nduTrgl1dxZq/jIAbYGXsVV0UQoOWublkigM+lyLlleYZMA0Z16kSC3wRFZiCQy5KDsevf357cvp9BJeFSAtSspYN6EI2ZQYFe89B8ZSL905HzZQBmaM4Ks+ENqiwMUJWMdrmYLhaadJB5lmpJbD3TJRsgYaYgcKYWj9LkrRRJXqfZDLVSRrCjwuzaiN5i06s2BpkbcBIaDSPgFZGsJKZyOkbAcHBulmUQhdR5w2aqrJEKtC8LEkXygmu
*/