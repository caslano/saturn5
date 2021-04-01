#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/cpp98/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>
#include <boost/metaparse/v1/cpp98/impl/update_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_back;

        template <class S>
        struct pop_back :
          update_c<
            typename S::type,
            size<typename S::type>::type::value - 1,
            BOOST_NO_CHAR
          >
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
hnOs+7Qn618zSCx/8lq5Mof3DXlMwowKNTZgKr4oKUvsbb/+KmBb4i9EnMXKk313rMqqJufiYAy6BC8p22WEpDRzR92Q6saaefjNoTkaJDXRQoK9XgphSuTk4FDzSxmaEItSv5uK1707+NbRDeF/QZCcJSSIAcKYTpZWd1byeogVO2/uB4GS9HDNrw67nbwRKHeZ6lswE/aQlQIUEu86iBaNrJiIlJt5iMoyr/UY6pYSKUj1p6JuxOZZdHQKtQ5FpSGiQ4Y39ezm5mjOA0umMQTupUbzGu6YPqrQauFRSs/4csZd8Mzh5WKGdXYUqMMuWO+QgcYSxQm8093kR9TZDsKxeqdBUa4v8o1AKourD7pgsJUbYoZBSZcfAKrHF0oqqHwBQqZrCrud9m8X/I/TBlTEG+Ox8plUer/JGgd6FtViEv0YO/2OccwMWlyFaznsEvsyVcNFsH4AgRgSLHmw03u586vSVHVez+n4nEoF+06rcJU2SM9V2W73dtHTfJ/cCBOdczwJa/0wGNnZCutaiykR0H8aCp8sfvLqd9mqE/ZLFCgBUuD8XUGtKw==
*/