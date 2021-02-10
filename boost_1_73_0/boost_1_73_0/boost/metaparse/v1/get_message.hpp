#ifndef BOOST_METAPARSE_V1_GET_MESSAGE_HPP
#define BOOST_METAPARSE_V1_GET_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_message.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_message_impl;

      template <class T>
      struct get_message : get_message_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_message.hpp
XZMh32Bcof28h/ujbjI9lXdx5YHrFmLnWlkgXBHVkYGW+5AovEesZNpClyqI1GLVu+7GBJkw8IKo4Mxk2p6xoOmxREA+rI51PmV3txEM3Q5fhcPmFKMP/4ly2Ky2ma7ke5+mD1+EkTEkm0Ue/ynfn34t2qfNj4nDfpI1d7YlhT7EdZXz0ePtan0fLpx+bCUdn/Nzhznk5KQk4Ed5/PRP/AVQSwMECgAAAAgALWdKUl1Zlg27AQAA6wIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjUyVVQFAAG2SCRgdZJPb6MwEMXvlvgOo65yqUodouyhyItUdaum2m6IElJ1TysXhoBKbGQ72fDtO+D8Oax6Acbz/ObHs4VD63JpMWGiVqWm1wd2/7QpbMJmWbYYHtAafejYPP27WKZvf5jSfkHwi1hwv599gxWaPZrQ1gUyYbBtOmoX0klvyaPbCCbjMaS/2E/pMIZshzcwvoO53lMjGkM0jad3MUmefmfM28XQo4Z2KHgpP5A9aOVQufAF1cZVMUzPK1nXYr/h4Hjltg1jpdZE6BkEPzIR6kNT93qPmg8FCfyQhFXOtSQ/lULJLQW1VgUayLUqaldrBTtbqw2E4ZDJDWjSGvKDU1zw3lFXDW2Q
*/