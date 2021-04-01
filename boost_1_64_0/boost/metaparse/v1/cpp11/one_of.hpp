#ifndef BOOST_METAPARSE_V1_CPP11_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/cpp11/impl/eval_later_result.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct one_of;

      template <class P, class... Ps>
      struct one_of<P, Ps...>
      {
        typedef one_of type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos>>::type,
            boost::mpl::eval_if<
              typename is_error<
                typename one_of<Ps...>::template apply<S, Pos>
              >::type,
              impl::eval_later_result<
                typename P::template apply<S, Pos>,
                typename one_of<Ps...>::template apply<S, Pos>
              >,
              typename one_of<Ps...>::template apply<S, Pos>
            >,
            typename P::template apply<S, Pos>
          >
        {};
      };

      template <>
      struct one_of<> : fail<error::none_of_the_expected_cases_found> {};
    }
  }
}

#endif


/* one_of.hpp
wfuTPOWEJmY5dAA0GIwF81zP/3QzVjpp/UdkEm1r/XeZgtmb1FIJHk+pchkS97CmZnjqwnXY+6vh2KPSfjaT1hsPFN9ZnvhbgAxDCOog04mzcLLRhZsxL/gtsuyw6NiqQUkrMwPquqdQ1fT558i1J6S+nT7JzxIqnNGyDYL2I7Pv1s/9PB+CXQB3gc6/uzKh04UdFDBkTqBJ4TrwV0JOvZLk7k4VABiSpsLn9/9xgbyqfSR2Qt3k1LaQAIvYELsXD9ksWX/v0MqMwEnQoiAOkHpTfdCdRwUrZq22NNrGO+pN1yafz6xksEtTOj7+vQyuJjl0oD52NJzcsdWJTdWsC54m6uxpwqJJw9U+M75MsQOAMKqtsbu9gKjTZ+Fs3B/pccOLDqJufr5r055HSDY6OI53ZXc9Fsp5JlEc3jj3a1/1qP6Ns7WBaZaywFMSUdyuaTCnKf3VkB0yNe/C9tK44jFYbTvopNaqUYn51mKLstZU2DInvxjFtHZ4ZdjUdZcw71tU3ZpjzOWaIEP8TkH97ia9dEv8FZV/eCd+H07xMVuc23iJUIepaDnDjg==
*/