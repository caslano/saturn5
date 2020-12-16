/*!
@file
Defines `boost::hana::Monad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_HPP
#define BOOST_HANA_CONCEPT_MONAD_HPP

#include <boost/hana/fwd/concept/monad.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/flatten.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monad
        : hana::integral_constant<bool,
            !is_default<flatten_impl<typename tag_of<M>::type>>::value ||
            !is_default<chain_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_HPP

/* monad.hpp
HeeyHdfd/JrW1mV/yr/5uvaZmK3t3OR11+nfVT/rvPaXB291vc6KWKczpzl+b+0zsVHGfOvfTmhtxWyfTb38Cu3dqthIYz8+eJnWtiU2wNiliXe/1drGOv+OueaAo3bQHhTrbezt3fObf9MRG2Js7xO6bqX9KTbG2F8+fkTrlxPb2VjPZA/dy58Xs+fm8u8/XK11cL2L58DXLtS1i7Ubi066cZH2vFgvY7mTH3lB7/pig42tPf64WToP0zr/Fvvs9GWnaW1ddsN2PbbWvIjtZGzkC29+7djZYrav773Fe6z2rpjdr5e0vtM6FMRGGYt1f6W3rk9snLF7tp+9UGt7Que7/oP+0kCtrdhexkaMfm2K9qDYnsZ2++K0e/VdxLYxFr3yy7ze3f7H1V1AZbWlYQBGBAkRfwSUEgFBsbFxLIyr2NjY2NhYV2ysKzYWYmNjY2NjY2PjFRUbO1HseWFmf77/nrVmTTzznXO+2ucougbGfcg8saar9A/mTnZog1kZ2SMY575lbhPZW0MHY+va/cMdZQEwF7KWXk3kfAmBFSILWfZZvkMiYDYcl9k5SVkUjJ+zfYWR45TFw/LyzE+qNk3yg9mR1epfReYlRbOkr52bKXsHsyeb+nGhlcxgR+NvqWLBlvIsHjDOod623fIuLgnj98rnxKellPlpcdtebQiVesIKkD24sqOtsmAY1+XmlBqFZHZhvO/z56fGyLzAeKe39StbReqpPcvjUkWkt4maGcaZ9Zd918xyeC0PmSWtZuF3S8tMZGpxH6f9lHPerJNxzQYdahMmfYDxXJsMcXsg86nF/VPsh3wzOMDMyH6dnNxBmZMW9zbh9RnpLcyVe+QcU1Z6BHMju7jJUE5mHuZE5ly9U37pEYx35Z5/T/kZdAyMe3v159NfstNa3LqPQX/OVlhBsn15M479z4aaZMJU381MwkzC7vUcqcyks7yrss2z7H+8lPnC8pFdKzN+qrJqML5mxeL5zJQFwApQXNkPtysoC4aZU1ze+4GvlYXArCmuu+f3vMr6wywo7mdQAz9l4TAbipsYtsNf2WQtrkbOHq7KorS4Qn3bWSlbBjOjuK8nJxxUFgsrTHHpN4vkUHZSiztwLlEsSYvbnNJbrvkOlp+sxZSEcsosuxjXeuS9jT7KbGA5Ob9tC/6jzABzpWu+z2tSQpkfrBBZdMcyf/58K0y9N83x3zxzbhSsLBxWmuxz/oeflMXBHMgG2+44rywRVoxsVeq39srewSzJPC5VuaEsE1acrOGTJnbKfPHEucnqFouTHPxD0FuymmfX+CkLhPH9Ivv3rC+5wwxkzw8kLlMWosW98k+apiwU5kJWseLvAGWTQ2Tms81l/4GmyqJgeShu8u0NtZXFalare3EnZfEwrsuo6/P/VpYKs6D7vX86bICydJgTxc0Or2OvzKSrcdxHc5dYZZaw/BTX5bWhpjIPWF6y/rHR0iM/zeYYYl4rC9Du99uz7znpEcyR4p5UPd5f+gCzImv8vnQuZWEw7nvvidWeKYuA2ZKtLjr0p/RBs5tvn/lLH7T7+fUuFiR9gPEM1t46xCAzr9Vs5+XI5cpSNLu51Kel7IP2LK4XNv4rPepmPEveJ12l1pYwb37OBp93Sh9g1mRNvg/LkD7AOD+HCq4FZR9gfmSTBm6tI/XU4q6+Dqsu9YTxGXJ/n0WgsgQY79HDae/fS81gZcgC5m0pLHWB8bx89b9RUlmmlnvpKcPGynx2N37OCR1vXZW6wOzJgpsvCZYZhHFv/3NqlYOyYJgP2YtUwxWpC4yfc6H3cdmVSJgHxe0d/efvLMfBclHckb21usuc4d+5Utz5hFWLlV3Q7le2y8/5Mmc=
*/