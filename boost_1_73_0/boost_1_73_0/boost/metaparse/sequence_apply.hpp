#ifndef BOOST_METAPARSE_SEQUENCE_APPLY_HPP
#define BOOST_METAPARSE_SEQUENCE_APPLY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/sequence_apply.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
#ifdef BOOST_METAPARSE_USING
#  error BOOST_METAPARSE_USING already defined
#endif
#define BOOST_METAPARSE_USING(z, n, unused) \
    using BOOST_PP_CAT(v1::sequence_apply, n);

    BOOST_PP_REPEAT_FROM_TO(
      1,
      BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
      BOOST_METAPARSE_USING,
      ~
    )

#undef BOOST_METAPARSE_USING
  }
}

#endif


/* sequence_apply.hpp
4t3ZifvGcwctNuWm4xky59DJuLuX/LOisxd1NuVq+RF8MCFmMTYWmxRewvhQz2MJi0KPIAiCIAiCIAiCIIj/Hb8MPMM88BkbZwj5w2IYIQQwZyywg4IX193D4tMqv4aEFRCwpDAuGiIQBEEQBEEQBEEQxKtgGiLESRzFwlAyPs4M3q/y8SIDAxxuJKTudNUhdcerHak7Xd79DVBLAwQKAAAACAAtZ0pSZLwhKDMCAACFGgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDExOTNVVAUAAbZIJGDtWUtv00AQvvtXjFIqQaXU7zyqrQWESo2AJpDAEWljjxurttfsbgr594ztGAMXDqiSkVaJ1vHszPc45VubaVQ65goji2VlKujygMdvQiYqst5/2G6bBdafXr9bbm4tZve7zG4HrDPrDDYoH1GOVZagxSRW+ZEaEq553dddT/VmYJFnWOrTQNzcUEuKXB8kEnrxVWsa6QtMNRQ/d7pbVvICo99kgvcAFT/mgifU2O6zWBQFLxMQlc5EeT3aZSWXx7GWPMZRi3pl2+e3q812ub46r/HWq49b23XnPowTeJmLe/uEWtcI+QRZ685yhJroevRHG0G7nh+Ek+ls7jzZL8NhOAyH4TAchsNwPDEH
*/