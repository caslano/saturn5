//  is_evenly_divisible_by.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP
#define BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP

#include <boost/chrono/config.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/ratio/detail/overflow_helpers.hpp>

namespace boost {
namespace chrono {
namespace chrono_detail {

//  template <class R1, class R2>
//  struct is_evenly_divisible_by : public boost::mpl::bool_ < ratio_divide<R1, R2>::type::den == 1 >
//  {};
  template <class R1, class R2>
  struct is_evenly_divisible_by : public boost::ratio_detail::is_evenly_divisible_by<R1, R2>
  {};

} // namespace chrono_detail
} // namespace detail
} // namespace chrono

#endif // BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP

/* is_evenly_divisible_by.hpp
iJdAV0VNPnfJnEAf0SBzAkRgmhUnC010zexJlF44k4Fezkymv7YP98dHAa3c2kJNKy/7uJF+PcevuzDLot06qgmjDsTJrJ9aIa3h4LlkDU8voWv4iURTpfl86F3ZbzlZMpjHsQSC8ayd7uzPqc8um+XUSlXladJ4M66X1p7511ALrW2WyGI0sTn0JPuBf4a97uZ1yhX3P+8PfSdL/LTiYpTzcTHa6flAiE13NgpfMWPkMJkmR6r8HpY3U8fN1fg0UPwUfrzY99wDV5uiRifK+X07EiPGTFTwd+Tr0trbniFrX51D1/5dxhlzYDjuSb7EXSy3t9ud2qUUjpEiQcEJg8a7v7CnzpM5k3aL2apz8vpyqlWPYbcVTmdLeoa6/Oxdu2JAReUKqqicqpI0Ot1BV3r4MKTSbyWq/XFp8OT18Lrx5InsWvAEnEBYwk3fZ4XqLM1CzlnCww6T13OWZneGU3yYOYLNpoxJ/74mzeZ5klV493k6m2+x2YxTz2ZhapddqUCUxqKlPV5wyporA9OBRWwi63D7TSbyvUV+nXx7Yc7Xl2vDnCMJdB5FG87j2GF+/AFOsNS13/VZVMt+B1OUmhJEudFI4eFUrVB+1qWmD2Qo5a5A0OePGoPvftcsQcVjqc8NoPsrmirdh7vD/FEIDoVXPMdGRaMexMVO7hV3utG43UWyPSoGzS/RfqMEBRncOsKYlQ/0FIWWZfeY
*/