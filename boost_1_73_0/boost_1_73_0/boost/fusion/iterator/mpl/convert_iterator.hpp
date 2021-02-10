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
4ICqtuTjQWHRGcODcu47xD9c51tdFkTRpTPXf7nkx1HEBhduELDT4dmZ37f6R0t+bfvCv3DqtCD/1br9vufGLgv8cIHveJ2P5s+i/oUbL/iv1/kUX78Tef6CT5eAxClTpfn8VKyJD0P/46XfiX2PxVeXpIQqb78r0wncwcCGdfBiKRRGrBOFsR/GzkrJSejgMbietym0keHQvfBtKoMIR99CyKb5GwlRa26tNepSDMyF3+HAWaWEAyQdrpE65Aapr9aoLj4k+maN6tWyL9+uI++fdY6PXx/WyMIBQUJkizcfCujC/chcz+vD4dEj+hzC0cPIwN6ngWGDoQMxNwd4OeB0sVTaa3EjcdLbUXB7dH30+YSgSG7uVPkFRjO8tlRJt4lN6iON4+uD489k9RuI6Unj28mq+/mpJE8L2kyOqjGk1DjXa7itjQ3g9HG9GrUVolCwRsScR1PjsSGaYkXEupljoqlP1fX80+H56bAXeI269OQNxwdt9zan4tYpVBcGcNTQulVmPUk0laa2yzH48TKVmzNN/MNx/BRczo9NLUzkH2u0FOo0bd1UZaaVtXGDNwtqrUaZ8ZUoNyGqfGsktQtkE66fzcdmS7QyHK+3SmT48seEFGbvhxJpwRNZTbcL7XKJL15YYV5oTjkQ
*/