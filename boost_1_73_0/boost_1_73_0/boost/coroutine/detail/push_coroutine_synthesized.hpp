
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
H5jjzs0/WhWZU/ee3bhaKIE8fI7H/wJQSwMECgAAAAgALWdKUlKogA4TBAAA0QgAAD0ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0VYUEVDVF8xMDBfVElNRU9VVF9NUy4zVVQFAAG2SCRgrVVRc5tGEH7nV+zQF8mDkRxn6jpxMyUKrqllYASKoxnNMCc4zHWAo9xhW1P3v3fvQJGdurEfgkc6dLf77Xe7367ttQkHP+wxbAUHLz6J/iT44LpzClv+J03l8w5J8gD9HzqucX1FqAnsvR6SMbzK6wFG2isZYp2p9yR5Rbi1Iqm+Jsp5nahX3Ok9B/8Zb7YtuykkjGZjODo9/QUO4c30zdSCT6RmtIRI0npD2xsLzjK981tB7u9tQT9YQCWQ0n4CGBdMgOC5vCMtBXwvWUprQTMgAjIq0pZt8AerQRYUclZSmAXhyvN/t+CuYGkx4Gx5B6LgXZlBQW4ptDSl7LaHaUgrgeeIgPgZExIxO8l4bWN4CpK2lRhgFAlSCg7klrCSbDAckVBI2Yh3k0natSXeZJLxVEzSXSrsQlbf3GqFbCqyBd5IkBw6QS1Q9hZUPGO5WjFFuNl0m5KJwtrTwoB1NuEtCFqWAxy6Mir6K1CIhmxZ
*/