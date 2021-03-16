/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07202005_0856)
#define FUSION_NEXT_IMPL_07202005_0856

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct next_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename prior_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
PwkU+72ngcI9qCY4jwF9FujvgD4P9DmgL1jssORFoHss8hDq7LPQCTc798Xrw/r6H0D/aLGT31eBDgL6nxbvNgCB7RQABcFPuw5ABXGu8fF73ODj90D5gO+NihmOaFgxwxB7j2SsUrClgoUFu0uwuwV7WLBHBfuDYC8L9mfB9gr2nWBHBENFlbE+lsGyBcsRbKZg1wl2q2C3CXanYK5g23x8HHGaekKHoHw+KZ/PpPu7YIcFSzABzv2vEmOue2M=
*/