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

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        filter_iterator(filter_iterator const& rhs)
            : first(rhs.first) {}

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