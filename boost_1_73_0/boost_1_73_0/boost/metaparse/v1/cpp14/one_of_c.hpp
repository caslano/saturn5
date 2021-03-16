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
lwwDpXPhEzGeVpYVX60vdC1Z8v7i1FsWvXL8ppIlXqnVGjNbBukWxKwI+MdKjjjPPksOm8NH/Umm/e3F9z9/1Pqfo/YdmyTMksNmkfWMUtY6YYH7fv2h9cj6+iYJs+QB+Nf4eE1ntcM1m0Wqwbnle6w+Ozs+JuSNj7W642Mz9W5zMFPfkoyvUFVWEvSIua4dGbEZs3qaJp3ZdHws7Y2P9ZPhIBkfGySDQavXzUU0W1NTyLRY4HmeysMAmONj7aQ=
*/