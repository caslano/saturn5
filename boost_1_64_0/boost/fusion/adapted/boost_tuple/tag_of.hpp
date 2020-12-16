/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TAG_OF_09262006_1900)
#define BOOST_FUSION_TAG_OF_09262006_1900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>

namespace boost { namespace tuples
{
    struct null_type;
    
    template <
        class T0, class T1, class T2, class T3, class T4, 
        class T5, class T6, class T7, class T8, class T9
    >
    class tuple;

    template <class Head, class Tail>
    struct cons;
}}
    
namespace boost { namespace fusion 
{
    struct boost_tuple_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template <
            class T0, class T1, class T2, class T3, class T4, 
            class T5, class T6, class T7, class T8, class T9
        >
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, void >
#else
        struct tag_of<tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
#endif
        {
            typedef boost_tuple_tag type;
        };

        template <class Head, class Tail>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<tuples::cons<Head, Tail>, void >
#else
        struct tag_of<tuples::cons<Head, Tail> >
#endif
        {
            typedef boost_tuple_tag type;
        };

        template <>
        struct tag_of<tuples::null_type>
        {
            typedef boost_tuple_tag type;
        };   
    }
}}

namespace boost { namespace mpl
{
    template<typename>
    struct sequence_tag;

    template <
        class T0, class T1, class T2, class T3, class T4,
        class T5, class T6, class T7, class T8, class T9
    >
    struct sequence_tag<tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <
        class T0, class T1, class T2, class T3, class T4,
        class T5, class T6, class T7, class T8, class T9
    >
    struct sequence_tag<
        tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const
    >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <class Head, class Tail>
    struct sequence_tag<tuples::cons<Head, Tail> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <class Head, class Tail>
    struct sequence_tag<tuples::cons<Head, Tail> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <>
    struct sequence_tag<tuples::null_type>
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <>
    struct sequence_tag<tuples::null_type const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
HoPXf2eVsM6Bj6SsUo7799PPA7yb7ttqldsOWiWCR+EzhzhL3Rf++qNV1qv/ZJXp7VaJ43KE7+tXqzSqpzmH37hzWtvvVnmCVOk6sOUYe+hex62ylMR0HXj+H9x1PABfINnrqBOOOMn74PIXNZO0vguMEtE58ABp033/tko/ckLXgZF/uFfMMU5bZXkHm/TBox1tsoakdF943hk2yWc8AGeRIl0TWjJskof74VJSgCfgjEybjMEj/E9ATrPapFDH4VibTXJ1fbjFYZNiPJhlk8+cNinRdQyb/OW2SSke99ik0muTMq3tLJs4u9qkAk/CJ7rZJIanYIeeNlmm4/DARTaJ67P9bDL6EpskdRyOHWCThDrMGGiT9XgIXpxrk0Z1WDjIJrt1Tfji5TZp0/qvsMlrefRBx2HXq2ySxsNwwjCbnNC9oATIes4R1pEueAquucYmPtx/rU0uu84mffEEPPd6m2TiAfgUMfAorLnBJn48DZ8cbpMheAyeJCHcuNEm1tE2Cer8+6i/3CYBPPSqTTaQkXgSbq2xyXA8uNwm35FxuKygZhLWZ+FfZKrWvNIms0kEj8PsWpuUa21wIYnqOPydLNMaVtnkDhLDw/BXUqXj79rkURLX9eEdH9BnHV9nk+0b6D8e2ch6X9BnPLWd/n3HGen4ftb4lbPQen63yb8n6LmO/8V7eO1yDJdsu/TraZfMDbjPLs/57ZKNx3PtkiJ+PA0HXWaXIXgQLiUBPAEPkuE6B04YZJcgHoU7SEjHYf/BdhmHB+AjQ+wS1mfhwqF2mYonYbfL7TIS98MPSTmegl3z7FKFh+HHJIrLlXaZTiJaJ7x9mF3iuibsfo1dYupwdb5dluma19mllKzX2mDx9XZJ6L5w4w12SeOhG+3SSJI6/ybmk914DF59M73QZ2G0wC5tuO8Wuwy4lWd0HCaJbyM1w8tvo294ENaSvngS5gTpoY7DaaQLHoU7SQBPw+4j7GLgfvgwETwCN5BMXQceJye0D7fzHAnrmnAFieAJmH0HvcUDsJqU6zg8QsbhUmiXa0kUD8E5JITH4C4S1HrghXdyLroOfJAMx8Pw3Ls4F90X/nE3fdZ1RtplHonpOnDfKLvU67vcY5f9JIUbo+3yTcguDfrs/dRMdmtt8J4H6MmHvC88p4g68QA8TsI6/qBdVj1Ebbg8zHuREJ6EQ8bRczwEzxrPn/Eg3EkCOn+CXWaQkXgceidyLro+HPgI74Wn4XNhzlEdXjyZs9A5cC5p1GehYwr9xMOw8xN2adVxuHIq9wD3P8V38Qx3DI+V2uXws9w9rf85ehvhruqc6XwLM+ghnoCbn+dMcaOMPWdy7vXUD3u8QG/1veBGEsWT8PJZ9FnH4XQyFY/CDSSic+BR0qZnXc67kBN4AI4naTwClxDR+uEekqnvDgMv4tQQgu/Mpue4vMR9IH7cX2GX20hfnQN7zqG3WjO0vEw/8QBMv8oZ4b5Kap5P3/AItCzgXXQdaF1olxKdD6eRIXgUbiEBPAmPki64VFED8el8OJEYuiZ8nyTxBIwuouf6LLzgNXql8+FCUoXHoXcxZ6E1wPlkmY7DTtXcVa0Z3kHa9B1h1uu8j64Dp5CE7gvfJ426L7S8wX3WZ+E8MmQTa8Lf3qRveDDGHVtCf/AkvH8p9eMJeGMN76Xz4Zlv8764DzaSvrj81y5vkIA+Cxcuo+e4sZzxFZyR+kpqJCW4v5Zzf5f+65pw7nv8rumz8Cg5of2MM4dkMh6A44ngEbictGht8HvSjKdh3mr+7tB3gSdI7kfstYb3JoW48b5dbHXMw4PwbTIGT8CMD+ySj/tgkQaPQP86/jE8Bn9eb5dTWs8Guzw=
*/