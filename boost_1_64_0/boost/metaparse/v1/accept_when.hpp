#ifndef BOOST_METAPARSE_V1_ACCEPT_WHEN_HPP
#define BOOST_METAPARSE_V1_ACCEPT_WHEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Pred, class Msg>
      struct accept_when
      {
      private:
        struct unchecked
        {
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename Pred::template apply<
                typename get_result<typename P::template apply<S, Pos> >::type
              >::type,
              typename P::template apply<S, Pos>,
              reject<Msg, Pos>
            >
          {};
        };
      public:
        typedef accept_when type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            unchecked
          >::type::template apply<
            S,
            Pos
          >
        {};
      };
    }
  }
}

#endif


/* accept_when.hpp
Zvx6PLxbLfCWxr/Aw9LaEt/E+IG9ovTl32d8vcr6zX7lFFyM74Nv6zj78/G/Uf5di/cz/gC+ZTl91+G7G/8V3yLc/wnv5Ljdny//AfPrVZ7/zuX0XYa/hA92/ND10f6zl+MvGL8Bb1FO3zV40fjneGV/JPw042N+cvaXWcP+BE76bHzab/hh+J6OP/5a1H/6HT/E+GU9ovvb5UPmf4y/h4d/7YhvbHzvXZz4yY/iwR9E/OgK/ATj7v4kK/EZYn3Yl3jWcVt/5j5m/FT0/6bgu4j5gXp8hDM+bNM/Hx/uuE3/Anyo4zb9LT4J53/xKunPfEp8q3N/7fjkZPxwk/+du0fxsVPxican4JX+O97V+EN4+Nc8fEfjbXtE9zf9Oec3qf1f8Dqx/8vR+GTjZ+Nh+qbik4x/mI7+asLV/jrJL4jfFPOPbfBRYv4xj6v4n3q8q/BGfBPn/lov4THhTdp5AKgfRP83hp/iui3fuNy/NvRa/R9czs94vBR6rfad/Dz/vtLpS+Lq96U8n0/j6vszuEp/1vP5HC7jt/G0iv/Ae6nxT7yDmB8r4V1U/24t+z+o9QP4GNft84O765/t+Scz8Zxx9/yTWfhkx+35Mafgav10Ez5RnT+Gj1fjs19Tf6j5EXyU+HwRX6TGX/H7xfsn+Ib3n/ExU6O/Yvhxxl+fFv3+enxPFZ+KDxPxSz/gg8X6jh/xgWp+5FvaF2J93kH4OBE/cQre03E7/lfETxflO9fE+X2i/E7B7xDl9wy8p+M2/9Pr9PhsDn/KiV+06wuPwx913ObvdPxh123+fhcPHhD3bxy+0HHbPz0Yv0vsn3U7vp3xz3aK2gd34G2Mj+rqtA++p/yq+Rv8OPX84C1UfBE+QMUX4f3F+z31r3jwhIhf7oQ/JuKXu+INIn45+YNpX9r9h/DuIj5wa7yLer7w+5zyZ9dPTcPnBtwTx594I1qfewI+x/h6POx/5vGzjI9609n/70f6ryp+BG9eZX+igWVfgC/nv69wfCnlZ9ty+hbizxj/BQ/3X38I/6vxA3aOoeX96/AG44/glf1bf2b9jhofwzdX4xf4Xur9gA9S72f8/TK47bstw/YVPncj0h4551tG4xvL8PONd987Gt94Bj/T+Jl4OH7wLD7b+D/xSv/td86favH/5bdjOX0f45/grR3v3j0qX5/gHxmfjofni36KrzH+Vzy8f9/gbxtv38NJX6tE0KZK/HWHMH34zzE+6/imO/P9Yfrw9cbH4i3D/iW+zvhtePNy+r7GvzIedHPGD1ongkVi/uYs/NaAzzue2T4qH9lNE3p9FP5ulf7poLJfiS/Ad3V9G/qg5etfhdcb32pb8qj8+2/GrzXe5fSo/NyCzzN+MV6J/9k8UZm/a1nl/bcYn+u62R/9Ifwix+3+6I/jp7hu9/fDjxL7O+aSCfbfi9yeb3ksPh636UuG47t4Frfp27z813H4AbhN32bh/rv4ELxW+pJbJIIJKv4FHyfql454xnHbftkB72f8Zrxy/hi+u/Ff8Er8FJ4T8YmX4xNEfGKwZSLYLla7fLfDbxHv79xWiWB089r199/wL5rVHn/otnUi6CH2ny1sm5DjB3NwNX5QwhNq/2c8KTy5nf58Clefz+DbC8/hOwqvw6c5987Ojya396QP7yg8i3cRXvBcvw5PCm/wfL7o+XwJl/cPl/evnSd/cHn/PJ/Pej6fx8er8QM8q+L79PV56SXk/rYpXO4/jyeEZzzXz+GqfBdwuf7X8/31+DGi/z4fP1r031MdEkFfkf+d8N5q/MHz+Smez9fjSVX+cZW/JXx1rHb9uhZfYdzdfy2TSgQj1Pw+rtb3lPD9xfqxT3AZ39M=
*/