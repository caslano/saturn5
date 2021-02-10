/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 *
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the preprocessor symbol BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS for
 * platforms that use the implementation of std::fpos from the Dinkumware
 * Standard Library.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>

# if (defined(_YVALS) || defined(_CPPLIB_VER)) && !defined(__SGI_STL_PORT) && \
     !defined(_STLPORT_VERSION) && !defined(__QNX__) && !defined(_VX_CPU) && !defined(__VXWORKS__) \
     && !((defined(BOOST_MSVC) || defined(BOOST_CLANG)) && _MSVC_STL_VERSION >= 141)
     /**/

#include <boost/iostreams/detail/ios.hpp>

#  define BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

#if !defined(_FPOSOFF)
#define BOOST_IOSTREAMS_FPOSOFF(fp) ((long long)(fp))
#else
#define BOOST_IOSTREAMS_FPOSOFF(fp) _FPOSOFF(fp)
#endif

# endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_FPOS_HPP_INCLUDED

/* fpos.hpp
fX8x+tmldRQHETAeRE4yEnkSUsTuOGU84PGdhVixTJGYQxrYYSwV8HIVi7QH1ZwUz5YSEFo5S6QgdsfihM2ghimKlFrJvu8HeZaAuR+KQPpBaXgvUsvCivdgsGQPJFaKlKBccpf0OpeWIozn+g5X4OUqnyWxjNyaChSloS8ykjxBmGqxmEtLmdO48IyrVxEieRkrfZMilVrTOhLLjYVwIUDmeZZCDVyANaGAg13K05BnZq0xutRQeNO49pEtqbmGJFIwodbpmC7GLZoxGUuXfruY/HL5bkK/nV5dnY4m7+nyNZ2O3gPr14vROfY7hqaM+P0q4xKaM4qXqyTmoVH49S4HGs9juUqwFUHE0gUcGYqUl+GT8ZWQsRLZA80zOO6DYouPcIyKE0rF2pr/TkJqATfPwVNLUMgU65UzJgYmv5yOfh2bPbkavhmejofe6HIyHBsZREvGU0VSMZVLC3phCWjYINGMMiGUC1534hOntg7zlZJ+yBPF6EPGE84kNgr02o6zDyRE8YD2T69+/s+Hw48njhPPO8Vr/ge1vKjVpT8dnbOrLIbu1jvJFrxPMl8uGcw1ll6nrROzht/H6sT54vBEbuJUKJXKW00ZwuR5UmRqgOGCZ/AIRyFZwD3UutHp4bXwrJA75B3dWi0B
*/