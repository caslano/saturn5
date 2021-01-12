
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
q4b3qmfF3x+1LUXDSTP5UDvv3vX8cl/ZeAH0fb7x+kkXO9oJ94nyylTF7A/8nrgNYefunfaBtk3vXsCfiV0ndYcPY9fZE49mWrahjd3f8RNxe4kVJAxvXFmbZE17reOq7jnlebmeYt5Fekm4zU3ZvizX76pWdm+DXF+2d166k5kqexnnSdipMfujFYhdvZg9q6eLXUDdkQ9jFzLyac/J/vFKvz3SavH8ne3V6xPbPmLeqUdp
*/