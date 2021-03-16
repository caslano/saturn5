/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EMPTY_IMPL_31122005_1554)
#define BOOST_FUSION_EMPTY_IMPL_31122005_1554

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/empty.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Sequence>
        struct empty_impl;

        template <>
        struct empty_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::empty<Sequence> {};
        };
    }
}}

#endif

/* empty_impl.hpp
Dp0x97J4eoMtrU5QQWPUeWdhvHEne7BQk0A3J8je7m+X4ObZ7iP6keDSyoFcjc0P8KxIZYBdcCFZ0mcuDHA8n0UBnly8WZYkTIu1oE2FoE2FoE2FoDFWA2wJsA3AHgf2KrDXgX0I7DCwL4H9FRjlKWZskmUwN3NXWGDuvGBkxVrBdmPucGbuTOrTN7cxtxj+JiM4Ln9nGv5WcyoxHD5YqL1+8ohMYuZwcuXEcjhlGLrWweELBXN4hfy948nhiy4=
*/