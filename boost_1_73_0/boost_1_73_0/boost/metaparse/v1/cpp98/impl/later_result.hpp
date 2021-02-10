#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_LATER_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_LATER_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class R1, class R2>
        struct later_result :
          boost::mpl::if_<
            typename boost::mpl::less<
              typename get_position<R2>::type,
              typename get_position<R1>::type
            >::type,
            R1,
            R2
          >
        {};
      }
    }
  }
}

#endif


/* later_result.hpp
6exxCTtRS/FekpgjExnfMpPuUybuDEpYYW1FN30YK7HF5HOCsJe2cPRE7Y5ED71PM2kqbaTzcAjBDNbSkfIOgPCpaJewc23TweLXjJd60xJ293Gmt1vXnK4c0tRXOuiaHNJJqqxscvQ7nRHng4f5Kn1cRAOncDFfpjycTL47eU7kDAicFyhy49JEc0R3Q+tn007tDWu5PkC7fWJtsW6NdKsDhTDwjqjAN4W2Pot3bS1BVLW2OtNlwpw1HXO/qx570MZG8I9Aj72SucHNhshp15q65IO3u+Xqcf7isZssw4rSl/zS7VnMTxQ0PzI0BOfn1Hd9OT5yol/G9rqvG5/Vffb/P/6UOt3jXvfkTLexOU3+KLyrm7g6/jkAfvrr+QtQSwMECgAAAAgALWdKUhYAenc9AgAAVQQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzM5VVQFAAG2SCRgzVTbbuIwEH23lH8YpeKlImtCuys1CpGqUvW6BUHafVy5yUCsBjuKHVj+fscOlEr7A/sCnovPOXM8kFo0thAGM5ZKtdL09YH7nW5Lk7H7PJ/7D7i7zVn0yFJ+Kqa872dnLG2xqfeUKoUVoHRRYfExCfdowh6Ex99iGI9GMHsK2FRYTCDvcAij
*/