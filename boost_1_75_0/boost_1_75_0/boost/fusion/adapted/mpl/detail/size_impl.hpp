/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_31122005_1508)
#define BOOST_FUSION_SIZE_IMPL_31122005_1508

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct size_impl;

        template <>
        struct size_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::size<Sequence> {};
        };
    }
}}

#endif

/* size_impl.hpp
Ena+ULlNqElBN/Dsi9KzdHlalGAavyLFHgjlKyY9lLybpXIJ8zYP1I1vdhkoMGcxcpuvQoKhhN6iBKxLLItsukQDd6hUF1ENjAX8LfQ2LkrQJ6RCHSwMHIBpNt9jMMJraPELLIy7VpDUEOBQvmTz5WOgotpCcFSVz+O31MbqzdviUJz6IoBZ3uaDizA4XaDf8zinbQeTG49bRUuxt0OPWvX+d1Q+a860B890JGb6SshMf3jMnOlyv0yfM2f6yVbK9Agb2TUkBcJD5LvEL98Mv3xfMOc7i+e7wsg3IkS+F/J8e2G+6iNw6veXyLoyxg6bhkxwCcAYDmbDYvBsWgj7ghzcF0DPoe/3PD/UIJx8BoXrvfr6I1axoSKZL7wYAYxuZtortOso9SFZxlom27vKvJYR/RltbIHEYXYNDF/TKOoq2C8mK2D6yqbpK4tNXyNw+vKfZN82T7J8R4F4bbMB4ujj/dHIhlkoFqcSK64jODAIcbIQQv0AsYuOJkBodmHBuJ+gVAODp2p81GrkfQJe8LTOqdTBoe7Hf9IIwKT/ZbFQ0R4QqdTgV6wHn3/USh3rfBThk7H1h5ZbdZeVLCq8PMjZrb51Ism+kkv2JZOD3cGZQM1g7ltDc+N4/hzDn1etwXlwBH9NeQ9fz6fHYHoMoEdPShrLk0by59/vG3sZXUvaU6e1SNVzrZ7DYe4s6LNMtgDcvNFqqXEgYpHs
*/