
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
+O9hVr+qgc//8FZ/399Kutsvje4bbtFgFj6/D+NLkh+qVn6pPRWrZSvEjz3LEhMe+mOP1h+3JuDw9WEi
*/