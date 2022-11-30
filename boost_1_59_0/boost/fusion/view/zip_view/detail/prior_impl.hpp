/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_20060124_2006)
#define FUSION_PRIOR_IMPL_20060124_2006

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/iterator/prior.hpp>
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
        struct poly_prior
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_prior(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;
                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::prior<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_prior(It)>::type
            operator()(const It& it) const
            {
                return fusion::prior(it);
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
        struct prior_impl;

        template<>
        struct prior_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Iterator::iterators, detail::poly_prior>::type,
                    typename Iterator::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& it)

                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_prior()));
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
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
*/