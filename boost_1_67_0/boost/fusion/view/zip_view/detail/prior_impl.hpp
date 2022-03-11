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