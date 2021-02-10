
#ifndef BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/intel.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 25/apr/04: technically, the ADL workaround is only needed for GCC,
// but putting everything expect public, user-specializable metafunctions into
// a separate global namespace has a nice side effect of reducing the length 
// of template instantiation symbols, so we apply the workaround on all 
// platforms that can handle it

#if !defined(BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
        || BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(810)) \
        )

#   define BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE

#endif

#endif // BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

/* adl.hpp
dXlpj7anWaYpf6E39QEqFRWoOpJabBCmG4dGBdghmb0LjYt3TI6JJQn03nntKvL9tCDFP7EUF0pc380vUEsDBAoAAAAIAC1nSlKD1p0AxQEAAH8EAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA0OVVUBQABtkgkYK2UwW7iMBCG75Z4h1GrXqoNTiCHYllIFYtKtV2CwO218pqhiTbYUeJCefsOSQsSQauu1Esc2/98M5l/FOmx8kZXOGQysytHy1/cbV25rIZsotSsfsDdWLHR4/whmannUTKdjkfqWSVM8qNY8iaeXbJLWGC5wTKosiUyWWKR70iw1F43UB51I+iFISS/2E/tUYB6xR8QDmDqNnQRhRDFIh4Iktz9ptTOerQ+eED74lMB/cOJ2hUU7fHN8yLXmWWMkJI3qST/SF3XNMqzfURTk6k3JKnqSocs9b6ggM8tSKvX1BTKY9F48A6qAk22ygykrvIk4I2C3oxbr7VdNhDB+Xa7jbr4ptdFjl26FDfhTcR7YTyAIDANMSCiEFeTZKHuZ7RSV2bJXJHA0sfAkdQ7JfXOkfbnX6H1T2n9M7SW7ivk+JQcnye3dW06GXHoKb1+eFW7+IRlttrB3mDQK48l+BRhP8WQ6gr+IFq4
*/