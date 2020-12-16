/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 *
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the preprocessor symbol BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS for
 * platforms that use the implementation of std::fpos from the Dinkumware
 * Standard Library.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>

# if (defined(_YVALS) || defined(_CPPLIB_VER)) && !defined(__SGI_STL_PORT) && \
     !defined(_STLPORT_VERSION) && !defined(__QNX__) && !defined(_VX_CPU) && !defined(__VXWORKS__) \
     && !((defined(BOOST_MSVC) || defined(BOOST_CLANG)) && _MSVC_STL_VERSION >= 141)
     /**/

#include <boost/iostreams/detail/ios.hpp>

#  define BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

#if !defined(_FPOSOFF)
#define BOOST_IOSTREAMS_FPOSOFF(fp) ((long long)(fp))
#else
#define BOOST_IOSTREAMS_FPOSOFF(fp) _FPOSOFF(fp)
#endif

# endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED

/* fpos.hpp
/iPMZZ4zIp8lzN9joFdG6oqVmMs97cs7eu5O+4DnRbrvdD5Z73mngz3y3CSOe6UOdUqQ9ghd89c76Fl8vYOeeesd9CWm3rGdLyl1URc37hoPb5/1omaO/GZhQtp3nd4buQ2x6xk9FVGgPiv+Tdk+s5b1jConYR6brWdG2vs/yPrf05y/qLzM+m4RWd+ZLKqjljMjVdbeB2vtkW2tsrY+WHuPXHvL/f395iEbE/ebPxS/U9xxjjlncou+l1xVD+Mb8sOrm2i9njHpee8oeqfpyzXSTM8F0XR0r7W26HX7BH3tHRrbyzDtMERIzj6csdGnZ77Oka/NM2l0qfib5gx3sqz6R7h+/TN9nu+K27mc0dzMqpP4Ne+838cDsWWIT1KoTtzr9nPIlzD2zVk1a3Cn+PPDXrf46w1r3vBeWO7D/bGb+8ek6Vv6ovfHmH66x/g5vdH/q2xp6i2/9jQdLv4ucSZzxZKmGq49TY8Xt5W00Nm2NMWvtZybNnqguG9kzNzMVvbxby37pi9ztLivZd/gLFt9gP/g9YHKWvs9d5Ino8V9DX70vEGxX4kuDrXVGYRn7+dsI6wJ4rbcnNPdT+yrnRMIy1KvmLDcc4N2ZnENT6vRv6QxnBvUPcfx6WWtOuyeKxR9N71GdfhsJ1j7GESHv4n6ZZyWhZdb6r6VmOMwS7UsOFfXWhbyy8sKCovLixewhMZfLkx+d5EwFph+SxuxN7WWEe7nLyMmr48Wt7NMOD3EnmMrL4RjLS/mnK8jNCxLWcGvtayYs8w66roXSznBb/Bygqy9nGh9MkLch9vKBH4tZULrkqPE7VSb/uPvq9XNCfR6/P+iXtdW9++He/+L6zs+fdO9nn/VBdsKd5T8ZFCHV1c9tvNXR9ffuo8bZN3Hkw/sLPrb0PeeePKP63s82KVb72//uo9Wme71W3944zOvv7jwwLLmj+UckfbPiTzvHPf6W5cVrr+91ScP720x892fr3y6z//eOpGrh0o65N08eu/d8wZt7Lvj1Q+/+F7PQ79+5B+mvEbauV1wPuZjzNzo+wQge6frPG60rO/RvaH3whbwzzAX/gUeBavhYLgPjoQfwKnwQzgDfgQLVS56vwq930zL/W7X+92t97sH9oP3wlzPGTf3w2HwAXga3A7PgT+EBZ4zbyrMXC7lTu/XFFOu93tJz654HU6CuzW8nfAM+Gu4Gv4GVsLfwrvhm/B++Bb8BXwbvgV/r/d9B/4d7lb79ug8os5t7vKdabMIuXR4oT73MjgBXgvz4CWarhX8K4XL4RK4Ai6DqzReV8IfwXXwKfg9WAVXazzXwJfg1fCPcBP8FG6GzYjXNfAweK3GOy+kc0M617YL9sSM0j302yE3BB4Oh8Ku8GI4HV4Nu8NrXT9wB+wN34d94AewLzwA+8HPYX8922EAbAKPhK3hQDgRHg1nwqHwPHgcXAVPgJvgifA6eBK8Cw6DP4LD4aNwJHwWjoKvwtHwdXgyfBuOhe/CU+A+OA5+BCfAf8GJMMPdyx62g3mwGzwNHgunwhPhGfB0OA3OgmfCJZB00TMQdHyr8wa7fGcgPKrl4EnVh6dU/3+s5e6nWu6ehqfDKngufAbOjLjrHvI6FtNx4y7fHvI36NlS34d94RYtV7doOdqq4Yw1/WbioOGkYo7XcGZofArgGFgIL4NFqgcz4baIXfdO136I9jd3+fZOPx+5o+F8LYclcCkshdvquE6s3LJWbNqKlLj1Yrs++ubWjCXnxa8b27k+ydmLSbR+LLm6Zg3ZRStSvtY6stzq2LVkGRuSYtaTVRL+DNh5Q9LXXle2B3rXlp1dHVlfNoqw7WvMkNmQVO/rzLzfm62rjl1vtnk=
*/