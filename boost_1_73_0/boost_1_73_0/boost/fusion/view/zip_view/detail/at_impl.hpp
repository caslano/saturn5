/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_20060124_1933)
#define FUSION_AT_IMPL_20060124_1933

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace fusion 
{
    struct zip_view_tag;

    namespace detail
    {
        template<typename N>
        struct poly_at
        {
            template<typename T>
            struct result;

            template<typename N1, typename SeqRef>
            struct result<poly_at<N1>(SeqRef)>
                : mpl::eval_if<is_same<SeqRef, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::at<typename remove_reference<SeqRef>::type, N> >
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_at(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::at<N>(seq);
            }

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_at(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::at<N>(seq);
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
        struct at_impl;

        template<>
        struct at_impl<zip_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<
                    typename Seq::sequences, detail::poly_at<N> >::type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& seq)
                {
                    return type(
                        fusion::transform(seq.sequences_, detail::poly_at<N>()));
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
4YtXwLHR5MXldBRMryfo1KY7aFgVPPKcQOuxBaUmkDhnW1SDW7lLILJsK2h+EmCLTm44G2q7WGU7HnAfCOXglIWetx1oH+w5T3O00dIl7V/Mz+lBjyqKnSZ6CvUMSOnEZ3m3sNKWwDuPbAPkexyfAFG7+bBDDx/Sg90nQ/zT2a2ETY0ZgHnJh7CNYP8030BKszvG/6XxSs50EW9ZmxNf7Jjf0XINYo/JcP+75uyzaWX90uBu0Z3p1MgeiiQx9p6BdoF5f0zm7Oj5h6K/kQAczeyC2tJNtBlfnF8G1y8no+HZdHg+si7Z3bcNgBxXTBqC1vH8EclSb2FVGNa78Xuezcr5VprdkWmf7Bs6tQQxJDXMwJrRgOy/jo7/XS90eSUr8g0vwvVviTrQfmiP9ugxmh31H4kksgsdm2H2x75QwVwsGXqf09W57am3Hhodvi3WmcTj6eXpdwwJo+H3PkOtZ+g368+lSV3L2GZ5aob8Swdp+5fooJHdRBuh+Sde+71V48wuBgfytoER/miPKvUeAijYxDLZY+Sm49m6nJP0vgYC90UU7VxGVRJtMoJzbynSdV2STd8Rm9oOpqgbAFv/G+W/WZxU0XMDBp0kesX5aFOPuwkmxeXOdskOmA9zFUUydXwGPmzjAAKmOrO+
*/