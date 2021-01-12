/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_10022005_1616)
#define FUSION_AT_10022005_1616

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { 
namespace fusion
{
    struct fusion_sequence_tag;
}

namespace mpl
{
    template <typename Tag>
    struct at_impl;

    template <>
    struct at_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename N>
        struct apply : fusion::result_of::value_at<Sequence, N> {};
    };
}}

#endif


/* at.hpp
eXda+9w11bW1d9+4OfHP931z4UPlx4KXf+q9Wb9Y9P2MP5626JMV7/7supe+v3z21zbeEHV5XcYrhzbcd+jx7V8JnBh+b96qhXG7Vub945Ozrv7J92ac8eOhtKdOzbt91qpT3v5lwa8OtS5rXbFsRcmDz3//4NP/vH/+kX/c8tSpD838pOm80U9fumfOm7s+HJ10e+YfP3XDjl/e9dE1Pf9YWPz4xxfdeuc1RefvuPSaL/7+
*/