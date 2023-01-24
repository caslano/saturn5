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
G4JpYPn9AL9ShyvUt8N64k/WYX4u/sR0UbJ+dF6xQ16Pejhx7iCPG85W9AuWZJLdcr84HYK1vLj98v6q43SaEdK9kY3iMPdDEE/P+nxwOq1+71wPi4X/iu0m4nR9n/W2MF6ACkcvL5Xs1XJZj37Q6YiA6kOfnpgE63tYXMkIL8p75Pn2SZ9ID4Gtmvs5K+lEMyLR381cBjoRmdWevz+q5HTpTDoRtr9m9Z51qtijLeDcmbTudjl/vf5Xhvt7jBpvFLFwXogX1iD/7HXN552v1waYh1V365zH4korOgD/lDnfdGHDb7dfzjPzqgp9Kh7KHO7/QJ9S6YBP0Nxp5iDGap3rwYbSBpkPKvhn/77za8yfAq1ERmyLUfIVWbxK7yCdbOgm+uWdf5nD/T2b7hucTXTDbrorw93zTvLwyA8ZJdrIEzVHAGjDRfYVDthdZyavN2IPmvBELGqjnA3yxWNmkz3By/tCt88pH+hBNB35A9imOM+eWuFocVD008uuks3K9T1+M7vsXm7fD9tLeCRAd+yKzWbFjfDk5PIxRcasdSAXzJ/Y6f5uYU6TPahTtIqcm7v9cHW4l0Ws5NNxPzzfgG5Q9N+gOzxGpWizv6zH/XYWlopmpf2ojueFvaZQDNvI/+P95+8Pnmb8IToKSnkyJz4bFgu6ZT2Fmbiv0M3J5SNf76iylO6/6SvnZQrXK3hKevNqRefLRT7Quc2R
*/