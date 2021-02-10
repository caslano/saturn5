
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_INVOKE_H
#define BOOST_CONTEXT_DETAIL_INVOKE_H

#include <functional>
#include <type_traits>
#include <utility>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

template< typename Fn, typename ... Args >
typename std::enable_if<
    std::is_member_pointer< typename std::decay< Fn >::type >::value,
    typename std::result_of< Fn &&( Args && ... ) >::type
>::type
invoke( Fn && fn, Args && ... args) {
    return std::mem_fn( fn)( std::forward< Args >( args) ... );   
}

template< typename Fn, typename ... Args >
typename std::enable_if<
    ! std::is_member_pointer< typename std::decay< Fn >::type >::value,
    typename std::result_of< Fn &&( Args && ... ) >::type
>::type
invoke( Fn && fn, Args && ... args) {
    return std::forward< Fn >( fn)( std::forward< Args >( args) ... );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_INVOKE_H

/* invoke.hpp
yx6h/2DiLd7fQDWF56zHbAJvynqEscnKBq5z/Zxlb6C71UXqn6lOvs30I0b6zCF/Lppdy+4qBeP5BGbv3/8I7+D749mpDRekZpRDomi9pu2dDeeFifxSkYcHR9IPNlAFhDsHgGnFJEhRqi1pKeAzZzmtJS2ASCiozFu2xj+sBlVRKBmnMI8WKz/81YZtxfJqwNmJDmQlOl5ARe4ptDSn7L6HaUirQJSIgPgFkwoxO8VE7SA9BUXbjRxgdBGESwHknjBO1khHFFRKNfJsOs27lmMn00LkcprvpXAqtfmqqxVWsyE7EI0CJaCT1Aa93oaNKFip7ygRBptuzZms7OeykLAupqIFSTkf4DCVUdm3QCEZ1LL1Smiweqb0TYpaarZtJTYHC1HWAajs2hrpUBZcVwgU3oauLmhr1hsh9iyDykbyV0b2XHsBosaqYOQm4CcjWBPJpA03fnoVLVO4cePYDdMVRJfghqsB79oPL9AbDFlboA9NSyVW0QLbNJzR4oD8m+50y0mvYL6Mg2iRZu4yjWLv0ou9GE5gNDuF37paW/uHEYw4W+vZw6lzcuocY0D/yyiRu0xSpaeMXzSURMzkCkL3k2e9BHz7DkinxIYolhPOd9A1BcGRa8FbWtIWFagowYEYnGQVRovET6zv
*/