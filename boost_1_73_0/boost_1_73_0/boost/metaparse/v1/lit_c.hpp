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
pkrKZs6FRqfE3h1OLcMoTK7sBACef4nftfs0ft7uLLgeyfqpuluuvliqab6qMF5xMGvJnKLi0mq9oij8sSjMH9EMHab33cjhQzCUhg4iyL9TGaelvILADZXYZjAXWkGvE3FTLXTb+mnLgI9ifQL6keoY1zDn5qa6C2AcZux8ig/ywgB0fcLk9QFVz1yYt0AYq78+vJTe9WFGU9i+1DZmucHxF2V6VdTN0vDBu+6E7RWET19aEAq6kYY7sRvWV30=
*/