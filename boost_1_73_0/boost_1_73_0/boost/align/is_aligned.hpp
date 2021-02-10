/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)

*/
#ifndef BOOST_ALIGN_IS_ALIGNED_HPP
#define BOOST_ALIGN_IS_ALIGNED_HPP

#include <boost/align/detail/is_aligned.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, bool>::type
is_aligned(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return (value & (T(alignment) - 1)) == 0;
}

} /* alignment */
} /* boost */

#endif

/* is_aligned.hpp
66bssvhxvCrhV7xTJqmWMEhxQjl9Kxi+uIMa5M7MMOpaed6VckQbUoayQYUlr3F7aI7aUeuxo73wVcHRydouOaOYVeyx85R/uxWEMBW8gTarBrac+zoD1flpbotMaeNPTT1zF/NOm9rigyluWdQI9IL5QxcbFLT/pTbJG7C9ebRnnJwfhYjjspmOoNtXtRCFCu4tPbMdmCDreWl2lkr2/KA1MxyCX6jhkHGzqhPjLyrOpESwizrheTiTzuwl7y9keMGjikKnEAmR5uAzL+409EB239ZX3a3Kfnnnwdmt+bVA66bNetnVtLivR+pzmDF8tK0HBM4xB2OeUVPPs6O5qEUazAPkecsVZbtYHgK6EZPd6t3XuJcrNRfMoRZjQbo2tzcEXfJQpAV57MKXywwInUJTUnJCEq+LhpX7dcC0G5bH29vbUc7RRnVzPRZ9fKx7DCj1bRHcGgZchWu2gE6Ey0tgP3v56NHjQTS+k/fCpbBWY96zl1999ZhSRlsg46UqoOXAPAHDjJslF9ku9m+JIN3aAhpmoi5ChWj0ZMHQuAaIqnn70YRSJks1C0IIVqGmkPNRCSABRJR5Rdohal9pgLQNqaqA5hLVEyAAERJLgzg72iOi4uZsbcBxIhKu3MuRYNlYoztl+LEeofwm
*/