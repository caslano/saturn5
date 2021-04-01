// Boost.Function library - Typeof support
//  Copyright (C) Douglas Gregor 2008
//
//  Use, modification and distribution is subject to the Boost
//  Software License, Version 1.0.  (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_TYPEOF_HPP
#define BOOST_FUNCTION_TYPEOF_HPP
#include <boost/function/function_fwd.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(boost::bad_function_call)

#if !defined(BOOST_FUNCTION_NO_FUNCTION_TYPE_SYNTAX)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function, (typename))
#endif

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function0, (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function1, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function2, (typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function3, 
  (typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function4, 
  (typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function5, 
  (typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function6, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function7, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function8, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function9, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function10, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename)(typename)(typename))
#endif

/* function_typeof.hpp
MxRQwzrrzFR9v8vxLgLo4JXtXrNT/Fqgm31eHgDpCp1DxsMsKUlInu72+hU9FZltJzIedVfnY6DUsSHWzFjjlNwKvgC/5WeO5oAuVh6xf9WJwwgfpP1GMrK3Ha9mCcPh6NTr3Tt0wW1DH8VsLCjj1gmhNEzkD40pPml/kd8GWMW6HHtkQGp1cwZPolHfV2OjoF9NGgoGkXUZdIoiPp1pKR/GbbgQxb0io/+yBTkzLUaoq/5p3N7hiPCHWhX3LyOs9z8rDzU9BbM/WzbJ37HIJ737qs2V3E/KeJzOsG5g3qgOf58VtKOYFRAjsOsK9+3eox+7e7qkHfENrdIZVIjaGc+osDB8UHmuL2oF1uUzYoL005vVjQMKOL3/YtcMp6Ta3+meVM0Br23JmsC0aiWHWmoMIOS2Fsvq3DBReC7Ra2q4Ym024bxmDYEQO4Ty+Qjhrs1AeQmdMSz1N9JTy/aiqQD0ZGesqSl4+cMtcXp1+wKTiPDswi63wRkfBvkIi8RrUtdeQ3n3eHoAagS4iUi5vOrfeQUJeTMySEm8waXJ4S/Z0ERi+/oumBGewQ==
*/