/*!
@file
Forward declares `boost::hana::permutations`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PERMUTATIONS_HPP
#define BOOST_HANA_FWD_PERMUTATIONS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return a sequence of all the permutations of the given sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `permutations(xs)` is a sequence whose elements are
    //! permutations of the original sequence `xs`. The permutations are not
    //! guaranteed to be in any specific order. Also note that the number
    //! of permutations grows very rapidly as the length of the original
    //! sequence increases. The growth rate is `O(length(xs)!)`; with a
    //! sequence `xs` of length only 8, `permutations(xs)` contains over
    //! 40 000 elements!
    //!
    //!
    //! Example
    //! -------
    //! @include example/permutations.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto permutations = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct permutations_impl : permutations_impl<S, when<true>> { };

    struct permutations_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr permutations_t permutations{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PERMUTATIONS_HPP

/* permutations.hpp
gcdGtEg7F2TQhxC6oHrostIxHg839rR8DNpp/Zkbsv5DDxGOs9bMysYn7l+dJviYMkfPLnmi73bggNlN1kPaTqKT47rlkuoAp0r1BfSu4j+xWpLWuMKNOCweAgDoFCh8CLFvYhFjETKD2N5wvI4gIHki/tXWhNaK528ygrJ/LLf80RlUGijaZ5g/nfIajvWGLZDwCqE6kPI7EibiRR/VzscrHiACGUIMmn8LdgHuMSLipz/eIRgHplI56I40V1EMzryZQWQITOxj2uFxRPHEFKj0mqHypzhehBD+YfTG8C07Yurg5Opo3dEByOTt/fsd8x38P98XuWby7HHuaGTP/NkSxOqITJQ7/yi+q+67IEJ4qZzBMP9ztYhYaTDxZNcF19SCMXsypuS3hUWf/K/VCFfmj329+a7WH/sj0iDWS18w0iyr7tKsVnE59AVyiZpkCixMPAcxV1qSj2fWLI6yvBbBfPvuS1xQJb2fJcmyGKi45W28s6TKFlTmrqzZXGruRn0k0zHUVOnyQ6I/i80EjNOR3Ncyjn2WsgRwW2XyIu2KE+UPAdlnwshBKtyCJbd0ftne5DI1eQoQ3HGL87syEgPW7GaUb1g2K00avbN/aBctdRcvtAdn82TDOnA1h925jF0YcxRTGvIFPiQtDHBg0M7b6BK/E8ZWxrDcHziKkBzGLKlF2SdWs8Im+kHGS8kdrd7DULW/q77mrKyv
*/