
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
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
*/