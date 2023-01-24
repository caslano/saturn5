#ifndef BOOST_METAPARSE_V1_IMPL_ONE_OF_HPP
#define BOOST_METAPARSE_V1_IMPL_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/fail.hpp>

#include <boost/metaparse/v1/cpp98/impl/one_of_fwd_op.hpp>

#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Parsers>
        struct one_of
        {
          typedef one_of type;

          template <class S, class Pos>
          struct apply :
            boost::mpl::fold<
              Parsers,
              fail<error::none_of_the_expected_cases_found>::apply<S, Pos>,
              one_of_fwd_op<S, Pos>
            >::type
          {};
        };
      }
    }
  }
}

#endif


/* one_of.hpp
XTeAuJCtbWlFLiyJuI274HM1WP6BZhS0js8UKptEAwZx+lDGghjpwcQInNnKL2dbmdC9JU9R+ekBdHAoNQi70R/dI3CrFLtDzm2YF7v2EE7EhyNbpg7pvnkkWCY9TxFtUp18p/oVE+6wNlT7YkHa19zHot8sSCGLPOcgDUrqe9864ozbD/JBqePBn+0jiHeRKSMC6jUdjLNvEbO8+ADd9pPKvqh64iLQMRqN6sDECOslB9DUA4N3KMJlqKatE7QwnLWXsrxhLI4/GSva6qADi6gDi9i741Gg0FIHxhOVNXr+SluzpF2KefIa7jy8ni7hZCY6chvdA7P7uU2iUgPHnhNEWDgSMWsF9GshqacuqY6l6s6UB/0UFIdrcIyfxjq8NMoBSvmaA5xQK/kUuDWLTYEt+rDBzjaedxnr77II10IW4fr6jyqxLAYU7m20eNcJQzc9KkTyY9Mw7uXx+3H4XvHbPdibNDk4fR+0BGcHech+7FiaEz4IzgnCfpR/P9KgqsLS0DkgzuYiTfPZA8d/0mgKuhama28kDXOzgqMZxMAGnEBqebLLPFUKMFt7t7xwP8vFzhZO2/GF7wJxolKLT9+GT9dyAHH6cNHTnllM10CLn6YPznqKeRUfZe4b+MZWdFLkbnJfZMseRN0IJ57fmHshd5PajSKuVbOeZHnU5b8epH6Mx3489gVFa/J5CVPhPdgSMi8RreRb2aUW
*/