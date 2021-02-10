
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
/6cPxpmeYMdZNTHGKfxjwZfyMYbXsuk5GYyj4eIIA73R2wEbi8QaD/saXf2g7VfeuLAqIbdDXh+tf59V6V15QeidBmGQrSyvLIftP8xffyDxs2USwZUXLn0roRp3murx/Ty+BDasr2Eq+653bSsk7qZhXw4Hl9FlFF9Hedyr3zhhDwaq7dT3wQvTGCf6NPkaLWCjWLDE53fzOIr8eZZn8RevEj+Nwyt/Z98LOY/jy8A3An1+/R9QSwMECgAAAAgALWdKUvkvyKWpBQAAWw0AADMACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0FMVFNWQ19DVFJMLjNVVAUAAbZIJGCtVm1P20gQ/u5fMUq/QBWcBtq765Wrzg3hiJrGUWzoISFZa3sd79XxprvrQHTcf7+ZXSdAoCqVGhQcr+d9nnnG/lUHXv60j+eTOfjuJ7HfBD943ShNlfyHZ+ZphSS5BfeHild4fYarHtxp3Sb78CytW9izWknr65h+J8kz3F1RkPSvR8pXCf3EE6fZ6g/kcq3EvDSwN9iH/tu3v8EBHL46fNWFE1YLXkFkeJ1yNe/CcW5P/izZzY2v+fsucAOs8h8YjEuhQcvCXDPFAX9XIuO15jkwDTnXmRIp3oga
*/