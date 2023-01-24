//    Copyright (c) 2004 Hartmut Kaiser
//
//    Use, modification and distribution is subject to the Boost Software
//    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROGRAM_OPTIONS_CONFIG_HK_2004_01_11
#define BOOST_PROGRAM_OPTIONS_CONFIG_HK_2004_01_11

#include <boost/config.hpp>
#include <boost/version.hpp>

// Support for autolinking.
#if BOOST_VERSION >= 103100   // works beginning from Boost V1.31.0

///////////////////////////////////////////////////////////////////////////////
// enable automatic library variant selection 
#if !defined(BOOST_PROGRAM_OPTIONS_SOURCE) && !defined(BOOST_ALL_NO_LIB) && \
    !defined(BOOST_PROGRAM_OPTIONS_NO_LIB)

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
#define BOOST_LIB_NAME boost_program_options
// tell the auto-link code to select a dll when required:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_PROGRAM_OPTIONS_DYN_LINK)
#  define BOOST_DYN_LINK
#endif

// And include the header that does the work:
#include <boost/config/auto_link.hpp>

#endif  // auto-linking disabled

#endif  // BOOST_VERSION

///////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_PROGRAM_OPTIONS_DYN_LINK)
// export if this is our own source, otherwise import:
#ifdef BOOST_PROGRAM_OPTIONS_SOURCE
# define BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_EXPORT
#else
# define BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_IMPORT
#endif  // BOOST_PROGRAM_OPTIONS_SOURCE
#endif  // DYN_LINK

#ifndef BOOST_PROGRAM_OPTIONS_DECL
#define BOOST_PROGRAM_OPTIONS_DECL
#endif


#endif // PROGRAM_OPTIONS_CONFIG_HK_2004_01_11


/* config.hpp
exF24hUFV5aVw87DPNiwBnPXctkjx3IaAkZL+0+/rIYz2HVd7r3d2bka/Zkiil8bgYUWrNp5+edq+11JHPdYvq3zJDacOExHxKXzCk6eBJIiS5Oe7eN/9BOwicmkrA6hqXdSxOBeTLzLeUseN+Qw3EnSvWhteE3TSJLEy8hMged24qHF+7P/Na/3xzrBScoxzw+Ova6kORc0LfxmMTFZHTWskAxXpxUtl2NLvn5gQD+1qhhOWszvJFq1ttSsHdG0kwrCdX2VV13vw+zK2aO1j9U/lMyTNA/L0rHmEgjch/ehpi8KhrYnCwpuTbX6pxXB5j8hktPz0+6z8LqafaYSMoWOWrr9KiYtLI18a9eB3bnXBCyktUAzMb9rP2xcJOpxKBj1+Dg0h0tEXy3K1J9h/C6OmMY65cJU3aocmh3obJgkLPInmuzyu9ZrUcWfCxuzZgMklnb+8HRgikO6Krf5MsMV9+t+S/uURh4B25TCQDrViwU9fYmmkQSihkiihlEoP7dYkauEwjsAAV9smyDnos3uW2+7aoH6twvCVsf79sgvo4HEcVmE19/60j/rqk9JV905PuR/PhzYqVvvWdxYFZ1fEJ+3GyCV9QsQRgzbHYdLe+FIjPMtWTA5ZmpK9sgRFyL87m1rudSOtdNIa0X5TvWS3l0Zvqzi+0RFJax2w0Rq/gnmQ3vlPa7GsvOLT/Hia1vBwCF/SgpWVSqh
*/