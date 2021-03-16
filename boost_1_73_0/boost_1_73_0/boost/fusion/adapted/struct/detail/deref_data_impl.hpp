/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<struct_iterator_tag>
      : deref_impl<struct_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
Csaz+Ct4vVEJH8zhMDEPEcULbMhhOfKRHA48/lujEo6RCh6TbeVJxhoEWyPY3YIZ9Q8npoapL0j5W4mM2wN7JcuEb1CtlsTcGytR1egm+d23Et47xeEACDoaQfJAbueFMfcaLvQYFEaVKHgsW7HMZUrREX1NOhLMONJnjgxIP5LccXBvMHngYGepuOB7I2Uv3aSdPvZWlfGzbvGcmK5nnqhTmMJYmHtZ+W2lHysE2UsfhTFVYHTaRb/LM7mlo3k=
*/