/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_ITERATOR_05062005_1218)
#define FUSION_CONVERT_ITERATOR_05062005_1218

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator>
    struct mpl_iterator; // forward declaration

    //  Test T. If it is a fusion iterator, return a reference to it.
    //  else, assume it is an mpl iterator.

    template <typename T>
    struct convert_iterator
    {
        typedef typename
            mpl::if_<
                is_fusion_iterator<T>
              , T
              , mpl_iterator<T>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static T const&
        call(T const& x, mpl::true_)
        {
            return x;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static mpl_iterator<T>
        call(T const& /*x*/, mpl::false_)
        {
            return mpl_iterator<T>();
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename
            mpl::if_<
                is_fusion_iterator<T>
              , T const&
              , mpl_iterator<T>
            >::type
        call(T const& x)
        {
            return call(x, is_fusion_iterator<T>());
        }
    };
}}

#endif

/* convert_iterator.hpp
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
*/