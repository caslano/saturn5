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
Kr7bB7HY+1S5eTthfhXfbYUd2A8jZxBXu+FqFavt0L7q75/ToDLl3n6dv+3g3/ybf/Nv/s2/+bf/re0Pff5nBcms+KysjKH/uuf/ppE8FMozaXQ+6XejbV0N/hrGNx9RNJ3XWM+kPbu16tSzfvyQrCxz3dK05CHp2UMTspONgno9SzOX+JNs9WdWU/tX8vnMStr6XUBd9XzLF1K08fPJ970xKvxkmI8+G71vQd3HrdcWVcca
*/