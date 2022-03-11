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