#ifndef BOOST_METAPARSE_V1_TRANSFORM_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/unless_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class T>
      struct transform
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename T::template apply<
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type,
            get_remaining<typename P::template apply<S, Pos> >,
            get_position<typename P::template apply<S, Pos> >
          >
        {};
      public:
        typedef transform type;
        
        template <class S, class Pos>
        struct apply :
          unless_error<typename P::template apply<S, Pos>, no_error<S, Pos> >
        {};
      };
    }
  }
}

#endif


/* transform.hpp
my4VclxWpGC4bsmLmrk0E9Z/Hoo7Y2OFUR7vGnFgPniqcWBGT+X9+8ooOtZe4I/mHPp4YlSCPUrI+h5Ypms3m8uEBUODHIch9DVC3F3xVGJCozxKaIQLRNWvuWDiRyx/L7SQ8+N0mQRvSjX/kWb3dKGX1jWm+Fz6VE9XJ5p/Vo8ygc3x+teZcU8dT4Kg/OApeNjvvJfdlVgXb5SLXLTJnFxOt1qRn/1FJDIGprl7rcgKNaFWZNVYclQmfOtZJNKsBZmaadSCpDKQZp3LpKdh3w86Veg/iV7VzHditqTt0xGlAet2h4caPIfTdEMvzkpgPMw8Vbh4T7XEF0/k2EpYtrYnrd2KlsMecGjIq8O0LjSXY+eT1v+h/vioITzBErMsa+AUwTclzeXoNHMubmMu56GOf3oi/Xozh7ak/fNpJh0eMQwoVsaQZDZra9J8X27+rfl2PnHc+b5h6TbfL5/4X+abP7j7fK/KStCXIe+Hs/bWVA0FZGmVlX1A3MIT+ID7EE+uDynh61E64GYYB9wvT+AEbzIPuO3aqcPjBxx3l4XHs+l35gxE52Uafmf/bEr0OzuE1DKPPM80o1T94T+LvGhxzzMPunL3WU3qjruh13f6wTfypkMKugaXQnvCZUUFjNTfAyJHxj0BXBY4VTIm0DcZFshePZTLZOfEnPmf8m6lFHOYFROgPhCmmkDr7vqz4ReWlUjVSAMW9wt7
*/