/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_ADAPTER_08112011_0942)
#define FUSION_ITERATOR_ADAPTER_08112011_0942

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    template <typename Derived_, typename Iterator_,
        typename Category = typename traits::category_of<Iterator_>::type>
    struct iterator_adapter
        : iterator_facade<Derived_, Category>
    {
        typedef typename
            remove_const<Iterator_>::type
        iterator_base_type;
        iterator_base_type iterator_base;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        iterator_adapter(iterator_base_type const& iterator_base_)
            : iterator_base(iterator_base_) {}

        // default implementation
        template <typename I1, typename I2>
        struct equal_to
            : result_of::equal_to<
                typename I1::iterator_base_type
              , typename I2::iterator_base_type
            >
        {};

        // default implementation
        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Derived_::template make<
                typename result_of::advance<
                    typename Iterator::iterator_base_type, N
                >::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return type(fusion::advance<N>(it.iterator_base));
            }
        };

        // default implementation
        template <typename First, typename Last>
        struct distance
            : result_of::distance<
                typename First::iterator_base_type
              , typename Last::iterator_base_type
            >
        {};

        // default implementation
        template <typename Iterator>
        struct value_of
            : result_of::value_of<
                typename Iterator::iterator_base_type
            >
        {};

        // default implementation
        template <typename Iterator>
        struct deref
        {
            typedef typename
                result_of::deref<
                    typename Iterator::iterator_base_type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return fusion::deref(it.iterator_base);
            }
        };

        // default implementation
        template <typename Iterator>
        struct next
        {
            typedef typename Derived_::template make<
                typename result_of::next<
                    typename Iterator::iterator_base_type
                >::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(fusion::next(i.iterator_base));
            }
        };

        // default implementation
        template <typename Iterator>
        struct prior
        {
            typedef typename Derived_::template make<
                typename result_of::prior<
                    typename Iterator::iterator_base_type
                >::type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(fusion::prior(i.iterator_base));
            }
        };
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Derived, typename Iterator, typename Category>
    struct iterator_traits< ::boost::fusion::iterator_adapter<Derived, Iterator, Category> >
    { };
}
#endif

#endif

/* iterator_adapter.hpp
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
*/