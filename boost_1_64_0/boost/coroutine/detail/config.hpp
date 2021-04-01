
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_CONFIG_H
#define BOOST_COROUTINES_DETAIL_CONFIG_H

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_COROUTINES_DECL
# undef BOOST_COROUTINES_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES_DYN_LINK) ) && ! defined(BOOST_COROUTINES_STATIC_LINK)
# if defined(BOOST_COROUTINES_SOURCE)
#  define BOOST_COROUTINES_DECL BOOST_SYMBOL_EXPORT
#  define BOOST_COROUTINES_BUILD_DLL
# else
#  define BOOST_COROUTINES_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_COROUTINES_DECL)
# define BOOST_COROUTINES_DECL
#endif

#if ! defined(BOOST_COROUTINES_SOURCE) && ! defined(BOOST_ALL_NO_LIB) && ! defined(BOOST_COROUTINES_NO_LIB)
# define BOOST_LIB_NAME boost_coroutine
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES_DYN_LINK)
#  define BOOST_DYN_LINK
# endif
# include <boost/config/auto_link.hpp>
#endif

#define BOOST_COROUTINES_UNIDIRECT
#define BOOST_COROUTINES_SYMMETRIC

#endif // BOOST_COROUTINES_DETAIL_CONFIG_H

/* config.hpp
/qqfJISo5T4QX2vXfjK0p3Dur7ofgo0tLCUAOPO4OC7qeQx3xWrBR2OLBRz3hvZatnVArxVjBxRpy/AengHVcLkIJ8LNkJmGPIhjn66kgZazB28fnyRmUVZL6IwQzyXWkegjBRgPaXpEHLJ3bzRLSdKlSSf9sZv8AJN2or6OZKCf7Vl4VDZHK8KfDIc8DgOkJcBnXXwm+I2/R1fskVTPZt8wxTw2P6XFpybZ4XTeDbnOtrLyWWBgs2obPtdWaQCA9ArnppAEXYgzQzJLpGMFHTv1rwpq0+W5vGFW0jvgkAnyEco0R7lXK0RXEvW1cW0b+VXiAZlsobwHSMgvB+TBtUpgOcvj5PtkvrSTyvbBjBz85vB4/lPbsJMUex519uGjmkWDWBpiP6Ro+ssFN/pd7ob236A4XaSc5IZ7PQkYVNKpvc2n4zd2Qx87FKnZ8Pc/fuoLAPp8YUw3xkkn+JaJXYsZ/wEosMS0Th/X0M3Dat2K7xFbwJNuQq2FLoGeTwlDofyElfItyRNPf6TNI8gVIr/3QG/MlOBoffEvDBjktb8fveRygQHA4CCrVA==
*/