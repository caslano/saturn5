/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_SIZE_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_SIZE_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<iterator_range_tag>
        {
            template <typename Seq>
            struct apply
              : result_of::distance<
                    typename Seq::begin_type,
                    typename Seq::end_type
                >
            {};
        };
    }
}}

#endif


/* size_impl.hpp
PsT2yFLizPXaqumcKsuNprKtSvRl3OkMByIhCQ1FMARoRW3y3+/ZBUlRsRTfS5RJRAHYF+zLs7vMMz1PYzUXbwa9y8Ek7N9NRuFVMA7fHD3Dsk7Vnp3O2df7HIkz8eQn5L8hPvhminFu/lCR2386DD8K/wdUv+P7KSEdsSX5GJ6Kp0k+ihMmCUspP9BzGD4l6HfSjf7pEOXvIT1iBWRE2TfZJteLpRMn/VPx8rvvvhXn4uLFxcuWuJSpVomYOpXOVL5oiR9iXvnnUn740Lbqx5ZQTsikXbIKltoKa+ZuLXMl8JzoSKVWxUJaESsb5XqGHzoVbqnEXCdK9G/H98Obn1tivdTRkphsTCHs0hRJLJbyQYlcRUo/eB6ZzJ0wc5CDeaytA8PCaZO2IVsJp/KVJR4kXibWCPkgdSJnECSdWDqX2e87najIE2jfiU1kO1F1/fbSreqb3EOJldwIkznhjCisagk62RIrE+s5fcMgWMyKWaLtsrXVBqLSuGNyYVWSEC/QaWW92kpMS/O06JjIoLF29GVNaknUemlWOwdhR+IyL/IUgmAHHIoNzNwSBZIo58N880pEaVM28EHXbPWNhUmhjDjuTcVweixm0mrbEm+HwZvbu0C87U0mvZvgXtxeid7NPTH7ZXhzCddr
*/