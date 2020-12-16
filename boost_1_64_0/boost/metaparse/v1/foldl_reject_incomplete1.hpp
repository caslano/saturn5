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
3z4Uv8M4+WvZn+dofJ6Y/38OnhLz/2PTY8HNqv2Mzxft5854Xszf7Yb/TLWf8WtE+7mMy/gyXMVHVHV6Gpg6fQyX6yt60ic96VOe9GlP+ozHs57j5zzp8x4veI5f9HgJV/EvZU/6isernvwHM7THcBW/k/CkT+IqfylP+jS+lRq/xwc59QtbvpyLN4v4xiLeXb1feHsxfrQB/4EYP3oXby3a/6fN/P/5LVumOev/XUZ8e1Pj718zPsBxu/5Bf3xP4+vw8Pwn41sZXz88+usUvI3xQ0Y444uzdPx7FU+q+RP43qJ/Knk59Ttx/0fio8T6BWfjg4zn9nbG73A1vhhcEQu2U+Uf3lvtX433UvG7eF9VPuFbC8/jMr7E40VcxadXPOmr2vkB2mN4e+EJ/P4mEX+K39sk9g/Bb8Qbrd9/Aj7Zcbs/zon4+cb3HO7Ub+YQX8O/RzWI/y/hQ8X8lNV4SqwvuRY/UPT//wHf2XHbf5y4kudLrL/QG++j9ofEdxHjNyPxncX4zfF4QuQ/h/dQ4/u4ej/L+D7CYz+l/lon/zvWfHf8GP7t4nhxByf+GP+xiu/BD1Dzs/FlqvzD7xbrI/8bv0msj7zPVbQvHbf9X0l8nOO2/6uEy/UxPF7BewmPzdXpE3hceAqX+6vj6vnIetLncDU/qIhf6NQf7Pv7KH6u47b/7TF8guO2/+1TvJfjtv8tdTXxT02Nzz8E7+q4LT+OwNs7bt+/xbg7f8OWH4VrqH+o+Cpc1V+Daz3tC1y2Lzye9HgKV/XXtCd/GVyu/+BJn8Nl+8LjBY8XPV7y5K/s8Yrn+FXtVEa1x3C5/6HH07h6Pgser+JPqf5h/AkVH3+dp37k8eB67TFczv/3pE97POPxrMdzuFwfGu8kvISr+M2KdhZj057A91Lzl/A9VPwFfqSYnzEeP1zMz5iAHyrmZ5RwNb85uMHzfHg8gcv+GVzNP2/G1fzzoXg/Vb/Dd1HlF95FeNmT/4rHq7gsn26k/Sj6v5vwE8X+NEl8F7E/TRa/w3Xbf43f5rrtv8Zvct3GP+Vjcn+pZlztL7U/rvaXKuEd1PcD31Z4BZflI/64U/+w46+b8Ucdt+OvX+IPOm7H17/CH3Dcjq93mRdjbaDG49cVfIR4Pzbgw8T7kZpP/bRJ7G+H/9BxO//vWLyV43b/9+PwwHE7vjwFfyOI3I4vF26K6n/d6zyfS/CHHLfP51L8Qdft+38zz7c4/mz8FnH8Ofg8cfzULcQ/uG6vL36Y4/b9PRNPOG7f3wJeEO33Jfgi1+3+/fitjtv7twb/ifF7Do3u31p8ivG2hznjY7fq+lEeV/1v83DV/1bGVf0juC0WnCa8A36smN/aEVfzW+P4UWJ+a2f8MBF/msN7iPkjRfzuoHH8zAp8SdA4fuYxfIHjNn7ycfyOoHH8zBP4ba7b/N/uaT/gqn1TwOX4BC7bD3h34VWPJ+7g/RKexh8R79dIfKXrNr4SX67W17kzjB+qH78/HL+79t+hT90pio8YgS8xXt47+r4cgy82ntjH6X9bwPVR9XNczT/L4utdt/UH/HXXbf0B/6taH2gh49Nqfwo8oe4/3ku8X4m7iI8Qnse7qfohrvr3qvgeqn9gkc5fxuN5vI+6PnhvdX3wXsITi+k/Fucv4Or6lPC9RPqgoK9fClfXL4cfKN7P2fhA8X7OxfuL56+Mq/UJgyXakx7PeDzv8ZLHqx5PLNWextX9zXo8j8v8e7zq8cTd2tMez3m86PGKx2P36OuT9Hja41mP53F5/T1e9Rw/tkx70uNpj2c9nvd4Ee8qvOzxqsdj92pPejzt8azH8x4v4ur6lD1exfdT40P4ADE+tNV91G8=
*/