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
+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
*/