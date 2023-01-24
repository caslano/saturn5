/*!
@file
Forward declares `boost::hana::suffix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SUFFIX_HPP
#define BOOST_HANA_FWD_SUFFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Inserts a value after each element of a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a value `z` (called the suffix),
    //! `suffix` returns a new monadic structure such that
    //! @code
    //!     suffix(xs, z) == flatten(transform(xs, [](auto x) {
    //!         return concat(lift<M>(x), lift<M>(z));
    //!     }))
    //! @endcode
    //!
    //! For sequences, this simply corresponds to inserting the suffix after
    //! each element of the sequence. For example, given a sequence
    //! `[x1, ..., xn]`, `suffix` will return
    //! @code
    //!     [x1, z, x2, z, ..., xn, z]
    //! @endcode
    //! As explained above, this can be generalized to other MonadPlus models,
    //! with various levels of interest.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{suffix} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure.
    //!
    //! @param sfx
    //! A value (the suffix) to insert after each element of a monadic
    //! structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/suffix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto suffix = [](auto&& xs, auto&& sfx) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct suffix_impl : suffix_impl<M, when<true>> { };

    struct suffix_t {
        template <typename Xs, typename Sfx>
        constexpr auto operator()(Xs&& xs, Sfx&& sfx) const;
    };

    constexpr suffix_t suffix{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SUFFIX_HPP

/* suffix.hpp
Rk8SoQBV01VR3sBQHVP0ZeiuZXlibADM8jxTYl1zLVM+B+yqKzBs2JrmVnURLOhVeRtjdh0JPcJPq6Kq4bq6JrFL15Yu6eqZmulJatKVJloyTVXH/6trDzXEtWXYbvXcMhxbYs60VU+VhDRpdLIv0zE0r2rTMXWanZXXri0xYboIdtyKuVTLkhxD145qy2vL9SR/oSaGI9v3dJBYjs0DvnRTQm8hejdtXTKnrZumoKVlqJ4le7YMoNGQ16ZtgfrVtWPLni0TPGeJEVmOzoN6cY1hS6zY6LbCnE101UVftg59oIryNvqiJKK4tk1PYsuGZKG2vIY8Ve1Ytma4sjw4zpG8aIOhNUeWt02D5vrltQkSS+htx7JAfXlta5BUee3QWQdSImmWW7bqGmhJ0MCBpDhade2qXiW2Kihp2tW1R8cl8muNXlTXFoipSzE3TdBZXJvAnO3JawP8J68tFYwtr23PhbiLawzekLLuuA64VIzHVVW8Ec9dXbU0SSUMXwdbS+hxZ5pyFK6p2bqUdciMBSGV1zbBJq6hvVwpQ2A027UExMAtUCRw7UIl1b1BkThSglxPp0Ma5LXjVfQmcfBMqdpU2660roeaUCHiWgPwkic8zam1omeoYAvZjgGYNVnG8MC7qtSRoKnUSZ5JHOJJ6D0LEFdK1SINInumviRkHpWX0GDIsAnVNbShXl+7ribrQtJdqaE8B7pEkxC4
*/