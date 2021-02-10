/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEGMENTED_03202006_0015)
#define FUSION_IS_SEGMENTED_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion 
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::false_
            {};
        };

        template <>
        struct is_segmented_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_segmented {};
        };

        template <>
        struct is_segmented_impl<iterator_range_tag>;
    }

    namespace traits
    {
        template <typename Sequence>
        struct is_segmented
          : mpl::bool_<
                (bool)extension::is_segmented_impl<typename traits::tag_of<Sequence>::type>::
                    template apply<Sequence>::type::value
            >
        {
        };
    }
}}

#endif

/* is_segmented.hpp
Y1VUBQABtkgkYO09a3Mbt67f/StodyaWXMVOer60dpMcx1YS3zp2xlZOb6btaFYSZe3xaldndxXFqfPfLx7kEtyHHqnTez9cdRpbuyQAggAIgiB8sPdwny21p1Z++vR/Hz7wk3q8S5N/62Fe37rfv1f8H/T6HX6uQnKgXJf7flut7nKvWtSlb7D8jL/3+6sQ/Y604T8H2PP3Pv4KT6Ab9jxJZndpeDPJVeukrZ7+9NOP6rH64ckPTzrqNIhDHanrXMcDnd501M8jevLPSfDp036mn3eUzlUQ7RtQvUmYqSwZ54sg1Qp+j8KhjjM9UkGmRjobpuEAvoSxyidajcNIq5PLdx/OLl531GISDicI5C6Zq2ySzKORmgQftUr1UIcfGcYsSHOVjKE7AB+FWQ4A53mYxPuAW6tcp9MMYSD6IMoSFXwMwigYAKIgV5M8n2WHBwfDeRoB9QejZJgdDO3w9yf5tBjJByBiGtypZJarPFHzTHcUtuyoaTIKx/gTGAIPZ/NBFGaTjqMGUMWjgyRVmY4ihAX9Qp0x2VpdG/Z0sJmaAcVhjj+yJM4Q1WKSTL2GwEeEMp6nMSACPkCjUQJs7qh5PNIpNaaRWxSGp8Tgxqlx9I5UEgMxauf4Wp1d76hBkIVZR/161ntz+b6n
*/