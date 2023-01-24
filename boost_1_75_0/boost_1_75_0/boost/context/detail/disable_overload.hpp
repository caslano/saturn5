
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H
#define BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

// http://ericniebler.com/2013/08/07/universal-references-and-the-copy-constructo/
template< typename X, typename Y >
using disable_overload =
    typename std::enable_if<
        ! std::is_base_of<
            X,
            typename std::decay< Y >::type
        >::value
    >::type;

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H

/* disable_overload.hpp
PiTkRC3nfBRgknC7JS0dyMsY9osdcURi+UNBQSiCiglRPrpLwoasQG9CglAoIIrPMcbvm2GUgWR0cSiFi63HnBHkR6es33sTu5BUPYn1iqmZIl1OzxbhNzuJEDlSW6yvmM9qlPBUvma2mFMuDNblOFFinGQ6E9SiDDMWUk8AH0+cXJ4LsOoWeG/wqMaF8hFtXSd60IbhugRdIveSFo/y03EPlpj1jnXdZPctCX8SZprISiAlwh0cvjrtz6VD6JCALXg5J/HOMOhZynK50Wd3KaW81lo451okaw/m+/b/4TYBgNpXG17JoAwiCZh8aFMZXL9GvXYXG6MPIR/+GtP5Pq8feYW1k/dz4QXJljxO0RuQFTlzUUF/QTYUwBYLrxBmhhn+KeNNKLIRu9fvpzc4iR4q5nVorSljEg4qCrkPQu+tQCiPs0HbCJW60UAIJ4GQ7Q2y1BbK+zY5KCV6uJbk8S4qQEfj9yc/13vfaPumuaBxDdPvbXADms9NEPJQNNSSei3j32YWuto3SUbedhKD8JjsgNFAIWyfygoO6gmVrRnr9bC9CKSIqQGbgRCUlaHaqZlXC6qypjYgcovIS6wrKBxUWQXFAIb3gC3BlWCn4Oa0cU4ZHqnZi6JNknLRD3cS4eWypS/oMHEJCFi2BoIXvSJsXcDovusaoGj5hA54rLp9RAusCz7x45YJCASzd57aeIZDwQP3jW4JASYr
*/