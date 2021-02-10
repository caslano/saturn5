/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_0137)
#define FUSION_DEREF_IMPL_07162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<joint_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
P2DPp53BECpmM/QWYGdzcBMWhQ/8xzbAdeP3i5OTdt9onZ72jgadf7VJ4/XOxkZ4O7dQSJa7mJH/24DwdWpcdDt/GMPesHVK2x2QnZpUcdI5bQ8/n7flsvN2/6wzGHR6Xbn0w2mn+3Egl1wM2n35+/t+7+JcLkCE8vdh56ydRt5tJcsGn88Q0cYdmTvGAozBmAGDgtAMrf14gFABVoYjjIaqGKzR6XaGYsSq+n67dQxuE2rvwMeGpmOMbTDg/0VUStCMCcZ5vz04bx21s7B5g+7F2e/tPoU7RUsOdACRhzngWHWrPxBUogfQwaL8zwHG6pHhFNSV7y3mOliUPXpQtFoaZB7PUOoICoYxbCikQauxTlXOujU1XZTlrMuupssuE7Y909IrtDJn+FETob2Kqk8QMXufBu3eKcWI/sI19Vi53ufxnLfI4pT6Dlv99+00KzP1zYL63YL6l+p6VqmuS7GDR7h9yc6DxWXazGU/BgC6Q+O4NZR9GCuU/Apv1en3+pL3YaVCNAznte1C2TLOJUamlpJUj38kRVNDiqjMAxc3Oup1h+3ukIIFN+VxR6WGna/EqTYcsq4avma1WOKhJLhtkXaG/gJmTfBpEbD0H8LdeGT6Y0hkr13HM8e2C9kKmUAOiREbv9HAJwc8
*/