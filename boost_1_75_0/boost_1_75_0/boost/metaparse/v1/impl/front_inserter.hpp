#ifndef BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct front_inserter
        {
          typedef front_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_front<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* front_inserter.hpp
3LbW7caactfcF4hcfechoHacbwuKmYBDVGAPA84PpugSQnELoEhNMSaUYiG4tWFgF0fA/KCW4l7ALMCaURSvgTviH4ryOxR9hLQ88wF3Anp/AuUAvCaj/jVBFD2KgE4Rd15TZAP1g3pHsBgP5YH6x0M+WYBrttJwfwjPBdwCOH8y1GsR8AvwdibFjBiYH+yiKIyDeQ/kfxPwvoBHbzHQA7y9iEvv8kcwzynk+u8E+mugvt5AV8m2dxrMcyabx2upFDcAJqVyw9ny+YB/yUzIH7AC+KIC/mkB7wOfxRCeALgOsBrKVQqYC7gUyn0WsAqwcBsNP7uNW38+VlgI56crhXIyQF8C6JEO8qEDuQOUAvoAOgKWQX38gF6UkEvn9ixoJ8Aq8PdLN19ON6CnBtQBSjK47eIBbgawZi833Hc2150B9dsLeA2whicPbP9hy1NlQW74WAT1LgU5dAT6JXO48XZmcOlnZZjnQzHUWwh0pYCFC2h4wgJufPWChpUzYx7F6Hnm82XbTQXhfoAM4Ja50E8AvQHd5nLzEUH55YDRgA+Vhy3/QtCvwLcNLP8A/XeAnn4f5Hcn6JUPoP8DfwqA/+WAkvegf20HvQ3luA3owvZX0Fd7d4O+uQL99yrIAbhjXmoYnw36Beq1E1ALKNdAfaCc1SIbjvwl3QD5gPwyAJMG0Hj5QL/4LeifQE+bBvKio3gZMCsX9HgexaUr
*/