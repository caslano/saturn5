/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_07162005_0749)
#define FUSION_PUSH_FRONT_07162005_0749

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct push_front
        {
            typedef fusion::single_view<typename detail::as_fusion_element<T>::type> single_view;
            typedef joint_view<single_view const, Sequence> type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_front<Sequence const, T>
        >::type
    push_front(Sequence const& seq, T const& x)
    {
        typedef typename result_of::push_front<Sequence const, T> push_front;
        typedef typename push_front::single_view single_view; 
        typedef typename push_front::type result; 
        single_view x_(x);
        return result(x_, seq);
    }
}}

#endif


/* push_front.hpp
lxiMFrHPEJEiuGlDIdv+tBr5KO5DaYM/vSzXYx1YN/YefiO9N5WAVbdxd08VH6r7VF7/aip+sM5TvdeK/vGIx/XqGPtox1AOGEPrVby6XsUnLSWcvG3guroViJN5HCemkqVck6PFyw8nYngUDe3xRBTNQSF7zFDQUDSGZ6tI4NkqFEw1XiT3dCdva1/7KQI9ZuVXxBRC1AezKPZvllcZ5YvDHmUxBU/fj/aAJ047mFUcVJmLVbwQAano+eq4QM8sHXoOuRh5A3oKFfSMHf3fo6f6Bm/oMTwnkHLhWULKq0WIlHlFav4zja2aZOLgN2qUXW0Vbs4ge7zLPH2ERqHseEBNiAMSf7sAlPhfNKHEv3wvSvyndpJCGRWl/w4jhTKcuMw3jdAmkgm8h1Q32RgfhuvgKFLdZKuqm2xL0oZliPxvRC7YXcFkS7FjXiDaFi79JwZ9whHxXwTrtKpcf+ZWPHSBtmBtjhUddp2oQ68byaC0rCezlk65WsElnRyLdID7fbwSpKhVU0VsH6lVS0YKtWqPYK0+W5sVwvBbM49ZITq7ZYUwq/kgMKsgNZJa9RCvJssg7zCS1Kq0CdWnpRMuqauCSEEKDbZoVZXZFCsC4v5f3fqTVxHFdGD81h0XQFtAE0FCjTRt/uJXtCWSqGgPHpzfWioC0BtxP+6c5TNXKJggVYzEt9w5IyhmvECbJARf5YERjalQ+ZYcGDAq
*/