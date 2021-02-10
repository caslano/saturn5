#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_SKIP_REMANING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_SKIP_REMANING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/return_.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class FinalResult, class S, class Pos, class... Ps>
        struct nth_of_c_skip_remaining;

        template <class FinalResult, class S, class Pos>
        struct nth_of_c_skip_remaining<FinalResult, S, Pos> :
          return_<FinalResult>::template apply<S, Pos>
        {};

        template <class FinalResult, class S, class Pos, class P, class... Ps>
        struct nth_of_c_skip_remaining<FinalResult, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_skip_remaining<
              FinalResult,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};
        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };
      }
    }
  }
}

#endif


/* nth_of_c_skip_remaining.hpp
hEqU4PMMSBakaDCDmJpMxHUfYQaBiLMlaMGfYY2wRAUqQggw5GWiIIkLBaJUeakg4jIwfRFgQHR1lN4MSqQJilo4cwKuuB+h/wwpRX5pKdyo1oeFfxCuhOIJYVkg1xtp6gcAzmFwDtvWdHTr212Y+gq6XbB7w84ptP8X9wew+wZwzCsdAPZgQMAJPnjMlObuoRgbOvtwG162Xh++lwnYpzvsfHRxNR6xRBPXz1tgOIMr9ElODR7AEx2s6UJZSIu6pN58qf71JPtl61FKckZ3Z7Vd957+X+vuDkj+sHNCl3GdJYIH7UilyfvZJ2IFvU7N3gdU/l/ZX9VNSPtk2OtBXj79ztl/74ppv6i2mquvS3pfu7qoL5MYM7Urar/+qAswT5CchEonC+pykki3dGcWsKtUEGEIStTzhzr7VEAupGqcQX+47JgCZtO5d6jz7bizBbksVDmLlMrNvQntJ5wQuaLaITfS8zRzGAAn4ynW7lb7BKiScieoNUtRLiN44WvgWNtoIGlpyrOgZh1aFr3bdo/Oea/SAjMH2ufj6+nCu5kNj2fz6cNjo38Hpm6zYbRldyjjsAK91cBDhbLxIbKnAp6QLK1VREK1mLOqYykFSVPCF4nLbhejOfBMZFUqysLQbr0AUvYVNzyl42gT
*/