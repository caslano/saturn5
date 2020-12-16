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
kXeQbUj4zaxLQlzIQmQlsgHZjPRaxXm9iAupRm5H6pGtSNgtwY7RSBGyBLkdqUe2IOG3ohNxIVXICmQ90oBsQ/rdZq+D6oiwHeb/4yXtmPn/KX0dmg90ocyzvxjpi1yApCv76t1q8FmRuGqLs7TI1azfRZkX3fs24su8aPHDsM7duG4+G+Kv1fzKob49ARxyzemfY1kgfhz9/nmxjXzQsga+DXvsd9TYfmvH8K19Da0f27f2Zdhj/h095v+4OuY/c/9pSfkPP1L+xQXDTzr+oMGhbRvzz0bke8b3j8+mvv6+MobcQ/q8PWEi3F/efQ+AJ8AD4XnwYOnbRsAUe414i/p69hrx9vXjWtOH64j+2/bqu1Xb/SI72MEOdrCDHezgDf/k+7/L3UHv/8m69/8q6/d/xo8M7/8k3rr3/+NutXr/N84hz4bmvfRyLPbSK4D+ffPsd3/73f+feff/QX33X3Pad+edm7JrddCq/nt+PuyTQW1/96+/pf3v/n3k3T9C3v0j7Xd/+93ffvdv17t/19vtd3872MEOdrCDHezQfOiKnNip7/8JzrwyT0WcOgTQ/jGAI3RjAOtk77kveG+IgxvhOGUd9NXq+0nGhNQpCc6MURNGj41zpk0cmepbG7gBEgKesVerO2OvXlvn52ErQa+vf5P3HV6u+X39Ddq4QHluUYX33s3ee+Wa/94t2vVC9ojw3ruVz2vVNZDeXWh8ayPJjH9ugapC9n4JMp5NEGrcr1BulrEILR/uYk/FAvVaunZvnoc71WtZ2rVil3JtT8O60xPVz8NUn61qu7ZGMi1K+VzAHhrOCo+ciUA1i30e9T6PdkYg+aso5qOMiRjiE9ewTne2Ng5z9gFqmsQ0rkNf28W/NjQccSJHoS/2eut24JySNnKwo+XrcM31nx2g/nMs6r8gQP17LOqfrFvWcxX017Mx771k/7mfyGhfuAW+SRnX6vM+L47sj3GitXDeLPRK3guaGQtbttI4FuaxOGsCNiqfqgDlsxjutrf3OpujqPVcrZ1Vkafec7n2HSh2+fJf4x9bK2FAT00jwx+v0FNACerG5t7qr5ahK1+upcEHvGdYznTHyZpv475R6vru87z5Jb6+jAnBsh8d7SweJkOljGNvNJSxNDGtmNUy3tTMs6ZOnjVKeaevMpZ3g0V5b7Yo7y0BynurRXmTgL68eYY0Lu+QIOvyljTK8tXtsaRtms797M21Gdq9yqZ1zmKX7v4cY7vX6ueRnlqdqem5Anxvskz1Js828iC2kQ1pq/Kdke+i1Plcw/fLuMa8Sup5MrKPjGk9wz9yvONdyvYVxIof7Pv+9GpmnXu4xdp8IDagSjf+u+5fOP5rPT7b+nXd1uPFO/56b+vx3NaPC3f2+G+Pnmq7uu+Fv7one548Lfip6G9uuI9GF+FUrh/7yoANT9875Br3a/1u/Wt58TltGxcO2Un6XdIf8/B5BP/uCn3rlOJgJBwOD4NjYT+YDaNgIRwAPTAaVsIYeAYcBM+FsbAaDoZXwzi4CsbDu+EQWAcT4AvwcPgGPAJ+CZNgb4wcCiPhkXAATIYJcDhMhiPgOJgCJ8FR8FiYCvPgaFgMx8K5cAK8AKbDm+FEWAcnwdfh0fBzmAF/gJPhHzATKmV0DMyC0+AJMBsWwGNhKZwOF8AZsBoeD++BJ8AN0Ak3whz4DsyFH0EX7EF9uGEfmA/7wVlwECyESfBEOA3OhlWwCC6CxfASWAKvhaVwLfTA++Ec+Dgsgy/AU+BGeKpuXZL0w7CFeKZ1SWfK+pizoBMuknj1SK3Eo29DPO9eJE9IvBXiZ7gaRsHrpH3dANPhSpgFb4Tz4U3wVHgrXA1vhy/DO+A=
*/