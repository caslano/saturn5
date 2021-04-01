#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_whitespace_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_whitespace : is_whitespace_c<C::type::value> {};

        template <>
        struct is_whitespace<boost::mpl::na>
        {
          typedef is_whitespace type;
          
          template <class C = boost::mpl::na>
          struct apply : is_whitespace<C> {};
        };
      }
    }
  }
}

#endif


/* is_whitespace.hpp
RUzIwgxlJPtJ9K0Xj9Y3WUUyorDjvyys5F8IafdEDRbxzC/YYllolFxF7/e15h2CzptMtoGwqHreyc9L8ICC+XLKDt4wGd0QhreQXhIb/KjppiBB1ooD81+7lh+XfkrIaVQ8LpNkjxoVV+xHp3E8io4uYypHsyk8K3kNlj5RB+4+LNdCh6q+v9pkW+hSDfGmTTBxMgMvXc7LeT6tBkqREpzVdmSUvxgOnmR8sBoVZzDeCNa+rG/zPn03r2OooMiOf4Po/B+WDpRo1DfjKD1pnagrni+lPgGOg/nfrzaIlZ391xGyrvZ5I1TCAi2727SOVlYeqhsOWbbHfFpoeAk2OjdiV2W0pPk7jyW5VZoRbOASD5aa9RVEPDXKUFJRrnodhNciAq2y+JtEWJTSh2yv2fk4PMBeGbBBELGrlcj9ee3jnZtTIxBLVlT2ZfVXuWgAH9axQlZOg7Juv1Dd78clQcLHdcnU7CRDRYByFI3w6dbGnackM8cIVDvmSTwMBCcyBRM8tAXAT+rlln9/Atg5FQ/hdIEtG4pYNpR1/2xWBtGxL/fONvr2wr5gGg==
*/