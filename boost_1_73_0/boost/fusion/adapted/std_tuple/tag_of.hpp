/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TAG_OF_09112011_1842)
#define BOOST_FUSION_TAG_OF_09112011_1842

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/fusion/support/tag_of_fwd.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template <typename... Elements>
        struct tag_of<std::tuple<Elements...>>
        {
            typedef std_tuple_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template <typename>
    struct sequence_tag;

    template <typename... Elements>
    struct sequence_tag<std::tuple<Elements...>>
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <typename... Elements>
    struct sequence_tag<std::tuple<Elements...> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
PATbwcNwBPwKzoZfwzvgEbgDfgPfht/Bz+FR6MGhY7AOPA67wBPwCngSzoHfw5vgD3Aj/BHugafgV/AMPAN/gjH492fYGP4CW0Ofl/oL+mE2jIZaPvQcMsqqW/nQcG6FfeE2uAI+r+1Qnyg9m0rPANsA1yMdorQ9LUc8w9mwPZwDe8Or4AA4Dw6F8+F4uABmwV4VKA+wN7wK3oj+9XAZvFGfr9Dn98Pb0X8c3gGfgXfCF+Fd
*/