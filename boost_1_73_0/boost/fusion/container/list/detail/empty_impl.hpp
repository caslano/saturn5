/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/fusion/container/list/nil.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    struct nil_;

    template <typename Car, typename Cdr>
    struct cons;

    namespace extension
    {
        template <typename Tag>
        struct empty_impl;

        template <>
        struct empty_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
                : boost::is_convertible<Sequence, nil_>
            {};
        };
    }
}}

#endif

/* empty_impl.hpp
tE19DpA2K3Ztht6q7WM+8ZLhVWrPNdpOrtX7zA1wC/g1LIDL4LYab6zG2xP+AifBt+C+sAGWwLdhOXwXVsL34HT4ITwcLoVHwY/gMfBjeCz8Eh4Pb4Inw5vhWfBWeA68DV4Ib4eXwDvhZfAueCVcoPVzr9bPg1o/D8EX4P3wFQ1/XcMb4MNwKXwOfgqfh1/CF+C38EXoVeYrMAm+CtvDl2Gqhq+p4ZnwNdgdvg57wkfgpnAR
*/