#ifndef BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED
#define BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_PRAGMA_MESSAGE("message")
//
//  Expands to the equivalent of #pragma message("message")
//
//  Note that this header is C compatible.

#include <boost/config/helper_macros.hpp>

#if defined(BOOST_DISABLE_PRAGMA_MESSAGE)
# define BOOST_PRAGMA_MESSAGE(x)
#elif defined(__INTEL_COMPILER)
# define BOOST_PRAGMA_MESSAGE(x) __pragma(message(__FILE__ "(" BOOST_STRINGIZE(__LINE__) "): note: " x))
#elif defined(__GNUC__)
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
#elif defined(_MSC_VER)
# define BOOST_PRAGMA_MESSAGE(x) __pragma(message(__FILE__ "(" BOOST_STRINGIZE(__LINE__) "): note: " x))
#else
# define BOOST_PRAGMA_MESSAGE(x)
#endif

#endif // BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED

/* pragma_message.hpp
4Esr7J3I7tsABmdPpBHqwNG+eCcHj8dQ18FdnTw4JkPOpS4OHJcRzpnbdnLgyAw5+e0oR1NmenA3EjnX3N7mYNLa80POsZOGuu682+Zh0pDzZcZh0UbOuTsMc+w7Rct3JBy4k/2AJii0wXYnG0cV2Hd+APpEnEtApTCmxbBTxnv4/XvWewGmo4Vn4LCKaXQOyL0TzjN3qCZLM/+x5gF5IoPArVZtB8SeBzyP6jtQRn4WxJErDk1AL9wxD3gJ47u+9KJKFqIxR4H0sR6MV7dX7ff8e6ndzTpZ6CxuB5mTvbvpQ2ZW1Hzp+NwiYmfXcuyRfXK3ZT1i7P779o3wHbOwmcCSPktsBtwuCrJ2vTbgdhG04frXQRwKvV0PX5d9Z+n45VaGQTqwP56/AWKdDvswXjdkvAV9nI/4wW2AlzwjST7vvBHimJm4F3BjxIbuOzz0JhzTQxL25Vu2a5xl+CTT8dObag7PdMS/tQNxlul4H+OaGscMpLrnb84xO93PuwXimPnou3EnYtAloU55K/Ud23ZSJtYbi2tubeO1ON5z+8AwPujhtEqZBdZ3QnBO+lRuJy91iki6lWCxbhoXtl1JZe6ZBmkapYWWoOdleAeJ8g9GqR/ljlcIldW1/Yeh9Whf89E2aeHEQVZ4otmomoBYNXcKBov2vsSzmGwgqjJLyqj0RXM0Pj210Hi+72m3/lr836FZIzH5UoAVnzCMXYEXEKbnFwfg4l7ZE4Dj5uNLyhd/D9cHuJfK9PjCC8oqTf241dNTCuabk2vrzPynTDYSVea5jpeFrWy9IpkwbvPNHQNXy489jb+dTqu8SKoSV1kTOI2HbWfufeyAWd9QHVIEXiL93KnEwiLmAKS8Z/teEVTuHlVaxnASXIvR5WUv1XxJ+Z4jytwNc1+mrcTEYu2q7PTc0uLCKbUFDz7ZlubwZTJ5m32G6spF7scy9ZygVqXbvQl/Cc8xXzPG1lexE6SF6zUyK+oSxATMTi0/bjScg2mQyNiTtUQ9quJZZGjW5Kw8SuGFXul4KpCVhToZE8uQ1qVefV0fGhCPLbaLC0xPIDI4oE1L8v7BFDA0cn7n/ZJVJ5Isj5PKKQRm5kRP2TarDw8hQipG1E6Dg3b+n27dX3GqHIwwET3qOaGKAeYG3xfbSeVLEUonKXMvEnRw0IFOmPzeQ2XuKdMiyGUlBfZQtk8/wcPIysqVnpe1AiQMvEvwdOt8tJBxHslcWEsMLbdi4jZL5Q5WXiG9II6EGktp1MaWsY7yuMkyTvNUFiCAY4idnmdRmULEfigzF5sz255w8LzXSo8M4iyLVXlbSwk7PeepXC4KGVZwGw0XGLpOLqINAcqXIikDryqKSvDZgGX7lMpUIq/CIHI9wSYIdn96maXHF6pPTiTY0hse/ofyYuwZfDxRNa6MEk+KoWkB7wO3MzlXVGHiVFniC3u6YI2Pe6hcLmQo41D1KmRM5fkhnsHzMHAiRUc+qxWwX/M8NUf46Z1hfgsEvrMJONggvXIXxJnTRXxTp37eRfY9gah3PTH9F55itYkgiXyZpq0NDj1ltOzafesp3L9X4cdFWgp1WrRvr6b2zLpD3hvXHTB3wPkZvgW31iU2fuEeiMNS3czfEL9yL65fTyERP38QcTbHLM1Y/BS+7nErP1R97qrtb5t1D/ph20/Gm32pk1e+k9TbmfMzZixFX5VPZX7YwiDxUjdRM5kF1cvqfjU0/SrlFsLLvTzKnFhpDnP9BCos8TWUXzZ/OYBbh+gDmOq5hyzzQlaFVsNUwc+Btk4+CercE0EWsrK+z2EWFC3+JI4/Zm5h3169B/m6G6s01HV62G/4Do33a7yuRoiizRy1f/5OPZ8=
*/