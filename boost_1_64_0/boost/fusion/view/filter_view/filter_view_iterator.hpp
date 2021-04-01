/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_VIEW_ITERATOR_05062005_0849)
#define FUSION_FILTER_VIEW_ITERATOR_05062005_0849

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/fusion/view/filter_view/detail/deref_impl.hpp>
#include <boost/fusion/view/filter_view/detail/next_impl.hpp>
#include <boost/fusion/view/filter_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/filter_view/detail/equal_to_impl.hpp>
#include <boost/fusion/view/filter_view/detail/deref_data_impl.hpp>
#include <boost/fusion/view/filter_view/detail/value_of_data_impl.hpp>
#include <boost/fusion/view/filter_view/detail/key_of_impl.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;
    struct forward_traversal_tag;

    template <typename Category, typename First, typename Last, typename Pred>
    struct filter_iterator : iterator_base<filter_iterator<Category, First, Last, Pred> >
    {
        typedef convert_iterator<First> first_converter;
        typedef typename first_converter::type first_iter;
        typedef convert_iterator<Last> last_converter;
        typedef typename last_converter::type last_iter;

        typedef filter_view_iterator_tag fusion_tag;
        typedef Category category;
        typedef
            detail::static_find_if<
                first_iter
              , last_iter
              , mpl::bind1<
                    typename mpl::lambda<Pred>::type
                  , mpl::bind1<mpl::quote1<result_of::value_of>,mpl::_1>
                >
            >
        filter;
        typedef typename filter::type first_type;
        typedef last_iter last_type;
        typedef Pred pred_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        filter_iterator(First const& in_first)
            : first(filter::iter_call(first_converter::call(in_first))) {}

        first_type first;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(filter_iterator& operator= (filter_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Category, typename First, typename Last, typename Pred>
    struct iterator_traits< ::boost::fusion::filter_iterator<Category, First, Last, Pred> >
    { };
}
#endif

#endif



/* filter_view_iterator.hpp
1DlFXHv5wcmTi/+nIFdtuYT57eYS2m1E089YfHQChC8gbl81MkKsFYRhSbMrlrdNP7L/rr09zO1d3PhULIinTWjTTu+76/hobraxvZtoqn+PeBfnbshhYpt4jzSygz3Zw1jydvfJ4syYQ+MH51gEqbdLg6QnX1AMaf471bjS2ElWkKDBNcOX5XjnrS7/sCTEcP++X6zLaQjA8RMclALFSnFkskuvcjpuYLyEcTiTtykm/MYbARZ21/mI/zFsjlIHvcsPyrug17lv2LECTnKIP/XOlvwwS2pk2Duybb3wU3yKcl9NcJEWn/1d90xjIERmlzwaFvKO6zkWRiV+cAsCugxyI6yG5cdjDO31/WLsCIrK/rV8v94BOFr9WY5rDSVTSxwLHcma3AKj5m2ETA38qOGR2IUu5UfhjCwQov+mOslgKT3UE7gme9CfGfpaGEsyBuaq7FowL51dxsWDw73c1OZq0Vp6vQFQjxubZPjXLPEXFAG8P9UCGcQVjJkIgX6cgU9MDmRyK2dHamJny4qZYnLyjUNuZRqJ4OR5R8d1mVfPEWsi8njC/XYWww==
*/