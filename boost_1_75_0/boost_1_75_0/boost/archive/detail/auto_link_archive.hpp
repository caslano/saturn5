#ifndef BOOST_ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//  auto_link_archive.hpp
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

#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_SERIALIZATION_NO_LIB) \
&&  !defined(BOOST_ARCHIVE_SOURCE) && !defined(BOOST_WARCHIVE_SOURCE)  \
&&  !defined(BOOST_SERIALIZATION_SOURCE)

    // Set the name of our library, this will get undef'ed by auto_link.hpp
    // once it's done with it:
    //
    #define BOOST_LIB_NAME boost_serialization
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

#endif // BOOST_ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP

/* auto_link_archive.hpp
j8YgOme8lncuEMM71ypPR4o6HOToZJmStb0P4Up+L4KDgOCMG1Hn8Md4vHkiBCihXRoe16zYsn2uVY/9coes6c/7RVgle/gX4dAiza/m4it3bKFdgfJe3AmQ57+adq1SYmKCa5Uc7pY95Lf4jt2ZVTZX9tplXAEycQ1dLa6fmRy7fU5BSa5sO6vZu6RyVbtOFspFdHD1da1T2AjTyfWmYRoTpzHVXZxy8tpJy4jrtoi9+LkkMFx9u/5EDsUmmqogmt63xrVyB1DO5A5njvgmEz/wo283P4N1aaxs4g38WZMqk9Pc/gJZYROtmSA6l0w24naoRZGphgK3LTR0eCvo11x4mbTQX7MLTCZsOmrHiaqAJmp4mOZOs/pWdtVlc/FlQWBLBgrsuQuCwLZeEAS2+UKvwKb8CwWmaenFzb2AqxxnIHBeS1LNkIqHlOXtTJvMvPYn5P8G+e3Zl8QBFtviWlULj9iez3vbU+dahZuq4l605naoGWNRblW7vfQjgXav6IngK1nNbqumXYaCT+zgjuKwMgXFbTn564iWESdPXrNF7GYTO9hV7fqzORQRNqvvBnk7CO3ijqgzRzSCKNvx04rXwaT7yVPfbf4DYJC+Ye44Lwr2/UEFa6aA4k7kaz/w+twIUW4yoUn+mmrXF013G71G0qrqQAeYuaoDHQ8H0t7Vq53Mt86CMjT7zZeghsBMm7P5COmrNf+xvIu3
*/