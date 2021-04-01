// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_remove.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove.hpp
250Ju3+qZuUm/DSlxjzEccjqEW+5SvvM6d6UGASZEf5VPLHF6BGu2A0EJnWOBiCL/rjlqZHto+YMrjROjFIAHX6m2qxyvZG18TZmH1B1+wpK45McbWjj0W8NagTY3bCHK+65G5/RRuYBkcE/inMQe+ku3YkAklr67OKkiELbwEnNtdGclPbjA48JDnJVR/jSPeY+qTDc4qcC/Ik8JrkUxzy4O8KFMPvpHAZa/fANhwoYb2w7DBDm2KO9LV2kSXnTH70DfWm6PCPwJQfGrKoz3NBxAt+JSlMB3DyBRKwa2WD5rQL3FW95EmkG3Hv6AGj+CzELEQjGndsUoyVpXsCvEosYz7qMKyOwZqzsfPd2tdOll0Dk/q60/djax2WSApj2AlxOLqHwc1QEaPt/VGs2Wc3kY04ygNObTfjWqDFHsppB8OMlKr17VAbAFV1xxSpDoeqJjlnCxHfb3/TFNcwy/ACjSMcdJYlll4/xlEhMblxhESY4Ek2qMI+v6qgHwTlGG8EO8jKsmI0Lobwo1poEZnVpuRHnar4TDfsPEdifMVgmyK/jLrNHRz/tlQ==
*/