
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H
#define BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

// http://ericniebler.com/2013/08/07/universal-references-and-the-copy-constructo/
template< typename X, typename Y >
using disable_overload =
    typename std::enable_if<
        ! std::is_base_of<
            X,
            typename std::decay< Y >::type
        >::value
    >::type;

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_DISABLE_OVERLOAD_H

/* disable_overload.hpp
jsUi+NeeF59NNPg+8wLQN5E9yvoIwTtyAchS6Nk+s7KcK3xeJHzOmBPwuUjKLpK/LxI+VRcXCZ81Un+tXz/T0/m9p+9zAR/2Lcb5Uv4Y0w/HLmDc2LcejlugumnxoueC6ylfeXh9bYCHPCww/fUi4hvTC6vC6fmqY4am5bN1QdwbaPH36xapboGsUF6L9W1HkdcJC+LfQ8ka+T4Z6GalXxQPeT2J8LTvVf8XO3yZu2oZ1NGnGLl5pD/aXkvDtvdUKnsy4R4egzuv4rt1h3tLK5Rtn6Js2wI5V2vLShuj5fyGnbEgsOvtktcuY3DZAk0HNknnDpqPcmoI1ijEjkgf69uShN8cmmcP9NLewdqebprxdXa6Qxve2TSHqZI5zLMWMBa7enwRGqbVUbgfr0PjV/nfCN9XafOqHc3qc4jeHEOxyN9yAyNS8Wfbzxto7yT/n/0E+Vvf7FU7gfaRxtc1oT3hXbopCH7WrjXpbeMWTpqb3jC0e4B4oluQsH9czfCNo9nObV7w9tdEdlNqcjSTW0vs+zQ6FrDvtbczlR/JpTmMJuM3Eby2Kr93YA95OTsGSntJJ8ueZyfl6/+uqopvr/axfsfxG90NdqkA31gcu2sIR2lkY94DWgdj2+o8ju31pq67Yurqgbr4XLJZJ+4z+QtNfj/lx+pCGZ+R7w8sCPysjQtK78Bw3ibJU3uyWNumsjBrqpvFLp4v5drQJ52mLvP+l5RHeZ1NsOfSD+X1PJWp8PYdWd9GnKTwdIFPMzgP6ThaYPbRBHckpv66mO9mCusXnEUGZ5vQHAc5Lza8XSh5/H5eQ3mZq21Eme8QGpPIs5S7P0bHsoJ/EcpD8K1u5wW3EMP7LfP8vJ2S99bQ3DhNL17oXpbOjTMKC2wB4+E9XS4Xuss734dlxhhP5sJMC9dmMpFyxxNMy+kd0d1gL5bwHGksSUi0zCK7g7miPFEQn0djJv7e30HScvLbiz4X+Ch1+N6w2JCLCXcFzkGNHOagjHWdAWTTI3uIl4Acapj3ifRkqiz3mmv5j48ddAj0nDwuRT2WMae+GO6HvVh08yWCvyikfxM5OcsiujexaxLev3iptt8/z+ZYKqTypcgfCCh/Pmsa5fhuYMy3lpL71Y8pSrvIh+WMV0q7XiXl0N47HByfrxHcKwQX99P2zTD7a5TW903xHtBPaqLj/vVC9+21givjHt8CrIK7kFVwfv+qGNv5ZoK9xdjut0qa9F3vGkEZ7ncuh/sv7xC+3gF8fU3ms3fC/BrTjo59L4h44Tow/736bdUxWB3m7/1S9wtEfvperfJB/SP1ajttWtsg7cSxbnT7I4aXr5n9s4+ZfNdmzP9EpI7ot+tTisP9E4/zGZV/8E5j8MbvLJ0P8/+0HP/vOpHVB2tBh+XuzhfNN/dLgnuZ4CrN67Fud/9L0i8/Lpx+kUlfatKXmPQLTfr5kEZfUd/SIz6Yz29ovvDm+MB23GLyX2Tyv23yLzX5t5r8S0z+d03+C03+7Sb/+Sb/BwS7skptZPBWHaxdj4zQrbjo+vUwXfhM0kFY+KYIbgrgpIP6jq+/6opr1wJ3q7wM1++20GEXMLx+TRTo7FouXxB8Xj9a6sPTGnvcrQMu9zhYWZIpufMqfu2lujdH8sNvEV9g830u9yv9ccnPplI5n3TQrsshj8lC3j7IY5KwB3QVfyMpTg2tMi+TvZg74Jt0NeerbPS7qZAKMRKnUc6NtR+b9ayfmLF2p6QdHNcuHe86P0D78xMzpu82tv34Y0ifQ3eKnVTQbxmZyORT5ky5c1mCdELu2CFOq8TtVJkvgfcWF0uMSopHmcc7c/eAnJezvMy+F/3MG/H8tvJi/dfM6+4=
*/