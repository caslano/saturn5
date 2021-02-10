
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_FCONTEXT_H
#define BOOST_CONTEXT_DETAIL_FCONTEXT_H

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

typedef void*   fcontext_t;

struct transfer_t {
    fcontext_t  fctx;
    void    *   data;
};

extern "C" BOOST_CONTEXT_DECL
transfer_t BOOST_CONTEXT_CALLDECL jump_fcontext( fcontext_t const to, void * vp);
extern "C" BOOST_CONTEXT_DECL
fcontext_t BOOST_CONTEXT_CALLDECL make_fcontext( void * sp, std::size_t size, void (* fn)( transfer_t) );

// based on an idea of Giovanni Derreta
extern "C" BOOST_CONTEXT_DECL
transfer_t BOOST_CONTEXT_CALLDECL ontop_fcontext( fcontext_t const to, void * vp, transfer_t (* fn)( transfer_t) );

}}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_FCONTEXT_H


/* fcontext.hpp
LDJGSQ2xImxDxK0J50UX+a3K7u8tST6bQBRktXUEmFRUguSl2mWCAL7XNCdMkgIyCQWRuaAb/EEZqIpASWsC8yBcuf7vJuwqmlcDzp63ICve1gVU2R0BQXJC73qYJhMKeIkIiF9QqRCzVZQzC+kJKCK2coDRTWS15JDdZbTONkiXKaiUauTH6TRvRY0rmRY8l9P8IIVVqe2zVa2wm222B94oUBxaSUzQ+SZseUFLPaJEGGzaTU1lZT61hYSsmHIBktT1AIellMh+CQTiQS1TZ0KD3VOlB8mZ1Gy7im+PElHWAahsBUM6lAXzCo7Cm9CygoguvxPiwDKo3En+wpY99V4AZ9gVjOwY3HgEm0xSacKNm1wGywRu7Ciy/WQFwQXY/mrAu3L9BXqDIqsAct8IIrELAXTb1JQUR+Q/9KQbVnIJ82XkBWGS2mHo+As4hdHsDP5omXb1uxGMarrR2w5n1umZdYIB/Sslmdynkii9wfhBL0mEiy/Bt68d4xnm+i0Q1nupaQgrKLvV+muVBdly1fu6K49XfhDGbmz8RFletwWBc83XO6/6bHTQOcf48zbGegbeVOiJGq1x3IIJNUfSnn7yqaNaOPE8csPEDXzD7ufxoGRbgjZA83XGnaEn6lp2raIQIhN7He5xvrcG
*/