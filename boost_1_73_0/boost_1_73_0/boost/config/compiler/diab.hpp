//  (C) Copyright Brian Kuhl 2016.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Check this is a recent EDG based compiler, otherwise we don't support it here:


#ifndef __EDG_VERSION__
#     error "Unknown Diab compiler version - please run the configure tests and report the results"
#endif

#include "boost/config/compiler/common_edg.hpp"

#define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#define BOOST_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS

#define BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
#define BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
#define BOOST_REGEX_NO_EXTERNAL_TEMPLATES

#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define BOOST_NO_CXX11_HDR_CODECVT
#define BOOST_NO_CXX11_NUMERIC_LIMITS 

#define BOOST_COMPILER "Wind River Diab " BOOST_STRINGIZE(__VERSION_NUMBER__)

/* diab.hpp
Gs0RBblSlXw5GiVNXWAko1QkcpT0VLi5Kr+L6hq9KckGRKVACWgkdUDLO1CKlGX6jRThZtWsCyZz59EtNMjTkahB0qLo4FCVUdmGQCHs2HK0JFToPVP6JQWX2tp9LsongkhrB5Q1NUdzSAvKpQKJd6DhKa2NvCGit9KxbCj/QcoefU9BcPQKBl4IfjiANZFMOvDJjy6Cqwg+eculN4+uITgHb37d4X3w5++wNhharYE+VDWV6EUNrKwKRtMnxn9pp1tudAGTq+XMn58H8bk/m0b+5RSOYPDsBLzmRhf2iwEMCrbWmYdj9/lz9xA39LeYErmJb6hiPBM60VhPEiHDC5h7l1NrF3d1AChuyK1pKTDTipW057umyCHVFYvV1ZSUK4MVXs+DReiH1m+MJ0WTUnitrbelmL+xjJ1E4P6OU7Y+gv0cq6TAYtlxyIFC8BvY115Uw1fG3LtpOFn6i8gP5taCYB4IVIJxpSsEm6LVwFXXXv8jGBtbmDcljgYtJGkieIplhFFRGMNnLJrx6fFh3+jvL6PRVTRpQf8WnA5d8DPT5RiddTB2AIs+Qa01xd+EYItp3JLwDVonphdsFCnNsEKhht9ycc8dAy9pfYeOmEMrZ8geior627NUUMn/UCCbqhJ1m7ZElKXuOZXj
*/