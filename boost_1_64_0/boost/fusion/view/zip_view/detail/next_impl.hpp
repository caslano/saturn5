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
YQo0oXeqvp7KdL1gd7bXJhpXUcQO+7WHwN0zCGBwa65J0SuhFWhVyz1UmIikkMYzoW9kAc3WWK/wBV9mveU1MifI0SLyF3HdZkUaxX9B+R1Ve0in4zqSpbAhurZ0vqW8MFf47gq50230XRK8+/a0JTAv0dXBdl7wEsIY8Tm2A4c2W5ncBbUC8C79HIFMFXfbmOo0lgTSXIjZt8xVhLmCa7I90Gq2ZOFggTj8CjOgXO7JCLhjdrFyVaXnr8fo2x3NxQUfZu3QFRoabcL6wmwiZtCgegIdAJn3eynd+Qtq581yu0/kbKQ0SEfFfwIDgyKYFsfscecyIvzcIy4wOo0d0aJHdaoz1qv+qFdviFHwZdgnjreRdPm7pdsxHAp4ohJvYF+Zd0Vnwr5LOE7nb8ynnVZnitggl92AnIB7AUQUiBQC8WdUm1NT95pzYAeXdh1iILelCumn6FSpAlhQ+qjg1FUPNqK1eXTbgnMDQd/wum+U87gp4dsNQh6Uz0Ct82K20++TBnHY7iaQ7NILkwOBCUrutFlBb+Dk6FB6yCYSeRlPLhJgzewUWEbOGg==
*/