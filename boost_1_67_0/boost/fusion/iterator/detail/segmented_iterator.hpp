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