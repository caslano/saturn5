/*!
@file
Defines `boost::hana::Product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_PRODUCT_HPP
#define BOOST_HANA_CONCEPT_PRODUCT_HPP

#include <boost/hana/fwd/concept/product.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/second.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename P>
    struct Product
        : hana::integral_constant<bool,
            !is_default<first_impl<typename tag_of<P>::type>>::value &&
            !is_default<second_impl<typename tag_of<P>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_PRODUCT_HPP

/* product.hpp
c/wKP2WNNTs4v353Za00C0/sG6isI8yC7NPpGvKcoTArepYi/7wyURYO4/mcVXZcPtkVWEy2BWVbQZd+f35GtNDEpB1ZudIba0ucZo4ti32QedGsUe/Jv5UF4Sf4XclqhXwfpiwBxudE+KtOZ2U+YZ0pLrLN3jjZsUXYcYprvrDnNGURMJ6z628XtlQWD+tG12yxKPWn9DYGNSU7dWG9qeQOCyazvzfmuOQOO0A2coJPWbnfYnyHcH550r9LfjA+62o3/NFaZnAJ9opseZPLck74wtQ+2GbttO0eMT9YHrLuj15UlJotkTnLtoUzX/vK3sLyUdzx54vyyQzCTCnu4crpTspCtGe5Z2t/ROZTswPtj4QpC9Ou+XlkzTIyuzA7iqtu+eqQsplaXKtOBw9Ij2AuFOfX5s1b6QMsL1lsgPM1ZYmwXHTNFZ5F5fslCVaI4mrmGjdHWbpWz8uT/64sMwFzp7gVcS2DpLdLsdMUl2nbyVGZE8yV4mIOthmhzB9WnmxPYu1Vyvpr10z6+8xnqSeMezsrdvoNqSeM61l3XLfnUs+l8ntk2Tb/Xad2ypJh3NvfjyfJt1QKzIZnomsT2bHH2v3677T6R+oJy01xlV8ZXir7BOMedQj17afMZJlx3z3LpMm3hhuM73cpepa97DvMQHFDclaUd4efFrfINnqu9AHGO/bE226K7BEsJ8XdL929hrIgmDXF5XBN95A9glUh+3w5UGYiFmZLZr24h4/MNcwqyzz+Z9vNBsp7+hDMjJ5l/O2uJjLzWs0aH05prywN5kDmOsu0r7JMGM/nMLeFS2R2lxtfc1b1m3WlZjAPsk85cjspC4bxrpRb63dGZhfGsxQ0xeubsskwnvnUQfOl1lEwniXHRa8vSz01OzJtwBOpp2bTtuZMlZrB8vM16yVskJmH2ZMtruifrOwdzInrciZ0tDLLFcb1LN915lZlvjCuZ9MzbeWdEwjjne5rne+2zBKsAFn0cUfJIRzmTWa6PLyc1AXG+e3cFR6hLAHGM/jynpecPUna/fxaJvWSWYI5k00w3xOt7AeMd9r1gVlXZWYrjc9Wm/ZX5by20czr8bVImUEY7+bXolc9pZ4wR7LIuM8flQVo9txsR3mZT5gH2S/f1nWknjCeQUuXc/KuioCZkq32nrxQWSTMietZ+cVK6cNK43fVjdQhP2Q+Yep9lPW/qWE2IYeyZFhBsrGfz56XGYSVI2u0qY98E3nHypmVbfPOOReTmsF8KS6yQWX51g+CmVHc1YpNekvNYMUp7uHVYj9kb2HmFHfY476d7C2M8wv56XNKcteumVp8rryLU2GmdM0Ph1rK+ygNVoziuu/OvVZmaZVx7uPGbHZSZoCVpLj+I1zkW78ajHMPmJToLbMEK0txlmYX3ZQNg3HuXQcMnSrzAvOjuLWhpdpL7rDSZCWbL30s+aln8fDLNtsy5+V8SYfZUtzdweH7lGXCCpNNuDN+kbw3VxvXpcjSa1IzD5gDxXXwTq2qzB9mQxZ5wXubskDNJr6/OELmBWZJ9nhPhc3KQmDc22+VpsvPynvALMjuN7oidQmDWdE1t7dtIHERmo24XdJfZhBmT2YYP36vsjgth9giTaV/CVrcmpE3LspuwuzIbNbPvS490nI/eWGinD3vYLwPy9dd/Evmcw16QVa7TZScn36wvGSH+sz5LvOpWfN6b1bITsNyUT2bPos+Lz2C8Vkw8pEhVeoJ43o2XPZcdjMKxrk7n08orGwtjPdocrFlT6XWmp3xfDNf2RYYz6ddWvlmsisw3jH/aX3lWRJgFnzNqtfrK0vU6jKjyhW5X7KWw+/SzxZI/2CqRwaTjoOKeOZuJ+93bI0=
*/