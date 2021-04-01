/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ASSERT_HPP
#define BOOST_INTRUSIVE_DETAIL_ASSERT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#if !defined(BOOST_INTRUSIVE_INVARIANT_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_INVARIANT_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_INVARIANT_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_INVARIANT_ASSERT_INCLUDE
#endif

#if !defined(BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT_INCLUDE
#endif

#if !defined(BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT_INCLUDE
#endif

#endif //BOOST_INTRUSIVE_DETAIL_ASSERT_HPP

/* assert.hpp
LmLym7VELQHIVFMpCqTdgKLpQvtMKRkCSJCbtAlAS8G5kCnNKKDSeXyDWwlJuJyQ5EAt8pMLWbLuB18ZZs9PDRyCcBZ1QU7kVJj59ptWa7gdV2plsOYvVj2PBzRXSXwlO1bkC4L2mscg5K5dsP43kqAHgk4GnMDPMTmwX9lgzJqAFugsnPNJZ+tpmo81FeI96nqpIZM99ZVYrVcfWOf8ETlOP9HLMmpjznZJDrmtNQTzwhYG+YkgEFtwUm/5s4g+gDDfRss1ygADTlbEXlY1t7xMcZR9U/tIIUB8NL6wG7UF0RFFSFwQFnJ9zsNQyxLAzkHg/wZ5YwLAzMeeD0Y7MiW6c4soTFn3cz8xrJb5bymp9sOebF+OwjZWGOZxg2G6XPHIl0iDK6JOSj0EpxSZhN8jBy+eZsJ4EFHLUREx36m3Jic1stXK2bbQBTGhJop8OpNX58V8o46KzOa3LZHQVPAtwpCQfAJcDCxLJ3vj8/54VDy11eDLP+4s1Xi35GyP+Lc8Vm+UtWtUPslJ2tsNeUS5wiyEXjVIIDf65YKJnPobskJBCB41zMHnrQ==
*/