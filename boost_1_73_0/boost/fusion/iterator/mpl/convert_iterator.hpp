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
2Lwwq9R4cZ1Zf73xPddx3u765PpxgedZMd11zH5e5uefNltHz3O83zF+PrS+eWuZ8/cm5/epPqewnw9d7LrS6+ewrrNuTnLdsn/f63Q9c54f8jnDgresa1f6PNj+Pfie66P7tOlfsj1eZ+vVrm/fsp93GI8zrBOmuF7sdnxzzMvjcR52/Tc/zLzdvPWE/WcdedS6bNlj/vxG17NN7kOuMs9aZ6z9p/HuPNgQtv4wrhbfa55z
*/