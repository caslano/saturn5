
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
dffuOgNcU7b8ufC2uInozQ4XR47glWEoxyWH4f68BXJyPwkeaCvlMzC4PdpetycbqNBrkCG5gp664G/8A+eNCvOlgczpt7kPLvP+muVRnkncHYJ7u8z+yZ9WtK7aV2t/ycJxPut0ZzxY5/U0kSe8Pp3UZt3+sjtvqGs+gKiZ/Dy2UFuzfG3MyN0rGP0bUaTCo7WpQNYy/n20QqLyQ5tva01L+3OX4Y7QRiHSAcjwigrvWY+9TKsIxYXONAanZ6wH51Wh3Wx095NpsXwjUvbfmgjsVuKqCUXmUZSQxxrxnXK/0IzdPk1IKvmubGFkrKWFSotjb+vJPYWJYWY3/4RxT1f0rvy8leJI5dULrFso7JSqVKExvz3gzcPtamq93/JoC7398FdUB8yBFAiL5LioF+UoIfFUrDTMTWMeiI0sU45DJh8u9Kr+FGoomCGzbTGILLI1HYomIkNDeiWP+SQog9CQrGkD13fbGqaIWQzn4pgfY03jLPXbajQLrCTYjV3UaPOBxFR+JxT9XlbI2qo3AFwRLmOz3kh4mQiGXX2PmOqaTKfh7chu/5b4AfI59BvqI13t4nd8UPgNXROOnpA0vO06Zkb/ADW7SOgb6TJ2wQLrAZyOG0vhcp8s9fi6E83nOcNXAlQMmYKa7II+HVE0huX4IoMup47Pw30jWMHrUK8kkhf1lH/8+SQLOtWHVYdVF7zxm7yI4W4Cg32y
*/