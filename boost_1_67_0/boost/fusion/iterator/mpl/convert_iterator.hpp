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