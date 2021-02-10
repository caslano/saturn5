/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05042005_1037)
#define FUSION_DEREF_IMPL_05042005_1037

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type element;

                typedef typename
                    mpl::if_<
                        is_const<vector>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.vec.at_impl(index());
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
NE1S/+koiWM4moodzkrPkPdNtzTOnhAxhRM5SaWs1QlvTdP5cpZHUWFGGstVJ6n8r2WUAnhsb5oMsjxJw2vp94kgCeI8KSyKHi9yYOTe45t8lu3jP6UpZ7NgNJWjL8HoLi7Oe5Em18iS/L6A8cWz0lOE2yiErvzHtPQpcOhZ4Ysb4NRw3gS3Ufziuf8VAGJUhhWNt7G/SwfULMxy8UKYFsihM33aDSWfjBHyUmTs3qKI7S3SKM4LG0JfzOU8Se8La5DzsRwur2kCWR7m0UgMk2QmYA1whCmMqY30psEO5MTEJuMGzARYIeFZ/ZhJUZNaEJzCtibx2ew+QKnlq8+tPnW6/d7Jb8ipYNGm6bv+KR14n6J4nNxmeKKKeTSDs1PCRMZAZlGe0YoVBf7Wbl+0zjvIYFong95l7a4uandi97U4PDg4qCOjzOS61h4fqZric5gj8pBN/WW/0wtsRx9b5/26GaD8HQl9n/qtTu9TDRhT8LHdPe1dNl7WEdjpEsRE4MvBFykX4QzkF/HfG0IsA+QicN4mk8mx/Wwa5dFcVj2H3ZDpTTg73vh2bNaltvQmicYbMJRpXFPDE6HIMLsXu8hrGhueUFi17fUNnCRuPcg9MJx4LfDNvTdw3Da91bw9PDoAvBBIlEk8uwdh
*/