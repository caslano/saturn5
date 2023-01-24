
#ifndef BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED
#define BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>

#define MPL_ASSERT(pred)                BOOST_MPL_ASSERT(pred)
#define MPL_ASSERT_NOT(pred)            BOOST_MPL_ASSERT_NOT(pred)
#define MPL_ASSERT_MSG(c, msg, types)   BOOST_MPL_ASSERT_MSG(c, msg, types)
#define MPL_ASSERT_RELATION(x, rel, y)  BOOST_MPL_ASSERT_RELATION(x, rel, y)

#define MPL_ASSERT_INSTANTIATION(x) \
    enum { BOOST_PP_CAT(instantiation_test, __LINE__) = sizeof( x ) } \
/**/

#endif // BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED

/* assert.hpp
/v6NHJWlS9+hhbs2PVXLhPZS+9vKjWx4/hwTx6FZPAFYAjXDcD+eDmyNhOH9eHl8EF4frbHYZeqOCO9wZ8Z+uLKTXe/IMd/NhhJjP9wpsOTBplmccnIMd+Vh4tSX91sWu0SKfQ30KN330w4sNn4d+0XsBGhioXLrO3ei/vb+rS0l3k8xuYTzIuXMn1DeU5TrkCGLSxwja+Ae8f5e4stFt/5DzuWLGesGE8SyuPpWZwonpbfAAXGyT5/CWOI5v5zeGFV8sKqosuSGsBhvTm7yPW2Ov2ziFnNv/97QfogZj55myvzfNh1mBuYPPPwv4maSO5Nco8P+U+xrRs8ApLH5lpDwDC5A640JL5nf3c7oNQfXRkTna5PNFv6miGbZbSMvZ8gsnxaAVLKGiyOU6hhQFny7aHGzjzPS5WV8S+I5B5yb7FVz2NVzYv5iOd/5e5WeBMwYpJ0gWU1Gn01pEH0x8lDfZcslGtkHxiiW5FaUH6yf1blpIvgCRe3XJgzgR49tVlo7Bgxu9WGtHY/cSO7lPbY9Yt/QVXry+OEUYO+tzDYUzCpZ+Hg0wru8HyiImSUlLWv5A5hE7SfTAJAxzOwm6yaaP5/b4l1G8qGmslKoH0YSzgxxknZz2f3PB83NK4vflT85CsI6M0hMDypjONjwO8I4aqndMl1zBcgGXAvea6AiVM1PamBo84w5yp0MN5ku2Rkj7H5dFkTRyaW+
*/