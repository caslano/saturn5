/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_SEGMENTED_ITERATOR_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_SEGMENTED_ITERATOR_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/deref_data.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/iterator/detail/segmented_equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace detail
    {
        template <typename Stack>
        struct segmented_next_impl;
    }

    // A segmented iterator wraps a "context", which is a cons list
    // of ranges, the frontmost is range over values and the rest
    // are ranges over internal segments.
    template <typename Context>
    struct segmented_iterator
      : iterator_facade<segmented_iterator<Context>, forward_traversal_tag>
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED explicit segmented_iterator(Context const& ctx)
          : context(ctx)
        {}

        //auto deref(it)
        //{
        //  return deref(begin(car(it.context)))
        //}
        template <typename It>
        struct deref
        {
            typedef
                typename result_of::deref<
                    typename It::context_type::car_type::begin_type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(It const& it)
            {
                return *it.context.car.first;
            }
        };

        //auto deref_data(it)
        //{
        //  return deref_data(begin(car(it.context)))
        //}
        template <typename It>
        struct deref_data
        {
            typedef
                typename result_of::deref_data<
                    typename It::context_type::car_type::begin_type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(It const& it)
            {
                return fusion::deref_data(it.context.car.first);
            }
        };

        //auto key_of(it)
        //{
        //  return key_of(begin(car(it.context)))
        //}
        template <typename It>
        struct key_of
          : result_of::key_of<typename It::context_type::car_type::begin_type>
        {};

        //auto value_of(it)
        //{
        //  return value_of(begin(car(it.context)))
        //}
        template <typename It>
        struct value_of
          : result_of::value_of<typename It::context_type::car_type::begin_type>
        {};

        //auto value_of_data(it)
        //{
        //  return value_of_data(begin(car(it.context)))
        //}
        template <typename It>
        struct value_of_data
          : result_of::value_of_data<typename It::context_type::car_type::begin_type>
        {};

        // Compare all the segment iterators in each stack, starting with
        // the bottom-most.
        template <
            typename It1
          , typename It2
          , int Size1 = It1::context_type::size::value
          , int Size2 = It2::context_type::size::value
        >
        struct equal_to
          : mpl::false_
        {};

        template <typename It1, typename It2, int Size>
        struct equal_to<It1, It2, Size, Size>
          : detail::segmented_equal_to<
                typename It1::context_type
              , typename It2::context_type
            >
        {};

        template <typename It>
        struct next
        {
            typedef detail::segmented_next_impl<typename It::context_type> impl;
            typedef segmented_iterator<typename impl::type> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(It const& it)
            {
                return type(impl::call(it.context));
            }
        };

        typedef Context context_type;
        context_type context;
    };

}}

#endif

/* segmented_iterator.hpp
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
*/