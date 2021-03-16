/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_0137)
#define FUSION_DEREF_IMPL_07162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<joint_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
+Fqf/eg2G3djZOznVWhox/FYFiSvPtObdAm01fSm88n2uXZb387HHT1azAaNP0RVCwMSazeaSlOpZNojshqO2skKxPzSOTfwExfI/Xn0xCWaA11xvpRjt2pi1zFhPVnYL6jFurXup4wFCmaoCrfXxK/65xi6R9KzILZri7Qab/omVgu8CTfsHkE3DbEtO0m5jTjnO0acJ+n6r6xU9Zx+Q+epb3U71dbKdqloC0VFG0Yv3JqMOpjNl3R9g9VG/Us=
*/