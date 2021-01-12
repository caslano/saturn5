/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_HAS_KEY_IMPL_31122005_1647)
#define BOOST_FUSION_HAS_KEY_IMPL_31122005_1647

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl;

        template <>
        struct has_key_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : mpl::has_key<Sequence, Key> {};
        };
    }
}}

#endif

/* has_key_impl.hpp
U2NlH2tKmI44o7ikxHP+sik/HhY3pwUybfpCkK6MkFzGKovBgaDVVPo+1F+u9j0lbQd7OHu/T7f7+VvbpvwUOwfum9sxXfqJfal2Eq14z3UExg/3s+nuK3pDzufwBKaaOvLbosu0fOjytFzeJ7rmgZ2E913kW/oST6Run8CYU3zZcaz6fdc0x81dlA1HWb0oP4p4t98IH2H++0n0J65mTtmj9rGW7UtjD/cc+gMTreUcR8eW
*/