#ifndef BOOST_METAPARSE_V1_IS_ERROR_HPP
#define BOOST_METAPARSE_V1_IS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_tag.hpp>

#include <boost/mpl/tag.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T = boost::mpl::na>
      struct is_error :
        boost::is_same<
          fail_tag,
          typename boost::mpl::tag<typename T::type>::type
        >
      {};

      template <>
      struct is_error<boost::mpl::na>
      {
        typedef is_error type;

        template <class T = boost::mpl::na>
        struct apply : is_error<T> {};
      };
    }
  }
}

#endif


/* is_error.hpp
/8xvUEsDBAoAAAAIAC1nSlIeNcOYtwEAAKACAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI1OVVUBQABtkgkYGWSUW/aMBDH3y3lO5yYeKmaGbr2gRCidawqaBswSKvu0XWOxWtiR/FBRj/9LoQVTXuJY/uXf37nc0zoSSuPiYiN3ToeXvDQuDrziZil6er4gPu7VMTyvBPLDhbvYIP1HuvQmwxFXGNVHHg7U6S67+Xw/QCuBgNYfgHfeF04j4H4rAgjSHd4CYMRLNyekeEAhtfR9Shi+P5bGoips4SWwvRQMUz4m2ROZRGIDVI4de7F8PI8VOUkxxrHkLlSGTspnFZF7jyNAxGIZ+fYtvOJ5cmPtaeFabM7bX2cMOCPxSQiJ6oY/zuF2KoSu4LgYf0VGkM5eCyNdoWzYCxUyvv2cJiVHQyxdmWpbJaIXpsXSbnjwKglxy36sT9bbtL5Kuq3uavlOpUNykZZksOrm1GPBd4S+PXkyO6PWJvtAdqiQG0Ja6Acoe0k5MrDM6KFns8dccT+yHJAVTtyrJsIbib88yc4NWoYiBmfWwT/iQXidke5q82rIuNsBJ+UNxqyp0Whf1XNj6fF6/JDttfl90kgHrjK8PYn20agd3Uh+4936818ueAU
*/