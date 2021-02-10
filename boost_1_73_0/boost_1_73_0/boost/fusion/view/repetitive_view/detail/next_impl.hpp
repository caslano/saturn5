/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_NEXT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_NEXT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator, 
                bool Last = result_of::equal_to<typename Iterator::end_type,
                    typename result_of::next<
                        typename Iterator::pos_type
                    >::type>::value > 
            struct apply_nonempty // <Iterator,false>
            {
                // advanvce to next position

                typedef repetitive_view_iterator<
                    typename Iterator::sequence_type,
                    typename result_of::next<typename Iterator::pos_type>::type
                    >
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i.seq, next(i.pos));
                }
            };
            template <typename Iterator>
            struct apply_nonempty<Iterator,true>
            {
                // reset to beginning

                typedef repetitive_view_iterator<
                    typename Iterator::sequence_type,
                    typename Iterator::first_type
                    > 
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i.seq);
                }    
            };

            template <typename Iterator,
                bool Empty = result_of::equal_to<typename Iterator::end_type,
                    typename Iterator::pos_type>::value >
            struct apply // <Iterator,false>
                : apply_nonempty<Iterator>
            { };

            template <typename Iterator>
            struct apply<Iterator,true>
            {
                // eps^n = eps

                typedef Iterator type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i);
                }
            };
        };
    }
}}

#endif


/* next_impl.hpp
zfcbaa+3350b7ZkwmmaD7xfj7mzo0ZbLN9xn4wO4qoY/0SHvsai4xZot/vkgbm3Ntr9Exkh4lY1Fll38F4lnFjL8f3gJXUR69OYZBq7kCVBLAwQKAAAACAAtZ0pSjiDmw+cJAAC+IAAAFgAJAGN1cmwtbWFzdGVyL2xpYi9oYXNoLmNVVAUAAbZIJGDFWW1v2zgS/u5fMU2xhR0rcdKih906LrabdtvginbRpLco2p5BS3TEiywJEpXEveS/38yQlChbdtK7Yk9BbIniDIfz8swMPdr9cVcPduHOa8r/U7zwmyn+KLJ/yVB3z55Ob8D8IdUX/L5rkRE0JDfTAdxNcgN9JpnaVY7ofjq9a6EvJBt9jIjyy5RucQTJiPI4y5eFOo819I8HcPjLLz/DHjw+eHwQwEuRKpnAqZbpTBbnARxFPPJrLK6v90v5PACpQST7ltVZrEoos7m+EoUEvE9UKNNSRiBKiGQZFmqGDyoFHUuYq0TC8fs/Pp28ex3AVazCmJgsswrKOKuSCGJxKaGQoVSXhkcuCg3ZHMmReaRKjQwrrbJ0H9eWoGWxKIkHLS+SMgNxKVQiZriQ0BBrnZfPRqOwKhKUfhRlYTkK3fb3Y72od/IJhViIJWS5Bp1BVcoAaGYAiyxSc/pGheBg
*/