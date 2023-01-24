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
bJ6WA79hqU3OCj+Qd7mjfIwnXZaTG1jzOaVFs6VQv9dearlkMgV7I8tfTMmh96kqsuzrOAkjytUiIZCyC/GNCGwnR3mXXJKZDkq7TpWBLUKyxooWdXZO/jGZJI/8VVqBp7mVs5rtZ1hlk2ttB7WsL7asFFpGmbXVMbCuoldCQ0rdyj4Cr1d24jEIGkP7RVNLfHs2qGKUsD0reeXFHIF1GbCTpRYt77eWxZT9nvzTLsy6Cg0861I+dG3VUslLO5gt1aRo9XJkmYUMt+gDj3v4MlWrL3M5dixr1uqjJ6Sanlxit1QVJqUzDAjs8hfWLO+xHpYFb5BTNxys/HRi5Z5KePCd5QPK6lpSyAxY+cmQ9bOzr6rcXYtlo/DGOvg9tKxOTX8b9blYML258pOJ62EuV+6uhFJXuRXNcWYlCo99CPxPJPhwb0NczfO5Z6wft9yL0Q6nVyd71o/U6uO8Bya9wvva4s5gh13RCf00brgn5qfhUT4BrgDcyId0OuZ6S6dTAUg3KX6dTF4zk2l5LyBTSLXD9wXLPsScF03Q+Z3Lk0P1KdF3Q/Xdoo3wXE+/TrwMM0FwjTYR7dLL0OWDZJPoUqnm4KZKov6nE8t6HIBq3l0+bFNtKsZqzc4eXXZ14yZTHvzo0Yj04ieRutFCFLugyBgkqGtTM9bh6lGLcdJ5m2ol+IWP2hMeHb0ZCa+cJbuCSznoOLhqgBAiuS/W
*/