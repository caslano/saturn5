/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09242011_1744)
#define BOOST_FUSION_VALUE_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : std::tuple_element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
3N05kryzgSgoWmcLMGuoBMlrtS4EAXxuaUmYJBUUEioiS0GX+IMyUA2BmrYEplE8D8IPNqwbWjYjzj3vQTa8bytoilsCgpSE3g4wXSEU8BoREL+iUiFmryhnDoYnoIhYyRFGJ1G0kkNxW9C2WGK4QkGjVCd/c92yFy1W4la8lG65ocJp1GqnqjlmsyrugXcKFIdeEhu0vQ0rXtFa35EiXOz6ZUtlYz+mhQFZ5XIBkrTtCIeulMihBALpyJatLaHD7KnSN8mZ1NHWDV9tGSKtI1DdC4bhkBa0qzgSb0PPKiKMvSFiE2Vk2VD+nS17zL0CzjArmHgpBOkEloWk0oaPQXYeXWXw0UsSL8zmEJ2BF85HvIsgPEVtUIwqgNx1gkjMQgBddS0l1VbwH9rplpOdw/QqmUVxll+lfp6mMziGydEJ/NkzlPXRqwlMWrrU+w6vnePXziEu6F85KeR9LonSO4wfFJNEvPQcQu/St3ZBFy9QkH/3RCrUAmU3oBddyGYp1HwkXxRM1kQYkHQeRnEapNZPlJVtXxF4q6MOAmzeWSZAyXF9N5k9/QYOGpRGiwrZScSGlmP0ltySdv+NCXXqp9MkiLMgCq24QOaLwWbIkzOyEcRt0WIBUAtU15K0fG1rEa2KzwQ2FKHOdSMK
*/