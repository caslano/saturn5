
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if defined(BOOST_WINDOWS)
#  error "segmented stacks are not supported by Windows"
# else
#  include <boost/coroutine/posix/segmented_stack_allocator.hpp>
# endif
#endif

/* segmented_stack_allocator.hpp
VlD76M5suLb4RtBWkeY3ZM9TbV/hg+BDXAaXMM9VDCi7OFo2xBZUVdUtjQ8CFSMDeajq25Zsajafi1/EvqrgSKpninwQ1YiVkqEKmuho7aeIcOlAxXYdSTNl/mL8OZxYoOMMmVfx57rpwdVRFPmR6PNBomPC5daHawQeHYMkX/R82/f4kQ4ukDVdVzwB1lmRAlcUPFg+w7lQjRQYoiJKMGT0SIFFVpWWJ/KuFCkwfEWTDZUXIwW2CBdOTRf4kZE=
*/