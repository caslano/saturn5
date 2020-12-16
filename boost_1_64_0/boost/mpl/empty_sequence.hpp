
#ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
// Copyright Alexander Nasonov 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>

namespace boost { namespace mpl {

struct empty_sequence
{
    struct tag;
    typedef empty_sequence type;
    struct begin { typedef random_access_iterator_tag category; };    
    typedef begin end;
};

template<>
struct size_impl<empty_sequence::tag>
{
    template< typename Sequence > struct apply
        : int_<0>
    {
    };
};

}}

#endif // #ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

/* empty_sequence.hpp
GiXB0Sg9eG5Ipn/oJmYo3e3Cxx+h8PPRh8niSGifPtG0TxjkPrq2PXK+c5MW96qcg0Y1JM1elUZfP7w3XLCbL3kvuhSlBjzYvWmU2jSerddEQ6gCeiSCbs9Q22Ps/mbqMM3D20OZV1deUtdabOjGMdclqK0U02bn6AnF6DXJ6C914nroR0M/d66HTslj8c/qdMU/R49tm3/+SPNP2VLZPELTaz9rYTEy6DY8WftRk1LK6BjdomJ880PEQGmdNfPEA8aZgURl2qpCi/xbOyi2Ob4WbBOxHutgbyW1nBL2acmzN5+r2ueMDNf+ujkIYHmLD3Y0mqKhjcBVbc2acSgNerJicxu18+bC8x067WTjVt4gLn+7g4zXZUjTDEPt5PIDKvQmpLW1QeZOv23p+arfZen5fTHVmd5HW3oO1fqgcSg+MtzqRNxuEeTiazvUNiTWvp1IW9RUTvnL/oaPcCU8A6a/gbUkiBwS+z8ri8GYN52o2fuwON9odNNHpCLnhkYfOe4XxltxrweqmdHl2FOPzM6cVk5bdjrNWc6R45YPcR7bKvLjOKZ47WVu+LmytoO/zUvc/jbrL3fDN13qhi+IgtdHwXuj4N1R+ddd5oYTor77otKX5rrheVPd8OIofP3T3HBKVPp9Ud83RMGBHDecGQWPjYqfHFX+yKj6zI+KvyUKn/ui6lMUVd60qPhZUe1nRMGLouBNUfDGqPynROEfisJ/f1R8MwqfXVH4b47KbzD2/wfGyIe9R8WXDwN8MWtXa8our/WPyUleAEY1Q2/yVwzRQ7eXuptghUwDMgfc/jyYOH3S2orfevCZ/J2SyYh8tab98m1+VtFuI6u1toSvBzwO4evWj5ucwlctxQK2hiVHftzFIUeu6aUUUwZVBXecBqhEsv2Wtb6cZNT+NSG9akGN7oRZxu+5MXLP3v5KUKuL9IoRpN4zlKDGwooS1FKBpGpS6MYpFdD7Ux+XyfL7QAItg0mBdpb9DX/g2fotN3rjj4DeDUMcotx+PYntl0lsP91oGTk/RrwUnaARV/zL2Ue3YZaX7E0oykKpjBvkM9T3TF2DorOcVTS4itW897r8LMu5IRUbOU3ja/7mA+5JrreIZT3P+g8Xy6z7pzv3U/LFsyIOwImpifknJ0B3LxSzzjBFRtU0PaqGnqtHFd/mf5rqgvoUesEVZX7uXMT8ewd0FrxCspCCqbbSa9F/p+iNhFFNTXoLouElCokdDZAFaNaU+6o3nGMNix+792YmYa8oZm+mRfZmWmRvpsW5NzOyq96baQcbgMgovVNEo17bpDYLxTQ7NmY+bsY4R7pOFIJ4pJUJFDLWjoihd1E5SDp00a/Z8PsolI97O+lpn43yGu6HEce2l9S9RaPsjcwuFNOOm5NUZ9jZP/s3IEwRaHdMayuzVTyzoL8eT900bzGffB8jJdJeX1el94D0CQdtR/X5vPfkqPaEv+8D/+b0LiYiHjERIUpa2bWyoHVldqvPU5ndiiA4HO4afCa7Fe0s97e9cky1pvJGvDznpycDW4qRHl7pL9lb1YZee8D8Y5yX2OnFMDXz1mvk+o+zHEaMT2NiUzkuUTmGOLZlhPp+PUdJIbooO8gf5NhVO7ziOp2yWrznBCLfgDIkQy4sGugwpb8Mxagyz1DFuEyEq6WUkzvr6+rff6Tq+/kyRxB7I3ZPKxJSncOK/fCC9jiCepgxDi4XbW5yRs7h4LJVWvn7fjOQ1vdR+KRCti357R812TWcKOKJ26j8iS5uo/IrUUk/RvRh4nvgAoeFJZJxvLDEjGxCDmPucMNVNLxOcglqtcc7vdT8sFMUluShGZe2O236Z1nG/Mq4P9am/3zk8WF/BxE=
*/