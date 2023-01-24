 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/named_condition_any.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

typedef windows_named_condition_any windows_named_condition;

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

/* named_condition.hpp
yXDDIB+Oas/CFRj9MC+1PooudgeKC+uuoLpoH14jeiPpLnwtPDf8MkI96mbRq76sMCCWF84JyQHJAaEVjteelMFDJdx8Ff5tJkS5X7mfbb8Fa4FSPNPpIBf4YM1I8VfZ2q/HNzFtYrw/EnRDG0lisShIydremr650ZE27r97+XDjJkl3vT6fJkujDhry24zJsApxeI2ROePg0EV91fax4V/I/7a6dzARQSBmkS8P0bWisTUIBKwiZlAkYT8PqoEohRxkUk4CLbgJ20pie538vwiEhdExlTxi48eHNjreM3x/0N05q2sKt/pOTEN3risVu17Z94IdYjYel/DnqiQv0u8du0A887Z4Pfrti/wpNpFC9GBsjJbNysf2g9hB2X5S7tSf+5U7CQ8GuHVWartPZlNJ4XeiXIJp3NG1gXs+g0RC5ZjCcuW9jygQ/y+kLfm0C2SUcZNBiHtPNsPkqYjIFP4fzXFrxs4BxAtkvbmoTFYKtex5McG1O7ylBfBTXNfAGNsNU5NdMgpMHHrHVMcSAbrksY97UikcgFHlh+FzXI1fKGzwXGZ2lkc+FEk4X/xH+K5sLraXCU8e7u9bvVFf14W6DV4FA0IvAoXeNtbX18NEHC8kTDaOtWcnRXstaHDjb5+qgLgds+LNYgPo5BeRTjdmxz2EdYB6R3vHDXQRmWk1rdJJWS+BPvJEQZ4gC/wZA0Cp79nDw8PsVy/g
*/