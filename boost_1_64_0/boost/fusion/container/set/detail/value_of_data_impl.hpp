/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
rV1V4pt2aV9ZoWhL8D2ezfiTPGx50NzjM3UcT4GmhWOXg5+hq2Rj/tdo0B2i4SHszb7pAXUh/bdNMvhzgHAlT3OPs76oW2qHP+3WLYpjjGB33Q0SiAHcdxRyuCV5HNOuZU9cP67m0bIP80TSSNUw6ft7od4wxruS/sLn2ga2DEoUxIftdUMBDhQ5HwaDrsCWJnDHsEVGzTv1rta47wVGQfoc85wNjm1g+4lp5u0C5cKX1Ryr/tHrINYDKKFhX57lV0jifbHYtyeoT6g5XAcfqZZqMVNMaDFO+Z/tsntYB7z42s7PR/cKv7eUTes+XwRbM0k7v2fWLaOUI3fINckB5pgaaQcnU9aI69pupO2hfZFzOzhLOAGd1Yh2P0ILRwFW0+CU2etLm+BNTRJV8/AY1oK74SoLDw5ykLJpi3+DMk54X5B+lZ5VmxUKTBWz3VFGnDU006fQ0LdxZsMolViX+q2msZdjaVuA32ojxfQZx3BJN0Q4psp7xeHX1hvpMobxDT1OWaPMTu9J9FFZJqlkdjJktNKQwFXjOKOmQjrrERGcHCO77wz1TLpjSA==
*/