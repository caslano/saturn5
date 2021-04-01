/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05062005_0905)
#define FUSION_DEREF_IMPL_05062005_0905

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<filter_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
YbJHN0SsbFqUnZx4eQNLFxQXb5uISZeWnLp5TX+4K142GfHoEU8yeGsx2u2HyTdNk+vbb2VKIozWsm8tseP7E58rCcA34xKziwUwcZcV7gRVXoCVZKZ53mPHjrjwurNIAT9WdyeqFMAD/w8ZaXJ6SeH3rj17tihDNytD66qDp8TMN4t7ldGDDl5MWLE3wj4X5WpJWw2r2E2uXrIIp0gFTjsDFdlAtVd3U8Pwnzw1CbYtWd++Orb+HuGosWiDOTOPnKdY5CBrmPunyPiQ9tUYxzHRy5fceClj7Q9DtOx+llY5as5rWFQYaTiH9XTBLCYHb5iHxj0tM8UrOq3eRubPd3UzFjqSKEEKc+Nj7YwOlWi1ko1NVcobcVCpgtyTjk+lMvuUASZKMltDSYBJOoyZcExtjSXKZVkB1oOnZtbsMq/xTed6z1Jz2REOJG7qEnGSSVkJEf/ItJa07j7MuvNEKvFL4+B4NeHH/EIGHb7LugWjpAr8xaNRo0KCDhXG0UlXPh/+ifG/zeigg7n02JqCKENiv8PqwIUWM0kvi4SyLOZlHypfavWD0KtOng==
*/