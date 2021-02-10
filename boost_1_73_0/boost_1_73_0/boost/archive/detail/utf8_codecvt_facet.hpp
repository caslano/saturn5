// Copyright (c) 2001 Ronald Garcia, Indiana University (garcia@osl.iu.edu)
// Andrew Lumsdaine, Indiana University (lums@osl.iu.edu).
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP
#define BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP

#include <boost/config.hpp>

#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#endif

// use boost's utf8 codecvt facet
#include <boost/archive/detail/decl.hpp>
#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace archive { namespace detail {
#define BOOST_UTF8_DECL BOOST_ARCHIVE_DECL
#define BOOST_UTF8_END_NAMESPACE }}}

#include <boost/detail/utf8_codecvt_facet.hpp>

#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL
#undef BOOST_UTF8_BEGIN_NAMESPACE

#endif // BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP

/* utf8_codecvt_facet.hpp
EGbswQZgEhS3fQoX3SA9tFMgIbRbzRTgN0nnfd/OVN2y7AHwYhWqyUITFEIo1fDGMtgS/xquuBOqQEBdVbp+pE+AjizmI7MIaSw0bNT7DIsSXtyJec3AZJTdmcxXtgUUgHIIpsWx/Msq/jM19KAYgiCHxLKXqYrRV3335CQywzntgqr7N9jEd21Xmq18SMeFoMiRJbzw2/q6fFktNnxyPJR8VsUalZqm1FgmsoVU25q3G2q7mY6nt+CaMTBeKmQYMiJoyNzIDOK+C0hnVbnhRvKtY91G4v1wJ6xbg0yMVqbYm7wJzhqsLVdbAgaZDKAOliEJQ1MpgmJrvq10kCQeQG8buaeICM14WtRlCZvDDH3z2Zt8NyM9ZmNSW5Ov4m+Hpt710BZuZzshjtTQoQ1D9wFw9+NssWk+UQAjXU74QCqnFSVhngmfb0oFKnIGcr5WRRYnoLU0O/rlzN8lOhenwSBkyAHJjVJcLTt2ktClwJ1wvZmrcpphwjWJIJmXBrFJD/dwfQpChbWCzSrV5jqK5asIx1MY02bEtMAaxFDpF5XusmxW3VVBWUSgoGK6F12lybgE9iQLWiRlqXrxVXeEVjhrFSNF7q0sGWm+LO5gBslX7uha0VQYuP90W/qUtcwDZ3l+9SYLoWSDUj1/
*/