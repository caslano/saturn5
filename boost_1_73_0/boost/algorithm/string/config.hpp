//  Boost string_algo library config.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONFIG_HPP
#define BOOST_STRING_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_STRING_DEDUCED_TYPENAME
#   error "macro already defined!"
#endif

#define BOOST_STRING_TYPENAME BOOST_DEDUCED_TYPENAME

// Metrowerks workaround
#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003) // 8.x
#pragma parse_func_templ off
#endif

#endif  // BOOST_STRING_CONFIG_HPP

/* config.hpp
r1obRpY6or4CEJrB27Nc5k8LDwUSvNUpwY85zOD9ErwqLZi65b5rBb8uwV+ygzO3SpUHVzLsLQm7LC3MI2FfYNj7EnaBFRa5lJ7HxPNU27OMnu4V8MywPU9pDvngI5Rj48HfgvLC8nhVhatgLNSNb3LXHK72BiL5sePOyMnNoSutOLcgTmKec+AlGZ/HM8NjYsczwFZy3AO2kuPusHtSz6Bzo4bZVCZYU9suwaxXgyqMdT92
*/