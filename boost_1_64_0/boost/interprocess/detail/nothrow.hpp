//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP
#define BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace std {   //no namespace versioning in clang+libc++

struct nothrow_t;

}  //namespace std {

namespace boost{ namespace interprocess {

template <int Dummy = 0>
struct nothrow
{
   static const std::nothrow_t &get()   {  return *pnothrow;  }
   static std::nothrow_t *pnothrow;
};

template <int Dummy>
std::nothrow_t *nothrow<Dummy>::pnothrow =
   reinterpret_cast<std::nothrow_t *>(0x1234);  //Avoid sanitizer warnings on references to null

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP

/* nothrow.hpp
ntaOqeVpnIGb5Wm8wTHL0wSDYy9PEw2evTwdZfDCy9PRBlfKE97BbeCy2iJZnV6aYn+OMXjcBjM+2cD1cnlsEJf2EvEpBq6X2zwDN8ttvsGxl9upBs8stwVBjrTdiBcGcWmTEZ9m4Hq5n27garmnMj0jwGmMY6lGrEjHeKqEyvtxPlZRVlmOa/bRzcyAXl2nXxzA1Lt/ZlkwdY3NbANnCz7jJSaurbEtNXC9bMwxcU5rim9ZAIe0RHflQb2UbVqX4eNzvQsgUV+p6NU1VHNVPbYiVO6OFz3uJqX7IHDxJNdc4s1rgZeuXlwXZf/mh/LgNogERht5C+w8uZnBO0/AypOz5BZaccxmfM+JdlyKAbdLJ7XAS0ajDSq3KpSLd+lW1cHUoNd+Lgrl6jbq6lAeN1XMW2znSbHjMNaE8+ATQN9zHAnlyt2NUSvH/5xATq2Vw80Th2uJnVOfWB6VdOa6s9TKlfnRmBXHrhDT6uQwXCYzkLcsnMdllteAtMCLJfmM+RY5eJAh8uLhPK1cJsJ5chwbc5OhXLNcnhLCDZa3hhBesLylQnmYhBo3Hc6Vssnvb7Ry1S6NzzcI4XEZRr9OtXOk++PwNVl51Mx5HY9/t7jPVecBKEyn6VhDFOc18MNAzq3XOBgOplA7f4aKV8lZLmd6elpdRw0eY2fpGFUI7gfOFqyxieZ0MBzNnl69BlW5b3Wlh9M3dWAFPK9B0TncrxN2rmDosnqZ7JU7L4DVVJOb83U911nCLtAxqqfs34UBLMbfcBcZeqyPiF0smDK6pTz6sWDG3C+uMwngXDARW6VjlMHeGQY+JvsFVqs6tjxQEeY1JCpOejrTwNebewyuEIzmnfn9V/p6mVu6ytNRamtrZNf4GKzYjOAwybi+FNeQGDw2k/F7r/ZxmbO+xtMZ81W8hkTH44l0Xm2a552uNbD8aC2dhUFrSAQ35sKvt2B0x0PaX19/g8bR67E3zrtRONa5sZs03Lzvd52Oc4JBEVPGout1TnpxyvWnum4J+3GzjqttiX932y06pzEWof2UG0SvdI98voGOJWpSSTrfQPT6/D+H53bBZfRKX6HVDdFq5NwRzonE+NvozhY5VdH4cnrfXaE8XN2Lft3dMsf1DHn3WHlc85X1vvcKT74aOd3uC2D+mfii1+c/GX/AxHnek+L5oODmfCeH6yGDg8NNxB4WTJ3fxHg/EsSi8Ug0guWQLnflMDyq8qS6at8+PxWOvr+Bw/iYissrEHtcwehrvi4aZ3836lhDommFx0C3TwhurDd40oKR3SSa9u5wfkrl6FUZ8U2CW9d3PG3HuTfldSQex1z/gXH4ueDGHprNKlavt4XPaJjZFj4reD0eMVgdOdlfO+Jhsi8H4/O8pzfbe7cXwnLzQjiHFsNyvF8UnpQHpf97yYaTDxiWLXacl9VS//Kyz5H5kld8HWR4LIKtn4e9qmM8XuKzFjwMLXe+CY0aFA7zL0wO47yeJICzc7oPwMPws4b42zwdNrWxCA3TCPulj/EEMg4r+G7xAEYDfowqFISI34+/aeUhhVsJXksS4BFjicxyM+9XoTxW8Lj61+G8Uxqr6/AsfK/t+I1wZaJcWeey3YKTXxQbfy1JKM//fML53HfsPO/kHSGzv7+18enVnIZUFt8VHmYi3k0gOm291XuiV5Zh833lOgYAudkhemzLeIiH2O89jIcsZF0hd3/wMCztehvygYaZbciHgit9Ht9ZLph1T9ufBPfabuwzvLr0Z8GtbftHKs5x9tx+LJi13f5EcGub+6ng0uZyPu70MGzP+c5y0fHaMnrPX3y9tP2RRmziEP/cxLXzN3YJroRR9nD81cClkcR1HSauNpI=
*/