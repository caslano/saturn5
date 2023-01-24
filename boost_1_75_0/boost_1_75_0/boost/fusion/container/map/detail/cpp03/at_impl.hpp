/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get_data().at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get_data().at_impl(N());
                }
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

/* at_impl.hpp
/vtxhnqaZ4iojfA5AlnWYCWelHYGwuSzbVwkIIw5ukkkNw7jBWgqLt3CpUc1v5CTo0xnVbxpETP5oYFSNDuj4KivIIrvnAZ1Z2IFV7k3l8P4wfxK3wxIRi26RqoQ+MLv6qRCgErDl52yG9qJLJMsSLq4MUjZxd6CwclbMTiWi8Fv9PULfR2gr69zWU6HPj/lz3X0uYY/P6TP96noQgpeocgX6WsWfG1Xn6avEkqbQl+P0Fchfd1DX/+ir9H0NYK+vPQ1iL760VcaffWir0sZpgvpszN/OukzgT8t9HlqNAZHKGikYVHp65tbEOIv6WsHpW2jr3X0tYa+ltBXNX29TcF8inxpNDU4iz6fHm2iqQ1zD69UG7cjQU/nKAdZdiD0mrS8jyShWSjiCMoJtEMZAODilH8Xb/H23ONeAbuDs8YBKoeJ7p71RQ5v9DrQOGws31KUrwxzADkxHP5kwp/e8KeboC6K+m8uhe3SZr6CpIlWq4IgE02JSHZ8R79hR2r8IrNSgY/GbRQJa7axjiCa3YAQNQdLgieAhuKCRyyyD5VnLwEv+cGNeokdB85aAriywWf1El+cuUScKAGv9413U/b8b8+YPdFZM9iRX4nP7sGPTwMDCUr5zlzKBVbucOcY7VCrxeU0+JQoKo6fHPCXgI9wbWb8raE/lf7BCSJN8Ucw6r9Jv/WmHbdHsCc0YRguvHuHGXpBxrq7aLF5
*/