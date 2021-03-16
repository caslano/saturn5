//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STATIC_CONST_HPP
#define BOOST_BEAST_DETAIL_STATIC_CONST_HPP

/*  This is a derivative work, original copyright:

    Copyright Eric Niebler 2013-present

    Use, modification and distribution is subject to the
    Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)

    Project home: https://github.com/ericniebler/range-v3
*/

namespace boost {
namespace beast {
namespace detail {

template<typename T>
struct static_const
{
    static constexpr T value {};
};

template<typename T>
constexpr T static_const<T>::value;

#define BOOST_BEAST_INLINE_VARIABLE(name, type) \
    namespace \
    { \
        constexpr auto& name = \
            ::boost::beast::detail::static_const<type>::value; \
    }

} // detail
} // beast
} // boost

#endif

/* static_const.hpp
i8Btt6D3pUW974A7aUEvtIM1vWjgunUw18uxqJcHXKEFvUqLevXA3WtBb61FvQ3AvWJB7zOLel8Bd9SCnhJuTa8DcHHhxnrIZVrUywVulIketisVFvXmA9dsIX8bLeq9Btw7Jnq4/L6zqHccuHMW9KI7WtOLB65XR2M9F4x5FvXGAzfFRA/zd5dFvYXALbeg95JFvdeB22NB73uLej8Cd8GCXqcIa3qJwPWOMNcbYlFvFHC3W9BrtKg3H7hmC3o=
*/