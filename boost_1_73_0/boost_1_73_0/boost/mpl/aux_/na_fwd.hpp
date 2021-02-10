
#ifndef BOOST_MPL_AUX_NA_FWD_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/adl_barrier.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

// n.a. == not available
struct na
{
    typedef na type;
    enum { value = 0 };
};

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
BOOST_MPL_AUX_ADL_BARRIER_DECL(na)

#endif // BOOST_MPL_AUX_NA_FWD_HPP_INCLUDED

/* na_fwd.hpp
p93YTzpO0oqZPnvfCsP7iTC8TRjeFRjtTsiZj2nout1uN21jl7vtjtsN0zD2Ox1+Fwz/P7K5rf+PKEOwWQb/ShkC3vbDxPNbDrHaCTrY5rHvMddl6LdcL76rDMFPhBFuwgiuijLsOi2ilNhM45bDPJZ2YpcnIeHtIEv+BzDCnwijvQkjvAKjg2mQdP0wTbqtgAUt7ndbIXc6LT8OPZ6612HoFXixakb2cim1V/9n+AdQSwMECgAAAAgALWdKUqGKxEi0BQAA2iAAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDI4VVQFAAG2SCRg5VptU9pKFP6eGf/DSqdz+yKGvCFwgzMRRGkVKQRp75fOkixJriFLN4uU/vp7NuGtKhZaudXKOCGb7Nmz59nnPDlLNDmJuYNjciiZQdSn8HVFJmPK3PhQOrXtZnJAJ8d2elINPDBAeMT99ELDPjtPm6a8sDTldLAXqE3YNWHZOHCJZDIyDCeHkmTuZrPICjlhEeYEcZ8gsCMMzjCf+4jcdHSfYLgXIzwcEsxQECFG4iGNYhIjTiUSxSNGUtPFSC4lcfQXRwPMwc0+ymZnfmsBg9EZ+TISXnwcLwe1h8aMRh4a4jgWsSR2pos5VnK5FBFZ2VeQnlNQ
*/