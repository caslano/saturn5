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
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
*/