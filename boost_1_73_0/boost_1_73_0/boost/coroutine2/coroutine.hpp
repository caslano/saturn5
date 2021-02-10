
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_COROUTINE_H
#define BOOST_COROUTINES2_COROUTINE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

template< typename T >
struct coroutine {
    using pull_type = detail::pull_coroutine< T >;
    using push_type = detail::push_coroutine< T >;
};

template< typename T >
using asymmetric_coroutine = coroutine< T >;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_COROUTINE_H

/* coroutine.hpp
kUPBEy4eKzcLVhhQM/SA/lOhDfosjVC5h9dzMLyY69oNBcGkVsAemZBsitcxA5kxC33WbidlITGTdqoS3U42UHiZmT/J6g6jmbM1qIUBo6DU3AU678JcpWJGT4QIFxflVAqduduw8MI8basCNJeydoemgusqBQ5hjZZLJ2GB0QtDD61yTbctMzXfO4iw1o5mZZHjdQgLnksVAu9Cmae8sOctEJtbapQt5N8p2Tb2FFSOUUHLD2EQtmDKtNAu3A6iq+Amglt/MvFH0R0El+CP7mp/7wejC+SGwFsL4KtFwTVGUYCYL6Tg6d7lP1XpjhddQe9mMgzGUXwZDIfB7TDo+dEgGEEXWsen8HeZI7uPX7agJcWUyg+nXvfU6+AC/Rdzptex5oYKjb/IKY1uwysY+dd95xu+71/ATEmplnAVRWPorlZI11QgZY22xuHdKBiHg9D5ReSJLFMOb+i2in/ZW8c6ThSuPw3igHbgKENmSCTI1wNwQar8AXhO/D58ba+86Ie9yWBM245f7aNs2JwjKZCKlsbHyBAptaUHwlGwYk3LdS4sX8NQJYxAOIOMM6SVYzKUD53XvHi0nvJU72oSyWJBqM6TzlkNiF4gmNxK1HnqFxK00wueoJbQoOASt1H1yBrcYFOtJCmJsGgC
*/