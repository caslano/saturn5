#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/cpp98/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>
#include <boost/metaparse/v1/cpp98/impl/update_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_back;

        template <class S>
        struct pop_back :
          update_c<
            typename S::type,
            size<typename S::type>::type::value - 1,
            BOOST_NO_CHAR
          >
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
JX4GDVIycko/0cbppP/ThMhHYBLjzmipIfACjkKroT5M703bGzEM1w7rovbeosaxU1Z7RrK3vg+uY5AqvyNopjKSyQXfkvDzj9bdxc1VdThpamnIeHKSNSsf/pbgTUTm6AAhBxyGrESLh+kfaQOEmpNnfqsq7SVq/2ew4fAum88RWFofw6UcgProd9qSmOiUnk2jMewfl43hIfArw2+zVRqXSVqkbzLA8P6H2CBuiIbWX8sg11JhF90AxhblCX4/jU2UxjL6ECY8x7QDNp8r0+azj6B0dVgTUipbTcmR7dDZn+MuSJXLVplo0PkxY4ucvIc0hpo70e75gJLd+KaJ8NC7JK9cRfLxZlT77y8iBWFGoQMkl1D1S9xcO9UmpKnfwSQXTObjGKWxvixrv2RPkNYrAM/WgyYEnmQowAYybwjtqrWPcsc5/Z5C9GIHsqUyjJvKpaEyL0VqymClZxCcmd+HqyJgaKveRrvFKv1h881gm/X/9S90d1Wj68B/h6mseskIq9RY7B01cYjnEmBtoSJ5IqYVv8g/dnuxNXfD/ET/2KbcDmFSvdSBVQCQ+RsWbfcqemHFXkxtrr9UlGKckqUDYyTKarBXtYTqDgmXDgCvGq8SJaz4V5fnS9Npxqln0irB4mmHCXXZKVZmOgFp8YKWFdwvCmJuw3wD2hXe/TDN1MhVs+B6xn6RR8PThjPcMmMrj/dH98blwGz8
*/