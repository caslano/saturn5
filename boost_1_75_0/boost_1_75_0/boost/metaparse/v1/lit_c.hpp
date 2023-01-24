#ifndef BOOST_METAPARSE_V1_LIT_C_HPP
#define BOOST_METAPARSE_V1_LIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/literal_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>
#include <boost/metaparse/v1/impl/is_char_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C>
      struct lit_c :
        accept_when<
          change_error_message<one_char, error::literal_expected<C> >,
          impl::is_char_c<C>,
          error::literal_expected<C>
        >
      {};
    }
  }
}

#endif


/* lit_c.hpp
di6Jr/3iL/0OaEPdDXy5ARK0nZKjeICKs98VptWfPwRXNdJbdDucCzgDa57Cm5cBqdh3b26fz7GlHVdF80BYF3NnxoEaNek3IGlGdd/4zwFtjeRRoYRlsJZNignFuYXJ+3uOMXkc59Y0bb9cb8a5ZdO2l62BGO1m2mSuk9PxxfUCsDZ8/DfL8e+zwaaIXPNU3P/dW3lskcSrfYQLs5RKe3KGbJ3HK8TYvezOuvTg2Dr48g3Xh699tt79XSpQjgJH/Cfd2F8IagCrfT3wMe3ARxhCwCNyRsWxf4nsXzJbqansmMD+sVU/KqXk7tTA3RmewN3jA3dnsWHuNwGGeRQjzqj1syASZlQ2u8gW+t35nsByVFwCy4GwS5YTaP9yitBbTpa/5RQlvXwLcpOofQftFHkQdeIAvheY8Cv45wJiwlGjNkai/SapKW7wXhWRGUAkx6DRYj0vkyckjE7QnfkjEBlmoO58lP3lKG+Zx+Sn6LmMn9zcUnxk5tmMZX1oEzpeYnrggqb4raNSbeof6YHrJH+JcNFM5tFMCk7SHZGXie+wmcz8EOS6CQALEiLUmWvsAX0Nu9/YO/leBgmEQGrB2Ls+YTtM1O8KxdDfI/ZItry+1J0zU8XyEvI6X15so4m6HCxwzgeYjMrUVXw6lhYYW2iBaIA2aF9IaG8TJgrFTbVgvYVCWV/mNcJENNa1QtJ8Y0xjTSvWF6Y4BJLw
*/