#ifndef BOOST_ARCHIVE_DETAIL_DECL_HPP
#define BOOST_ARCHIVE_DETAIL_DECL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2///////// 3/////////4/////////5/////////6/////////7/////////8
//  decl.hpp
//
//  (c) Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------//

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

#include <boost/config.hpp>

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK))
    #if defined(BOOST_ARCHIVE_SOURCE)
        #define BOOST_ARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_ARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

    #if defined(BOOST_WARCHIVE_SOURCE)
        #define BOOST_WARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_WARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

    #if defined(BOOST_WARCHIVE_SOURCE) || defined(BOOST_ARCHIVE_SOURCE)
        #define BOOST_ARCHIVE_OR_WARCHIVE_DECL BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_ARCHIVE_OR_WARCHIVE_DECL BOOST_SYMBOL_IMPORT
    #endif

#endif

#if ! defined(BOOST_ARCHIVE_DECL)
    #define BOOST_ARCHIVE_DECL
#endif
#if ! defined(BOOST_WARCHIVE_DECL)
    #define BOOST_WARCHIVE_DECL
#endif
#if ! defined(BOOST_ARCHIVE_OR_WARCHIVE_DECL)
    #define BOOST_ARCHIVE_OR_WARCHIVE_DECL
#endif

#endif // BOOST_ARCHIVE_DETAIL_DECL_HPP

/* decl.hpp
ci9kb2NzL0lOVEVSTkFMUy5tZFVUBQABtkgkYJ19a3fbRrbld/wKjPLBUq5ExY8k3ZnbucuR5UQrfo0ld24vj5cJEaCINglwAFCyMjP/fc7e55yqAkmnc8drdUfEo1B16rxfNdt0y7xuhqprimWf/W30L8vyk/z9RTN07YfDr2r894iXbupBLsj/6883bTcU1/WyHu7lcvJLb/9WN2V71+e3ff6uqT/LI3d1c9tv5G994EV93RUd3rW/5HKOG9Mzmd7HWds01WyYyv30d3hotVkO9ceyxQP+93iErirKu64eqjBGuLIzSlOl4zTVeKSy7renEy/pan65unpzeHkktxfDsNZrz6/eyO+5//y16q6rru3l2if7U29cnb94dX4ll4dq2VQ24POLF+d4u15WeuHy5U/yu19dG/iePcXoy7Kw4c9PVkW9lEsV/qvXfq6aqitw8Ub/sq2rur7uh6oZ8jNdRN02mNc63NAHCRDFlHkxq06btjm5XrazT3Vz4/Cy2V2+yJfcx7rCSH2/HG1zfnm/um6XvKV/6e231bDpGplGWfV50ZT5RTNvu1WBGRV8vOMTMzygrzx9c/r0pwu5I/imV86WtUxZrsz4h158Wa1a+e6z6npzc2Pz5aUSVwzyVT/klxvBCEK/t1ef
*/