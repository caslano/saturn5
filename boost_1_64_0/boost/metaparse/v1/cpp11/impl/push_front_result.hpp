#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Value>
        struct push_front_result
        {
          typedef push_front_result type;

          template <class Seq>
          struct apply :
            boost::mpl::push_front<Seq, typename get_result<Value>::type>
          {};
        };
      }
    }
  }
}

#endif

/* push_front_result.hpp
BrU8AKVcmEyiiFOBo3B28ynpuuwHe6e+WoZumj7em/OCdmInMckx6fH5NeBp2w6F1lJohl85Uy+MVLstOwy7gW1rk/9Sb3KlXMXCMVPanpaFAhgq9SnOmv5RkYjw32EielDvEVT4AsvKE7w50RJ0nqnqqj4mFwSzC43go1O95yBIQW3IwQtrrj2z2NO0QYXck0LiVrt8Aqy22YADAzbr0e36VKrW9Q44eeFLjpy47pw/ngRfzdPXKd7vcLwZTPr7Y0hfWCq7KJR6ldyaqILmq84u5EDVACpwK+/z7zkhv74idPYjVbsZanh0htFKSVJODTmY1DB3Xns/KssDEvicpH8b/2nqMSaWdYbxMvm8+3Mszo5FuJ8Wr6rCr8ppnLaRSYxyJF8pRJZ9voW9alr5/oC1i9mUDPrLr4Nz1T6LeaEu4BTG/qfwb/2aFISvh2dpxw4mjnHFc56HnKoT4EexcNh6hruHCaH5bjIk5qhwLGaN6YB5a0frTHYRxv3lkvG70Bja/Us0nJ9cKYg3F/aGhC7x6Bs6WAv3rYHRgCF00vO7TXUkMPui5sK+tQ==
*/