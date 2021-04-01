#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <char... Cs, char C>
        struct push_front_c<string<Cs...>, C> : string<C, Cs...> {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
vrzDsxqNMDyBoYA25jWcJux8LYMnzP/ehdigLJU19jThyctG45eyCG6MjENhPDCrIOqaBCjJ9JgXVgxA3V8JIqLF2b0/uKAt+sXjUgBGOqutuC6mDcy5ScjQjaTuB44DyFlxjFEiLrOF4MflDnBCEgSgu5m5mpX357zEAC5Cg2qTF4/KXswBw24CBK0nrKndFXMem7y0jxRgEho8fjxOf2oya+gh965j/e/h3RmqfIk9diUqS0gv/oKp515OLI2BFv0AEnhocH+CaLqaRrG4qiRKRRluyiYcGeHbmvsjmHLWfc2NAraW0k3N7zgV00JKn8yc4sv++qhFdeYyYS4wuFxCIFT+B/tC3X+74z64ACzpha7ehG6nGH4pzLrdL/fLmoXdMRJ+M0k556TjjZczMsg6ID608bhWBA11DR0pcpcSjMdCY8r/fsRSlN1cJ69FtdqqHc7YC55I3hgzy41ARwZYqKMyLij4b9ZPgRWgjzTOSEVEB8+fRZ9NPcQ8xUGK8v9CjpZWiNQddphfxdLhF7qMt+2NrFh5cpXn+0hfUGwCnI8nH7LLG+jMIA==
*/