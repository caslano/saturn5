
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
0+HKg+sM1w4R5zo3roy8cED3DHn9/95w1cAoqD+Ki2Msbp7qNzxjDRe+zMJAklsSz3h+pN861BqbXj0ie8WqNTa94pVeDBgRq4QjyMSq+JzG1lN6oA27KUFKZuvFmCX6EfcELx6sjXiBfsQ9wdMGayNeoB9xl5XzpAV31UEV6aHSgvE6qCJAmY0VnpBwnrgY1Xm26pwnrovOM7Gli85zQZud8xSuiOo8e39n6TwpcogVdUCd3RpQk/PE2/RyR3Uet02vBGvncUvOsyMaKWgutYcNWmKkDHFqjU2vnkovxVEzZEf9/Q+jo2YE3yrVvMuv966M4DOlmnf59d7Vw8pRdw1eqYMq1kPtGjy/1Hg7wDww4S0HjrpOc9RVMZq14rvoqCtWd9FRZwXtHHXq11Ed9YZms6Oazz/dJkftlvOojrpNThLbLScxOmq85KiX6NaInlamd+lNcul3Nkb36Od/i8Ho5lHJXG6yu642ZoXlsVRS1EmSZKN/cmSvHmqNTa8dInvFqzU2vVKUXsZ7Aq29/giHy2UiXBb0L1GR1fOYWbyKSN1VuorgVUO2o9LD77zwVUSBdO+4F1phXr6PswFcvz6Ar1Dv4U/w3jFvcjkrvfxyVKJlmtxymtwyweFDy0Fay6p0TpwCTpM8v3QOPuOHjlBbWmSpF6X8N1DbM10snz99mvr23UXWNxDn2QP/bipnvr8Ot2jDt34b+c0lkHfPZ0o30vsx2SAlM5lcKCV7M7lMSiYugPhMtfUtbHiNANg/ZBM8j6/gQC+OxtCER2Po1IwvZ+X+TEndvYUNQGcnP1rzfh07udgJwaCTuG6m2DhniSLkbA/7bP7JH5jrH99YRRn8igyzZbjfOiS4lwj36p6AQxO9DCnj43EWR0DqQa2zlYwS9ubRC7I8KTefxGNQ5Ry1LVle4XBAyQWObTI9Vx4lFfL4fyYRYhf6A00ps4CvHJP6Yxf7A++nzErAfioXToFd2ZTlE51tzxSDPc2r1gCM38Ha1fAIe/ZFciGv1jTeZjZkj9jEWoCnqD9LAIxzmQbaGI2gEA2KOCfY70TalAfLtA5Y0lOCsBUS7DxTNV44TUBdGdOtT+FSQmfpzEjTZ0vgBndUxqHEqccMqpiarMhBQh6M33SC19Flo2Vvu9GijtrHq/69Uasv9ZXIQzb2+OhD1vo4hqJ1FKZBN8bD4OHaQGu1DYZa5pThuxjDp7kJhWC6syGdqQ7pDL/Xonx0cIq/06HuH83SKbOKk0pU604sSippe9s0pBL3QHM3xnM7HEodQhxG1eOBG/rSS8dxFGuR0S1V7GY1qvUY1U7WNfPk4uhYT6RDwNtUDqvvftw/YfXeK/49q+cf23Wrd3n54+hwmkxmRc6HwbP7Ij9uPjfn7dnxBf2fySpeO3NwA2+/BkelKhHb+b3ViM0TXkqxI2oRGzN86upmnEwgj5hLieAQ+qgRXJlTjeDKnaYI7kB88/nxX6XoaS2+glf3MURwI/DNCI6pcASXLXeaIHdaz05H9YkawUFO+whugAx3qAy3gXAbMwgHNaxBaIGwQAjsXg3vaGztH1grSZ5S+6Z0tgxeuWodpiHrcPTD3apnLQxC+NkuvWwp42vCxmYtWZXIGW1BLZPWUPDYOdySqKwYrbLi8mG7jrm4WqKHGjGWFLPNUYG0mwOuiTlzWZ4dvsa+o+1ttEWWZVg3Mabkuyh49lcdoa5wyVa5lHWBC1WWZaOuTGXhOT9k8E1lVUuE09RZV8Z0KwTDsgcgZStZROvTiMHPC7zIE5klUscmj9osOAvVrd8YNic24io9jav0PajXDYjWky1mskUlWigjNNgARHHZrJnNTkKzTowHfZmh8QI=
*/