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
6tgD5p5uGHs5MWzWzfaPcN1g5y2EyTk1h144U352aqzWexxh0Crt0FLB4eP7e/VUyveonm4s8TnmHWkZZjV+YnzczmIb8wfKy7jG6zE7TxyYQVLDVQcp1/AcuzcLo9AOs0ph0dJZv+tpnLarJChgLElcA7UR0vpdpO9hbVIVXgNV03dxbvV+wPK2kOGth8R30gatWsPcAYxD0B/NGwaCJ4QCsyLPcr/maV8jR6ttpijUZh8r
*/