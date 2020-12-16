//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_GRAY_HPP
#define BOOST_GIL_GRAY_HPP

#include <boost/gil/utilities.hpp>
#include <boost/gil/detail/mp11.hpp>

namespace boost { namespace gil {

/// \ingroup ColorNameModel
/// \brief Gray
struct gray_color_t {};

/// \ingroup ColorSpaceModel
using gray_t = mp11::mp_list<gray_color_t>;

/// \ingroup LayoutModel
using gray_layout_t = layout<gray_t>;

}}  // namespace boost::gil

#endif


/* gray.hpp
XOvnevaeWf/F2/vDePaeTZj13jC+bedVuylMzxLp8AXktb2Mx69Wrvgjr9g2f5bjp2vvBs3yuc0nOjzfzpi8637a4Xt3u8x8qO8JLl/u0Jm2fmzBpy/tcoGHPKA3CbrlAe8XtbWui48lrr5nx7+fwmk7m/bKdkM0eN64ldZkoaQg4o+D3G7DSjeZfj/ZW+5PfB9LVHQu54abbzKAKefeOX/+OnnBdW3bZr2WTh2O7GeUXTcxTTqoDrgjjXLHiMt4ZB3N81gJy3+E456I+/NqvljN4uYO9DfQQ2awmC/0OHPDTDadD8Ji8P/ODbX/6Ur2P00PXsH/FDY+U73+p6sF7vqArnEw8qFk/DaM+31ErzK41z91rasb+aduJvy2Bnf9PFn/qwXH9eO8HWPSj9Tg6xh/LPn52nlzjcDdvLnWYN60394JS/6xLLtX4K7edzCY9J1l/I4Gt9OFOdmn4vs79xaBD8orbQn/rIO776h/ycH5+k/HT/MeS/ppEt7dTxO4f19h/0rCuvhiXiTc54t5YBVhXXwx/6rwZfpinlsN7jJ9Md+2hrhdfDH7buPBdxj8vT58p5lrbr2K8CV8NW8ijs/fMlwLbAl/y8sKX4a/5ctvS7wu/pbrr/bhO0w+efGdrMeW2wFfhj/mOeJ188ccWEd4F3/MMwo3/pj8/ZHXqO+4sXA8XpFnX9r4Ozp1ZWzo63rEW/3XAu8+ZnA5rr294lmDpX7cmufYxxRneTYhh7mxF2GWZxNqf0R0Igjzf9l3FFeXcD5/xKk7+bk+f8R168Fdno3KYdp3Rpjl2f8cZvVGhFme/c/l396E3z3+iOwfqHDHH4/mMizjyF2I08Xv76+EL+XT9+y7EqeLT99lFycJnI67EW6mmTCMTToudeLkeGdkLFzXyYHzHeM9dwfu8fnjPprwbn59vyLc59c3fg/CPPeZXlLY0rYguJRP93S4HgNa90kTfcSVroDwDKTekdc8/3ov4vnsbOKc3AzOMuxmXR5T9wbftcvJm4zXSbd4OeRN1sO8Y/fx8sijzKzDZe7n47leZVxnML/w8+FZZvq9B/g58CzjvDmlOFee13B5b3tgN36nL+HJB4G7jPkN+1Y+uBufenS5vvlQ4vrnFazDTYp35Xkey33vNuL756Qs94iyf648N2a563a4fJkFRu6FneBdeQ7N/L7d4C9j7qb1uPlhxPfPpZn3tgE/j0qZ69ixh3fwOvwuex/p4VBL4Ts9H+Xj+H0qH/RoD5f8JfW+9ueitVQceMrEF6npd2lvuYN5lzba2dy9E3JjDOEZG2q0A1zNk1UeH3I98Kj0nYu78SzP+f+r/eHiO3toHZ1sOZrDX3b83eiaTfYN895BMYdz9Ydn25P4INZRj/3B5U7OkI/KLK+LdXBgyIInfTc0t9cTt8t9iE7rH3xcaX6RDzLx+zrSPdpsRpMQtuvGzTubvCdMu2jRFjTnYeKgxGebBHO+nHwMrV9GEyTLd22U79ay3hUsJYJqspRO5f/vfeMNJO+GaF8PjiHoJpCWhJpvlnv1mcVcUHss3ufDnHEYU0aNrWBMnDEkbKXBBvGERB7P6iSHsz0UFnEJnPzHGFttMHXwz8LWMEZTWNKnGOmqRGECipjqBfyaHSQMukosVcs8TtVDwlZKDC9hDGsfN5p346Fw/IcXMIiiE3sPwlYIzD13+qRec/YRDDrFOIRU1arEgQzoIOWj0RfQ8ocKyXKW4oEcxCPlhDhhqc5aQkfCV1r4EMSYsKsIM4mMA6s9217UAHXtsrI5tL11Ej9398zVtY9cYQVw896AqlCMnWYMbe9gA5avwbasNBjJZFvo5QZrRZjH/+nWiKPiHEO7Owg=
*/