#ifndef BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP
#define BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of.hpp>
#include <boost/metaparse/v1/transform_error_message.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>

#include <boost/metaparse/v1/error/unpaired.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P1, class P2, class P3>
      struct middle_of
      {
        typedef middle_of type;

        template <class S, class Pos>
        struct apply :
          nth_of_c<
            1,
            P1,
            P2,
            transform_error_message<
              P3,
              error::unpaired<
                get_line<Pos>::type::value,
                get_col<Pos>::type::value
              >
            >
          >::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* middle_of.hpp
y6iCJH1/sqsqsp9NPiIk5QyTtQZtODfozjdZ55qG/Yf7OunO+X8FQePRBJe+NQ2ifxqH67perFNWtQeGqXqoCKFBSTTDcP6YJdEsmDPne7R/5rL9Mzk8pBtn7+hHxEn7fozS93X/EjY/IXvDBH43yQjDFrI3Rx9KllJcn6EkIyUbMlJyynKawkXkp3AUBcEVdMHQ5VQxJ8C1pSzBVWjUs7g5zW8zwd6g3RUTkFJ0Z1OKwC6kznJLGwYhyKJq9YpEveEwHlse5qg37BVrU+wKnwXDkJfBt8EItOLvxvnS7v0UZzsL5Bc+f2cxudz6PGFnThC2N/W4XF/xKRyWhn10WArXq7IkFWQJvWqY+e2Ph77dUdQDwCCMLzTa2e/8KU3PqdzemGwWoqpk8Hncu2QFRu5WuCXXpJGcXC80sj/gLzzXuJ7ooTunC9hT4Nj/NHvLx/eclgd3uqYDHuwofl7hdLGU/aEu4Muw6BkFC9f4L/YER7WJ+IkaT4AAp2Pk0G64GlhX/8I2u7/Jo47OFpjb6m69FARwFNnGNtWE8jYcIoO3HVzTEW/bWyFGaGeFGKGqClwpLeuFfjTOrEu8m2WG5WkxmxKMpfLnVWZWl8xY3V2ao5jp+8pU4FkUepYudNXduUi1T2WBeRfoyKduBU1+KOtVXrR2dicoTq3FoH/00RbXJwBWgIEhN+fqzh+usVP1Jtdkee65FCrW0s0K
*/