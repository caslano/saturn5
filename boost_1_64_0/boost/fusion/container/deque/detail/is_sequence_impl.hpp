/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
b57SKqW7in6fTVKnQxoRiGj2g8bHVl8l/CUfcwOGKKLrJnU5rOyHNku516s2lb5+tovwomRa/TneSRuTazQqva+KzDlxbZirYJXThAqpUVS4uC4BbTBzB8iuyQembl0zSrODnEUaKQnSS7XpkWpj9YHntThcWH53JYue9KUzZf2tcYmlViAx2Lc0bXNqfV+h5oHf3HP7nmb4aOK0HdmchBPogS4P4aDqiVQpcCXCgaFHl0OhLVve8WazzehdzeDFDap8tgkUXYFm5/QEPaMPpd7MEvw6tgGhez3Igh0rvIywVAIhHXNhD2C2StiVqePCzOepTtwZL0u2N4vxIBSrzSeaIxhk9K7kTazexiceY1AJAuA25pHxxoXmaKtKnN3nGA78Y8ayFo+1rNpk9UgLNn5Rm420vJsOuEAQkxL91+M2tHPHNBTRRPMZDuXSVx1fAi1I1hty3UePl3cJCtEui8hSwK3cz2b86+IhLg4YvdivD9JFsDl/mtoZy+TS63vAl1D6/gYJNvzVUhTmGp0d+LiEWGebnfaqwuEiZ2l1E0qnrt+9c1abtPkvrQ==
*/