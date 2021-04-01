/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };
}}}

#endif

/* is_sequence_impl.hpp
e00tKmPQel9orbES9weuxOQw2c0TN1lm2hc+zYQPZpQGeLzQD0cRzmQPl0PSWO9SvOJJ63QEr9msTzxyE3xyPga2BFZXVZovZs+WLqs6ffQzg9pnjFGTQWNdeXr39v72rzTV3szW1BZQiRDlFyw7+zx77dChyueily+8C3hIXkJ82R1x8NK/Y1lw+Ci7ZdMhfdR56H9GDY5uN0x20gFUEMbwPHSrr4ns35sPTbQjYoopM1TqunhdpFYYJTCh/eKIlaj+ZB1lSN4aDW7hbPWcJQ8JeMKCQKv/0WUAcHnShJ+XcH/yWK3rPyj6mCcq14epynSy5EQcVigQWuOuXARuwVmhXsLNxdDL3ouUNqQk2nUf2XdKtw3Nnq+YhMzE+CR/2iqIMkOZahiOVoAglchk/x5qc5RNrHjSOQuApwG45zOQXqyP4oW7AVkIki7p7CF1RMnfWuatcYhiXc6sQrNr8PWZrOGL5cvBIIudtb33ZL7tDADyJioM4uCnJ06WnJ3nJm1SGoOYvbaJzhA2xUBXQp7Oe9wMSQEXo8ZugBc9zEuFRyxgEUqCAvxZRg==
*/