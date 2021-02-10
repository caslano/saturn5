#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/int.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct size;

        template <char... Cs>
        struct size<string<Cs...>> : boost::mpl::int_<sizeof...(Cs)> {};
      }
    }
  }
}

#endif


/* size.hpp
B7O3TXrcxQePJE7CXw+zzKUI4Sti669qfhnnfDRBg48Eg9t/+htQSwMECgAAAAgALWdKUs04V7UdAgAA2gMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzIxVVQFAAG2SCRgrZPBbqMwEIbvlniHUauoJ0pIdy+sF5XSdBM1CSihVaPVHihMAirgyDZpefu1DWn20ONeMJ4Z/zP+ZkwlCpmlAn1Cy2bH1PKG3TvjufDJfBnE5GGahDMyS5LYfCCMVqtpmPSbA2cfHaHO+Qx1ehlySS5hg/yI3BZljoRyPFSdCshY02AmfaPguNcuTMZjWJb7QnawKxuEsskRc4uUdXrwQLQcoSgl1GgRSyX4FKB5KlOfPHBWe8p7K1iN7wVyFZcwD3bpG942bLBY5JXlnV5t2yIAHWu5AFE2mXJXnRbu5YxqVmD29p+lB03qDCQMorAqsZEDosxsVIgw4HxDgBRSHuwT6ZOH7jCVioxCrv3k5D+bgTZpjX0XwXQRZKvIVZiDLDhr9wX800SgTh8PqkN1nTa5T65MBxxHL9fuzcT1RlotjtaJo7fOj2UwX8xX99OXn+4V2C20qj5PYMZRgn0A+wNGs2iTzGNvFK+jl60+alo4ZFC/w50NjWfk5a4DTQvS
*/