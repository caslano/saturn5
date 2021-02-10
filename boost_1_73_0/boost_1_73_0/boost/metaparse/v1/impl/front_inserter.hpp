#ifndef BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct front_inserter
        {
          typedef front_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_front<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* front_inserter.hpp
ZGGFZdFMyJuJAoe3d7eQKGlQGt3v91mYcsNBqiTH5H3caVB3JuwxjpfBsD+Em8EAFj88FnGDI4hr7MHgHn6qPUWGAxh+Hn2+H1HO9+fYY23XEVjkvnZGkPF39Ni0beg/odyafAR3ziUxMULJESSF0ldZcVOirfJhgtzsiksgErpUWrSX7DSS73Bsv+xYD5DkvNJoxlktZfMAqrSZY20qLrdU32PPC/oQUXZmS9iRGuJmWgjboWUscYalzORCQ4Vka1CSTIQUN/UWMuSmrhCMAl4U6gC1tmfqDqmoaDBVNc5BB7T3qJi/AFWbsjYgZI8uCLl1Facvq6e/8WwdR/MV7Hkl+KYgFMcWtFnXkuBePGFL74RlpqTAyQotF04ekKqDLBRPe44oOAiTw9SPqLWd8dSeIPmi56IEDfyIirU1qANxvp+wa3Tj7vItCgq1dT3beJio3Y7L9ER3Ryq/HbNHJyGTok6x45COgqD7uFjH8+WoSxiXi1UclNzkwVmZDg8VP9ak6rRw47Q5YSVWBXTXqykhCQqxsToLpCKhCE1iLgsgZMFJDlTl6i6VPC6VFvGKlcgacMrnmcHKrcGWg5xr2CBK6OhcmQ4L9y7XAqmUUYkqJuxlPVsBl0o2O1Vrjy2/rtdA433BD74rC+wT
*/