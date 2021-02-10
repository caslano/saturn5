#ifndef BOOST_METAPARSE_V1_CPP14_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/cpp14/impl/any_of_c.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_of_c :
        accept_when<
          one_char,
          impl::any_of_c<Cs...>,
          error::none_of_the_expected_cases_found
        >
      {};
    }
  }
}

#endif


/* one_of_c.hpp
AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMjRVVAUAAbZIJGB1U99vmzAQfreU/+GUqi/VXAPJssVCSFWXtd3aJkpYX6Y9uHAEVLARdtLy3++A/HjZJAT2+bvvvvvOhA6tS5TFiIWFzgx93rB9N01qI3Yfx6v+BXeLmHHeoDXlHlkozphQDGnsgl3ABps9NtwWKYEarMuWAKlyauAS/rUPgefB8if7phxKiHf4Cbw5PJs9Hfge+FM5nUuC3D3FbKCT0Gnktt+ITL0he1QUeDJpkRWYHlj8CfzY6Y6eWALpe0eWRay2EsaB7wWfeZp84ZP5dBZM51/H7CZJsHZ8rfQWrYTXliqxW6MdascfUW9dLmHWRTQmrjBaQlIaiydM3NbY6ftwIndVyb7vtG55jopUtWjpYYxnxnDyafAhFAdfesNuy6KjGQxL+g1BhlYjljtX86LezyjrGAu1qnCwE94Ll8NpLKB0Cr87uEpTitk/lDagw8RUFR1H5yECfqiqLvGajuRlRzdbLdcxLZebePawgq64FOLfMOFPginRn3hpeVDf9/WCTZG10LUMKnPYgMuxnyPkysIrooaxzY0bs3DfY4mibowziSkjRtcN+hJwvDYjdm+sk/9RPWK/yB9+syUFNKJdU4rL
*/