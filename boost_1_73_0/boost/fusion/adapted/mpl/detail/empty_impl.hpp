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
vo8040fVgvIi0159SuwM9DmjwC2RAcgU/j1qBc074FaxE/InsfusV33SfR3C6h6XMGWx1zsqA1OvqY7LnjxVieZ7Tx51TROPV+Tr/lSEE/tS1midMX7swjwLg8VNU/ONqfi2ZFO1t0ju42dfJmFpSbz2Y/fjB3199drRePiWlvfrMqbdIE38mFXuulah2GlktdX4XS7md3xZ+NebOJ2IzCcnXoV8hey3ztd9Sei3dPIDmvex
*/