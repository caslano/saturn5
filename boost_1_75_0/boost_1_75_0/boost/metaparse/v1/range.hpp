#ifndef BOOST_METAPARSE_V1_RANGE_HPP
#define BOOST_METAPARSE_V1_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/util/in_range_c.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class From, class To>
      struct range :
        accept_when<
          one_char,
          util::in_range_c<char, From::type::value, To::type::value>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* range.hpp
E9q03K0Y0+Ymc1w9NP5crwqkVe9Rq108eqBVXEZb2wDWD4dLJrzsRJo8khcL35QBBB41Mx5H0r7kGEaGsW++FwWC9neMsvZ4VD8bxyMADAfS4TR2hfaqplvZa5qxtIi7mQ3WExqQ6w6zWNIsBqzZJJY0w1vhXHtiyZ+4TRAEGZN2D57iBU7F4oZ+502B8eJvvB1qRneBrkNQTtMl0D/WpR18ZCUHqBcBe/ViR8COfhZJBsN6EbvHL7sXnghFXFJ9reIdrXJXMW06uriqG3tOtHhtNC1Y10LWIt8gWIPLCsigQGAlVoMC7DCwg6xeQIuoehEdKxfRFlPBj4v49TJ+3fskx0YIRnV/MFIxcuxBsLnmL+ZaGd90WB+jTxRF5Z8nU4QOzibGWcJlL0AFaLd+xom55HWc5DmT2hm9JnN9PdFcNQNINf/cQqaf2lIdS9lwnQ1nb4lLXVjVCFGDrJvrVcme7ygOsbkaPGXU5ZboBAx176DLl0ViqWfodVJwZHezu/zQLMs0GQWVPbICUyoNQR7GKBx9gscovC4s3pgCYB2GXPMwOCaFDEO+HIaJbBjy7Wzv7w60PQI5cY32Y38QhSp5BnuNNi4ZvpQb41F5QWLn3ezEwFZP4akYZCoPR3GJgA+lWtV4Do3kgwvlSMYVEe00Nl9pxHsI2jk+8Mxo5yc70U5iRXdux0UCWv34GRLQR3OIgB47IwL6+p4O
*/