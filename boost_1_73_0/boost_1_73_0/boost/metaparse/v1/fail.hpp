#ifndef BOOST_METAPARSE_V1_FAIL_HPP
#define BOOST_METAPARSE_V1_FAIL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/reject.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg>
      struct fail
      {
        typedef fail type;
        
        template <class S, class Pos>
        struct apply : reject<Msg, Pos> {};
      };
    }
  }
}

#endif


/* fail.hpp
N296bt7/+gdQSwMECgAAAAgALWdKUtsdR6CwAQAAmxQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjM3VVQFAAG2SCRg7ZhNb5tAEIbvK/EfRo58SUQWp1IrIYpiW2ntNqodG+e+WQ8BGbNod5zE/fUdIIkPveTc7kgvsMs7H9oLj0gIHWnlMBVJWeeGbzs8Phu7damYZdmyu8BEuVKDOlAhEnkyJLLPOYM12ie0oSu3KBKLTXXkt1tFqq8iR5cjuIoiWPwUvTWGtnPouoXM1Q7F1NSENYW3WD9SEcPndqdGTaWpY9CVcSdPdmywLfFCsqB9JUSYGxPyQH3PRL7OwKNNq7LN6EfT3YINfeNUFEQN29+WkNRqz4exWd3Cc0kFjKIouoAKidDCgW3QGuACGuVcewycIvscSLTZ71W9TcVg7MOHj38+4okPHz7+g7gezhbrbL6Mhy3RLBerTI6uPn0ZMD28f/f58RUwGDzu0Zb5EVoiAZW3/EAFdtgDhXLwgFjDwBWGuMRT5+UCjTVktKlS8f0mg64DvBFUIGbGUQx/DRKIMaOZseVv1cNSz2t3m28TLy8vL68PKmumd7sfXl5eXl4f1vxrIDYObTh+ZAKOQR9sJYf3N6v1fPGLCVVrbHj7
*/