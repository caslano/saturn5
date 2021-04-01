#ifndef BOOST_ARCHIVE_DETAIL_AUTO_LINK_WARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_AUTO_LINK_WARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//  auto_link_warchive.hpp
//
//  (c) Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------//

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

//  enable automatic library variant selection  ------------------------------//

#include <boost/archive/detail/decl.hpp>

#if !defined(BOOST_WARCHIVE_SOURCE) \
&& !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_SERIALIZATION_NO_LIB)

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_wserialization
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP

/* auto_link_warchive.hpp
0VpJjKslcwo847MQmRCLs/IUBkbysH+bZM3yKAmq/tHQaE+Tw0vJ17jGnpQ8h8QLLNG5jUZHbsBiD2hJieWeqc1unn6nFzfJ4UbBjUm6zBw8NuwDLlVrVGtxCNuE7aKJPQBVH5WjfDGMCmUsHtPO4UP+XdiFsNe3qsNxssoumlVAZdQ5YXB6QfM5zrXnxRm6kEBYCkt2Y0fWSo4m0mKhhpthmkdnI0gx0YFTzUOSCYBuw/jt2ecv5Uo2KQMRCPHEKqWKGzor0lZUWxhROCkaPJ95kJDXRMfdni0L6qqAGCOu/nOrLZNZ2b081TQx18V37LQNwg5pn7mFSdQTTm9C8cnCtoi4lMWAJ8kY2Zr+FCGSOJF5ViFAd1t4wi+4pE/RitjGaMrtI8cToGBfgUV3PNnYFRNT6te7kAfoB0r36rTUNyEynoGBCvgacpYz2qMsLIGkG3sdNB58+RWAuj1H6fQmv+20z3vscka0KeTLUyghS2hyJwwJiQp7JtSSRyPwgdjY4udUff28HU/9WzW6DU0RvKHI9StWCbpatTF8QxB0GlkA3mgpe0mjvQ==
*/