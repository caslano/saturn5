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
z0u9hRs8h3NfjhfM14xFOJEhsM8sSQvm82apeZGfNL/ycMSXTZg/0dlprEwfTGrxTM1cX7lroJSGq2MP58f9d2g7LJ0nQNKbDJ6/v8gHg4LtpfMWN0kwyd8wXnTTrvKmiPZy/cwbbZONBPEBgoXndc6jDefr6L8lZobj4HpeiK+LYE6B+dfs34NnBcMCHmSXx0H9Hv783F7uQY/nJF2yB9NP8E+rML640P2lE6SQjoCZY788L8/KtArOs+eT7IoXpiBbD16vUnaUG3edP82UDNjyqKK0UYX5LdxvQP6/DOebZlkx8tzzZX93eZQgeG/ymJyv83yrStmUSnrKtgr7fc3/9Yq0h0OXmL+9iJ+Kk3/cTERNDDpn3Licz5zq9iCrS/8+6BZjIV5GzneIrl1jkcUDO3raD88e7OVp3pR/sv/SpfXOeYGjzh4xCLMFc/tG1y0zb+haGOU92X/x35nvGjtOFYRMXI5PxC/AG3KHwok/WGPW+2PXbvIMevmAcBB1l/dH/oE5cDDunPgST4melMfAP4Czj6wtuYYhkw8MJ/xhi94fUQc9ueTbS/1doTeOd0BMmM8PhUkDXmGihE0ZQPTBrl1odMYLRQ5VssLuDs/312zrvawGmTH8l1n+0BSeEQ5yCUQGszHQFV6vV7RzojDB8JtfFGbuQftqvAAZuFk72Wb2t5DntckieR7LdLw/vIxG56/QifB8HtCI
*/