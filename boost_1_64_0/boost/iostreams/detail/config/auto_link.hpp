// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_AUTO_LINK_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_AUTO_LINK_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#if defined(BOOST_EXTERNAL_LIB_NAME)
# if defined(BOOST_MSVC) \
     || defined(__BORLANDC__) \
     || (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) \
     || (defined(__ICL) && defined(_MSC_EXTENSIONS)) \
     /**/
#  pragma comment(lib, BOOST_EXTERNAL_LIB_NAME)
# endif
# undef BOOST_EXTERNAL_LIB_NAME
#endif

//------------------Enable automatic library variant selection----------------// 

#if !defined(BOOST_IOSTREAMS_SOURCE) && \
    !defined(BOOST_ALL_NO_LIB) && \
    !defined(BOOST_IOSTREAMS_NO_LIB) \
    /**/

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it.
# define BOOST_LIB_NAME boost_iostreams

// If we're importing code from a dll, then tell auto_link.hpp about it.
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#  define BOOST_DYN_LINK
# endif

// And include the header that does the work.
# include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_AUTO_LINK_HPP_INCLUDED

/* auto_link.hpp
Ir6/ilb/Xn7ZEDwJTBIL16dfU3soeeNq6lrBqgIYMVJ/v5iAM2AQvZSP/9SYWgH4Vh57vBLtMoNmtRsnEkGqlGKTHeFdi6KUnGVzLH0o0qRNAWMgiUAq60Qjbv6i7TsSbDupwRCy9Vfopl6Bmo+NCtW2qS6y8mRmKQ/41X0chkHYJXqtOsEwmCdE1f3VOrbIz4ff+Fy6oLUOL7CeE6MOhf+5ZaHxvtsNXxvNw73T+2CCb4g2AVFGa0bqbpcmmL8/6+mHJEXyVU4/B9bwWrYdfuC3o3sgI7EuqbiljH8pShlvqql0kUQ4waXMQTEjVJzMGOzMXUro+QyuGsgfR3/59XF5x6XW9MTV8O6ZaMHna3MK/C79NBF2xsMph0FuCJqE8ppzbWiU5E4kNVQb9BGqOQPhbpxgyUpTP+0OlvXbVNB8NU85ixBO4dxgIf9+2TMXme2zkbqYHFh+DVZRi2XTYp7eDoNs5RxYQDuw6iVPYEmxghlEiQhlTFaj+Qj9fBms4mmJZj7HVJBSSaxNjCjRyiF/diI1QkcXfolytFOydL1l6mDBfoAQ5ilKsA==
*/