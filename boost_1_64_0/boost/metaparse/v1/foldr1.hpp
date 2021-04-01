#ifndef BOOST_METAPARSE_V1_FOLDR1_HPP
#define BOOST_METAPARSE_V1_FOLDR1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr1
      {
        typedef foldr1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr1.hpp
AGlFPbYsMfFumJ5WkFMs76X+F57ZL6KeFn3jfOgDSJb7hT+uFOwtJvpM5KoouGg0FnfWa/IvWKJsHuHGe7K/drRPSzQF1eQLCyTjZ6hjdcZ6c1gK3rn7Ls61octdvmontUY+62UPeJZR0Be3Ghj35JwNwxNfxyaWFxaN7xNvc6hbiaUBjQ/nsOHNonV3RUXr2vG27nPqjl7Av+9A/9lz81tHRIkcBdY0fRnu3jOVVjdGsRrcC5hExccieRCOdqmFjP8ALVvN23lmkOM86R1EOO1g10ZcnSx7j8mgpLKWxAuxCfHocrLhnjhUfBZcSUAjQ6Bv2qM9uL2PQtOXxSu284AQgpoMpYJXuRTna5OipoSs8rkAPuFUMoFEa/Lv2khvJuQFx9bGioMCO1aYE0lORDTmRszNSby9+u8QKD2mMRa1xivS4PGPMYlkHMf8MMAEJqGpUROSKT6jeImpNVTcTq2HwoRvTheVSw5Zo+KYg2qc3LLIjcD9JeeGUbmUZr6oB9UvOXymxAv3ujTg7lHXScz5qJ38K3HY7UEHyC+ohCxsg5uTZ+WjOWzG5g==
*/