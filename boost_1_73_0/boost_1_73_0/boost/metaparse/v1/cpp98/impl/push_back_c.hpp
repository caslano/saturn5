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
25yl/BxJeZ/MLljaYlMfyVUKK0DposJiNw2PaMJegcffYhiPRrD4GbC5sJhA3uEQRtfwpA8UiUcQT5LJdUI5d7/ygK2xPWCbgGOLjDf4RuwwYDOtLCobPaLa2iqBH96lsLBSqwSKWptPWfmxQafy1/LK7uuABSweX02+E76Ddc94h6d3XMCslu6WkSWytPBGRm5bSQMtkm1AKzIRSnzttrBBYbsWwWoQda3foDPubNBCKVti0u3RO+iA7h6JRQvQnW06C1IN6YJUW684e149/slv1/n8YQUH0UrxWhPFewnquC9JwGdP2ncmY5W1DUVOZqrEHrOPucGbtJWrG0l/pPJwatBcmkYb6Zo3hGhOpCWFSauXoAqUdsjYZ7rpYPl7zmu99SX7eFro/V6oEnTjtKah0lH/zCGdpCrqrsSwJ004H9wv1vnDMhk4xuVilfP4anLlAB3mHCKSfld0MzqNwg/pBVu5OYJfNrGx2Pr2uU2BShh4RVQQmkrbkKUHn0sSTautLnSdMdeQvtppNQN2r41N4D+ogD1TS6ObLRWn1eramg9eblfrh8VTwG6KAhtyX/JLt1YpP5egqckaY3A9nIbUKF/vK/8YPO8JfPwJvN+Hr4rfg48dOP8YNT//of0DUEsDBAoAAAAIAC1n
*/