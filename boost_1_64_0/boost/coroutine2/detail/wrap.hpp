
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
kCGaGFHHE6Fe/omdHOw5ChjsruIMeDnYPpdXmQVo+8gKmxRUTVEaT3tqAGl4FL0gndvMNk4klLCkwKDvGkLUDNCddU/BGq1vXDbId3ut044gRFnWZaCcXKY0JbWNBp8WXi0RexLOBSd4Fg8vP1ft1dYm9DU74Oz+ivxaoIT9a1Mjlp8ubvrwUgjyAOL9p0sW1cNavZoDhRQMyLaEuT/7qagl1PFTl4LwDSi1mGe389dAicC1XE3GveqAj3fUx2FLZAhctH62Zf9EWPw8TPkGL33WM1p+nbj396ciEDOmJ990HhBfzKZECpD//y5xDUT6go8/BzOvQuz++i+q0XmXK35ozIphEgs1b+XW6vmpWd69DFac9l0pmc/f9hMzHXkYxdqDYW2jmlSLO48DuWtnkLOdfME3iVkzx3knRk+9iYwurAdJ7QhWe9vfnMAgdaOygh9fogvw2Mwqq0gkI8tAr904XuMhmpVlGVZxuNflD/DtbnMa3UZdBrl2TgKl0HbJ6j8s7miKAUCOmLgZuDOZOORa126NKK4F4KXBBDUGHtz5W7izgK9HPqpBoQ==
*/