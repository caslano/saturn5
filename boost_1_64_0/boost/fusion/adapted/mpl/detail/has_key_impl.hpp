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
G+0x8XBXRt1uBcBYdaQz+m8gCU4sy6imAZRyIeJQJ20l/tr8DU9xpmqxvaPkVsmMozYZM/cyLR8pPIRPmY+5ZYMhQiGsCHcRXMm4EQwLrEE67ZEXWmJepYAxFPYDGMU28bUlG4UxzG7jcFiKBk0MryvR14i4tqt1g0RzWKnEMga/Ux2oOmQBTvs0BDkwkNDMeezBM6NRBDKT6QL/8l3b3w938RUN12Osl6ca7X/Eu4tbAE3UaB4VTgdajpWl3Zor3RG0UNKD8q4bDP4d/XNqpXixaK8XyxUfFIylXdYTVukMHsZbvrF/xwn/6mQTwENyYX3WHVc/r83i3BYxprT0Q4fTfzttlWCsQrTS3w5CRLs/Rcvc+KVeu6M1cJgaZrf49x0O2+53h4dIU+HIWyo2IW66YjHm50c0MJ5cW2kMpfntiZE2BZyI6KkgOZO5kRZD0lycbTgiSymEiqEzyOS6pWF2kOgKLdWsf7S2llll3QzejRvb7NyE6dh6hK7U7Q7lkMdq4Ru5/FRT5dKUPyYmRHJgnM6FSTG+G7cuKgeuwB+mwtoZsaCRZDikNw==
*/