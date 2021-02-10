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
khd24nlFfavfLkriEeafVzdxH/T+WLD92NftnYxOu4uOFA0Mt+4Tb1kF+CwYRmcxvPMVgnux6EroTKd3HeDfzzt6n4gsTCbFVYZFjKSaEAwx0zKL506NhtOEQv4mUsxiSeINdyYKjr5xkiUTDMTalYpwMWQ7YYYR2plnyP6O4H4ARga+iEQuyvM2hdfjrWFd4B49NkFm3xW4R94ND3FoDiv7a4LdK6IBFYnTqyiRORFW6J+mysFq1Fpk6yH/zHRe5OixJWUCDq0wODILNZo2pmFTkcQ/gOAxjKjUQDw11WGwoAn68Kv8h9onlIYjYxV9Hs8T8mzjvuCq5HK4gs1oXzFPmgXMVrrws7LTWiXQVMEAuR79IBhYHGj4o8MCF0WGrin1qr1h9+wNYxKzFIwQfnBn+W8SNeLcMuk+3K7Ld7ssaTPmOHyodwMdxZvKl2WUYr7HTDL4qOqWwHFeUCk0hFFKOaiqi61JRkgr0IZ0JVtrAQ2C5s7PYRZTcqUNhKWNYJYCvqJOryW/CS1QmTNF97LJXmvSMfal8wSxYqcEwrLSnIqbETBin0BuZTLVmEhtwV2gz8I8zBCjKTwfZvGMc49SJkQY9x9lmHn2lyGqpfBr3WrjyK9M+FJ8l5472TtMUUJV7G8WZXmcY5UH
*/