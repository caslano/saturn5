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
DL7rv3D8MJasGnm/JQgEaqtrLeYgMXQN78ATCAnzRsjmkMNNYpPFPRTem/iAoSr3tvUtznHetJx4KOWdBbbui60NBrzSbieJR74w44Jh+jR7kSwo2XZyZkKKBWT5OOqnq3Fbf8pHVmCKze2Shnmy/Bzh2q2ageIbKV9lTVQnAZ0h4xMmpQb1urN+0EjUMXCvOT8d5ZY/Ee0OKhwXRMAkq8TFYM0GjC8hFM9XawJbav3ooAQWpqpprME+cIsmo9ojiVK3I4iusaeGSDA8BjY2mQZBAq44KwR3KX0TB5b7cgbod9YvTiyL28ycb1sNrVRUbHpwtP5Xfn1yJbShMmmzDLv/FWG2kpuiP5+ZlzhWSVSh9mBgTjKE9+qs1Awu9NhWg0EoiWN3bcnJwkomQlCreqvoAawXa3wAklaBvhNaZVBu/xOjYRccWA57A8p6F966udy5yW2VUae8yxgqNhd7fEnf487whXeQ8P0SFZKjbBxSHyPpYeZt94m6qzoRUyD0Qb1eBrecIKkxCT63ni/65HxUXL1RrvWhm5XCtyzvuDa97foxA7JwwXUyMg==
*/