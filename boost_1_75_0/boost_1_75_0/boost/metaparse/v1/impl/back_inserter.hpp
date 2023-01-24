#ifndef BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct back_inserter
        {
          typedef back_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_back<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* back_inserter.hpp
ZB2D13Z0+Lkpg1UkW8/AZG1qSly4JnWWJrVfX5w+iejvNAiXkXsNM4OMFXMM/Akg2l1j0PbsNQO54lBYKvLTML1RnCQmCeKnoth4rIhnIpArDI0NyWQUmYFiKpgMxgfFx/98TWoxCVJyYyuRXxpy+UKKnmj8mYJKkkhGm3jkmk3GrAR0p0GpUwkNMUoXRka/bszTjASl80e50rHpg9nTF74clahckXaxeM5I34g+Bb19DwkuuOYuY0pCj+7I7stzr1jV1rXEf4D8463PTbxz7Lvh4489te/wr7eDD//us+nrgGOrbm/s2f9XVw/F2yJpO/8Ll4q/L3vrwf3nZshz1etPBw191ku95v3Ik/dsA9boD/0u1vTLa/2Xw/XX1ZeC1y8Zt+7YO+uHd1mTPeX16haK3Lc++LCn83M97iVPDxm6cvTI9ZWuqw98ELG22xLpCO1HhUH5X8xrP+fIB8slg9osT7dfIFszxsUuaXziMfegyNMu8lOKj4+Ib9g+u+FSrKRLavGpQ9L32m1aNemAfefTPQrLn8otd13hxxSc6tzrs+OVpc/smXLBddca6i7mhR/kuQ/x3Cd46W/wwj/juRcvbv3K1Jpy1/cHILdzj7bneOHPDhr8zJyQS65rZiN+JwwYcYUXfo3ndgNtXEJhRFue24nn7sFzM7zr6Rbc8Ba8+LYVAm56Ic/NmKdfMjd42dDicte9XXC93yqN
*/