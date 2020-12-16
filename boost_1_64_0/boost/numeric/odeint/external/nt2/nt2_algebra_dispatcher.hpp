//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost { namespace numeric { namespace odeint {
template<typename T, typename S>
struct algebra_dispatcher<nt2::container::table<T,S> >
{
  typedef vector_space_algebra algebra_type;
};
} } }

#endif

/* nt2_algebra_dispatcher.hpp
yyHQ9tkA/gT1LPcp2ASOcQV/mofnRDpi3olHrvsPAv3fjuPDd+lqCtzPVmRNSN/ZatksI8/gnupPmUekB2X+c4vHfLr7IrXLL6lMrrPGZ/0AvV8bPYfu8rr+S1Zf/621h/oy84g0rkOmytD8Hdsj3z7tNSLu4I9WGa9aZbzGZWjbfqUvbgmbnlb6PvbZQ5H+quAReDr9L1Z5izhuRutNVbW/vLeYno79Rz6OX0X630X6vXafRvo7wp7MLffbj39aecuQLstWtZzehPTeSn/6WKQbu2LOrObwg+0exwCMr3V1h+2PsnRnQq1/f3uPcuabddWk7V5LcRz4y7odtLt417TLatkGaJwRx/yJajLynCTPodAcgOdicFKUPH+SHBjIxNw1V+i7njfEY0PmhlUDN+c+sbaUjQ0rb4+xvFasM5s5G07KdrU39nprNxaw2B5jb3tPaGlrY29fdytHINtA71s9lVo2Dk/Ku5fVdB/7rlhdC8+PrBY8TxpFmU5//LqIm6it9ffHOtKDNvIpplBbv9fCQ7pvbNyH8KbWjri/X5JsHT6n1TKf+xLdba4frOnFtVPKOpHz3uuBP0mhmVNDWEVlvSlT2Ugyl/D0pE6f8R3IJSKMU23W4j3ZT6H7RhfS3aL7CdlPLemstZYzf0Oz1vqGZq3zWN/QJHnOtOR+mRW3P4vyXRaI39HnvIAfvPPhoFpjly8VMUgHW+XMlfwAax7bIk3z7Qq/LTrESp9n+QGHcrqmnVX+8egwrofvTPgvagI+PMZ/zo8qafwjSF5H1vIeNnTGix1eXNwv1hcZt5mwGBvI56OI9swi+6mLa/W6QjSj+Dswx9QG71CWFyi7emLu1nLbsYC/USS/vtfR8GjOXOnfPEa04B08B/0PcNyKNIEHnPx4yyy86So/Xlst6xL48OnsStYFpBmepC6sstJt36XTSp9u6dKxVB7S7D4Bnvl+B8bB3j3pz1+tOeNqCx/pGn+NxYN9B8I6kY48gfTjqQ8eLWzciVYfPMnqgyGmCT0zdCXNMKfrvFnmWadHRNvBJwTf+e9WiLG/ADy+s0HKa0NtwfuKN6VCw97ukXnTGmrRtNsVa+HBcsmfYpyhWv+8ZolSZhylsx/v4L2UOLiuvu6uzh5eSA2kkP+eojZpyPPNhXZsdeZ4Hd2s51Ga/PZU2tf/ETu/dh3tA7lSkrAi98OWmFffUYQyg994SkW6sHHQrldg8c2bTDYdjvNYmEMe8J9ObtnqfX9hNdVhU7AOfIqco/xcpoogGFs107ffGwlbMjTbG8Bz9323+MpvwhpZc74F6ECC9CeyivvaNst3ddZhThV9JktrEqex74o0fupIf/n8AvuupyOPPPu4u+Vb91uxx4081+N004/BV/BczXbu53p+vMpaF/qQZTewTiHwg7GvF3C/02lZFZyfXlQr7nrfbtIwj/bocywsv1cWKB+vPt/hwxa/3ZWmj28j274IfVqmn1TB9NBmePz1uZLlE7y3HulXW/K72ppjXku2+TgxN77ess0fs3i+QdJEvsMt/+gmTkde5gn2RKffQmXmRJkft8q8zSrzdqaJNKaJ+miad4j0U/A7XG2tH4ox+gxKA56mfY9Jg/1jfu61+LnP4ud+q7wPWXPpT3G6zot83E+Q/lBtgTjJXervuNOO+F2dj+Z/wIY5ZTxq+VgYT/Et6vzn+R6jPvS6OFf7kvh9pvj9lPj9d/F7srWeeFu1KS+bp7wnaiVfZgxHWuCs5peprRuF7n211r8GO0y27mu6TwbPRHzd0yXgWHrxTW53pHFe8G3WE2t5vW9Yr5vzeYpgvSao79aOuM7tvypeN2eBNLSkuROefUV5NrVLKS0=
*/