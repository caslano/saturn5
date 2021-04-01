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
mUPjVOcDBJvQpnOXAMpmVFFIV0/EfqP7tXk/iQr8NxjfxCebAJDAZHyN/EPv+zqUVSDQu463MrH7l55KeBWoNIu9/Wh2NwvRMIwFAsk0mgaqEwkhte148qcKF4/62Lk0Q0DO5JtpKnVdSIJo7irU3T30NA6Lp/Ep4VuOTv90FHVk+kWsGB1rE8BCmdb5WvjYFNyNK/eCl2dZve9by2IWZFbWReJ1Fg6SqAbVhTtClksDtZ8sYeW7+5qQ2XWUu/LwVJi2AeHzyp9eKcyVUmv5t2pCUNow9P8exKJ3QJhxs2eirHwF1ybFGszSSP14DMhn0QHyN0WEj9I/5/61uK6eoViYvwZfj8KI+poxtl73DcMguBJwYORWflcrMg7LAF13JDRRtDupawGY/vCzCxG14JCDAx//Xipqn7+EPnIZEN4paywW4tYl9VpownGZOgwlNd4ZCBQEm2dKwq8Ay/ufkaYzVeC7E4Pw7Pj266QMVUtaCBYkJA7LQ2m8yS9AttzsKAAZVCjO/8cjzHcaeH4snor0Ezo4XeOsSDGSPEyJF55VnpEy8rSVmJOnyw==
*/