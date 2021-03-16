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
Jpcw9WhUcW1NdW2eS5x5NCJoliJqisolTTwitSvbtuq/ysdHJOoKrwqkhwdfUcegoxm6xisaR7+tjg3JIVmCzftTN6KTelw6j0g1DM6bdSLqtB5FI9JJJdlVDNIB04FoYGQ0php1c7ZjW8GJTUWDCSLDERzXUXh/wkqyKCPleFI/5KTw567UCeXw1FHyz996IokXZFNQhFA0mHB8ZHwUyGCjC3JtrklyNJvTBFJXmqYxwuSIrk16h0FGjHCCSr0=
*/