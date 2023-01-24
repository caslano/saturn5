
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_PROTECTED_FIXEDSIZE_H
#define BOOST_COROUTINES2_PROTECTED_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/protected_fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using protected_fixedsize_stack = boost::context::protected_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_PROTECTED_FIXEDSIZE_H

/* protected_fixedsize_stack.hpp
hcixz7Kn43nB/eJK3fCNN+NX5UpSd0KuIV9KJ9ELbHVAz8tWvFYqK/SlF9SBtoHC6I7oALQlkhr7fILezFuvzAsH7L81NJ9AyVz6VoOWdLwOt0wDr3PsZgzx7x++sfFh/nEKaNmhZae+RpmuOhIsh1Xu8fsa5fPSNkircaZApQQlrDxZTY4DvX6p3InN9GkKkpxDDywtmTYpDibQ2PitxMt2Ojb9LBt53d+ZyD+pFoups7P5SGTVJ4adzZXxrCkW0XYcEZZAPPIvkd8EHUQHwqp0qAqI/mDd9ZBYmNu5KcH5GR8TOeQLj1z5Ml/nq4Fr2XpEcHeBxun+kqsQLKNct1rQ43MX/G0wluDknCnHoSsgTNX40+MXBHPWL8XfhBSuYfllabC700ix0aQnknpVnWOdy4a5yPtVfm6L+J194zWFoCtDzs2cZjisa8aMI02k6pXEpqL/Oe6xJ0hiJ2lKxrNRimeEQDYxmN9WR+WV2ZkKwcgZT8XSYdBvKFBCDVc+BbugbN9Q3EaIaJmn7iHCCrRap0Pis3xzacaRoeg62jf4RbufsrZQ4rWYWREXdx64cGBUsqhw/zDWPi8XRe7Yanm6GGsPDPwuPD1HZYd73/jjY/d3T73eraaqoZaV8dykl8ol6hEiqpFjtIFdN0W+GhO3M7HdgVbPufa3BMsTvWvn/uM7v4HAp3bf9iqv+hLqRKf+FveGFhwnC6N3
*/