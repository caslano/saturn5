#ifndef BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated_reject_incomplete :
        foldl_reject_incomplete<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated_reject_incomplete.hpp
2CHS/6A0lRIL2t7je7cMusgkZ5xmplWP3saWlXSyJ2B1uyvyvBEYbwrKSLicDOgVWe5u0KewTTOZgigxIOBpRX56LA2be/1K1X/YzT1c6R9NqJaX2vQmthQSd4GN42lsJg08xjVdPYkkf9JdPbisLTWMtiJ/QvfaJnRZfjK+/m6e/ePQ+4tx+Edz8vdn5++O091j9t6gZQ8HESnKfjV79p+P3VztKhPy22vM7/5HvwNQSwMECgAAAAgALWdKUk+W3JUCAQAApgEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjg5VVQFAAG2SCRgZZE/a8MwEMV3fYojodAOQaaBDkF4KaUdCzVdQgdZPtuishROchx/+178pylUg3TH+73TQ1IJYzI6Yi6U9XXg4xvHIVAVc/FWFO/TBq8vhWhcKEvrG6HkDVFydomt2MIH0hlpF22FQhGe3HgFloL1Z2fRp0U3U8NAnFy5aFM6Mb62yuuOU623wmBTC4Gl2oUBtK+g1BXE0afLhW0zrUzoOtbmaQcpe7p7zI7Z7in7v9j1i3O55OGcn0i2HqHSSYOuExKkFuH6UtDqCCWih01sQ9oIdZ7YnF2mJ3eA+/0DHNfQX1NG0r5BsB5McH3nQSgkCmRCxYn3
*/