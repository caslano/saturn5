/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_10022005_1720)
#define FUSION_PUSH_FRONT_10022005_1720

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_front_impl;

    template <>
    struct push_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_front<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_front.hpp
p+qCPEn3vt277F6Ag90bV3BsDGDgRW0IV9UFAc2mT+MABw0+XA7etS9pTJhUy0yWFuj5guAMMfQQxwLVC/QXR9ZiB8MI95+No30tOh09BNCwjGy8ap458NZJcFz8mz3P3D8+PkNwNsmMzWfwPUAo5pJn2o4c2Pr/c8VnNF4FAqv2WMmpdbhNlFIcD2+6TVrOae1i0C97dEHo/VDkMpML8KnRRFWLAas3Q5f9DgyNmfVLsnSDIaH8iTXQxK76rrVzV629RyPJosa2nauxKnZrttNgZUNVg1a2O6eMeiCuXnIHGEP/b70pWnozotVKziLwBOMHJjaU2ivx669if06/M/qd0+9pjVni0WPFknHskza7Cy7Zgx2YJi8KjMuCUCC7hP3QyWbFpsxdmEUch04ewE0F+tPIuU+zW+H4ORXfO5N/30SZZH8VxLgIV+kmITpXjK2HQmTlJ5qrPTusRjohFyv9DqtCzqnYWexkiZJzBX43sjSs9D5Milx1YyBsX4KiZJStzvZKdtfcPjGmUm6fWZMrsw+NbTQ9U8B3MACL+AmnxSaMBSsbBQrvBAZjgVVwnQX6mK5AqmHk9+3LkeHkCitbgWo4WT1iNm4ht+Zq4+ONhL3CIQ6s1D+gML7EuD067SST0E+lM4CJ5OGA
*/