#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_BACK_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_BACK_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/cpp98/impl/update_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_back_c;

        template <class S, char C>
        struct push_back_c :
          update_c<typename S::type, size<typename S::type>::type::value, C>
        {};
      }
    }
  }
}

#endif


/* push_back_c.hpp
AKpmy3Xt3D1YihtWCfysxhzPKPcCqpbK8nTYCxXz/ndwbasNn3yDuQlEA63czPq7uhTgHsjesREd8DW2tvP3d7AqtcJKuWYr5jN/19EudRc0O/Ztipq/DN21R+F6YGBY1Vcn0ywU852sDVSDSAm5sQl1IqYucUVnTBPlsB8KypT7r6hM8Ucv6/poMlyiLFWp5DTYKr83CG++nd3VldbVP9TAfMHZzBe8bKdqVaTSHuxOrLVFrl+n9PZHVMPug0qyX8sosRkutwb1QA4TGn0J28nxu6YQQX+F+ToL3mU5O9q2McdvEdpiODxRw67RrC9rTgJTsGmliDXn247JJigiUSjbTIxLfqLqED9RNPcTMTOiSC7Yzuq1YZ6TF9gr7nh0EuVE3+45GYjClSCeg8DCqh+gdQGqYhSLigKFlx1Bv7lK7Bhit6pFx9cdSl7HTQ6Ub0lxj4beL2EpLHM3uQfYsvWhfiN7ueaUsJdjNS+pHvVZBPHoDgyt8A98eqqe8jLwNCzjtlHEBScbo8BV23i0Sir3l9ZdTOZCN53cpY87WB+bWB+/0qT2MaWulD7H7fd27uLX1jNWNbOPr6SBdEzO3UodKt/EXBALoFdX6lQj86Ktqgvi1rRMMKtDLer6SF/+Su6E+HwrdxzPtUp1XlnvTsI/8d4Oo1S2AKsV/4X79v5E3149rqkvwTbILZGJbom5agtX83hQ6Jgxb8EA
*/