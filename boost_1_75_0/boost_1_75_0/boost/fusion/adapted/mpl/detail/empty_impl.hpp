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
kY3TEHpIcqYcKuU+j8xD2kDWMnCsGNE0zG8fYgzzPiKsDw8DeKxuaH389ltoNuFn39HO+oOLS8zgdSPTVTIBOd2+SkyP2cNhYdBtDsfKsoTGyvp6RxzhWl30lsC1qtnGgwboQR+IoO560IsiqO1NEbRMBP2sB83bRruRO3eQlvXNO+j9Bv6cyp8T+HMsTzeSv4/gz+H8OYQ/B/J0fXaQ3UJPXk40j9e2U3wrfx7eTuEH+Pte/r6bv9fx9xr+vmE7rpkQd+qmMy1+6ydQ/le8tDeqcvgmdsd90Y1vW9ttmbqKLdMYihLLVbboeuV1XHRVmRZdmGtXyM7pc4ThWkbWBndnn/phXrXH3aZRFZU+SMfddilH1BxNY2MFXadVwiIeD8eKurPdnmYrfoXJPie5q++CC35YjCj1sM4vYnFZXoSedSm1tCWJ1AEwoFIRolJzGCdkKQhr6vgYl/6lO6WS2eQUosLJFmG+7KfUh/+Lpx/uF1gAT83CX1DHVlH4637hr6vNGK4seIG8P2Q/BXT3IhlcwYf+CbDwuhw2AX0I2LHCECsHIG4AWiqgtEeAxAqThzNyX1EhlaC7QK97lSikDxWyii8WwI9J02dYLa2oL5WzytBAfhiiX8NoVtRMqvUGKm6DAQ3kRdOyBRtwWtwAJXpqNVmrynekXTLWfRTa941wnDWLRjgAMhYml6nX2XBWsy15G/Z8binLUxOf
*/