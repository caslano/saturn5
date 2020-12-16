#ifndef BOOST_METAPARSE_V1_FOLDR_HPP
#define BOOST_METAPARSE_V1_FOLDR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr : foldr_start_with_parser<P, return_<State>, BackwardOp> {};
    }
  }
}

#endif


/* foldr.hpp
gB8j2r9L8OGi/fsrfKDrdvy0Szz4BRC6/T50xa/hP050/LNTnf0j8YnG+4+Ojj8H39H4lXj4NF2Jb2/8Xbyl/rFDPPhYrC+1Ad/kuO1/fxN/x3Hb/95nx3hwm/HTxkT52xW/xfjTeEv9Y6d4sJ1q/+MjxPvVjA8T79ch+I/V/ub4D+u0D3rWjvArfBMnG+F435Oj4/8Nv8f42Xh4/L/jS40/jrfs/4gXjO94ilP+9oy3zH+K1dsfBJ8u1ifvj18UNF5f8nB8rOP2+1bGH+ZQ4f9i69f/wJtbR+1DW79+Hd/HcVu/fgvv67jdf/ltvI/jtn5d3CUux5/LHq96PNZHexK/Qawf34xf77pdnxX/qYg/PwafKNZvr+Jyfu6u2pMeT3s8i/9LxC9Owb923I6vT8U/d9yOr1+KbxLtmxn4h6J9U+z7v/fT5m+nWv7W4lfiXRz/8KDo/ryEzzJ+64nR1fgIH238PTy8Px/jpxgfdpLTv9MvHvRQ8Sn45XXqhzvU/Ct8Wp34hc61o23BpxhfhXes5b/d7vHgDMft9f0BPt5xe33Le8SDx8X+lK/ijzpu699/wB8W8dd/xH8p4q9LbHbxhzr3Nxb2j+Fr8DaRsz9kdH/L+LPGX8bD+/sNfovxHqdG599vL+6v8Svw8K/YPrzfYv2DOD5HjH93xi8X498j8JQa/8Y/aWpcfq/Bj8Tt+TvVzv87fLCIf3kV37/O89O69tef8P7i+Un2j+vxX1yOv3jSZzzps570OY/nPV7wnL/o8VLojb5vnvQVT/6qnvTBAO0xXI1fJHA5vuM5fgqX+3t40mc858960udwef896Qu4XN/T4xV8vig/NuB5sX7Km/gNov5b2DcejGnduHx4AB+B2/7x8Pu9HB9mfDkelg8P40ONf4eH35dH8JTxTDen/TLQ8/zi8vn9sU4fw+Xzi8v4CVz2j+Cy/xLvKDyHq/pnAZfrS+Bjmhq3n1bjpzpu27+b8D3wRvEDH+H9HLf7U32M93Xc7k+VGxQPtoj23Wz8G7G++HL8JbG++Ap8jVhffCX+nIjvKA2OB3+q0z7cpZaDv+Fz8e2bIv/p8VH/1d/xnxr/LR72X72NX2q82wnR2doeFA/2Mj4Lb+kfT9E/KOb/j8RXiv3zxuMLxf55lw4J29/1988rDKV+39R4/uYS/FXH7flfwO913D5fr+AFx218wZ/x243Hj3f69w6PBz/CG8UP9cF7OG7HJ3fFd8IbxQ/1xXcQ9efd8G6i/pM/Ih5sFv3X8/BPHLfzF+fjG+v0X4f7m9+GvyP6r0tHxoMlov6+Gl8s6u+/we8S9ffn8AWi/p4/iv5B8X2bhy8U37f5uFofbDl+mVgfLHM072ed97tv7fxX4/3wWFPki9PR87tmWJz5Pd/3f+Lh+dfiVxnvPzI62/P4lcZvx1uejxH6+1TA5foIuKxfetKXPeeveNJX9fnp4NAe83gC30HNr8Xz4vsyBL9BxM+di58l4ucuwMcFjb9/F+Jjg8bfv+DYeNCrqXH/fVt8B8ft878V3s1x+/xnj6N/pnXj+JGZeKkVuXG89XHO+jD4TOND8Zb1YfBLjd+Eh3+twacY/xIPf3/2RF0/ynk8jx8p4lfn4Yc7bu9vVR+fAFXtMXyLWD//h/gXYv+GrvhnYv5UepSuX2bxjur64KNaN57fsQA/Eu/u+Bk9ov6RAj7Y+FI8zN8b+M2tvu97HBvd//X4fOM34C31q9H691Vw+ucb7u+xEd8K3z50E7+zCf9Pk+Mmfucj/DvHbfzObmP4fcYfw1vqr2P19S/gcn1hT/qKJ31wuk6fwONif6reeCexPu6d+C2if3oFPkv0T+fGMf4g4v8=
*/