
#ifndef BOOST_MPL_INSERTER_HPP_INCLUDED
#define BOOST_MPL_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

namespace boost { namespace mpl {

template<
      typename Sequence
    , typename Operation
    >
struct inserter
{
    typedef Sequence    state;
    typedef Operation   operation;
};

}}

#endif // BOOST_MPL_INSERTER_HPP_INCLUDED

/* inserter.hpp
bKA22ChFeaDxxl8Lzpch7nfnbFifgDYwAwtL6fSOrH1FnpPF/gRvJzudY5B7cldBRaPzsK5aStt3/jHxC5fw1oMOjmiIaBOyN46XZULJ8a6Ak9kL5j70wakW400ZebZu1pksM7uGkBSP2FPuZQSttvKAvBFESKsxgFnbfVFPk7Ct2HaszLeSXBU7atGiPOrkPStCaCGsRRychzqeWl+JL4VLIhtjeCzMDIo+a0Ba/oNWksAn+ExitfKvlze4oF33V1PGOVOz7eyJJhj6wsARgdPXM7b7pDhSQkFdqrqIYu1cb43BnbqulsTEFXewkWSs2yyiDvoWBSvPjGMbWnko5dhWE+iEPE3VBOzw7AHxoIi5RsOX3sLlEnBO+jR7Vjhu7jkIVeBP54IPJwdmFiV4IgPk6D12dLZ59Lqcc2BYY/lKFSXD8X4Wwt5llXeZ/lwRmaehnvrGJN2SRykRFzuZ97luwbLAnPWJSGwL+koIubrzc5q7AOgK2ffj6XOAeD7H8Xp2YbaFfmtVrUx3tkCesxbAlCIOg5uwrdEFvDl4b6EjiFBJ4Bs0WbpE+Q==
*/