
#ifndef BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   include <boost/mpl/int.hpp>
#   include <boost/mpl/aux_/lambda_arity_param.hpp>
#   include <boost/mpl/aux_/template_arity_fwd.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = int_< aux::template_arity<T>::value >
        )
    >
struct lambda;

}}

#else // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <boost/mpl/bool.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    , typename Protect = true_
    > 
struct lambda;

}}

#endif

#endif // BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

/* lambda_fwd.hpp
A638qWnVqwt7L7U7wCCq9ST+Ly+f/5j57c1gfcQSjlcxW4y3jp1PgV0655N51He+fuzSfPPhnc3Q6MjoiK5f9VWx3vmoYs55/RDLhOLlnlC3zTtUjhoJp+pmQxfT0DslNFi8JtMJaR5Y+1FFoiN8fbhsibmoPq2luofSMGY9F6tdGq/D0ALHunseDjBboxIww3CmKf/ztA0CP6ar3YEnZj09vGyWMu+fw0y5lnGfiz2OiLesSA4gwC9P+HUtdJPpmDEhn0TjdbZ1p6/WNcNCzy49NDmy/JgepAXv77o566Jcdyi+b7xmp1E16uwURd64ppddHyXKN4qulg04Nb0U0f5rq/p3FkpCHsgO1+nAYprQsu40ntDqgpnYUQPtUvRw9XHdgyWfGpDzqJb01IWqdST/aKWEJmlY7ao1TdiO/LxI7LtB055Fyt13H6PfL8Ei8Fa8Tp+LWXXAWwosmkLTAtQrntezLmcyNIngAmIhn1dvjrqPLUqvN2LdisPkWNFgefwRhCfHtJ/DlQd2S4W4Pyr2a+za2vULEUut+k3DyYSloV86XkxVDPEF1dHr1DJlmIvKAw4RnlmclGKSIJXLPJJnbNVpaXf8tic28K/3EPsCr1m/Ka1B58t803yc1CJT8kb5Y3QIFSTzyPR3Cg/t4k3f1E3z70PArMVURVogpuMd5JNvFpBEQDAgFkgECBREng0K5YQ65QyO3POL
*/