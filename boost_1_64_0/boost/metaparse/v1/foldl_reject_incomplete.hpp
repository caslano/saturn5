#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_at_first_char_expected.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl_reject_incomplete
      {
      private:
        template <class Res>
        struct apply_unchecked :
          // I need to use apply_wrap, and not apply, because apply would
          // build a metafunction class from foldl<P, State, ForwardOp>
          // when ForwardOp is a lambda expression.
          foldl_reject_incomplete<
            P,
            typename ForwardOp::template apply<
              typename State::type,
              typename get_result<Res>::type
            >,
            ForwardOp
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};

      template <class S, class Pos>
      struct accept_state : accept<typename State::type, S, Pos> {};

      template <class S, class Pos>
      struct end_of_folding :
        boost::mpl::eval_if<
          typename boost::mpl::equal_to<
            typename Pos::type,
            typename get_position<typename P::template apply<S, Pos> >::type
          >::type,
          accept_state<S, Pos>,
          typename P::template apply<S, Pos>
        >
      {};
      public:
        typedef foldl_reject_incomplete type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            end_of_folding<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl_reject_incomplete.hpp
rpv8rt/hlxi/LevE/+1D/32ARW76Txr2DWV8ag6/0omPs9tn9wuDGrG++Ay8h+P2/TUT7+y6zX83lPfnNrHb+MC1eF+8n+s7xvFf6/CdjXfsFPfPfYHXGN95Zrw+11d4F+MX4c39cweFwRz3+tn8A/gs123+ATzruu1fPjgMuqn8aHgXUb9swttVifz0eNJxu/3H+D+D2O346Sf4J8ZvwKOz+RT/yPgmvLl+PjIMxor1/XfHDxDr+/fD08bH4NHz3R/f3/jNeFS+6fgmsT5X/lD6H1pUvv/ewaP19yOf0Du+/97Fa4z/cu/4/nsP72H8UTy6/z7EO7tu1vdvHMPzgVeK/16I7+24rd/citc6bus3d+B9Hbf1mzsPC4NdxfpZ2cPDYF/xfMzAf+a6fT/gg8Tz0fQfwu483KnijOP4uSxKRSBBCi4swYqIay64UEENuANqcEEFkYALLqCBKiKIBqyo1WrAXRACitqKNeAuVUMtiFpt7GI3pcFdQQ3uFm37fZ7m3DO+TX7zF95+OudMzjJnlndm8AdF/+xL+IKAMt/x0y6J7mbHNP1zxhfi4V8F/DUxPrAE/60YH7gXf1KMD9yHP16nfyG8/8vxFaJ/oTgyxvo9jeN3V+BjxPjMSvxEMT6TPN68v+b5H4T/ObDvZ/T8p/AXxf55Q/B1Yv+8ofha8X6mT4gFN6j6KX696j/DZ6jxqRMpv0X8cRy/VMQfd8UvcNz2H3bDJ4n44+3x80T8cRFvcstPO/8D/0/guJ3/gX/tuH3/H8c/dd3urzqK91v1z+IDVf8s/pIoH0biL4jyYRReEuXDdPwu4/9y5q9cii8wfueuzvN1sh5fHYmr8dUifqqan4OfrObn4Ce5bu8PfpyaX38K5af4fu2B/0h8v/bEe4nv1154D/H96o93E9+vymji30T9ZAN+taif7D+G/m1RfyyfFgsWOfFTdv/eV/GFddYH71I72j/w642vwrcJ66f4XMdt+f0OnnPcvr+FsbHgUSf/9vv1AH4vHnN8n85O/yF+gfF/XRT9/o34BOPDL46ej014xviv8Jb6zzjq/2L9kn/gc836BX16RN+X1/HZxl/bxanfZmLB9KbG60/Mw6fhjdafmI9faHwVHtb/bsInO2777/+B79Ik5ndMiAVH1DxWp/yfgh/muC3/p+JDHbff/0vwwY7b8n86fqDjNn+xM/l+qvFHfK1Y3683XnTcjs8cjl/nuB2fOQK/1nE7PhM7KxY87JSvtvyL4ysct+VfZ/xBx2351w2/z3Fb/p2Oj3Pc1k+reM51Oz8Lvzyw+XPmZ+GXOG73/9zhbMpn48nTnP0N8Nud+Evbvk5PjAVv1lm/8+iaT8NX4NMd7zqFNmwtf5fgDxkfhe9cy9+1+ELjv8DDXps78OuMd5rqXL/zYnJ/2c34nmp+7/mmfWrer2a8k+P2/eqPd3Dcvl8D8PaO2/J5IN7Wcft+5SeZ58uWT/gy4/TvROUTvsT4OrylfMIXO273d3oQt8/f1c76e5nJxJ+L/uPz8TdrFnO+H+HzOwlfb/wCvKV8voD739T4+7kAvxy343vbhOPL+HTjL+Ph+7sMn+q4XX/wGfwUx+36g7ks47/O/n52/4nr8OPxhON7bxetv5rHjzY+GQ/3x1iM/9j4M3j7Wv5+ifdx3K4fm5oaCz4R6/MNwT9y3PYPno0/77jtHzwfX+247R+chD/rut3/6SfEX4jybwrex3HbfpyK/0jUvwt4Uq3PgA9oahxfuAFvNs71aan/v4vvKuaf/gdvY3zQICc3F8WCVsYX4i3v18X074nyaTw+U5RPE/CLRPl0Bj5VlE/n4JNE+ZS6hPaNiM8fgi9w3O4=
*/