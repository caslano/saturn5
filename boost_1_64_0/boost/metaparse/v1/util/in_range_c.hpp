#ifndef BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class T, T LowerBound, T UpperBound>
        struct in_range_c
        {
          typedef in_range_c type;
        
          template <class Item>
          struct apply :
            boost::mpl::bool_<(
              LowerBound <= Item::type::value
              && Item::type::value <= UpperBound
            )>
          {};
        };
      }
    }
  }
}

#endif


/* in_range_c.hpp
qFV4OwxW6OjYpHD/gor63l5OwHDZ3lXVnfV+QrxU6k89pvfohfQ9Z7i77gs6P6zJlo00Y/4FKV7WB5Lt8chybhc13LvTeOt1ZH/Em7B+t1BjZ12997YGfFW4cHCA1m97J+QLQ+kT2jyy1J0ldpmi7wDEiIjV/WO8s/xXgPEjdT+S43KK2gjKItVfe/uIVL1nnYn6ZcpTrWkhUkP0+OaoboZnZXv3ztL7uumKh/YEce221push9HG9MH1MdC9X6z3xSPRY0NNyh7q/V+3/lofotttT6qVfu3opj1NXpVtkSM/iHP9XOC3R/GyHiD8HADrtc3VU0MX+gI8Ne8nhuq+INfuH87Q+JBxpMbqe5wuFrpPb7Fk/n2Ey4vFYGMi9PtrUvVQdzP0ba3ft3BR/Fyep2L1KSsov/Ld4xCfSaVsTW9Ydd8Jl8Tu0FXeBkiupt+/0p3TXC6LYzq28/rr+8Yiui/o1YadpkAnnc7Bssjs9WHmNGUrJer92p1f79up9imWrhtXWPNFfpoi4lxAesQGKJ5iq/Ooqt57e+n7jwmyN8IBZXbKP2T76/tfnR9vtN4U0flUiux2f8A5necxyhYoCXi5BGAxQP7YyZ5/Pi83yDB0aQNYpn2tusBuf4CD3pYl9gOkfneh/yLk72xOd1apzbxK19ljq41iXy9IKiSQKq3Tvprcn8GyMb1zo2rTSMVD9VNfWZb6/i1U8ekcpLbr+jWjFcQLjikeVdFO7zf0/vmC7FMH+q9FFcVXtQLqKyT+epneO+rt/u5aNOnrQdn3drKfVde/jfaDJfo9Ba3VlWIaq9HKbqLvt3793tJy+V/EZXCE4nl9EMNKz3k/frBkfI10HvnLH7ucuveGkRr1Sf6wFbKvlgJ+KLWvFYj3zrT7MxzsU5nsBTfre2KFhELb0E2T9G1u2e1km+mX9j6pi8tp25xxgexJrfOVJbTfr9D7P0n1wA9ZXuVWvKe45ssnZG75SP7EEShzog3yjS2g802ns5tm3Qqt802htNZnvNbHPMUrNOGqaittk4YKgenM8ZCu1EhR8O9IR53n+gx5dy/dVxWvraGzItVP/iZj3Vd9FV8Qq/Qz8t/rvU/HHbInoxUv+41sZke6qaI+wBmje0/TBfreb6Du5xuo0eyj3mOedqH/rst/GkvW/AzZSHlOlhyG+Is2rUFXdZ8eQbWvclZP7KTv86T5yFf6fakneu89SfZaSb2XPwo2eSmpGSN0f/Mju/Kt7jMxes9QTPZkmL7vGSX7T8Qu1QFxDVE1SbttoS1IsE1H0cYTem8h90Ryb8pq+pJaqxtL+ZXa/0yQxaOQ7Ht9mfNKG61lZ0DGDwTy1mdzxZeTrdSXuvn26f3kKfh9qkTZJe0lJR/l5D6oFxrxukLdVvaUDqV6nSjzMpf/pQwCzdUHkkdkI3Vere/z9HTyjXyCzSYDzPqSzX9Bv/egAEqjq+hR14Y2XuoMHV5Evx8RIX4i2aATcfB5wNY4vS85BuJEtN5Tv9Pv03zW9zONAbNvQLJYvsNhZorX6mP68z3kL5a9m9yDPtiSBD/PUoo3qouPWGt/6aj4ZU/Fk/Po/EiTf9xD/vFaZPPohL3Wwxz5JEF4A72X6guren763k+/p2BZBPBwJX11cTzYkRWc6T9d3bJ0EbOeTCo1SO9jGyParQi9p7bS+2ctYluZfvsaKl7RVPE8T603a4iDf+r3aSZAnEsGqWkqNd7oUljDyQj5frjBT+xttEF91tp/l6X1a6Bux3qKV6RQw64oIKEevbZLZ8WAZYBvzfRe4CJTtFURvZ+UP2eontX2kCvnRZrOj2tgx5vofpQIU4uHRvrexVT+ITh3ugmi/h/Zuxo=
*/