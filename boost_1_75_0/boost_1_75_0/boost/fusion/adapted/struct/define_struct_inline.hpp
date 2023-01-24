/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_INLINE_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_INLINE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct_inline.hpp>

#define BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE(                                  \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES)                                      \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE_IMPL(                                 \
        TEMPLATE_PARAMS_SEQ,                                                    \
        NAME,                                                                   \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_STRUCT_INLINE(NAME, ATTRIBUTES)                     \
    BOOST_FUSION_DEFINE_STRUCT_INLINE_IMPL(NAME, ATTRIBUTES)                    \

#endif

/* define_struct_inline.hpp
/sQsrD6hk7JnLCETez5uIa2jz2qVq+gyjeDX3F6NwbXX+cvLbTzTeJyAmLwMlgFZ7vxZqUXjxc2nB/IKgB9icrce28CJEt58zJwft0e3NAD3Xdw6lqOqPEPMx60lGQwXDV9cHhZRaG7Z2zl9heJhnUgTbQRkv6UyRqM5EEIeimZJ6oCt07mDktPHzN3Xs8D8/iT8/i0Z3m/h/Txwix/hKrpYIk95Q+BzxKp1G7aHB82RJ1OoGrj2A06IhUlTJZ5cD7PARFdZqGAxQ7C4gr5AsPj+cmIxIAHfjw4SgWfPt2vGhPOD8g8NDMw/VJIfkH8IwY92Iwi+33HvCRhzjvN0bPTR9ta+x6hmOOCcmIIDTulDOOBsvV/ue+w/Zpf7HnEndLnvcWSPXQuEErn5lC73PSgFegZAiTyWrZeMCWFgpYcYpCgHnPd448Hx4ovgN7qREYX00gFciHEVfANy2KsZhLbZjpMYLV1qM2E2UmFaq2JtfH1S56BkxNrIZayNXFFXj7ck1sYuCc2Qa0Iz5KpYG7mEuw2368Yf/wg26wubgqNk1Z4saleQPvK4djGXcrzyZh2kjzyz9jyrdow7Q8QkcbsBpI/etFTOv5zkp2jFLnTC3EgbcN6dFGfGTQqxB7VdQXQT6y++3V++yyqO0Zd1QKgxZ5NePBoxkTjCq+ZuRhDzmEhLHokXpuJBXHyCLXpyYPCF9KpEoQgAbsgN
*/