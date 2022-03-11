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
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
*/