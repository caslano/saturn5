#ifndef BOOST_METAPARSE_V1_FOLDL_HPP
#define BOOST_METAPARSE_V1_FOLDL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl
      {
      private:
        template <class Res>
        struct apply_unchecked :
          // foldl never returns error
          // I need to use apply_wrap, and not apply, because apply would
          // build a metafunction class from foldl<P, State, ForwardOp>
          // when ForwardOp is a lambda expression.
          foldl<
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
        struct next_iteration : accept<typename State::type, S, Pos> {};
      public:
        typedef foldl type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            next_iteration<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl.hpp
4dH43BP4DONP4NHz9SQ+3XG7fmfub/r+zeM1reL7166/9BG+HW7v3x6l8n+Pf1Pm/m1TOlrL55PBP8vcv9HVnIjPEPdvOm/yt9rxIfwEx+39Ox0f4LodP8bV87ECV8/Helw9H+lXk8E/yny/u5X2cDj+t8Dm/4z7HzL4SuM5vG3U/sOfNh50jd8PJ+DLApH/87UoPx9eJn5lAv5k6WwiT+8Un/+5+C3GD5rqzC953RN/gMvvF769qh/idW79yrZf8RNF/et1fHeR3zP1hslPaean1uALRP7QnviNYv9F/Fei/2cDforrdv4DPknsv35VPD80LFN//B0+2nWbXwOvVu33N3X+mxSedvKL2PrXHvge+FaxU/+K57/U4v0dt/Wvgfjujtv613B8J8dt/Sv3FvFnKn8TPkj0fwRvJ4PfifwbVfhvxfyeFvhcMb+nJT5H5U/DXxH351L8JXF/3o+/IO6fpr+Tn0zsfwU+X+z/KfxydX/+g/5F8fzOxYc6bt+/f8Y7uW7zb+IDVPwR3k/l53qH+pWY/9EOf9ZxG9+3A94k5n90wR8V8cXhu7r87XBV/gwu5//ix7lurz9+rOt2/Aw/yHE7fnYVPsJxu/7q1fjwyMutv4rL9Vff0x7iMj7P47UeT3uOn8FlfJ5n+6zn+PUeb8D7qfVR8R1V/waeEfMjfsRHiPuv7n3ic8X9OxF/UNSvLsH/JNb3zeFTHLfjs5kPksHFzvW18afT8P78s5Pj689x/u1ClJ84dje/0w744iDKpxHND4z7D7rgtxs/58D4/d4Vv834O/XOr7U6Gh8tn5+qB34gvq3jS+bFpe2F7298LR5drV3wocaH/jY+/oF4V+ML8Oiv/Id830X+jlfx/UX+jtfwoa7b+tcaxj9U/xz+jfj+rsa/Et/fD/Gi+P6uwb8U39/Ux6Z+b9r/h+D8/kGT43+ZG5/t6fgc41/j0dGm47OMHzzPiT/4hPgxp/1p87vsh29y5t/Z/C5D8R8ct/ldhuHfOW7zuxyIr3fcti/qP/XU33GZn8XjTZ79FzzbFz0e/JP6qZjfVIX3F/Obtsb7qPnJ+Brxfjkaf0q8Xybgj4n3y/H4o+L9cjp+nfH95zrzIz7T34d6PFS/r8ebPPsv6O25GNpT+H2iflOD3yPXx/fULzyewmX9Aj9HlG8gPlOUL4+PV/GT6/T4QsbjdR7Perze4w0eb8QHCS/grcX4SxFX9d/UFzr/TNrjdbjMn+/xRo834er+LuAqP034pb4+KVxdnwyuzj/r8QZcnV/O43mPF3G5vux6fX3SuLo+GVy2n3CZP8njTbg6v4J2LoD2FK6uTxpX1yeLdxHXp9HjeY8HG+h/FsevxXuK7evwPcT4+0S8v4qPxXuo/Ez4SLV+BX6wir/4Su+/Dv+5Kj8+TOw/h3dU5fd4Ed9GePA132d1f+HD1PcBV+3PHP6GyI+zFH8tqDx/+n48b3w5HvWvPIQ/b7y3k7/+C/xK4xfjzfE/39D/oq7Pt/r6hfhpTv3cxn91wetwWz+P4r9S+HGO2/UBa/BjHbfrA/bEj3bdrg+4kfMX48Nr8QvF+PA6fJ4YH/4Crxfjw1/i54vx4cL3zC/GK41PrMXvxbd1/LiR8a+x2w9cf+M3nBSf7QD8ZOPBBfHRBuMTjU/Gm+OXNsX5R8Myv28P/Dsnf7S9fim86Li9fjX4l47b69cTX+e4vX51PzK+IOqXE/FTVH5tvKpKrD+C2/wtxP/H64/gm42v2zf+q9Vm4geM9zs/Ls1peL3xP+HN44P/pn4tyjccb4lXKt8BeBVeqXxH4V+I8q3AVfkafiK+Tqx/NR+/T6x/dQV+j8gvci1+h8gvch0=
*/