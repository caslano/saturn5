#ifndef BOOST_METAPARSE_V1_REPEATED_HPP
#define BOOST_METAPARSE_V1_REPEATED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated : foldl<P, boost::mpl::vector<>, impl::back_inserter> {};
    }
  }
}

#endif


/* repeated.hpp
JV8ibPbrxs/xMtYBgsWvEy/n8oSrz1iu5PKwo7nlr8a8cA1k7+bGKzEGfxqQf/oIzt2WNS9v4WtnJh97xm9Uyrd8WOe/hjOG3PXFmOCbQnbX0t9XGdlthn5cxWdMThZUF+vUjWG9TOdbrDdUztO5ScjwCdRB9YU0bzY8dJh19y2V+hyrt5Bpfcvo760ibXG/BtjXUO8PK/UZ6mrwtV9h7vegdIE/X6afWkvdaeyzPQ++y8DtefBPDNzq/s/MXH/xRK8/lOa3CcT3m6dM+Xuhe+sLdR/dX8m4DhbGceUxS7TstwZtWx5iXKJlcZmuw/2lodtUMDTdhxVdjWvpPmroFuQPTfcxRVfjWrqP85jGe9C5Y/qJSv2d7ZgJ6jsav5kF/X9K9PP6GPgzos5TJsR/y/gDz0W6TpSxNJ+D/R8U7yA9b8bqC5W55bYoXuLnzq2MAxq5OC8qOvHfjF5SdOJxXjZj+tQJPKZfMLB/CDk/BVryneBtwC+MoZXJM+ctlTrO7hblx+VprzJr2rcq9fjMN2+HFFBavj/2W8Rues/MyzfA7+FI6Ne/zNnD+EJ91rAA6coJDAevdC+YYwqo848k5nKDkzHrsbykT0NowR/yOe3peD27X9ydG5vUerZzkvsiH/ZmlyTgqJ/yFXxckvlAGvJx9HS/755U50H002ULGF/Ja3Hs2cXQcRuKQeeOmPs8lKfvhgme7ohZ25dCbg8KuSWSWg/KDd8VEU3AKB96gjOOJPc7t0P3VzXTwBmN5qvWwC3fexo46yrOORge3kE/0pSfzP1I5bXMphidONisBaZyWaKty06DrKgcaPH5m0y3l+p0q0mvNOkmTqt22/O0WcA/3JRfbtJpk15j0s0mnWHZsM4a3XvAyGIucJ2MLO7kQi2n+aZdc60fj4G3m/OghQbeauCLDXylgS8xcHse1chygJzFOy5DnJt92tC0305bDPxwU+dyA19u4IcZeNrAVxn4GgP/rIHbM7YjkvpcwJ5vtybl/jZ+3mxL8pqnpHD48/QU0yPc+H1QmnkCPc3TGgEvjYF3ch2A59ZxtMKJb1e3GRdlwm8ntZ3vBn1Mn3Dj29mf1Hw/Uiz3AfE8DSb9vH9+oa/zavKnkOkSSmPfiPEodTg+3vjnwccNYgxPHyo+7Zr+Xg50xGn6RsN3CwsgEzNWjk/qb/0fxfg/oiT3e7XLs9+jv8gyJbg/L5ps/PhPNjgTY/wiTlU48XHeT2f7Tzja5p2RlOeaiKFk1mdnsY4CR59lnZ006/pC4weBe6bHJXnOPp/nbIoFzPkXmrn8K6B9QdLTuki05QKj05eY9O8LPP2vC/pfNfQvN2Wu4PFP9xR5vE3Mt2v+HYOrNC50PB73mqReYzdZ3xqxrnxK0dFrqWtVnXpPZuu8Lpcmxrn2ObieeSN55K7/bzQyOgS8z+B7nvxdwMTvWMhtUTr5HdGP6wu1Tn5X8LM+Zn9+K7eL4Cx360vxA8KbGTv22zt7TUwqztHjvzs//nzqduYBfnjgw/TXnYQnae1XKM878FaywXkrpr6fcH3w2/U20p5J/wzr49vEWLsbOu/w7knmrm0oL4R143zuPlEX5eHbD+tNIep6QPEdPzc9RDiOh8nj9d7ml0LPunB34lfAXYa4rpKHJwrj2/uo6oehY9g/Jng9ks/29Ns1ye3GXQnPDxc1NjSFSpObnfXfe0LYtydEXzxp7M9TZmw9Le2EkNG1GIu/F/Df0d+bzfn4s5Dhb1APy9DjP5dk2VA6lM2fTH+fV6TxUvje9wLPefYbNO536HKXodzW5HZjes2jhycXNbcunNuykCVrAFnZvpjkO7Ec741icqp3CCjdyrHc/0plxgY=
*/