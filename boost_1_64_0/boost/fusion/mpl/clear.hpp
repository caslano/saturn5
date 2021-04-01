/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_10022005_1817)
#define FUSION_CLEAR_10022005_1817

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/mpl/detail/clear.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct clear_impl;

    template <>
    struct clear_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {            
            typedef typename 
                fusion::detail::clear<typename fusion::detail::tag_of<Sequence>::type>::type 
            type;
        };
    };
}}

#endif


/* clear.hpp
CQkIQz9hdfOGaNNUlE4+uN7qrZjG1Zn80sss5+day2uWXBBS5mribJUpCk7WD6mHJUvaUANpWpOruvinjp+uTUyRKSNk2EkZxPxWzH5PpdjlDMSBWS5HtmNbt7UjjU9O9LQfEl67UgHqWSkMaJjUuT2LTBLLzpM4m+7M2GmZWOxD4c/iVbBPRcAFZzNkxStt4gj1CG3S/HSf4SlHDu2LQKZy2w4xmAqs1dA7YSK4B6roeqhI+c+vnjc/0t3Y316CzQIdJOqE/27tnt1xSQHlbvdQs+IQDeSm444NTpTJ+zpsqU2MjDe6+8VUHhBQ/AQT1U5ZBbOgYzZr09b2oI0sI0+ETG05lwM47sdH+p7TbSeAPo2FZKwJZKNIUDqZuBq2qEdskMVOkIUkS0dPXPXYo5BG7UkpL9Aa8j8BH+hD64/bWrE4ESYHlPwB4F27nSu4jquUy1uY+IWIHvHpuOuamcOiIVBFPCIMvhle+vPqXKn6MHyhoot7I0Cse8DGJZWWB/XHaDwKLmhb+QvkheXa6a6TTZT7aHhU8/vg+S5bgeuPPRneipQsepI28g==
*/