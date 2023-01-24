
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_IS_ALL_SAME_H
#define BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename X, typename ... Y >
struct is_all_same;

template< typename X, typename Y0, typename ... Y >
struct is_all_same< X, Y0, Y ... > {
    static constexpr bool value =
        std::is_same< X, Y0 >::value && is_all_same< X, Y ... >::value;
};

template< typename X, typename Y0 >
struct is_all_same< X, Y0 > {
    static constexpr bool value = std::is_same< X, Y0 >::value;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

/* is_all_same.hpp
QiZx5mlcxCcj0eCRPQDffN7mD7epgiRTqIBUtNnJSuT3UmhAvkGJ7Y6Mk1Tk8xwoyvVNrGWfIDhZi+jlK5TpsU/pJKbjd3QStLYmL6UiQl46pk6tByOws69twEz2ILYJRztUf94B/51hiFpsgLauiAx5Xeu/M1x7HReJ6VPza9l/eQdA71ApcklsjkPpOj8YnbBdQVtYyuj1IssTeWWSP7K4LykewWE1bwkb5yL2B3KUJ9JRjlIJJptgTasbsSKElIydzkuW/PkxQaspCRERWzMAgeUoCafEzSlOmXVnBDsYauw83sb4CP4apVw2NqQYVUGfGU40egfWafFNVUAST6Qamg5MbKCJB93Il0+l6CceNQfXUhGc+MsgYwsk5xzTwEWxqnZhItcuyHtgPeahtQMMqFtiR6K8RhzRMhJVsdezZ0LGpbaWilPohgGLC6XqsBQm13gWD7mZdWilO1RHNeRlpQ70nIIJykay4TysRk6R3Xvb4+4UNoyl82nlcpQpfROxCQmDaLENcw02RicbY0h9CR1Rag9tXRpuwki8IxLI0CUn4MbC5SbOvbrjIN4S1rsvDryDFX9SFNSQE7Rz/hD0M/wUBAuHsGE1yvM/JZny/Hnm/PCq2/3te4B54eyfkqjFox06qt3H4xywAI2YncmG0QbC7fKWYA0b5C0DZ1rKn0ZkH/RAOM1P/GK4s24BHxPo+kPY/qZY6LHk
*/