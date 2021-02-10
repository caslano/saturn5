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
2drZpaFNl6ckosjizwr1gdWUhiGNNVkhjUT6qKAF8gIQDpyTrAATcFrS+fDVdPSs1aoXWOtnTP7yO4A7xyCI4czvrd3Mnb65OH255QuwYWFUOtfwx6HFYpvRZp2Gca5TXRryum1wGWKh/qhUJC7zAe82bOZlGnJps4rNc18VUJJDRJPRZR5KewClM1cFSrT15Jpe/KKhx0RKrlmoLYh3Mogj6dyciSKMvYFsLQNgs4eMQpSiUq4ryaANp89snYqlDHJopIyrNXEuRXRoxFxW2lSVZ+tMu+PqllOjTz/GYA+fWETdgdkePxDQYlkXXGuFbQowFhd2fAUshAxQxeZzrKXFHnG9bKbng4FpRbLgBs42GzYcrKkhRwF5lmTKLNM5UsS3KLDLXC1KMOTeJXMJwolSZkyNt1gA+3aEWjm9fvHmYvj9KJgEJ73965/D13xw78OnkG4OmDQkwhCgAfyHN+hCF9KlbHVqeHY2caeYFvvXyZojDzKd8kHKS4BR35V91jBXS5ErlDc4q5uq2yZdo5cSvYS6tdZOxA2Cy7jma4+v6zbDeW/H5WgIQx9Bg1YTF6rMoO6dXLkHPlrvbWo3Hw5egAxAnLosCgvy0YcBwcQu/6QD3ZVQReZQbL+OQtFzunj96tWzLdwIzsbT
*/