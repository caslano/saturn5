/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_05042005_0741)
#define FUSION_AT_IMPL_05042005_0741

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename value_at_impl<vector_tag>::template apply<Sequence, N>::type element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    BOOST_STATIC_ASSERT((N::value < Sequence::size::value));
                    return v.at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply <Sequence const, N>
            {
                typedef typename value_at_impl<vector_tag>::template apply<Sequence, N>::type element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& v)
                {
                    BOOST_STATIC_ASSERT((N::value < Sequence::size::value));
                    return v.at_impl(N());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
9uAw8k3c0luI++1DryvjlmbtP26LamJL73P5tpFAPeowfGzNJ85QIkSi4W8obNM+kxbKqU7IsHUm4sscmTa9a9WYMu4cZwmdVRcz+TTkDvE4klEdX9AAEizt01aJ588Wn0VhbGDzZyCrfqL89bmQUY3xrWDjWK/WRFTueObdiMoGejSASCx2Uh3GwPLn1KmOK9+1UnC7UZu6Yi8Z/vyyjpygGNZeL/XcIe1vYNh3FVjO/I4nx6KRb63y10pEugS05U3/4hiKnmuVWx62mIIt8OWYL0CBWs7VFTjkNbGF4jpLyVj+iekrdUxfqQJ9pR70lX205apQXym5kro5+x0rxK3igs2/c/Q51MM/wN2Pz0ig3/eZTmeauGuVKC8G3dHJE/wdyUyvWghzBNTs3kHy79nyfFum/NcwOe6UAZ2HebsxBWXypyQHyqCvK4vYCNSP0l+H6hbU+DbDU67OlmfbWN3h1omzodaJs6oXiz8MIYPTHsYqrlr8N9uai+7p5t0BJhAfflNcR06q0mT8W/JTw4MsmrCHYeemU+x+sFImkj0iY9RN4QJdCcOS768UWKLkTD6dw121j2fLdxUJ9FjLPiJVVB2xawE9CNNBVNqHm0CiPYZh0NgGXGukqpcTDVljItWkktWzRklcQqoJq/HVtzXiNH4NVXoYK+UE1pK3Bq0FNUBgcwWBtXMCy/aHEoU2UkZcF77OqkLi2h1p
*/