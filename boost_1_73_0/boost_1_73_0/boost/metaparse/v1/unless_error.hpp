#ifndef BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP
#define BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T, class NotErrorCase>
      struct unless_error :
        boost::mpl::eval_if<typename is_error<T>::type, T, NotErrorCase>
      {};
    }
  }
}

#endif


/* unless_error.hpp
ZXN0cy9kYXRhL3Rlc3QxMzAzVVQFAAG2SCRgVY9BCgMhDEX3OYUw65ILBDdzkCIzEaROBBNbevtqh9Z2Ff7PC/+HjNW2oOyBksTSx42fj1J39dAk2djD2mq+Wjo4czQgnAjheQULLG7NicUumnYG2t6iE8r1ztWDFOk2fiRFDtYq/+YQTtORhKPX+st2A3WD1Q7gSRB+s3C+8wJQSwMECgAAAAgALWdKUrYUVx/AAAAAWAEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzA0VVQFAAG2SCRgZZDLcsMgDEX3+gpNvG5IJl2q3vRLGCynTEF4EM7j7wN2EnemG9DjXMQVFdbirHIP5GVM9frl+zXlQXuYxZfWB+GSHZDZWmRWGjro8Dt4lvKhfmAgtySVUM4Xzj1Iklo2r5RGtmXO/Pd9MlsRSWys31lm4mSzejljQ7GxWgGzEjT6wNjir11IZ7MojqfD566HaN2PF0a+2TgF3rsUsTJe0A6xnpNVbVbWYHjzbs5h/1/UPGyap6M2vm3i7dhsy3wAUEsDBAoAAAAIAC1nSlJhJQwCrQAAABcBAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMwNVVUBQABtkgkYE2QwQrC
*/