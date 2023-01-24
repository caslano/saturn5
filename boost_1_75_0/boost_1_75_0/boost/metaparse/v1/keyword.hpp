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
0onCkz3re7ZGK9pbO4GzoS+aScnJU9MCuZEQn412I3aM4cc2NOStQfXoWbyqVR6BU+/yU3Cj9jaeWstPwTPaC0fIyoY+PXUz078G553jKD9rauHR2f5I9r1kiB9zlMdMhRpVPAoyAwUndy50iUw/GyhcQuTHsxaBua+KnDELj0dgI6u5/RItlrehsbWO7gLTOlslc+GuFsUwibEVePkUWCb/Yhrp2V9FKtrzB2icrowiG1yLYaiDlhGsm1s9VVzpcvytSt5BJqh14nZhgmozLGjFmUjFTBKdlWkR9GfAT8A7L4LQGQiKBz4tYzaeG8djNtbBH9x/B8FDWQNOcemsiIlcsN7W9UvgR8R+C0Y1zqJHUHtkPSAtcofmX2zDY98dNsW1tXiuDYAbZIKzxcu4IxOEnGA7Jv910G4zjSgouZhxFeAKZ8q/RpjoIOhcPILy2j3azP3gb1HPAtsqhUrHIa8ak6K2UOgzd9Ww5eq61a5AhMdKhJA7BXSMOdsKeZDJr100ViAwFEcYxMutt2006QmpVgQGMU/9jdsFAsMG+s3kyWxxkRAYBrC3s0dhyNlyy8Ionwn9xoPMN2yTo/BuUFKrPSpNDgqmV7AnhnkSHu460JMgZOFmvBKPo5Oa6FWHV4MsnYsBYdvRzgug/hCfDme+sFOPkIYN9cdVcYKvOSLqWE8tI+XBR/gWK8hyNxWCxwRQNFrzop5HfsEp
*/