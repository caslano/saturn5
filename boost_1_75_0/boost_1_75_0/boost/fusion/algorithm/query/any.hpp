/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ANY_05052005_1230)
#define FUSION_ANY_05052005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct any
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f)
    {
        return detail::any(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* any.hpp
c7T8DEYkPrM4Ub3d2F9taYp2WVNQ5K6YEG+iqcW7BqkVVzcxRCsuzB3v103W8ODY/tHx6ssWjPRymXZAvdpkbUfcm/5vSe03hCe4/0jU9BoNY+nU9ljKWhtLYEJbY0mOPJZR0WFj+UZtz1jGvxk+lpwOkcZyeU9tLD3lWDppY8Gj0TCcLSHj6dHmeC5VI47nSnPYeJLbNZ6Fb4SPx5tg0Dll+Zzv1hD5nFvAr3Jco4HS2RxU8LpB+wc/I52SCPc7rL/rzurl7Yg3/DtZnQDDU5LuNEhJgCJLl3IUpUGMbQBYrsWK8XgC2bojqt6SmUR/Kf3d4KwX+T9HyzKgBQsb6JJYk+ldM3cuQXTuoXWa9OuR10n6BZIv8CkWJUauToH1jBCHCe665t6izUMBBGoBKjU0EtPSn4iOdeuRmEAn09thBdKh74kxrrGKN1RqgOv1lYCb1P2wRWi9G9Q/8P7uIGLlQMqgvXRZB95oFRCPVTWXFhKf4h8lxuT9AWWK5wft94o3W92xuVtlwI5jVcHpXdxKLE4tXjOgEZivV6DrxuEFZuUv9DjDqlrf/Gg13gxKJStdYFiA8P8vUmQuamFuEWnOAHbyi7Q5c4fM2W4xZ7sxDvaPNGdOfc6chjlLBD4O56xUzhlgXfV13IrHGAxHpIh/DvEvw+0b4RTPVPFPQOaIzOrxTjf4yAZX0r7xJeKfOAqXwrlXPV6Q7+ML
*/