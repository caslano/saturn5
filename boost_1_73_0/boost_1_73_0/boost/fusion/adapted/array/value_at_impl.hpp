/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<po_array_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : remove_extent<Seq>
        {};
    };
}}}

#endif

/* value_at_impl.hpp
rG+QhtMvwt2zo5wQLEqmO1tbt7YAovyAyYvMfc2YxhLcY0/QjjUHO98b8NgAbnLMePDO9ZZnwkKH2Bbo5TVKKDmmoJ2ZhWorjUAIoLpgGe9vEzdvJNm6AXuD/27VOhR30NbUMzL33bJ390a+E7pjMLaYVA2/O7b54kOaLMPwJJ1HZ1E/kwl9UcOOph8K9qDL+a6r5WpxugqT5M15PLN07VUR165MXtlqQTZQal/fIFKqK5H5PdPfBOfztXfCC4Yu3KigqmMa/80bdTR0g6N+O5qa74Yuk1XN2+Zu/zu/yGu9mC3miRfYqwuS8I/gbDkPPb8uvG4jOQr9emdfYZmYMVaQKMZWeET/ePT5OrOC2zWGx4RGw63Mr5kt289UNYIjmE/tlWlluE0tXoRd5jQso0fTr0e4WZQ/Hs87n7cGdndgaXTpvvD+9fxCuGqD90E0D15H82h9gRbs2UE7+Spcn69ieh/Mz0NvxQ0uYe0iheninU/3Ja+Dk3QYbBqsTs/PwnhNonBcxIgZZnGFTbUbOAqEMOpeHUAdzlEpBmY6NFYgrxiqF3a9KLAa/390YxslYUjBPFngAnu9etgC7AcaAWFo+L3j2SKOw9l6uOF6FfofuN+4+A9QSwMECgAAAAgALWdKUtsR+Y9eBQAA
*/