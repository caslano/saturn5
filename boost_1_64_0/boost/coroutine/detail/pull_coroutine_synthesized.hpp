
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
hxUQ3logke0c6U7BGiK42+iVESmWMwWbK84IyW0ulrSf9Udx/4rve591Td+/0z1CQNJoLy00MEnQNZVPHPvwRQsksOYo9POrrGfXifHF6JwDsmNLzDTjE8rwLk7JPQsiscaukBWpTd+Mtd8feoqyIvCd+rAvew6E6P/UfeJoeeWcTEw6MTdyyl0NErd2bXHm865w0oDOqQ7vQAU+Ahtt5RTaO84sPtOqxfUMIJMAnzr0fD+tbxp/6YWI6t+X9m/1QDtoJWp7DBsPHuSypp+28MycDY66z5n8s5tb1+Xw6Yufj+Jo8BddDr7OZDod+nxBaEulBqgNKjaXAiDwqh2WBZWJiAcNBAO65DS3yYTBq9TcWddLq5WjfAt2HfcFJMEIG4SIOPun/1RGv8jkMxprdUAW+VdiDSPnTT7pkc+7T83WqD1DPmxFIkMEzRadSOW/AKyR+VAtdjv4I/ZUQK8pK7bMUAhZw6RkfdLvN+FCdkdqVq02oMbwz71u9GtAe6rJixzk7+Sz9qfVuFvX0I3/ofaLTLKa1EAi1D3POXAXJmGc7ncSnqeebroWMQ==
*/