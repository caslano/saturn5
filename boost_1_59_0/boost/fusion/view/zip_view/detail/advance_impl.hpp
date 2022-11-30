/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_20061024_2021)
#define FUSION_ADVANCE_IMPL_20061024_2021

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        template<typename N>
        struct poly_advance
        {
            template<typename Sig>
            struct result;

            template<typename N1, typename It>
            struct result<poly_advance<N1>(It)>
            {
                typedef typename remove_reference<It>::type it;
                typedef typename result_of::advance<it,N>::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_advance(It)>::type
            operator()(const It& it) const
            {
                return fusion::advance<N>(it);
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<zip_view_iterator_tag>
        {
            template<typename It, typename N>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename It::iterators, detail::poly_advance<N> >::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_advance<N>()));
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
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
*/