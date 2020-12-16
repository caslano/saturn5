/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/scan_method.hpp
 * \author Andrey Semashev
 * \date   30.06.2009
 *
 * The header contains the \c scan_method keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_SCAN_METHOD_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_SCAN_METHOD_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to specify scanning method of the stored log files
BOOST_PARAMETER_KEYWORD(tag, scan_method)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_SCAN_METHOD_HPP_INCLUDED_

/* scan_method.hpp
/wBXf2s8e4V8bvn4+8m9cxR/b3QEv5T/gyr/QXyNz9W8idANineszjsZ+lLxWnEJfMFwudYp/jS5N6BY+UiruHSJ62EvT/rhxyqPWupTpeP7Q++r+BuIv9LqK/Hp0JsqPkHXLd3Hq9oYp8vKhLZVcX0sv3yyoIdU+YWqnDSJe0nl91PcAusDl7+cob70qv79aS/pJW64ynNS3AlWuWuNazctixHQUyqfY1wp1gfWr1ZDZ7lyr0SV20u3Lwf6VuX1ELHXdvJK/CmKt6fiTZe451Xexa4jrY9VfH/57pOm8pjt2soq0XXPg5ZPsslI4vop3lG6rAKoh4obrPkKoKv279JbqvjoJau4PJGvS8m3UMU9JTp3KVkyVlQ7iVNjJ1fz9ZQyyEXHbS9lsPuUjrvdSmUsjG12uRYyfj5T7d45/nbrcdrni9813hd/uY9Xx50S10KcGjfMCMJnzQmJeyxubmicNS8kjhEbEnfK7+xdB3gURRSe2d0rqSQhJCEkIQQMKAhJgBBKMGCIgggqiCAIhCQgEAJCaKIYrNhRUcQG2DsW7AWwYRcVK/aKHQUUVNR/372d27vsYaKIbd/H8GffvOlzO/PelBWL66ehXVxfTl9eX05eXV9OXl8/Xe1mG0+9x0Pv86I2Po765kp6r9c18L1ufWP0Hnrf8vtQvdv5/azeX/b38BxlAx8rItuci8nm3P3HM266rd1Go3REwrpFF+v3Nt5mzvs7eVyluQx+46H7Ow/i/YbDgOXAMcBreT/memAV8BXgeOCbwInAzbxPU0ek1cCOQPN5Bj9fzc938POzwKnAV4CzgTuBc9X+Tn5P81iUFvZtr314P2kB56cr8CdgIbA9AnXjdIuAK4HdgVuAPYAFKG9P4HRgLzMcsA+wK9IpAe4PNJ+H8/PR/DyNn0/i5yuBZXwHy5OHGrDVBmyrz/bzwCYZsO+Vwl5X6drsXHLJpf85/dX3/5fPqB2FVWsoRabm/+f1/nNyhLp/tR0P/E/hqRC4CjgGA9CiLgG9v8+QoWNmVNWOQeKB89mdWEdmfagIY/3DJHtpYhLfGbqSnm9MvEPcm+B4XrVL+BlU6IDO53oha7cPqPPe6i7VbeQf53xetUt9fSjLpg/17G76b49OEmcb1xrX6kP8V2gpNp3o0FK6V1jGiEXS5Kdw/vejcFP9HcUHviSb/nNjMfhoFZonM++GfiavNafL+g2Fv8nvE6PQbzb6BvqHC0qX/c+neEr9xWInxZ/M/FqKKyZELzoYsiYvx6YXjS8yeQujdFEsD5DrtXSjrVHq7y4pXyxTUxrIq1WuZLillK+x/paikz/Fpjd1oDR6+JuKZMXPgJtN/Lb+GNHMT/lk/kjKZ3MqcwrzzqG4Z0G2JeY0fv8IhLDrXF0QF8IoPYfmHr3Ag06EHfEhutirFH8KySYz74VAeaRP3ED8NObHdCU92v+SnOe162iFhVTHJNuUeQf2oG8Y+JuJvEB5mH96b/CRA6or5k2h8oz2txLZkA3qcoUk2wX6HWSZl0R5uDAuUy7Th3pu8GXZdLkbKR9HxLYV2/Rc4zLtOe9cj12nO4vKmqnS7gD3KKU9EHVZqNojD85H/FK/LnpTnpoyP4Hbg3Qm5o0hXjTFm8q8DMpnrv8+UeGz63/lxD86RP/LJd59Sr/uBbfY5IFDdce8Nymd/oG2Zt4yauuTZArrUV/+8uuvfanPpsY/LuuiLZ3G5P9EfeAJS1ZuBm8xyd7geUhO0Cx9yuSn9qH0wQvIbgXvlRKTN0NacZq8HMoT7B+c/nbwRpFcCxXW5N1NfeoqS04XeNflUd5vk5yuMMBrTfk5h8MuIF4B5buJxdNM3o+UxgcqPpM=
*/