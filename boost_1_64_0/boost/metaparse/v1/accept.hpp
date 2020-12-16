#ifndef BOOST_METAPARSE_V1_ACCEPT_HPP
#define BOOST_METAPARSE_V1_ACCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/accept.hpp>
#include <boost/metaparse/v1/accept_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result, class Remaining, class Pos>
      struct accept
      {
        typedef accept_tag tag;

        typedef
          accept<Result, typename Remaining::type, typename Pos::type>
          type;

        typedef Result result;
        typedef Remaining remaining;
        typedef Pos source_position;
      };
    }
  }
}

#endif


/* accept.hpp
3D8kj6v7W4cPVPvz4Mer/Snx6ep8w4m8H9T18Z2EJw+ifSv2F8p4PI93c54P6w34582i/aFs/+lR/B+O2/0XHsOfd9yuv38cf9Zxu377CXyZ63b9/WH8PpH+Olydb12PHy72v5yPH2r8HDAejr/gI8X+UIvwoWJ/qOwR1G8qvgzfQd0f/J1Y5HZ/vsX4qir166Zh/AXeWKV+bR3WP/gLjtv21dP4M67b/u1knf9J/AvRfmmDfyb2990aX+O4rV8exbs4buuXx/BOjtv0Z47S9yePq/tTj09oVvv9Nx8fh9v70yqML8EPxO39aRnGl+D74/b+tCj/moX4CNdt/Xl0POhbJf9bldN3E76j2N+tEe+jxp+mEl9T/v6U4+my98CPxac7fvNesWDr8vV3wacafxdvG67PwY803nNvzjcL4+/xscavxSv3d1o8aKP6R3g7cf/r8G+c+2/nP+/H/xHwv5tF3m1wdP7aYvxp49PxluHzhz9qfCke3o0f8NnGO5E/lf7BcYyvqfYpHpfnj8f1+dV4C+EpfDO1/6Ln+lmP5zye93gBjwuv83y+3uMNeCvhRc/nGz1ewluL/G3CNxeenKE/n/J42uMZ/GDhDXhLlT8eb8SnOde38zMr8GMC2z7Fwv2P8KOrnC/WvPzXm/gk1+37+3hP+fR43uMFvIXwOvwkdf9OoP8nvBveT51Ph+/uuN0/v4CPbFb7fKOL8CvF+aPf4p3F+aNNeEqcP5o7ifKt2k+4qn/q8dbq+cVl+fR4I66ej5LHm7TTgfLUzx5PeTyND3fc7u/QGx/quN3foQ8+xHHbPu6PDxD3tw7fRt0fXN4fjzd6vOTxJu084NqTHk95PO3xjMezeFe1vzEu9zf2eNHjJen8m6k95fGMx3MeL3i83uNFXJY/vJfw5CxP+wp/zz3/za4vwx/Dj4mcOcmo/zoEbzD+BB4+n/vgC40n9oqez9/wb4MNfSZemR86NR4cJuInLsIniPiJJvw+p31txx9+wu9w3fZPTmN8Ss2fn/6/+PGtavTPGvH+6vyEP+rxlSyu6q883laUnzqPN+DbCW/ENxZeCr1W/aY/T2HSnvR4Ct+tyvkHW5f/7odvhh/q+B0DY5W/puKlYENfjVfia84gfkaMz83H71Ljc2fS/1PPP76z6P83SuffWdrT+Fbi+7Mez+PbivJZ5/EGPKnqL7yt8Ca8o3p+zub5UPU3Luc3cfX9eVx9f73n+4u4jN/E1frZFXhHUb6S59D+UedH4f3F+EsO3yOofX7uFLyvOD/3aLy3ON+0AX9QxH8sxy/FD42cmLVYZXyuEb/AeAkPr7/RuaxfM957QDS+cTL+YbCh/wmvxFed54mvwlX5CAq6fKRxVT6yuJxfL+CqfBZwdb5UAVfvB1yuH8HV7y96fn+T5/cn53jiy3D1/RlcfX8eV99fh+9XpXzuUPYH8RSecXxk/+j98QH+bbChX4xX9v+5wDM/6PE8LusfXNY/nuuXpPPvQk/5xmX5xmX59nje4wWP13m8Hv/dmV+x62OW4O/iWcdfS8cq+yP+DX/D+Ga9Y5X4viK+0vhReDj/8Tz+svFn8Ep8z1w9P5DFu1ZJf9+yT8M3xscGuHP+U4dwfQ/+exB6dP7TtmF8Cf6D8SX45uW/LsA/cdye/1S8RKe/Cd9bnE+9Dh/suH1/bX8p8RWO2/dP4TJdvutxVb4bcVW+m3AZX3v5/+Z/W9aIf896vN7jTR7PXMH4iTp/FN9LnZ+LX+K4nV+bh1/suI0Puh4/V50/eiXjd6r+83g9vpvqn3g8dRXXV+1DPCY8h/dsHobtRT6q7Pfh7K8SNDi+xR7R++M1vH9sQx+Ph6nd+uo=
*/