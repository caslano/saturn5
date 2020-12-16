/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<set_iterator_tag>
      : deref_impl<set_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
r92ck/vfo+X5sBGkr1juwrly7UZWsO219mV4JstxDaY58+CZoJRJhvejZct7/PvLu1RCSN/44DxDfsrr08vxzvR2zvzU57sWtba/r88iwxo7h2VZpFyB8sxXkZSLeamvPfdX2qexXCnZpZapIeshhGkv2LaRtIz42DQm09dDpLyzP1piX44nXWEZCoz5Ka/yLkN8idLqvUjys5K8Samkq4zrP9+QXxb1/gfXc23texLlnZYh6vcs3XvMt8q7+98gSQx32zstD2rLk5UyK7FM1wu1763MlPc6664DGt+vqV4XvGx/J2GWo4344H1N9e8B9Ndfe9Q9X+kt7+TvIMuhTH9NWY4FshyazVTZhMrzXOMbtjxjdesxr7p5Oy2YWyw/2lzp24+jrcZMdd1WL0ueLaStepG+Vxb0nuJ50lxLXT5t/U2oUbz+flTapTrvYYYaLHv9vSP1p83vdA3z+suba5YfNVGGfZCjDq/o61CXb3e34nV4nfJZzZbzD7y/f5/M/z6pxwWkgcw//x7dNXj7k7axWbw8N3umNbHsz/pq2r9xW9K90/Wcu+xn2J82wlT8mWkj7i1ejsR42zOridmJmerzvjloKeG+wIb79PcF5hvK1lCea2Xb0T4rK9u7DJd9QkPjez+TEtVjhb/6LnHlVeLOdwl7OO8jGO4X8N5g8/ea6upna015HpuFaITJeENZT4tN6yfVWUOl7wfN7pM0lPsk75jXB8OlPly/11feqyzLKMszWJYnWZ7BH0LhW+EA/E1p10uKLw8nq9mxUzLSU2LT7G2wHM+aa5ZJXRfTbOstNcCiqXcZFugYFuUc1s1iWBfXpOxvyXPpp0gWpX/K0uJlJ/60tuR/qNy19eXW1eM+eUZ+T02mxRewKmVpuUxXFvWZc93GI/W4spRt5/7H1G3H1i7ylfpoa94ujDGmUNMuZB9reF48QvPMt5e0Rb7y3XZ+HR2Xkq3mkYNhxm1J386kvtRnxClzlbrXWWe7qSvl2cVeD9qWR23jF23zU18Kbhvfh3EXkk7w90ua8a1q2ciLMONTJtnahjrNTlJbRj76ENNo2tLn9jIrLdk2Pkm/Pci79RMqMQ1Goxt1nLfKfD0aNvJSz/MaSj1XL+N689fWqeHYe6Z28WNvLeYbsVrKqvkBUdbzf0e7qNlWc+4i59jhdVwce03yK895dn6m6+Pu1jrG4y62ZRqzPFkpZTk/s+1DZJn8PcyXKcZ2PlHiD9dSl8+L5bvOj5Yg22/alCk0kCksIpPq98FbPYqvxzosY+HqEstQ7vNR+/YVq1v+znXNl99a8vKX69y0cIp2/er34cvrFl+/Hm1Ja0rMv8znqY626+ZpvpwHZTmdP+wpYjnOGa1Wk7YreS50ked8ydN4UaIs56qONmXNMLYp/fJed5F3vkne5dlWL2Rol1d/DptWz9iOkXUZIuvSeDGpvPukz3W/B+R3fz3z5YyYa55neZbVmu56WcPqF2+39VjW+S6WtTz7JvXajuTRR37zByllI48Cex4JgSnR6u/+sszbUY/1Zd/uOOZMqqt8pxud87wH5fzXcMzJblC8TE2Yn2WtWib9b6FylKvRv1GuMHlvvxeF8MYGiswvwlAu9UhdjusSXppyJZuUy2ool/TrM56zy/UUtR+gWb863fq/IsvUX5YpGFso63+ddpnKfu7hOMdrplmeKJPlidEvj3oe8m499dxEV84Y6fA6tQrlxDRUyhmRry1nZsr02OzEYYkzy/Q7cclT6rmurdzzDeXONSl3nkm5gwzlljpQ14H0gZTzHSuFjE6liLbzyGvU/w1+WCgb16H1zvPIMOxJ3ozPuHLeKeOHN7bHuVz1JOOjl74=
*/