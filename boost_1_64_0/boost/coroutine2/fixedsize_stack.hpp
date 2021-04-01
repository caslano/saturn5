
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_FIXEDSIZE_H
#define BOOST_COROUTINES2_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_FIXEDSIZE_H

/* fixedsize_stack.hpp
WAbFdCTxfJyAkvz9fyiLmXC8Dt0DUiunwVmiiZEFrtcZiaaJ71xp5NzYw7GtTxkGCacoGOXO5A/tQkPlKESA7tvDJfPeYizxtrPEuzJ+jB0rp9svHffI8D6zIZedU6WiGKXLbKpREECv25pbOA4uSPgIAQKDHmwPms7rwvpz34N93CIj7PGItsbtON7Kgjcjw0JKhR6ruIpTk27W7yrgfAZVXnYDN1/LO0p8YIe2FJQG+oCUz/McD0cItJpNMtt/TSYXKO2N80txKVrQ0qR6MxmIYiyT3pYm9WP9Avz8q7rqafYLUJFhBQUrVk8AgKhtSWOD+6I0BUuS0LKzfLa10mHBkumj+KSLCIfBS9PdokYD12kiy1CSy5rch5aPWALOLIxRdxgFO8kt53kscbjtHhvwmR70quF2maEZb+oivBwJsmJAldDhggYdXfxB7UdV9bG7Pi3IKbEMMhtK/Ls/malB0dSnCDohrzLV4pzF8jvu8TEpKiS71rLP4zik2z7XU/4/quDES0S3owTjzmbnYtBRIgRB1Edxk4wMeAjdI8gODFPFiIPYzALO3w==
*/