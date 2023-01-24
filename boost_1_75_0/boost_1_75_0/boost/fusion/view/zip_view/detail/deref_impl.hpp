/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_20061024_1959)
#define FUSION_DEREF_IMPL_20061024_1959

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/container/vector/convert.hpp>
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
        struct poly_deref
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_deref(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;

                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::deref<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_deref(It)>::type
            operator()(const It& it) const
            {
                return fusion::deref(it);
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
        struct deref_impl;

        template<>
        struct deref_impl<zip_view_iterator_tag>
        {
            template<typename It>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<typename It::iterators, detail::poly_deref>::type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_deref()));
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
n5qv1ysHA4IO5KHjQU85Jo/OnneHpkcj5P2Ii+JKUPz4Pue8xS3cr2GmLnAmRDFLLPICl4t8uyywu37PerejDlBa5F9AUFJthwFov6yH1cMLND+D/RezRMJW5enU/Cw+Krnb8bKecfSePXDej3PKe6W3C1OWZ2aCoxwu+2EGzyKMsG/D2AB6n2/KGBhjQ7XOMwew6Pl6nMkqPCuvDGPpjNQB7VLq9pBpACXJ01bZeq38pE0SnEyt5CeHMJ80+WwYw+k7hI9su7y/Vv/qigln+Iz3O8nnTKq54WGeYJrOlK3XKWppjtxhEUZizbrToHzNxlnLVoIImV553k2nyR198AA533nin2EDI9+ODXM1M5dvOPJ4SNXrdt3kt5rPiHyEZ11UuvPcvzlbr9c7aKORL4q1M/6A/o/puL9GzMDYCwNRfj/G4x1iIag+bsd9I59Th+tRXTANxJaEzEK+nqdyEe9X8vkdX85aZQtnxir5xn0ssor5foBEd9/FLahhn/wlSxjVOcv+wsZDHhZEZneRD9+li0k3gInNRl543myvT2sVxU7KXJHNP9db9Wa3MKKsCeNVisNeGh3NXHh3KReKVnN7SaaRWmUXMCZ4XoyneLl3mNPE55DX5vad58/oozLcJTRHdcRbTXje06x3Cr/9Gn0YZ0Dl6ZRvVwxGVhQP1PPfxjAq293uW9ThKer0BnGbTvlK6apJXh+1IvON
*/