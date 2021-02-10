#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>
#include <boost/metaparse/v1/cpp11/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp11/impl/size.hpp>

#include <boost/mpl/clear.hpp>

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

        template <char C>
        struct pop_back<string<C>> : boost::mpl::clear<string<C>> {};

        template <char C, char... Cs>
        struct pop_back<string<C, Cs...>> :
          push_front_c<typename pop_back<string<Cs...>>::type, C>
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
2dy4EQt3PZYo6sY4k5gyYjRU0JeAw3B47MFYJ7+X7LF/5AS/3ZAA6sO2KcX563y1fly8ePtOSrgQFx7zSOipTCiOtcVp2v8DUEsDBAoAAAAIAC1nSlIJEJuNsgEAAJEDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMxOFVUBQABtkgkYLVTz2+bMBS+W+J/eGrVSzVivPWwIoQUtVFbbS1Rw6pdPfMIVgFHtpMu//2eoQlSpxx22AUw/t73y5B5dF5JhznLdF8bur3i/s3YyuXsviyXwwXuFiWLY4vOtDtkGZ8wGR/H2Dk7hxXaHdrY6YpAFjftngCV9HLk4mIm4HOSQPGN3UqPKZRb/ATJNTyZHW2IBMRVenWdEuTusWQjXQrBY+yGBa/lK7Ib03vsffwd+7VvUkgY+Rh1BjnxQc+hMn0FNO+06f+TtghlvIce2rhpdQCObahhQZCRK2eN9xsaOCwh62WHo294076BY98gybujXWiM8xBwsHW6X0Ol6xot8UI4QkckfGSBTJmuo7l8OjZ41D/xVs3dYqaKLr0ISsviuaSnYlU+LCE4Sjk/AePii/h6wHT6N1ZBc0Y6HzBJkggKdjRAj+/Zh1Ze0Op6D6ExkLVHC77BoWZopINfiD2c
*/