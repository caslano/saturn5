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
ZG8iXcjpBT2rsI7bh+u1ndhz63zL4d6xG/rVPfBTH3NDnW8/XNPr63zff2Wdb8OrYOr7uzrf4T8i/iN1voNws4frfBdfj7hPAeYdSHsI/qi3X3zp5ffNXu2e/i7FzrqxWXrCQq9zAcd1buecOQPrAPR5OJ0mh7fDmxCBPkNINLei2YUEpSIhEeTVGrAkDwrQUzl0HxirzF5luxDRejpM2v14x9jAxFAy56Z0IUUWQf0dpZmi
*/