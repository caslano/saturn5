/*!
@file
Defines `boost::hana::keys`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_KEYS_HPP
#define BOOST_HANA_KEYS_HPP

#include <boost/hana/fwd/keys.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Map>
    constexpr auto keys_t::operator()(Map&& map) const {
        return keys_impl<typename hana::tag_of<Map>::type>::apply(
            static_cast<Map&&>(map)
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct keys_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct keys_impl<S, when<hana::Struct<S>::value>> {
        template <typename Object>
        static constexpr auto apply(Object const&) {
            return hana::transform(hana::accessors<S>(), hana::first);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_KEYS_HPP

/* keys.hpp
xwzoEDubGKg+RKhjnPkXOByB1xUHCnJMehihfncZBpB0n8pznfq4fXuA9gBX47vd9wB+lull8NI7OGWgtcs87/pG1jHGwfUdu4iCSPU3gzYBfnZui4ao41WcTav2n0P7OZ6ssJM0sDPrOIaq7gOaTUZyzQJ0ioJTcESMDjRtwqw0zqa8Is8jnHRLAww93uwv4uROtAq6dX1tucanBmJN4XkT2sRlP0HXcGTq8/MmGJUsREUSIEQNnn2zHWNsYi8OwdCc41kRkoqNDR0KslN9S/v2T3A8pVWmkIyk9Dia3qMaeVq8l+LHvTs8XsuOqsJNIzqawHh6RV1lQsF/m8HnOAoo/aoqSstth/phOVFt+/STzBiRLM2j0LXlceCYeosPULRQz4h1ylMcabngsT8/MyV0/+mDhvAcNM+Ff8frH3byIrZLlIvak90zBIxjaAV/icMfCZIytB2cWk7MTB4R/5uZbOHf/Vg+FwInRjSJQ4cpDec6Gn7Xk432ZFUWh3lh1euiqsDOp/7Ex+aA7+eJHcSppUbRU3PyRS/gcU5lYFe+g1g0QwndR7UZbWDj5+U4g8aJCoC9vMCcsesgO69sZOUOqv33eKxxbpPlOEeOE0ln//T6Gd0uNX77QIuPX2TbXhoUARcWFqt5UCHQ4/9j89wtitIqyJLEynsr2+uISwDLtjcXT8OEX1xa18tKM/68/rQbxalT5BGvbdLr/MSkl0BP+m5SWce3YNMK3pzqYd1dRdgHvN5KXhv9/l6jvSli/FzPwyLL9ftOmkXpummDZ56V43S/qALHmjkAPqcAn5I/p+Zohh5srzbNOlgZuHzEtfkZQjtsS+GIa1EFCo2Eig605WbVwOVYuVuKNTqVUXwqDmVp++RJ4KN2HFLz/1yrro9ZmFRpYkGPcS8CcdRSuualvB6iQrISQXJpJavVLFzQy52i9SaDFmL5chzr5mUoK43GI1uFGjvUM+JusjDNwgx8n8R/E/iDv3t9aJrB+syRAzOT+P/+kzMTsJYHMxOSCZPLQKjX6b+a8UY4YsqK0LW0D6sRv3VVJ+J1jkRJhADn0LHIpWWolHXV30dgTjIeVRBXO8pyC3FY9dH3Rnejt6XFbEbJeh/1OJ8crKgBVABpjakAgtrdkvY3pzuh2nrO0AVBGWJxL7xaF0ycED+WqU5D84IxNgHiOp3Sj1zXCtXEqNgaTk1mNF9qGWtP5MBZKprMa1GdR6k5eQk0jfiXIgliMKih6dqMbsroDhSPdz/FkMM8icIwsAurXZPqpXptRz0eKx94vhPkGFGizcJWzQa0YkUtAw8agCXXj9GAzR5Dgc5TGBpZczC4dV8mFQ8fAVyMh3EYIBIBYe0cDdXRcdN91DHjpRAoAU2Ofmx2txZFV3aIjiXyoK/G47zRl8RCQHySJL5nrgmPaaKwodbb8UVXtPjqIeYqqvJ8HA5MnjYiS+G5y7O5fZpA3/tVjP+LqBNMHgo2plilhqm0M2JxXa32RBBqu0hSC4vTkgoLlNs+zqamY2od/x3HM5naiB6GCQINNNhaVzxQMnnJlMkAIRRZWqTamHA9pY5NPb7rqbytLtZkN/SrKLLUmTp6h/V0m/F9WcvzU0073I+CIHFDtX/BJmqIrbieVGIbzNa6Zo3bf7ZjyHOSh5mIflZ4gGOITqwNgEqhGQyhM5k8qTZVfE+Fpc2rfATEVZibLZHEjlo0y9gnMFmoeN9828phy6dhVtG+gAJNOUaMKliMn/jY9O08x4MwqBwLpWMHl0Ezg97VpbSPnVTy8HHg4nYdtgUuui+70d4XfhqwbF8mhiVwSZmLv4D8IP4Y8XVf4HUmYZSXiBpLrQd1G2PioIL9htE=
*/