//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_DEFINITIONS_HPP_INCLUDED
#define BOOST_LOCALE_DEFINITIONS_HPP_INCLUDED

#include <boost/config.hpp>

// Support older ICU versions
#ifndef BOOST_SYMBOL_VISIBLE
# define BOOST_SYMBOL_VISIBLE
#endif

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#   ifdef BOOST_LOCALE_SOURCE
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_EXPORT
#   else
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_IMPORT
#   endif  // BOOST_LOCALE_SOURCE
#endif  // DYN_LINK

#ifndef BOOST_LOCALE_DECL
#   define BOOST_LOCALE_DECL
#endif

#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* definitions.hpp
zHJClDxO0MpkXayUBo8AlGlnzM0N3OKibnNAVmsFTe88O2X/kXdOhEZgC/smfEe7RWKeKG99gij63mmfkN82h9AVELfoy6HaULQIRaktPmzs0nrWpiprtvFanBj9CkQf2jKgXZ9zw2TpI7ikBrHtePEXMgppPOCmuuE35dUEWehEUaW7FVu1s9wCmvhJYPuGkJCfVk1JyFr3yfbiBfwbx/m1CWOpCVOTXeBQDdu2GdQtxvPLb3Gcoy98VlTaRXJAaAYxToeKOtwtmPQksnzthFzPsLVsC65bc5NW5BXBe+NvlLl5kot62XjSkEgrOdzeXNsuk/rr6wL9jils+d5Lp9/E2lv6xY3bbqYx7HoXyNnYcKj80FlD3d2jr5MUPNHF976a825P8T42hYq2zL28X+z5FlmZUM5ENkmK9QVSk1bszcr6s3EkO/mkNPBtjmQgzzZef9aMCY7fXealM+k31qBwJQ7HDhZqQprqRosU61Sfn00A4KZgMkZDhxPnevVPEwaeAfrHO7e65hv8EsJ677Cdfmbi7q/cviyTWyULtyKWKkkpPXTyIcYVoA==
*/