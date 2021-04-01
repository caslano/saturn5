/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0830)
#define FUSION_REPLACE_08182005_0830

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct replace
        {
            typedef transform_view<Sequence, detail::replacer<T> > type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace<Sequence const, T>::type
        >::type
    replace(Sequence const& seq, T const& old_value, T const& new_value)
    {
        typedef typename result_of::replace<Sequence const, T>::type result;
        detail::replacer<T> f(old_value, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace.hpp
3cvXvzIXujFTF0X3+aE7KzvGXRhDV9QXKFo9jVKdpAGyNwQbdH6LiNgJQzgA5btPVK1eVYy/z0V/ZQVvAI/qwPZzOIiWltxiXNz5NaaS/r77+IdX5fznH2uG3xq+xe/Ez1+d4qRDpiGqWS40j9mIZhxespPe/vDmGF5hCEA+aIKmZfxBEy2dyxFEDvNBua9K1Dm9y/xySNK6QAiOasYI63vKF214uj6aCI7K4g31nxdFznbiAv2e0l2LehSaDL1UAVs3bHj/uKGQ67aBGczxxjqSj8GqmejTbwqtuVmuRBDIqMfRYBCYL2rXuO9PHLu7jaoXKpIVaj5x7Q9+Ro0WuQ6iAfl0dgva0+bFiglY+P9v5BSB0aKcqJmc056WOKAkVzrI3Xhz6bJWBNSpCEzlPegyuml4wZ69kju0ZBkA7BI2F8OZJ/kUWM55ZE70ywKzwfxgfqRgoDjtH478JmRtFBTZQs3XJWUAzz33e2wz0yhBZHbA1IWVJvxyS7TwuF/660M6pGJR1CxNlLwxq9ARa0cCbU3RpMi/aL9BrCZXVSpx3VyM//a2rtL+rg==
*/