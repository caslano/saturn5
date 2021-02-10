#ifndef BOOST_METAPARSE_V1_KEYWORD_HPP
#define BOOST_METAPARSE_V1_KEYWORD_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/void_.hpp>
#include <boost/metaparse/v1/lit.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      // Does not consume/check anything after the keyword
      template <class Kw, class ResultType = impl::void_>
      struct keyword
      {
      private:
        struct nonempty
        {
        private:
          typedef lit<typename boost::mpl::front<Kw>::type> next_char_parser;

          typedef
            keyword<typename boost::mpl::pop_front<Kw>::type, ResultType>
            rest_parser;
          
          template <class S, class Pos>
          struct apply_unchecked :
            rest_parser::template apply<
              typename get_remaining<
                typename next_char_parser::template apply<S, Pos>
              >::type,
              typename get_position<
                typename next_char_parser::template apply<S, Pos>
              >::type
            >
          {};
        public:
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<
                typename next_char_parser::template apply<S, Pos>
              >::type,
              typename next_char_parser::template apply<S, Pos>,
              apply_unchecked<S, Pos>
            >
          {};
        };
      public:
        typedef keyword type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            boost::mpl::empty<Kw>,
            return_<ResultType>,
            nonempty
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* keyword.hpp
ZhaTzKLy673N2cbkuSlzo6TPjGZhWNrMY2j2ngl+QRC8AWXvYIX2BW3osgSZsLjLj3ScSC9BG5Wier5vHdG1Glbeve3C+6gLcZo5oEtCiZlNDHg8eCjQOblFcKVTuXEYsNlJSR8qSN6Nep+iKOrd+oP/rIzJHam7J/yAjYz2qH04Q731aR/uevU3TZ3V9SfAgNXUrlYNtd5Kx8ZYqCzL9JY0uazY5QgX8sYWOqTOKyGVA6deyYJRnlXMjQWqDiihoRiw1PsdpZ9DEFoWNJbOte8dKDOfQhienQepEwoLeQjrPCrjTR0IZYqCjhvkPuftyXwVTxf9duXwYr6MeYm8lNpzs7e827vrQlhCp/3rmvH3D9255rvigojkvpLQ66kj6vQJbbY51rMAufHkoE+xNg5S6eAnooaWS41vMfFS5xLAzhpvlMkHjNYN3oo7L0bAJsb5PrzpJ2CP5F443JIMGiSp5+2n8XI1nT8EbKgU7ujzDb+ppiv4hY4m87icjdfxfL7+Nnz4vl6Ov0yX41G8YgKtNVaZhBz98JGqrmLhfEIL//9s7D/N+e9s1QKeuhL8dTL88pf4A1BLAwQKAAAACAAtZ0pS8+GP5FUBAAAFAgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEv
*/