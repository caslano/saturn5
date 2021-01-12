/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_BASE_05042005_1008)
#define FUSION_ITERATOR_BASE_05042005_1008

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_root {};

    template <typename Iterator>
    struct iterator_base : iterator_root
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Iterator const&
        cast() const BOOST_NOEXCEPT
        {
            return static_cast<Iterator const&>(*this);
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Iterator&
        cast() BOOST_NOEXCEPT
        {
            return static_cast<Iterator&>(*this);
        }
    };
}}

#endif

/* iterator_base.hpp
WwyM5OSXLm3qf3SuDxgtGjMbdSkt3DJdi6ejaQylB9EfJC43lSVd1mLP9FYy1j5VbEu3Di/IiI5cGbPbYbf4ZVsZo9uZcXBql002t9shJ758zGZfy5DTZfW5mhODJwg9ZMy4s/s0dziinhIbub4yhlGrTTm2E2/6uNXSdqzdOmZsESdbyXU81i7X0d3VvJXckRz/ih9ampJaVJjtMLCtXHebLmnqLL1kc18wxG1yj7DLNTQ1
*/