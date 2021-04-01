
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_DECAY_COPY_H
#define BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
3VsVQa1lL5DMj0r0Z1VHdyC2g7eYmv5UwYELyO9vez7DL9tQgyrho3l6XRUNtjSx9b9RQGDHbC/wYIkDe/spSWrHN9NMKmsOjE0/qLMoapQ8KIVMQwXe81VUGc5VRdroXKdsKRkEZuO6Hl6dDJ5loCs9XnMMMNKiXCO4QP+RhC/rD5R90+dpYiC1LECGDU4pCFf2YxhYgBdcwEqIunUULGhb+mIL88zcuVjTnw3OEAuz+xTMYYTD3UYL4Ud+eV8HWPolRW5eopxJXJphmNKMR2A9aH8ER3UYXcUSgFpzQYqEE99ej2O+IE6l41zTYMQOGEd5ivgVrv99Pxel/Pdev0roG5hOjbvrWJ3gxOcQbmkkEa50aW24Z4LF6xHYOT65ZTYgFIf8yWZwZzBRG32+f8QnBD7cuILPn0tVYVhxkReOTifpLyJgu2+L29GbG9TUQSjROCrMU/b9fJjWLAcz4z14a51To2oEd8Sev5DYD5IMUnr394l6xodi4Vm414A1RtyHz1AuVIm8fX8zGdzT+OYSUDPW2vFeWCrALdDOt9BSPyvaWW6Dvlz++g==
*/