#ifndef BOOST_METAPARSE_V1_LETTER_HPP
#define BOOST_METAPARSE_V1_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/letter_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_letter<>, error::letter_expected>
        letter;
    }
  }
}

#endif


/* letter.hpp
Ki5XkUzF4+6rHguJuz9kCiq/0Ic6T3vg+8tvRownAItj0zzEzk0j6IsBswGhuNm20XkPBf9ScJfHyLHvjwJ5h8VT/nozIayzTeiYIu9kXZkM0eDZEAwrgnCzLBK77WYD4J5y7ywg9/OfRJj12bTpJnLjSyrXuJZxO894kXUG7x9PSPd4F+7zj9tkg7yTNodGB871EYQ5wK+RxI3vkxJ3Kt9wxnspry/VUAO7QSihgbrYeOqUhLxPBObYk+bmyZvE7t/G98hUDNsBSSLojOthQcOPl9/sze80AktT8c142qXuwMDS141VkEZpbqFLwdsvQ6wDJuj9mAFLID+/o+CTrpwG2iX0Sk7ol2+xJEVI4GPIugO+O43z23v48XY4aoN20K8BOxReE1lWsD2QJ0m7VDBKzPIN3NpviMTaEwSUbCGgypvMUdzjLSD9aUVSbeeYXBBqN8iEmWnKmJJIO6yHN21GbQqah6H5S79UOL6IqRbs1aLVUKS9zUv+0Sp3BXlAM1k7YodVcWb3lJD33BXp6hhzhCXUGl5LLrXbo6i+CdRInriWzCEtpoxLqE3sa8Gu7EEHIrhCqQJxV1FaORRPBQsSz/6XjRyhpBJu2ym3vunbaVI+2Il+UNOcjH/kf5+Ty27seE7Wzg+dk/FnNiflm6xzEoFN/txVcRX7bOOn4Mh1VQyBv9fD3z61GnUoZ/2QCKWxy1BArJC+bras
*/