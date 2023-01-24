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
Wv9UnVW65YlbYFAhnMB6r4ANbyHrPhcnKOaSmijZqo5DYU2+15L4EmzeT/5OCi3rIvTc5bTYSqHEWFj+H4Uzih2wolttN2kvpnZrHcrb8bZ5NN8gmqKRY1bf8JdFaXQW5UH3n3vu0dMpsoSfvnxYVM2xYRdT3DixOS0KuKUKY5GNOBGMmxfqlCRl/fJKA6jLt2te6cpq7eCFX065xtk5qUUTK11Oqn4TCkhznHu+pQnAWYxlmW/1drzvLEftFVjd6GaGvQZ/tkqCot+aWBccjMl51Pug3Is7bDxhGpXY3X7xxSEyDWknXRYPbKDljv98Ilv91UpOL/XQ/KYEFfWuhLIE9Qy+wdgxsvSYLLYcHMJTR5T2u/+zzYBXDFQR5FGyKmlrPHV0SAM0jHhcNl/0IOvKPY/7uvs77iWOYA9zn1TphvTw5ubYT2k10STvCv0QReeJvWjAQSYtTFPqDY6krNUAJXX3fWVo3HaJRGHdX8Szyz4uQOoHRG75A/Ize+y+9v6cGzk7JmG/4MB8NkE9sInf/gvtMEaFYtIMDUkH3Xjvxp1bZJyT13sKumViYaxvmDAkWcNa/B5TCULwPSE02388YCSwyAWia9inpjQJp9bIenCF7z39lusT41+Db+WonGVRS7zIBRq3TjFPnz9QrmVkCi48UxBaeYPM9jgupZmmkQF/hrJ2LAmsgqUIrADcBEcAeobpV9UUQeZu
*/