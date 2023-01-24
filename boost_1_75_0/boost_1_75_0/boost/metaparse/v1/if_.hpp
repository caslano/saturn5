#ifndef BOOST_METAPARSE_V1_IF__HPP
#define BOOST_METAPARSE_V1_IF__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class T, class F>
      struct if_
      {
        typedef if_ type;
        
        template <class S, class Pos>
        struct apply :
          accept<
            typename boost::mpl::if_<
              is_error<typename P::template apply<S, Pos> >,
              F,
              T
            >::type,
            S,
            Pos
          >
        {};
      };
    }
  }
}

#endif


/* if_.hpp
QxnsDHiTqb6kdvC6U3p6u6bIVTBEbNMHpaxSMZMh50tuzpfm5Bh8iW0nAiuBrfvYWY18h5xh5HHlhvKiFYrM0QQx7pkByHjR+N/JyMnaYRgfL40kNbWMq6vIzII8HUdwopR+jBNt7kOQ5fkXWNKsiiiMLOh8pj8FkZhDNgU/0h0l28wRmaqNLUwZHPF+hDRxUjFvGNsGrrvionMegYKfhU1QdJ791wX+Syw8bvM/xlo3vS8g/6+cjnn1KGXMgJpIg4ynK6dTlv7toOhuAE0ILQ9oxWB9hoXQNNi4fcl06qmjZBC7twKK4UwNiJa9iLfTWxxxdNZxCVMUfnfE0RL43dHdS6GvMokNgxpz4Y0H7TRBKfBh9CxXvMlZboq2qAuy3E2vEstNIpaLIo7guze4OVIrWCdqT8DVTnJHIHvUVzjB1RauS98irruOc91ErfdJxZTDZLVmCK5bxrmuJ4zrruZr1ZJbVN0B123PagrjTEx3k4n62s3+Q6a7EwWtpaQWE5Fp01YxEXpSiztlzRvsap5T6OmM+DrjR/Km4Uf0PK9Ux1f2O6HQUbERtQMv8albDXvykWlWPXnrh/Hi0t5p5kxDYrBV2XYllJWtPk2+mdmOo2bbkSISaU4v+10x2wFz8M3GOrgvJOvMIRav5JkyMtScGicYj4nrZnCRvqmB+GkWju6dqenqIx7BT0npRpb6eSOxyARkpTXagV8V
*/