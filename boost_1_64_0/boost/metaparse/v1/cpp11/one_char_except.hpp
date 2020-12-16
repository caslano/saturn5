#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Cs>
      struct one_char_except :
        accept_when<
          one_char,
          impl::is_none_c<Cs::type::value...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except.hpp
+0uLGKeRbe0f9GuAT1ZznzDhDhWe5bnhzSq9S4VN+bXcUxzWuN259q1cT4RlnvC3tm5TY0FS8ep2la7XE+9Q6VrG71LpXQr/3TwXMnzF+KrH1hLv+whPLuP2wLiMPGIPV60H/lCUYRbgZRl/xOkog/Ln6tJG2/BZ73Kjy6C/rlH66+e5cZrlsAsydT/Cpq4IQ0bcMOF07weDTpfSWb+tdtJJR7j1+J1K1231e4rTNsuQsln+oGwLva71iGrfr0HHUds7NtHjCj+lW/x/dGQWMEpm/wwavZIvwAHbyNFVFO/uh1DcceH7m/ZNpBJp48OumA1fGsG7Cwtx9+pJoVPnwdZ1rVzYxoXt2/p2moTZXG5UzsZ9KrApUe6nLV0ikPEs7nFUln+KspSM0e7Geq6VFU+NJw8d6q879/dI2ynVb2cJuVlpKpkhPKvAj2dEGSbJMth7IlL7h6exbxwtv6ThuV1t/d+ixqAXMB48JcaDF5V98ZKyXV5mnJTGuuMF2Mp7GN4tA8qn99L+S3GrRp0HFcMLOkuCOhg6Xo2P7WFxr5ziHD6NV+FHD/XDV6j+8nSITfVi0OdK3LFlYg3Xm/oD6s18OkClV6r9kQMp3dTlBaUHDqL4Jw4VfAS9N9c4MDZdw5TVuPLwgurnUyjd8Y1NelquL2vdNbWG1/sqAZOEngR9oWf296YRfPha5coTG5to/pNI2NbNhdCeh9bgzCL67fYy0W8L5SXZrjQ1h2xX+HiKPK/f3EKLdm1rEmRPJgfN1Rhz1N7Wawbhmyj8ELydwuodE+xZwuefaOOJNM4ejjaeiXwmbRv2Spct8NNmI820yzaMnx6fYXLuU+h7F0dQ3gBuG+yfTSFw8yH/M3FX4CDU5x0h9ZlWxnVJlLn1OQr1WYh8fFeJ6xOxaTi/X4a7CIT/AOCn6tjfTBvm71gNhR3+HeBVgV7c4uS6xg+29aSfrTPnobrWIE8t8kh5Py1kvXimGksXU74Vo4xNzU0rEv6NGx6hVEJunDrGlmNsOBs1Up2C/nIccJ6OscreMTD3iDy+o1QixvDnF7rvw68pd9+H5/fLe1P9W/mceDmd5xnE2aLF2LNYUuPMmWgsNJshQ3ytxI1yfPCddLBdj6BET5WTw6XwR8Z3/Nyz62WyTNgzXSbKVO6XKeUWCnFcKvQHnCGG3rPlQxiyjTDr1fdh70GOs8fXuOmUz0lvFP0Ud2BMm1A7SLol3uoal+7Jgu5JIXibrKyPI3ng8b2lxh3fT6hxx+vWGk57lxoX2xE2dUAYYw6PSbq/nMh1A4yCgw7aiLIeI8p6kirryaqspwi+HkvfFM/8ovongnTk1ekdoq7Hqrp2IUzx7lwCsCepsbCnxpWRpXz+2MKi3sQDt94p5HuXpgP+v0/R6XXo0BtwMxj+AcLdp+yrAcD/htKA34F/rNyFH2SeULrLkyxwTUHbzp2B9gesqd8UyCCFLcz2GhemLwRmp4RBmTTMu1Xb/+FQrscTIfU4S+B8iHE6snk2xoKH57py9n4lC+cg/H7dRoDVNu0HYUddV8bjtWyDh4P8KFta9dvzQI/iEWb4OQePnG9/HPX4BPqL5OX5NQIe9b4A+GehH1wyC7IqyvNq+Ug74SKVr2SGy2OKp5/L4101jrwhnXFcrHCedIgL/znlC+IylxcEo9YIwYvPhfDiihoNT3eYVPm07r5Kpc9R5b+a0uVYMfdgn/4XQV+WdY7qy9eirNcp2C9R+Poaln8D+2XRL6+a4srnVygtdL5szxer1405yvE1+TWU4SyMxTfW8L1qvn8fvORNK6Xifnwpx9NhWIaf5NEB5o7+bgPNd+8RR5DyfHg5/MnGYEfc5NoRhN8=
*/