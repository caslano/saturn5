#ifndef BOOST_METAPARSE_V1_EXCEPT_HPP
#define BOOST_METAPARSE_V1_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result, class ErrorMsg>
      struct except
      {
        typedef except type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Result, S, Pos>,
            reject<ErrorMsg, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* except.hpp
rBEVTEypLUE8DrkE0LTa6lxXCaOhA3dsjguOBntspo2N4VV7Hrsj/f7lluhjyLu24tP76+XqZv7TY5d5jg29PuNnzvI/oaO/B/3vdC34yXdhbKE7GqHvP7iqB99//S8cFX7gnnoDXfSR++w/l0fHwThHwV92Fz+dt89QSwMECgAAAAgALWdKUrnTxNw0AQAA9wEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjM2VVQFAAG2SCRgdVFNb8IwDL3nV1hFHFHphwqbQiWEQEMqdCplF8RQaF2oVpIp7UBof35ugbHDuCS233u2X8IrLKtElOgznstM0fWB55PSaemzXaG221zu2GQ4DZbRmHHzDnLzwm/BAvURdafMU2Rc42dxrtFrQPioyFFWVzxpEiKUjcpnUkkqm7cUuBQH2ma1htt4UIRkhTrVcbVH0ELuEBL1JSvUpDAvkhbY754NgwG4nmV5fa9r9V275/R7T12XaIk6HIRMfWa0X8JFPH19bs/DYLqIx/PXMIpNy3bcVbdjrb8NeEBZWZ1/eq8flA3y9TuUwqt1WvQNdZ6dIRWVAJGRi8ZX/RewFyVsESUY5V5V1OLYcGt7Tu1ttIyC8YaOzWwYTMJoNowZR62VTlRKr+DQpD8p
*/