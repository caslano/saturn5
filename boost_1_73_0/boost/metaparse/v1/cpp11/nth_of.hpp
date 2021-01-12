#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class K, class... Ps>
      struct nth_of : nth_of_c<K::type::value, Ps...> {};
    }
  }
}

#endif


/* nth_of.hpp
g/kkD+EHbM/veChb2vE78XAezlR2ZjaP4CweyVvZhW/zKG7k0dzfgdiDh7Mnx/M4nsfeXMA+fJzH8wv2ZUUHyknsxP7sxQHM5UCew1N4MwfxHg7m2zyVH3NIaF9tKJsxlUOZztEcwckcyXM4ilfyNF7NLM7hGF7LbN7NHN7PXP6Refwrx/MNTmBhOdnwXJL3lFBO9gHTVebDTOEjbMBH2YKPsTOf4LFczL5cwlQ+yeF8mmO4
*/