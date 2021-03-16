/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::pos_type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return *i.pos;
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
XOKcfgBgBjMszMCMl/I8T8L3xMrAuhiusWXwKZHCuNHpDjQEFOshrD/xQvnEC6labxSsQrCVgq0W7F7BHhTsB8GgFjTWZatqloqJxykNLc0bLBRdR1/BbxycsrcA9EL3oO2m67XL6PCJDR2hM0EnjG2p8cq8Gs9wxbtzFMaHemKrVJl1D8MjaPuQOEZBq4FzlCIncBecjEfYoP7EbJKjempBlUPXU0hA4UgZz8kxPhhinDOertE4fzxdX6xieyc=
*/