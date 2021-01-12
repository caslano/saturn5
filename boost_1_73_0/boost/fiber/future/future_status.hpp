
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FUTURE_STATUS_HPP
#define BOOST_FIBERS_FUTURE_STATUS_HPP

#include <future>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

namespace boost {
namespace fibers {

enum class future_status {
    ready = 1,
    timeout,
    deferred
};

}}

#endif // BOOST_FIBERS_FUTURE_STATUS_HPP

/* future_status.hpp
NfKyGFUeuree1qt54ndC3A7rrNiT4+K0T6JMnDqkOv/3u8Lb7e+Hm1A/UFReXlpu5WpYaVKfOsakUJs+t971fxwIetS1vjHTYwqtHTFJfAOdJHUtW/I+fI1t1i/slvSx5IHqc5xbWjlzaWVRhVVTJ52cc05U2/8O+0Tsz8yR+mjya6C024baPjQutPYAWrnWWamBbHOdytLSBbMKy4tK50geRaQ9xR4p8Uo2bbmoqrK8UHVv
*/