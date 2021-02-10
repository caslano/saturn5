//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_DURATION_STYLE_HPP
#define BOOST_CHRONO_IO_DURATION_STYLE_HPP

#include <boost/detail/scoped_enum_emulation.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * Scoped enumeration emulation stating whether the duration I/O style is long or short.
     * prefix means duration::rep with whatever stream/locale settings are set for it followed by a long name representing the unit
     * symbol means duration::rep with whatever stream/locale settings are set for it followed by a SI unit abbreviation
     */
    BOOST_SCOPED_ENUM_DECLARE_BEGIN(duration_style)
          {
            prefix, symbol
          }
    BOOST_SCOPED_ENUM_DECLARE_END(duration_style)


  } // chrono

}

#endif  // header

/* duration_style.hpp
mor6ybW6DlOf4VNLc1aiZWCLZjpAu+PlYjqbJ6kLaK2S7ezY4I5j03PR4PnAcHiMlRuCUudEoa/xEOKKaVTCd5ywhEPHKzxRuDjUZZgszcZKZiCfkypaTqe+lTr4HoTT4DachsnKSU6Ct4hOiqI/8k5dZ1MXk2S5iOB7MF1OnOAF8Q/+QMXt9rCK/461uPFkAsE0nqGHbxf/HwlOdxpcbIbn/nZeWDHsPkkf/D3s/QRQSwMECgAAAAgALWdKUivv9GY4BQAABQwAADAACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9lYXN5X29wdGlvbl9uZXh0LjNVVAUAAbZIJGCtVttu20YQfedXDNQXW2CoNHlw0wRBKUVO2CqSINIJBAggluRS3IbaFbhL2UqTf+/MktQtbpOH0LAp7871zJkZease9H/a43hkDr77xPY3xgffndK8Un/z1DyuEMdfoPlBxRW+f8DVAI5aX+Jr+CGtL3BlteLW1yv6HMc/4G5FQdKfASmvYvqIJ41mqz9S230l1oWBq9E1/PrixW/wBJ49ffbUhTdMCl5CaLhMeLV24VVmT/4o2MODp/lrF7gBVnpnBqNCaNAqN/es4oCfS5FyqXkGTEPGdVqJBP8REkzBIRclh9Fs
*/