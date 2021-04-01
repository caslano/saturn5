/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LIST_LIMITS_07172005_0112)
#define FUSION_LIST_LIMITS_07172005_0112

#include <boost/fusion/support/detail/pp_round.hpp>

#if !defined(FUSION_MAX_LIST_SIZE)
# define FUSION_MAX_LIST_SIZE 10
#else
# if FUSION_MAX_LIST_SIZE < 3
#   undef FUSION_MAX_LIST_SIZE
#   define FUSION_MAX_LIST_SIZE 10
# endif
#endif

#define FUSION_MAX_LIST_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_LIST_SIZE))

#endif

/* limits.hpp
RpoYjndxtZvg32VMq+OsAjX0nSsvCyaQ5Gi/yC9wnqY3tNbPg3AhmdVj/QYx+g+NafH8kPL3coL5HrSXiCM5MgGngbH5GzVfS/C3GRwCe5p81Vl4HhrDoGqbtQe2AzTfuijYfFXxpJMpHW8sBJgOh/V2RV/vbTufjBvXdI+C1TtxsE4FI/BWc0nioDBkaIiLWVCNWww8h1b5SAKsGJUfEmHT5KtgZ+GdQwkf7KGxY55rCkmQw9WQM7Jjx1mtcJBXxd6l1U5TG2ZmC4i3NesbmTcH+3NlQnGh2/ZIkSPBwxFQR86gJI08IhMa3JFHd4JHeCUwLcprnNL4lvNt/I6VQw6t/c0VKgB3+ZLVwfhQiXmo/5sV5eKOR6CTXkUfaRyz31mEySP9d/1RKwk1fWGJ4WaiMbm5Oihi752FYM27nQ19CBeFHticlvKpdMJPXiLk3STeSIPYheys39ZlK4xz/jDW6sZtMjQpVdmoXIkausWVLucRsI5bsFO9MC9x24NyE+19WK0kuA9cWOqORLse3iAtSO3YcOLk74UwRTalZfklPSKhbHvwB0vBkw==
*/