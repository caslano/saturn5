/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_05052005_0232)
#define FUSION_VALUE_AT_IMPL_05052005_0232

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::types, N>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
oHk8jq84o8DH3TCPo6m5eJ9A45XM46F8xw2Zx1X5iifyHQ+1bL4y/4nuH554svG2ds9+/s6Ax6f9+9ErjxeYZpHvLNxjMj6eU8bTK8buWIJjcCGm4WJciEtwDd6B23Ap7sBl+BmeJ8k5n+8Cdz7N+fu05JMo+dyGnXE09sQknIjJaMfxuA4n4mZMwVdwEl7AyfgpTsXa5DEdb8AZ2B/TcCam4xrMwGcwEyswGz/C2fh3zMFalHcOdsc8HI/5mIYFuAILcR/a1fgE+X6Q740cj/iEMOmr6RZsj80wCsNxCjZHJ7ZQ4yvkPC7n9RyP+IpeEmfSGwdhLCZiXxyP/XEaDsAMHIR5OBiLcSguwWH68Qxf1Z77VZJ8jmcoy3XyvRzlV89XnMe8y/8j6UOsFUZjG4zDtjgA2+Fq7IInsCuexW74OXbHbzEaj9Sx8Lzwv/MZYfD54LV9Pvjf8Gzw/+m54NpneQ5KOkK6SLLuDbHEk1L3Bp/d/T9M30P///ZCOuldWAPj/3fgGmi1EodP55613V1vJ40bOto2bMJtI1JsKeOShk8YPHbocNe9gpxbLWp7peRa3u1QyllP6SHX9yHrSR6XdNvQqbbhkwcnKd15V9u+wNCWT2uv79n+pZZ3O9r1LFvpM1+lybarj2q/2wat88h7hOSdVNuj3bDkHfrClfKWbt8DaJvkmf8oyf+ESf4bWDb6yvmrNwUCaR+1zkf9J9XxLsNDLJvsuwzSROvq86465o5I3stlvy8hbWRZu8+8afbr5z2YKx1zKXJdniD3SvqTHmZZ64s+8tWGkbiq412unXV9dxuPwwtSnsFSnngpj/2K5ZHjMID2tPoyNVXL5D0WwgQpV7lJv/6Pso4TVyqXzX2u42XSuJG2iSnjJgwP5Dj1LGMoJhrvhRn2ZWQ97zI+ppw/fJcx4ONXK1P14xB0lvshm6VcbeR82pI0hguO0MNV90P8vw8zOkzJy5aivKcRdzY6yrVwMvO1NlGBt0H6obWh+l9tE7V3vqsest67+7HMD/Ym7rbMX5E6e5H73kYyie9YQ+zw9TiMZJFryCbYDZtjd4zAaOyEPTAWe+JY7KXFJPMd6ruNyXhpKzIBG+JE7X18//lu0zJZ3jcFG2Gq+j7SFd43Xd43Q943U98W5grvS5P3pcv7Zqkx3fI9gctNYrpbynb9SOrJij2wNU7CNjgVO+AC7IRLsLN6b0S+DzDBpO1GH7k3EovtMU7y6Yt9sB/2R5KsT87nONhkfQNlfYNkfQmyvsEYi0MwHoeq9SbnYbzVpN5GSkx8Iobjbfrj4grvS5L3jZH3jVXfJ+cubCOv9e9rWpvjFJthSwzHChY4tveHfS8jGO987e9n/Df0bf3/dD+jks9kOB23DCM5STtJJ0iXSO32h1hSSGtJL+4P3t/4np7/F9ZU/3+p6th/2tgnh+TZ436SQ7m+fMx1Hs/smWurigGo9pqqkTzXnid9/1U9057tHiNJHVOOoqMyj35afPQvIM+I5Rkdmy7rj1T7frEbns+Hy3WyU66PCkkLlOu1La7tyO2ZGfh2FHtsx5zGxmeIkXghVMrn9VybbfPos+qMlHFPHcqIO3AheVRUlbFQKWP142kpz5hHbvcYa8zkuXuOoczSN6M21qDHGIN2HpgWOfXPcdtq22Go60tyTf6+9AlyEpW6TtuhbYfUtV99gtTepW2LUka7R92XyHboj6Fkrdw9LbJtMVfsv9G9HY2M2yzxCbpt7SnXvfp+Q+x2112FJobxEr37kTou1+g3S700QmX/Vu4y1IvWBZIfY6cp9fPRnu9/X3PMGp7Z72bbInA7LiHv8iddZSrsmev/MdvhWe/tWMS6KA8=
*/