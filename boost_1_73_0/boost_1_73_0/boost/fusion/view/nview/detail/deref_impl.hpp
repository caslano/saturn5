/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_DEREF_IMPL_SEP_24_2009_0818AM)
#define BOOST_FUSION_NVIEW_DEREF_IMPL_SEP_24_2009_0818AM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<nview_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::value_of<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return at<index>(i.seq.seq);
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
r8TtiE7tVzLs++C5+dwIIX2P4mjJYNPuyK9QenE0MBiaZawtQrLedFUcLRqcSssmKCRIb8RZ9Sv7SXONKLP6AUkzKOlufkw/zKif7e4qca8AMpNXXOzON+xIG7TmH7sHNy5Ec8DIa6g4quD6B+m+TaWxr1fQ3GQeD3Vpc12G7BL3Tkrk7rLdexHVJWc0egeSQ7OxquuVVoLN4gJWe1FjwcX6jlg106IyVG4JrSx72ACe0gBpDjXbO6kEdGPktTI=
*/