/*!
@file
Defines `boost::hana::detail::fast_and`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_FAST_AND_HPP
#define BOOST_HANA_DETAIL_FAST_AND_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <bool ...b>
    struct fast_and
        : std::is_same<fast_and<b...>, fast_and<(b, true)...>>
    { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_FAST_AND_HPP

/* fast_and.hpp
dPnqpOEyPNYHa2I9gWvsPLruaEhcIGxkRBS8WPAKKGUEFLy4PlE4b2REzCy5CPUvFkETJC6c5b0OHSrdM466lO5H+75dF3DIx/sMGLJ0HKJH7VlDRjshVUlxfaI02aDYMDR5EsJcSbH0Y70CuMqTyO0aSw6vXSW9Uoy2v8LLam+7zpvXkAiBc7n3Wv357UI0uWq8P/8FITq+apQ//318Jgtn13G+76O4OCzdwbC7jm+DtJxvNUA9ptKhBzstwykSEXnceGixD+DpJG53YrlNeFFpFGEH0gZpkQVZC03QKECeRNYoi4ovIk/CImzZxHIhSikUkb47djiFfkYpFJHuHEsp1MAodDAfKQRJpZtUiiQDRvRM9AigExrHpFALtxuotEr6nyJ6mTa80nPd2vLcyd7FiLgv4J1HrkypBxil7s5niNqa+GZIzvnuvJhWhcXWE9S11JmGpAVPBpQutw8pchWqhh/nYZ9LEgZN/Mdv6KkNrItScruTgLW7VB6XMPEYTHwiT2FySG/mOy+XHkt+XSl5T6zk+9SSE76p5Fa15GOxku/RlJwyvGR6iDKZewpHInmGrzLToDifll77Gx7fQusl9LMbPsNfEXuatS2nHperuO3B4CdT8D4n24kcHrKlDXctwx9fIgA3e8L/c4kAPab4LeSJtyECcvhXuPWdqaOnOml0j+GiwkvVIOMlSv+Lf7nul1MMlj/C7334
*/