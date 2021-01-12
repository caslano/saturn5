/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::pos_type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return *i.pos;
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
O2doz35lbFRWCfPYbRrTLTKzJesSCtOWpBYBmu7r+NpqrT8PezG073PaQ9HT9Cmm4caNHpvAkI3BcGVj3dDGN9EWNA3/CdrD0ByWRtPWB4K2s0vbINqNN9HWz5Hewwzt7D0ZTZe9pVmMj8pO9bI8xtmI9uNtDY2KQLRHXELSNhjt6pfs0NaJ9npOWwHtYUTzthNtY0nyfUfTqBqINrwUp0m+K1ya0R4my/CKLo3l5a6X4TRZ
*/