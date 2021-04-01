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
FIFWfFRwNHu3Aa/cU8GbcivgUiU0Vuwy2o28IT1LMmauXMm5WVxoA2NzvqCw3HcL5Tt5ptskDXbftaO/8oT9xd5JhmKkWlOE+33LTWl7wc73UUwGYD5j7At0eoos0s+JNXgtcRot5C9dpvRdplmu8owv8pe7t5Dra+/HEr/Pafl68foEb7DZ1eOdrlMbqo/a80nJWABtRhz9d8W36K6M3GEpIjPBjrLvh7gvuDN1FAgzliH0BHvo3zcAICmI/ENzhjcObq37YKVyi8Bg6a+qaAHOs9QkanFUS9c9UChh4af1Dqqph1S6dYMNXseLg19m/9x1dTA+Fj2iXRy++DkF4BjVxHnSPKociCwdxfLXwowDEg/HHcXMky6hLJgsODIu/KR3xfnKmAlHuH51ik+6HyJOlwqMLtXQdbmKGUs1m/iV+eZ9UQYTY0gxgqiIRbqAt0bpSHXOsbPaz1rsgjagiSUTGMJ9wTIMIEhA1EOcza7ts6VtXkB6ofyOU9QxPN6f++Qr9gpdug9VKSo6fw5c6rXhw7fEvZJw9KtZW0eO+E13W+FD2Ofq2cdnwQ==
*/