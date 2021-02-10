
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_POOLED_FIXEDSIZE_H
#define BOOST_COROUTINES2_POOLED_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/pooled_fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using pooled_fixedsize_stack = boost::context::pooled_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_POOLED_FIXEDSIZE_H

/* pooled_fixedsize_stack.hpp
8ZQs+axhxhkKluMAQ2DRBim4Bmq2lD3lhdq2U4rPCV98BUF5Lrfsc+rGIdWDSCrtUGRUHVQxYrbt3g8cY52pCrNfG0AHo8ugElm/F8W4UINajZomBvRWIiMfduuw3/JrZdat/tK/GUZOx204atcbGTukzYPw0K72P/rX42Hf8fKZUw0XW5M/d0aPyIU5wDkiZge0eAj/OvB8MtHCdiLhw4XW5sWKrxjB6CVq3kJHaN4+gp1FQn+rBhffPmDJ7TRqSLIdRJuDhNBR+/uhPB2Ox8MqhK0Zvlxhy5hX2b12/nO8mbDg+B/8wdA/HwwH0Z3j26lpy0wA2gOTfnQzGcEHf3jTdya2/2t7cT8O3oOYVcOP3qfKxUIVZtNfqiM3o/ej4HYUB3Yu03GcVlURW2G/D/4wDPB143wC32jI0MLCI87N/rOdPetGu892nxFxz/P+bi+4GUWNh/8BUEsDBAoAAAAIAC1nSlLA+fCeGAQAANMIAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9GT1JCSURfUkVVU0UuM1VUBQABtkgkYK1UbU/jRhD+7l8xSr8AMg6USvRadKoJprgX7Mh27i5SJGtjr/H2NruWd02ISv97Z9dOAxQVPpyj
*/