/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05062005_0905)
#define FUSION_DEREF_IMPL_05062005_0905

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<filter_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
+EiBDxPh8nBhXmPcuGIfAfRecRwrvkfBGwkUZSwaaIL4HuVpFNAcoOC1WB8Cmgj0eaDjRZicDPRloClAyZkCuhtoOtADQKcCRd07DegZoPcDvQB0OlDc48l042F0FlBMtmUDRd2C5/k/6q49uorq6p8zk0AgCbnBABFQAiSCigimIGCrBIHe8FaRN4RHgjxCCMkNRkW8kMQCV6wVqxX9XOpn+RSxYn0UsEux8QFdCpQPFQUxPheISmyVD1dVvv0=
*/