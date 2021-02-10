
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SEGMENTED_STACK_H
#define BOOST_FIBERS_SEGMENTED_STACK_H

#include <boost/config.hpp>
#include <boost/context/segmented_stack.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! defined(BOOST_WINDOWS)
using segmented_stack = boost::context::segmented_stack;
using default_stack = boost::context::default_stack;
# endif
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_SEGMENTED_STACK_H

/* segmented_stack.hpp
zuceA9GdIkM3IAQCB3546oS94/P5kGOshAZzMReYS41KMAMnB2avgzK0D5+/CVEa3zbQqwpQHEVzxihqwaSUA7PqwDoNro+ccT+0BuN+3yygMEK/5/cDy8kyc5GMlITTo4u4yNQBHYfhMLDpyLx7pw4/hv5wH4/gFIvod3Gt3f3inA77rtXJ51ZdhyaZ77eqVOZS76DI5HyHF5/Sfy26X8S8cFO8eNjU2nQn3CoYU3TiYtGCop9Km9LfkjdYPHjxYv/Xpe8RB+Su62SSnvxxEvxVhHpv9vJo+Pz3+WV5XLye/zH5/mfvqxPtH59N9vXl6HTlvn+7EdKv9npivKf/lN+/iavx6xefrqI9cfF6Ppq5F0UvDYtYngrxZpUX79lPGOzu0lBUzAfm2ivxfSmUpt3urSDK+kid3LfW/6zOXNYXbZwnpmL3SzhyeobbPENB3CNvsHWvaqtLUf2mbnE2UxMLMuE0lYnSs5rS/BsFW+XaMRh5woivpGisPnSQ5MbD/DceqyoRJevaUdh7AhWgOrWsTE0wNGReK9vWgS0ljCrQA+pslYJSWeuGVo2iM3BRsVJthTWWPMBam8ZKEKoFo5nSsM1c2k3EZZc7QMec8EuRM/XxJLSKYIE7mszLpd4WwvSwYZH8okPHOCe4
*/