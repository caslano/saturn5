
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINE2_DETAIL_WRAP_H
#define BOOST_COROUTINE2_DETAIL_WRAP_H

#include <type_traits>

#include <boost/config.hpp>
#include <boost/context/detail/invoke.hpp>
#include <boost/context/fiber.hpp>

#include <boost/coroutine2/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename Fn1, typename Fn2  >
class wrapper {
private:
    typename std::decay< Fn1 >::type    fn1_;
    typename std::decay< Fn2 >::type    fn2_;

public:
    wrapper( Fn1 && fn1, Fn2 && fn2) :
        fn1_( std::move( fn1) ),
        fn2_( std::move( fn2) ) {
    }

    wrapper( wrapper const&) = delete;
    wrapper & operator=( wrapper const&) = delete;

    wrapper( wrapper && other) = default;
    wrapper & operator=( wrapper && other) = default;

    boost::context::fiber
    operator()( boost::context::fiber && c) {
        return boost::context::detail::invoke(
                std::move( fn1_),
                fn2_,
                std::forward< boost::context::fiber >( c) );
    }
};

template< typename Fn1, typename Fn2 >
wrapper< Fn1, Fn2 >
wrap( Fn1 && fn1, Fn2 && fn2) {
    return wrapper< Fn1, Fn2 >(
            std::forward< Fn1 >( fn1),
            std::forward< Fn2 >( fn2) );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINE2_DETAIL_WRAP_H

/* wrap.hpp
eY1MtM3u3T+OX/KOhOBLMF8En+aLebp2gqLoT/Aj/+DQ3+82xLN0FYfwJVisZk6Mhs4l3ZU5y6IL4P0R1DPfCd42jVTkP2/YtAovwugqzKLOuTaAxPXo1HAGkFWaRWfZ5ewyitcDHh1Wd2QsLnRbljzn1kQVsgZ0w3LsBXaT2QyCRRLRIH+Kn9hPZrEdanBHh2Oi7r8XyyBJrqL4dPfC+RdQSwMECgAAAAgALWdKUobHTJ53BAAAYgkAAD8ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZUUF9BTFRFUk5BVElWRV9UT19VU0VSLjNVVAUAAbZIJGCtVV1zozYUfedX3KEPdTIs3jTdSdOmO2UTsqFxwAM4qWcyw8gggrpYopKIk2n633sl8OSj3UkeFtsIy/fj6Nxzr/1rF3a/2eX4Jhy8ehX2U+CF69ZpLsWftNT/71AUDzC80PEa1zekmsKj10OxA2/yeoCJ9SrGXEfmuSjekO7agDS3qXG+Lswj7gyeo/+x6O4lu2k0TI53YO/w8Cd4Bz+83/vRM/cDD04IZ7SFTFO+ovLGg6PK7vzWkLs7X9GPHlANpPWfhc0bpkCJWm+IpIDPLSspV7QCoqCiqpRshV8YB91QqFlL
*/