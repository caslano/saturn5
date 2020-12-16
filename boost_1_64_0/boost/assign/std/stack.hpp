// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_STACK_HPP
#define BOOST_ASSIGN_STD_STACK_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <stack>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V,C> >, V >
    operator+=( std::stack<V,C>& c, V2 v )
    {
       return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V, C> >, V >
    operator+=(std::stack<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* stack.hpp
b+NLvxMz/qEa/zCNP0DjD4QLXR0Un9WsH2LqQXU6Iup0RPy4+aPl1K+1mE2YPZhW2+PMUEzx9n/vnNGv9f6P5PlPfv933/F7ePb2a6vvrGfo+Go+5tvezJdvjrY+Vq6hylgoQ96ng3FK6T+TzSRMxJodCZduguFmmxaMw47ERI7BMnStR6WEm2o68SZ9DEbHXBo/JXKMJ/Fmea7jQPJlHKYRYyefjJ32b/wUOS7KjbIOKy/KmGpi2NhLx7Oa31v8Ro4LMa013Pfkd87b0ddSSY7HXk+u8Q60+gJmif2EWGvrNHxnu3ZmhtjHR5aBXYcxXfxP1LwPxu8Qmfd2HchU8S8S+ywbvm21a/FyahjrZv+KZaXy4R7Z9P8Mnbq/9Pjx5xonXiLj0OWNz7rnxj/mFV7SLfubNlsuvf4/T9fuf5pO3V2yr7f2Xdoft+VHMiw2Vh5/EcakwqYwDfaD6SoL1xoOhBlwEGwGT4aZcKr6F8KWsBS2gvPFXXXwBtui9k9tI3TwtiPcgbAD7K6ylCNVljIPZun5DoTz4EGwHHaFEwI6xGocH9bJEtXJEtVmLPgBY77EHf/ecV/dUXfUHXXHv9g7E8AoqjMAz+bgjJKLJIQrchejDZhaQMEgh1GwbIQKpbRJSAJJCckSgkalNQgoKq2p4gFSTZEq4hUttqC2TRErKmo8KNRipS1a21IbKQq9+83bf9/O7M5sEkipbXf058vMe/+b/703Mzsz73//RJf/7+UUPf+bw8ad8vx/mo7/p+KYq+WnSAryArJ/NM+p+wLPo2q/haXL/N9q7oKuxzA36WdQyZumv9X0sVr/kXGN4VE6+0Zbvtknz50J+808m6hGF/mevX+u8zasKk7s2LMfNvGspmyyjcdPl3cbk5EU4VvY0rrfXrcFNWVlJGlbdf3E1i4/C34viPqKfpqOUXKOSvfo9wzYj7T/297sU+y3vys4JPbHW46zn5PX+zO7/XwIPqew2OcrLC2u5SBw6yfRi2/T70D8HELbVb8zqovV9qjFXD2AXUVOdlUVLy5zt0l04k7YpkBbJcaFt9Xb2OQLt6lwfpX+/LirXb5OaqvNDnb9Arvqw+0SPxp3m+o7yaYx8eH99w42NTjZVFm8cKnjuSHfae9g/1GGo0174p3bqTHcJvHrcW+nxk5qp6Iu4TYdxKYmB5sWlV21sKzK3aamTrLpqINNv8SmZgeb5CB3tan5JG0KnHtru4bb9Ctsagm3Sfm9mN4UkfqvpZPsGtLN2a6DbnaVVUW06+BJ2hXow+0udrU62IVfg2ouN5taO8mm6d2dbTLecrSJpnK1CZ3Osemgg02/xqZEB5uWViysitR3iZ1kU22PcJsOmfGSHWy6oqymYsFV7jZlnaRNgXu4u3oaatmGZCCbkHexKSfEpqqyK5UtI9R7fvOHWdtCXolZKeMIBWr968ZkW+w19WsgYwkBnUwdj/IStb7e8Nru+5S9+r6vROWp5W6qp77v++MJ3vdRD9pD1SPknb+y03YtqJRgFdJ9RnfkN2a//dzeRkut91Luv3ui10P58cSqcRmtJD5EOk+7+9f625gmcSgom226bNuxuO40Qy03y/1tPfJbs9/D6zRK7sNC66P75WKlUyn9LceE2tbH8ZjJJ32qSs+Q+gbyp6k28XVRZ8tin19FPxsUqzxfMEbxbzL9H2uYfS/xjDrQ99a2kr63Hg+2vvedHt73v0f/YGg72e4NXfte9HqoGGY/7memW7Us3xw+if7PlP6nfLZZy7cfA3m9wuv2B/O3JLRu+v7SvV6tlmP6epUe0LD4xZ1EnQLH9PVqm5QdUp9uicF6qHXkj+Q3DoTUpx33pn6d7q7XL0k=
*/