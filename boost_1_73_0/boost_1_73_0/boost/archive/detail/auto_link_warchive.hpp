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
F/2NoGCOdg6glsBEFgVN1o1tIja/zWN4nojB4eCBC3VFvDSBcmBETMgLVxc+Pz9pY+MPWX4HkwKEjilMlCXwJLv44fjNi8MXr9nPwo+DF89evn5B60qR1nBDSInRWo5mjcYJxKn1LWFd4pROkmQRMylS8uAIw56DHgYRI65YVrErvMzthhZ5kpCEYtMyIrWAIJccGjnPb5WRk9/eYwBU70dtdPtQTHBY1zisNgC33lCQuv1yLE6hVZ+314ca8KFSIJJQpsoPfXfg+7yEgyjOrcUYWi/bWaB2qSgP9dY6YVH0mRv6CDIoSAtVP438tPKTiJd0i/lW2ZhFx3kFtQYCitOyzEstxlJrywriav479IgWA1qIWRW6BDRl7fqn2PD+uiv2C7eYr3gxvzCL+WFZ+blZzJe8mB8liT9vFtt3dqd0LIm4b67guvDBZsyhgrI/ZAQQKPUo1o+ZFXRNUatLcHipSnM22WVZM10hRWpBNknqG2cyF3WJIyoFnV6TiyG7wP48JSJKZfxhsCIe0y4S1dj6BlH2dyQMHJlsfHZe2EDfY0MHPk+q2JhY+AzROpMpybCwJCQu7CRlnFwbMgqaRaqPDfnL4K8mgFXi3eCfTSbR2JYLrPr5+aHnXVDAqVlXUtSM52d4vqspHUne
*/