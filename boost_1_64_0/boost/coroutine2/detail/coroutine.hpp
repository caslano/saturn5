
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_COROUTINE_HPP
#define BOOST_COROUTINES2_DETAIL_COROUTINE_HPP

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
class pull_coroutine;

template< typename T >
class push_coroutine;

}}}

#include <boost/coroutine2/detail/pull_coroutine.hpp>
#include <boost/coroutine2/detail/push_coroutine.hpp>

#include <boost/coroutine2/detail/pull_control_block_cc.hpp>
#include <boost/coroutine2/detail/push_control_block_cc.hpp>

#include <boost/coroutine2/detail/pull_coroutine.ipp>
#include <boost/coroutine2/detail/push_coroutine.ipp>

#include <boost/coroutine2/detail/pull_control_block_cc.ipp>
#include <boost/coroutine2/detail/push_control_block_cc.ipp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_COROUTINE_HPP

/* coroutine.hpp
cItvKVkKrMLd0WW0REZbKDHtuB1qlaEBvpkboZhBDyCFl+QAkwViGgI+iVJLei5csjrn5Eo2movpW9wpzM5NB/WDlJyRbE6oedjUp+B8QIsPTnJWRTec8mH46HYqmQSXcAsVDVhTCtX7dRPepipQX12yaz3jhYpM7brCZUZbMSHjuNb14puRtj2eFUNG6oO1HvqOMABeEqyfOYidkObg2PuIq2oDBHJ6T9HSb0/z9N/B9g7+k+dAznspuBS+k+ZuuM2ERnHdmUxD0f00nIHKrZsR/9Ng5209tK0o0vm/JWXVH4DgFqphYRWMe0whdgGuV/JavO40KoINvLpdO0q20KWGcxPCoo7kwcfYMOZNYBJW6lNrrR7cFCT5ZAbakU3kIzMUT8q4sH73MsG7SAwFT64bYaLo/1jokuoarlS+kRxPhruh03lUTQidtlT5aQkD0FRyTEa6PGa8NR8lbShfUHc+MFZP25fpa9r6se5zTxYsznjW77Dj0v5c+m6AzjYs8kUz1zhbGS/Vxxh3CyrSakPNqCqP35qv7lrT5XMQXTfgWlNVzGd7gjCGHA==
*/