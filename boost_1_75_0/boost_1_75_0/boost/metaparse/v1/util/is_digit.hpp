#ifndef BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

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
        struct is_digit : in_range_c<char, '0', '9'>::apply<C> {};

        template <>
        struct is_digit<boost::mpl::na>
        {
          typedef is_digit type;

          template <class C = boost::mpl::na>
          struct apply : is_digit<C> {};
        };
      }
    }
  }
}

#endif


/* is_digit.hpp
znB5/9ljENdsOXp6AJW9IL4httCtbmIXs3+Pz7FfK7ZVETlg00SLdEg0JbTUZTkYTadhVMX9LJ2/Gs1LgtfZcmntzfZk0HieepiYIE41uO3IvfRseviRMs+tOmPRJIQB58Q//KmFP3YfxTl+Tjbr/AWnSMC/KKkcTlTkStXSotO7qlRj0FE9twt8qaNS2/NYcopGneeeMtq5Wj5RCTDXSXgdSMYFd/rskt+ZhlNQSr8QPF+bt6eT6E7P2wWbbjsVAbGCapc0Yofv1iNsZA+/HqvQRf75Qvt0z+lXvGajmBRUjoaDZC3onpdNQKyaVz+W4vz5Y7xaUqpRYtCDKnJNw68rK8TzaOrOGAnz7GXuPeIkf3/SW5cVuFjg64tUl5j7ROYgXHGVYGpwWSJMD8CeglNbeZ0anPdXJ8hbCDbrVryp+fDVYE/71Hrz736OAGfkGghMwUFAOEzN3e5/MwLI9LAv1NfGVDCh2KBIzhv2k9AcymIK40Tbc1x83fmDCSooSdsfnPg3+r3NW8ls+fPlyuJK9zC/DUoj8iGUF1mvPAP5kwKnPBPtp1R/Nn4Yz+L9x/T5kyffzkx+ITj0il9Ok2qc/PjcdUbjwZNEtyy44Jv441oI8VGlkXkovM5Z5ifF46JLEM0cyBREaQW3XW62OSnjUGomdomY016wV+Gw85sCDDttRMTSXJtFqkPpCsvTqgVM3XKJ8zVRGJPR
*/