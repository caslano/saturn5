///////////////////////////////////////////////////////////////////////////////
/// \file rend.hpp
/// Proto callables for boost::rend()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_REND_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_REND_HPP_EAN_27_08_2012

#include <boost/range/rend.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::rend()
    struct rend
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_reverse_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_reverse_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::rend(rng);
        }

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::rend(rng);
        }
    };

}}}

#endif

/* rend.hpp
AHOs7JkOOA9SM+h9fT+7hDZ3zt0uVndO37pszs9R3YJe9uQKR7D3qkqap2VFtGj8eSyol5eUN031RfuGIYiyblCSudERksd1DnudhuuRAD68Nt+9fnyOVNLpD3+HDVJlYlrqNE7kgw6PiVwWd1eQdXuZCNyLG5j3+QQhysrohd1Z0xVV1wc9xG1cSyICG+CemWY0bCRcOx7Jsvno1hpicUpvXViRLGVyubSkpM/b51AIpLU5SF/fL4tA3dtvQDHpnp8/oAud0Y++hGAqcStKk9dKQG7XDj1Eu9VJI9RqQBp+//nZSls7bW8sxKUq0/gm6g7P7PMtHSFi/uUu3rum0psyyVKf9k9IMVCAqBM9YaqL0pqU3Jk2yc35vF8nVkJxO1x05U/tVr1Y+iTh8gJBN6qEk7GaAQcdddKeoUfBMeccfbF64VWItbCdNRtLTREjVlqw3FEEaMmawXsjX/X0xrrxqPEeE04u4M1o97xd4jU9D81zGEviO+6aoW7TbsNYAjyKIaWgmPapF98OVMuCc3KTRETbTsIrX7294I8u7SgvWdczT/KJxFfrP6HiOGZh56pwny4Klu1YjCrzhwXU+Z/xNX4dGbrcmqBn0VCvMgjf3tb5uRWZ8NHt/GQ+IJ/jhIG+QGdJi3vRxIfwqiR6TJV8hwHvUlPoyrak2+qsvNSGpaX+zxn2alpwuqtSmZDseYAVTrtoN9Tpg3ZH
*/