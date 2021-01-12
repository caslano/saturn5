/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_0137)
#define FUSION_DEREF_IMPL_07162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<joint_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
hnl5Mf5q+jKlP/qwHtPHitRnnZnWPleFnO5u3RjZgMGZ4wUmr2uGRkHPXOcv32jp3cMbhHmFwWzafDaYV27IdEgQ5eVxRm8UXTzGbcPkVS9FQWt18Wojf0SgJbP5E0YG89Ix+mNIp/qEp2wzLzP1r092dNrqM28l6KKtPsfQ2IlQJvu5nb646WqpjI83eRt5qMfo+gkG1z1oSXX2RMKIU59c308yGHNCgtpBl6ZPT3BdPaU7
*/