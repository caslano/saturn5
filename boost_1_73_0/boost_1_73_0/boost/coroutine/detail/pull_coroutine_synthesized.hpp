
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PULL_COROUTINE_SYNTHESIZED_H
#define BOOST_COROUTINES_DETAIL_PULL_COROUTINE_SYNTHESIZED_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/pull_coroutine_impl.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename R >
class pull_coroutine_synthesized : public pull_coroutine_impl< R >
{
private:
    typedef pull_coroutine_impl< R >                                    impl_t;

public:
    pull_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind,
                                R * result) :
        impl_t( caller, callee, unwind, result)
    {}

    void destroy() {}
};

template< typename R >
class pull_coroutine_synthesized< R & > : public pull_coroutine_impl< R & >
{
private:
    typedef pull_coroutine_impl< R & >                                    impl_t;

public:
    pull_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind,
                                R * result) :
        impl_t( caller, callee, unwind, result)
    {}

    void destroy() {}
};

template<>
class pull_coroutine_synthesized< void > : public pull_coroutine_impl< void >
{
private:
    typedef pull_coroutine_impl< void >                                    impl_t;

public:
    pull_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    inline void destroy() {}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PULL_COROUTINE_SYNTHESIZED_H

/* pull_coroutine_synthesized.hpp
mfu/OT647pyGJv8gI/eww3z+kcp/cJzh+hmpWnTj9XHeoM/y+kh17zWvcr3g+/n8M9LNuEj+r8XOsznf4qT0rPzP8vXWqGXqqH7WoJPvv/+OHtPXx18fN+lcaCUzGjupF9Ism/Qi9ic/peL6OrTyhyZJRyILDwJOUmXJ5onbCCMJ95mKpLYyJmEpljYyaoEvSpNLJSUqk3Q2GF52+z83aZOqKK3ibPOCbJoXWUypuJJkZCTVVRlmLYyjPEEExI+VdYhZOJXrEOklOWlWtgrDRYjM5iSuhMrEAumEo9S5tX3WakWFydBJK84j24p2UISpW93p6hLVrMSW8rUjl1NhZZPYvkmrPFYJXwERDtfFIlM2bd6UhYQ6buWGrMyyKhxclbRlC5LGFVpNtqQ1qleOLzbXlrNt0nx1YAhYq0BJYTTSARbYxTmAb1KhY2m8vQdil6VC2UP+iZHd1B5TrlEV1dpj6o5rtBBW2Sb92p28Gkwn9Gt7NGr3J5c0uKB2/7KK97rbPwc3FLIaktdrIy2qMKRW60zJ+CD5/7rpQTh5RWfTUW8wnMw7o9FgdDq9uOiM6AnVTp7SL4UGtU++qVEtUwuePT0NnzwNj3HA3+ZS2O3cSsdTxh8IZRFz/Ir67Ted4KHAs8cYqyNpDPpb
*/