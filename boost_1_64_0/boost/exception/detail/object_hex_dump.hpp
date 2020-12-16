//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_6F463AC838DF11DDA3E6909F56D89593
#define BOOST_EXCEPTION_6F463AC838DF11DDA3E6909F56D89593

#include <boost/exception/detail/type_info.hpp>
#include <iomanip>
#include <ios>
#include <string>
#include <sstream>
#include <cstdlib>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class T>
        inline
        std::string
        object_hex_dump( T const & x, std::size_t max_size=16 )
            {
            std::ostringstream s;
            s << "type: " << type_name<T>() << ", size: " << sizeof(T) << ", dump: ";
            std::size_t n=sizeof(T)>max_size?max_size:sizeof(T);
            s.fill('0');
            s.width(2);
            unsigned char const * b=reinterpret_cast<unsigned char const *>(&x);
            s << std::setw(2) << std::hex << (unsigned int)*b;
            for( unsigned char const * e=b+n; ++b!=e; )
                s << " " << std::setw(2) << std::hex << (unsigned int)*b;
            return s.str();
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* object_hex_dump.hpp
rqPv6uqq6rf/LM5fg2zOX09/KhatnJCnr5P79dNX3Ke1Pn2FthdrByR0z1Tj4c/kSQhSMrAuUjndEL9xi65Y5ZILkjgi05XbsxEOod7j88H+vygz+w9Adz7/WP28Pul4KaZZe5VAxoWQlNeGt4HnGOopAVUnN0pcD/Bz2JciHdbzXER3WQXku0GAtxLW3oCV4/+/Ul9mXiGwOgHre5AHazJ5U03YDvfKjjjAf81y7cyXqtd6rTNw0lT7pbqLjblnJ/xfiQ1N4XKJzI3hl78+CQ76LYgXN5MU9RQ57SV8hVCwG7eVZO0tppIV0pGkg1NdA5+DFacyVLHcElHrZKgZPmhvFXfgWz2Ml4RJxBKmmsTfrnD3ZKW+FwwJBdFZQUQrX2Wii3UB8StoTmnQ9yq2d73gvt/xalDfb2CoP7xKfQ+WyGlbZoi5FfV6qQck8jglkft38q0BFNar6x+ctmUOwSw3w2xmmLdgTuK8nUfz9jYohwxmFE/madtiK07b/1aNnGafHPfWr2KfbL62f/ZNtg+WDmcDHOggpy4z3CR9PF9CQyLb6OQg/7kVcp3ADPK9M8HtdREcZ39dGa1lv0DZ93D2sUfFAhsnXLZn9RXXsshUFnhIv7lVtxSmCxj8KCoShhoS5Q2AEpRI1xDmdGZ4KhHOg8TuTG4JkYsHhPGOWVcjuXhBzluIA3TEVm1vIV9Y8ZEvbQwS+c3EROorBHrxZTH+EyvedQpO3iTzjnmbFdEvfhGcnAOJIzcr9t6jRFmJlQQzfJuCKQrAzN2kYJ4ywYwmmC6bFMyCAMzPLyuYiSaYHtLvgmF8AZgjryiYC00wP1OPF7+iYNoEYLYxTF0TzB6C2fmygjF+Zpg1zNs7P+swDxLM/X9WMC9hNnnQT2KYxylRvuwyCu2FmMj8AEBJREMJcJsJoBfkxTPA1QGAexmgvwTgZwl+BXOMf/tful0ol0V7aJEgoYifyU52BD8XmSOeiwSjC2XGJHR2H2POvoOolK0KLqZwI/Y9WWG4jaYwofiJsZlCi9yV9okBWz3qfc3RvFF8/ZLQIs9VKOQ6mSrOugedUmnVm6au0i1h5sqk1/Yd867Afav0kAt9Hd75tOB1sSSCMYirPm7J/bSCol6Q229xU2dFH+mJniUWgdP8mmX18TD8IAXzI6V/+qlSLKLyugu+lMFNZcmFkD4Db7huYoOYVBJ4UKET700q5QcavfR8YP/j0eoduXPphZDK3VQGP8QVXJzI9ahHzSArCTGewgVMaPnYSTU1OT97TWb/uptDsu7mkKj0p3y9gs+D0wOehdhU34PSQl4ATuAHtzLTsVpYKlNJiJXgGq3biQibinZkKnZ/MZv3j+UxOWIjHuHb04qWU6xO9r3QJ+Q0eVSE0X4U//wv5WHFJ/6wSFiGv7u2HN7/KCivdTzkq8KkdxfRmw5NYlx0CvQO7QiP3vHNgt73azD++Ye1pzcpTHrrid7KjzD+ebX0gt7/3VF+SvGKGhD1cUVAffh91cdjDB3Pa+728lOK55W2Be0jYd5psuYN9Wq6VAr+bDepQ6/Vij/Vaul44DFzV+KuKXfB/Tf4tVPrv/Evi/5rBbeMxvJ7q+8/K/03Sk+N/l9fEvSTNgH93furpx96/KSV1qp/qhw/v0TUtIdCj58nSmrFXxXjJ6vG3NnM/5JT67+uL4r++xA2T8O9r5b9lx2J8/9VZQ+Qs53tAXyQY+VNOcTlINTOx/STFFlW1pdO7nOEx3174YOo25CiwX7lMpEtbmXa2pYwhryj3/Cch9WfQ1vxxS+ygWk+b8V715fLR/XrPS0ExQWi1wCB8CqgrGsXSK0Tff7jKfgMhBr7HYlZxbJOXvo=
*/