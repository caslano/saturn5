/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ALL_05052005_1238)
#define BOOST_FUSION_ALL_05052005_1238

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/all.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct all
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f)
    {
        return detail::all(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* all.hpp
Lgf1uK+mCoHBGIrbPT0TRlapXNdMuUw6+VUoXFcNVsZPwUaJI4i1gdFFAm1cgBZDrZfgMexr9UwlpZbzS6w0zIPibjgcOFKnK60LiI58hUoJrX5UccT9mEJWovDh8+ze0bx2WYBhEac0KC9uNrxIDxiGmHwfoCO6JVOJSX5VQwC6G0gVhIpwPZzBHwxC1ZCZyMb48CIj/odShYu6BhskCZI6CpyvTV0OFcpXNWF1Df5V4OpACFB9dtio3iNzwtA88zxhbh1EL50tPfHXhT7S9e93+NoM0gqsVZahoIbb2kwNKvjT8/pqBqo0SFUqYhHqLteXUgmGPTyPG6cuVsjsY1k797NVKulH8B7bQKQD3wmQiK1mnj32SlIslvgfrZDS0EGGWOitQpuqpToNHQwuQDxm5aFIXktS4SlgT3vsGVBRyjAzbFgHuAwk108/2LA7POVqC8BjWu9VkFv1Vp9GVgmA48nZkNrKtxL0EAcQAAWU5+kLkTGV4dqknEq4U/eLbehp2ZkNeHEjOSgFWQtGo1z3oqYsL6xOzacad46KaSGgV9gCYZhZIgMkFA==
*/