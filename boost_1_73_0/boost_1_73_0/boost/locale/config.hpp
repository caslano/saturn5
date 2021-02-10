//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_CONFIG_HPP_INCLUDED
#define BOOST_LOCALE_CONFIG_HPP_INCLUDED

#include <boost/locale/definitions.hpp>

//
// Automatically link to the correct build variant where possible. 
// 
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_LOCALE_NO_LIB) && !defined(BOOST_LOCALE_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_locale
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled


#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* config.hpp
v5oucrgdzGaDSb6E6QUMJsso9n08GVHrFZk5wIfaoSdzB2pVa4Vi5/l+I0u6ypS6EQidYK1mHkNT92UnoVsh6VGJudYFL39CRVnEu2N6k7PR+dni8mIxGebj6SQhkUSZ2E3iCyyae1YWBxELPUmt0LHDdDCYMpUN25pqSo80+fd1KiV30BM88BS8+oUstOE16NoqAT06PS7CD78kSRcNnR/Iem/fdECp/gZQSwMECgAAAAgALWdKUqTCAJtPDQAAZyIAAB0ACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF9jYl9oZHIuY1VUBQABtkgkYL1Ze3PbxhH/X59izUxMkCb1cCcztRW5lfWI2SqiR6THcS0PBgQOJGIQgHAHU0rs797f3gMAacpqM2mZWCTu9nb39r2Lvf6f99mhPj348fU/Hx986xOvy/xXEart0L7/mcx/OHWN74eI7FFz5LPfo4ePfCZPH/EtlR/5t+8/ROiaeeM/e3zy2uefWMExPnmSF3dlMl8o8k56dPDs2V9pSE/3n+4P6DTIEpHSRIlsJsr5gH6M9MrfF8Ht7a4ULwYkFAXprkU1XSSSZB6rVVAKwu80CUUmRUSBpEjIsExmeEgyUgtBcZIKOhm/fje6/GlAq0USLhjJXV6RXORVGtEi
*/