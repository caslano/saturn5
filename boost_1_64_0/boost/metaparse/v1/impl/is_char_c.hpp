#ifndef BOOST_METAPARSE_V1_IMPL_IS_CHAR_C_HPP
#define BOOST_METAPARSE_V1_IMPL_IS_CHAR_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char C>
        struct is_char_c
        {
          typedef is_char_c type;

          template <class Ch>
          struct apply : boost::mpl::bool_<Ch::type::value == C> {};
        };
      }
    }
  }
}

#endif


/* is_char_c.hpp
umxeEv8cDYGyu9fZnCLqoJARQeTaK05vc4EwE1ptQsJJOFKwGREt3/UHIIAiWV5wvjOWNf1GSg3BnPOZAAoHeJ6wY6Wn5cogWjJv+TEpp/NcuclhTYWstFWqT/QMgJkvwZwnoLV00WjNBS1+tgYHgGU5ROAtN8Ul5FfHHv7KroiW7I3NKquiJZKkcHkHRLgflCcB1Cr9FWhmVgMDyXb/dbsFrMOlX2WgL+qFxuMdeL+sLgNpc5W5u7d9Vr3jA2ZRcx9H/L0QAZrMu8wteRlDLZt0A33/42DhEp3IYfruAIMpDNyVAadGyHTgUGUwWmXLL98QsVZP/UfHbFq/gtW6MJuSn9ST9zcKl4rT6TSeDhxbLhOnMncyIygNIdWpP4xlj/2GAD38OsbpaOTvu9JnPYpZz9ZmtSHiS/L+sYsCbLS8+cPkQH+ljXnrHMJFjzKE85M9gjO7zx3/YPmMf+m8ZXPDAkkxudsUFAFh22z5c2ZJQldyuaCxF76zYFjtzGaVDKwg6KwHp0mw+H2N6ac8/F8IX6gpzrlnzPikQrO+jLPEMyRlCOMdhFsxEg==
*/