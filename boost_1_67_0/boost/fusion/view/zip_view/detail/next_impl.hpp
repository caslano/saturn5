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