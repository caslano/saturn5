#ifndef BOOST_METAPARSE_V1_LIT_C_HPP
#define BOOST_METAPARSE_V1_LIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/literal_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>
#include <boost/metaparse/v1/impl/is_char_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C>
      struct lit_c :
        accept_when<
          change_error_message<one_char, error::literal_expected<C> >,
          impl::is_char_c<C>,
          error::literal_expected<C>
        >
      {};
    }
  }
}

#endif


/* lit_c.hpp
OUFp+XEnuusTpcsHGEsAlVvswBY4tQqFMvAPsYELU2h7wWQ/YUmAwlqd6mrNHu4TmAxg/oge22hjBXySxGOPVJh/+0LmAtJjV/HF0/3+sI12HrtNU2xpfMkvPeZRyLOJ5Cdnfv41/wNQSwMECgAAAAgALWdKUnsFxOg1AQAABQIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjY2VVQFAAG2SCRgZVFfa8IwEH8/6Hc4FF+EmrkHYSUEZMj0ZYp2vsf0tGVtUpJM6bdf2roq7CmXy+/fXbgn55V0JIAX+mzC8U3NzdjMCVin6Y69zN6As0eTsx4HYxjjgeyVbOyKjIBbqssmADLppQATkH3FXYdSVSbA3ZwqjQto9tTl7M7tRN/LgrS/i6ruMogIyL2vB7YA5FpW1GfFj1WKt8LnKNEV+lJSfGo84d8caMnVRgd35KynIVemqqTOeuGEscl6e0g3u2TSsnbbfcrmr4sFxnH73i9joITyHq8LfiRbnBtsp0Z59mTR54TthjGXDk9EGkcuN34E/Nphg0RtjTfKlALa9L1ZF3g+m0ewNs4n+C9TBF9hAfHyEswTVD+2ZJPjan/YbD8jWCpFdWhP2TSCKIR8WHA2+LLHz/8CUEsDBAoAAAAI
*/