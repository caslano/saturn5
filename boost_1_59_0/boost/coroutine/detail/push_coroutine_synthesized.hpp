
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H
#define BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/push_coroutine_impl.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename R >
class push_coroutine_synthesized : public push_coroutine_impl< R >
{
private:
    typedef push_coroutine_impl< R >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    void destroy() {}
};

template< typename R >
class push_coroutine_synthesized< R & > : public push_coroutine_impl< R & >
{
private:
    typedef push_coroutine_impl< R & >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    void destroy() {}
};

template<>
class push_coroutine_synthesized< void > : public push_coroutine_impl< void >
{
private:
    typedef push_coroutine_impl< void >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
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

#endif // BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H

/* push_coroutine_synthesized.hpp
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
*/