/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09242011_1744)
#define BOOST_FUSION_END_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template <>
        struct end_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std::tuple_size<seq_type>::value;
                typedef std_tuple_iterator<Sequence, size> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
2Y/IktbG38jOJeuh/FFOtj3ZGj4vWUoDYyrZxWQryFLD0Vjgk9dTS3YK2SU+MZmswTEFOWKDR7H9C9nfkN1MdgdZireM42R76rKxPTFDNbYnikblNLBZYNVgNWBrwR4FWw+2AewQ2Jtg74G9D8Z5UbL2umK5YF3BhoONBJsENhVsKdhysMfAngT7Z7AXwA6BvQn2PtgpsL+DXQLr4VHsOo9iA8BuASsFKwObC1YJ9kOwlWC/Avs12L+C/RHsQ7A=
*/