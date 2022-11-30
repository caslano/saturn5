/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_20060124_2006)
#define FUSION_NEXT_IMPL_20060124_2006

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;
    
    namespace detail
    {
        struct poly_next
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_next(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;

                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::next<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_next(It)>::type
            operator()(const It& it) const
            {
                return fusion::next(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct next_impl;

        template<>
        struct next_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef fusion::zip_view_iterator<
                    typename result_of::transform<typename Iterator::iterators, detail::poly_next>::type,
                    typename Iterator::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_next()));
                }
            };
        };
    }
}}

#endif

/* next_impl.hpp
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
*/