
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/fiber_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/fiber_winfib.hpp>
#else
#include <boost/context/fiber_fcontext.hpp>
#endif

/* fiber.hpp
+6gr6UjRNvIC61DGkvrq/SXvgtD1jlR1oX74VP282jMmwFCfvdKem6U9D1vtqfrOsT1lzF1QcZ91bM/Dzu2p56xOzTzh7bza93Cp9o0jbaZq37z8LCbYMZPGjmWKLmnnv1+9nRurvKP1mrxdlB2g1yueruwg810cqh++jbD1ReC/ty8S8Hnqy7bg89oWrz7hXh31yUDlUBrqx/y2pZnVJ/kZqelO3zFR0ic7VdyhRn9ydugX
*/