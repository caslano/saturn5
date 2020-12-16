#ifndef BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_move_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_move_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_move_new_t)
{}

#endif   //BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
Gfd4Wus1/ee86iif/cSQ5Xej/J5/7K/87NIFpsvMKnLx3+eG/6OxzvlkR9ukN8HfMXdU4clQIpfz4aJysIgW3MfpDZcHNjcMtr5eGR3N6nZ6rRskEasssRz5IOfwQ/IJ+Eptpo5jf7J4iU5Y2ByE5x+o7fGADVXMGe1TKQN5JnyYJyTsGy2vpJCFm/iX0l1Dzij1Otc+mmcQtH1REXKg0OIW/462CnoR3SPWT+14pZKrObx1i5dujfPi1jjPo1gVVnfEl0/mFOV37d2Ep3jbRLzzb+AHbQiqDZU3BxLtCIFwyA872k42EUPT38lmY/GQ4KhaKaE9Cj5wNOHYaFj78m30j2638jCZI7FVUb22lJZ0kfL2sN6gP6FzN0veJr2xvQ0Zaf70IyM1dIoNQPsUEzY8JJbjt5YaBgDWUZKMWrzIiUbNP5wL11a8jhluG6P9KCk9uQCNQhYuxUv6JM5FN314ZJN1cfuHUecmhJbECBzcW3cCwCmV50rUuxxPjYG1bR/m5q20m9fzElNkTvO+MZIB6J1Iw1bAW+UA76aRuY1HawX73HhpXZs0/nsAol1a0s4taefocPn8ot7bKHJ4zQysXU7/QOjzDzca05pqWRAIrOXoeDuOKKLh+H8iF1uOhmsPSINxd8jfXrT7ExgwCeHhUmnwZKvBuKfPRMftEgsOYGb4+HdZ/K83kgw2KZTAy0M2zr+9l+1Dz/DIbTmPJnBve5WQ3lQG6iECimsyKzmfQSt3VvLyg0NUkuBfmeKnH/bfO8Uf1E8e/iw8/WcDBfmzwvufZbI+Fubpbja8UP8s7/0s7MTC/cFwuvnzcp8Aa67GaZDtUa22ptPYwDiO5WEVJBKmfUi6z2rn60aUn6P84oTorr3N5l3lsTKmT5be9TJx4NI2RDVbyqxq4HSjgWjwwu1G3Kqy4bk+HtbH9sfJt9rqt/02LRs0mfNpxG3OqMbOZ0nijnkrxquDvzDm1Vz5T9032G7sxqbtmXvZKGNjJGX0guHXdkh58ukAyiuX8hhWy49oqay1h1Um748r8P8ZcM7f7W3pvRin+l5MVH3061Iwl6fw5HI+mZTY3tZDIfXt7QN7mVEgDwWmJFBHoP5F9gBbwZ5LL4NKzPUG9eHyFJLq70sxpnHDXqR1ExcfrU20DaCARDveRb2f/g2ni7f1U5B2pVWMVKW/vJejk5UJExK0RJC91Zk1gV+D/TxR9k6xH8sf0xGj7fvX241rBtuJhqCkx6VLLgM1csfgRNa2lODxiOThdL8W34iniPsQvvkWtyEPwwcy6r+Ex/8ojH9dNGI9QhU9ckRYPJ/R6CSNsBRbsURZHB4koR6TIv026yWBRbcpLloMhwZJOyQ+O8uoLZSxtuxq3KtWIkYroksvDtz6KbaZ3EVHx3vO8qqBzU00+U2wr2KbiKIsbFi0+xBvbpYbfqcTCi8tDA9lFaxYq+gFKaI8Malq1SvjIThQUQO33s0E2R1Ye0dwplcdrFruon9gQDtFo1expGxxE9rHbK4ieR0MD56E4UFOLckL4EruKR+hJQcfyQ9zmUreMsdzmWreMoEnvq/gjBJqwtqmQdK5zWClvY+wesxloZ7SwObwYPs5SgcM+XLqPR1II1UYLkaoZCemlYmmysR0ooqeHEioLq8sduShdycJtSi+9bUTY+MoEJwrP4xFSH5XcR4YT4KnjOYSY3/hslCfA+C+AwK4LxdgqdiGYKwBMBtOdrW+PCveBL8EEwK33snERqZmi6dyR7dPon+k6XXnbdIXKIjVtJdj67cf7c5ob78nb7ZTkDZvTJBivHli0IRiQD67SEiUtx/2tOoT4vTbvOcTgVvL2K/VHiLRVUKiGv0=
*/