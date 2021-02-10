
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIXEDSIZE_STACK_H
#define BOOST_FIBERS_FIXEDSIZE_STACK_H

#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using   default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_FIXEDSIZE_STACK_H

/* fixedsize_stack.hpp
np/K7YZ3bb7rPiliX8J0/OTcX0yPV3PfXwxfHRixtPiUzevGjaeAdW2FSzMy7FB8G23Y+OQdmUGg2ANraphzQVXcpe0AYarN6xo1eal5b+r9XjOQ0+1BbcKUGZVYP+2ZSJmg4XA2CKVkGREC4Nn9TW3VuqfUXTVkDbYjU99ZhEPqsnI373NJVt7ryKTLJCo7iDRSl5fW5I1z77Fh20F3TkVe2+fpw+xFShm/IlYWtJtNVttMLKexpdbp1gMIu+eos49jbxnEzmwZBHaBmhWHkzCInKXqid3xjDbK/+KdzQPfGYncaW3Lav73HVPjgusheRTPh2bxAP524L+eZxbuvY4eLgz6exxvGN0tOCJ5jQeE9Gi41dkOQEn8l4VU+v3bw6cD3HvtYIw6HZtO098RZN8VblsYktXeWelaNw1uD7qfJy2RiabqX/3jjHJuKfTOvWngfZoG03jleFnWjlJ7cdkNCz9eLmZw7gVL31lYIStohyE8pbm1vb43+85ZMHO7TcvZ6Sy8mCWhvRtMAKnFJR90OpBlnITHyZl/Fi5WHR5p+5r+FCMPaXISHyfvIN9jFcmRpdj2fhD5PnhBFNId+mkB/zfkMKAxJx5/uOkkjOJ+0x7aIzg/QPgXUEsDBAoAAAAIAC1nSlLa0sH9
*/