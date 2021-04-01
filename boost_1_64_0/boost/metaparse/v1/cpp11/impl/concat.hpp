#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class A, class B>
        struct concat;

        template <char... As, char... Bs>
        struct concat<string<As...>, string<Bs...>> : string<As..., Bs...> {};
      }
    }
  }
}

#endif


/* concat.hpp
qjZid5MulxmU+yz0oV+LUqhJDRcyZq3uSxPFXFnpA/cOZ5upifkkv3xesTmvN7vCOJwYLCrhvfRG3ExqGj1JTTBzlYxQ9qbYLjd72p6vv/6N3Sa9x10qtRxDKl3JEp8QgOIt70sAfz8ZE3rBKZsfUC7JS2iTNqXIETGkdYaGaA5CxKnjmi1CyMHIe1mFI1O1aWdM9upCrWrfXk1RTPyOYfRiVovpJpGZroU41k8RFqQ1Dmbv9+UEqi/rxBjbhv5eW5cRFYKtukMeDfnUWGXXwZ64AfkzFqMjkBl7WO954n51fBb5Y487AyXkwOUIS0cxlCjMR0p11Tyh2uCjBS5MdTpkAZbkrBXVeKIRV5CJShNunG2HoxZ8fVscyq+REYZ+n7ZWhmqE6FBzFLHvmZ2aoccltxEdrVk23N50JK9Cz5F2ZIehSOzbGbJZ5LJnBdD66TxcyQAuyXvkLKn/bPHyftiwT0qokAuJUHNI0MPDp1kDyZm6Rg3wrOj9ITSZtev+nYrejMBdXsPnHSQp55O1M0iZoAMJhwT6QSShhbhpYmNgObVNUqhhhrhrjA==
*/