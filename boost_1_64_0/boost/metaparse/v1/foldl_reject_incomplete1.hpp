#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl_reject_incomplete1
      {
        typedef foldl_reject_incomplete1 type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldl_reject_incomplete<P, State, ForwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldl_reject_incomplete1.hpp
EfmRRhAI37IbYA488X/1vW8NzXyxMxkic1Ta9D78KRVSO04oRNCL+tIPEfEYYy2X128UxU/4VtkB0tEryPKNuylzzTgVMZj2dn2j2/OB91Zg2/29qLsTQbqlid9ueycDH6Lcdru/KpXYmxgyWjqHpxO333pt0qhDvNNovkobyYhtawvf012Yrln1739JMvnWWNlkq8yBivGgQeRnX0W3eOKZfEpfralHfC/7tq8DE1862r1wUKkEza6SqiYhGzuma9tgK3aHbCE3G5yE1QPblwF6Jw5D9Pyi+kr1CbAHA9SjBiFBlFPPBsegoE22nNgHK5UdV7RbHZRE3R79ufOoM5yPVvRS0Rxud3EOk0XvgwCc7mOojxaZTPVYhU6FHkjum/D7Lk7v3lN+rZToDEu9LGVrPKVoSdw48CGPnrOz6otCW0fbwT5MSl9f+5KE7nZFxD59+Hp1/L/c0tPrrHn//yJn7zs3Oyms6aMO57NRNIxfVhD27OkENc+7sDRAXtvzb9+YgMYYWPGSIUjHjwQMOPeAquhiSvT0w4ZJjq6fIr6rEqHYPdigVoGSEg==
*/