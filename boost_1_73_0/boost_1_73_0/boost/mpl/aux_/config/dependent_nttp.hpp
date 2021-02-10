
#ifndef BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// GCC and EDG-based compilers incorrectly reject the following code:
//   template< typename T, T n > struct a;
//   template< typename T > struct b;
//   template< typename T, T n > struct b< a<T,n> > {};

#if    !defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__EDG_VERSION__, BOOST_TESTED_AT(300)) \
        || BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
        )

#   define BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC

#endif

#endif // BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED

/* dependent_nttp.hpp
iOudjlnpfUOE9yVIo9YUCtUxqD14C65BXRWVhtI6D6+VL2GegsrzFp1DRxQ+cGim7XqtTD7ICs7j6KJ7YnEdXcd8FH29hDDUg3ZI2kfn4myWrLJ5SiNllSbLjMCGWoSd2s9CR5EQ8a8OPvpE7hjwUY8a3Tuk6S6LPqVHbKtiC12AoAqPLfgSobslUCoHvxENnLjS+hMmNz2WJJrWeqttPWZ0UWAw9P6dAzajvMRxiwF7oKTD22cqLEC/tDU/e5wuV/NkEbBbrbGh7XN+HrDgH5LHbf6PpuQHy7TYN8IPv8NfUEsDBAoAAAAIAC1nSlILgQQWAAIAAPsEAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA1NFVUBQABtkgkYLVU72/aMBD9bon/4UTFl2rBgdKptSKkiqFSrSMI0n6tXHMh0UIc2QbKf99Lwo+t7dpO2r4k8fnde+/O5wQOrVPSYp8FaR5rev3E7Uabue2zURRNqgdcDyM2uJvehpPoYRCOx8NB9BCFLOBHcMDrfHbCTmCGZo3Gs+kcWWCwyLYEmEsna1LeaXeg6/sQfmffpEMB0Qq/gH8JY72mjY4PnZ7oXQqCXP8gaZ07zJ13i/nCJQLODpFoW1C2wyfHi0ymOWNEGfBa
*/