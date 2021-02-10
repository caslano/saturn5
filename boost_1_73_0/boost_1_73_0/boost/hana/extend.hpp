/*!
@file
Defines `boost::hana::extend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXTEND_HPP
#define BOOST_HANA_EXTEND_HPP

#include <boost/hana/fwd/extend.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_, typename F>
    constexpr decltype(auto) extend_t::operator()(W_&& w, F&& f) const {
        using W = typename hana::tag_of<W_>::type;
        using Extend = BOOST_HANA_DISPATCH_IF(extend_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::extend(w, f) requires 'w' to be a Comonad");
    #endif

        return Extend::apply(static_cast<W_&&>(w), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename W, bool condition>
    struct extend_impl<W, when<condition>> : default_ {
        template <typename X, typename F>
        static constexpr decltype(auto) apply(X&& x, F&& f) {
            return hana::transform(hana::duplicate(static_cast<X&&>(x)),
                                   static_cast<F&&>(f));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXTEND_HPP

/* extend.hpp
fpiP9xefon3g5sk1dx3GyfLmFkX7FLYDWsYgneMbb7vfvvRGyacw9v70y8Hvh79tEw4S5kVvNOz8re0dHm9tQYslKCfAxf51AHMTT3yUJ94/t0BzGZzDUGDax97OLWw8s/AEno5vg9TbGYPMjnM/jsaf4mBOLwSoFg4wDLIHbwchFd/QkveS6//y8Qd8239/ePg2jMM0GveuSVXawddj1ANS+OLLCaIZ5CCp+4MLYCBvB4jgR3GUz/C311736uLixPXNOJ2t+wRIMslmSe6v+xDGkEGHwcT5ZXmIon8xTPEZ8GsH8G4lcR5+zgWS4pcCxLtkBv/CngVSz8PBRsEs+gdsvMDoJzT/KGJw26Hd/T4NFt4igY9BLUC1h5GAvSvDyRf4LfKUEPLpc5zkuySaeDvw3DlRPojxOUw0AZJTQd+MowVs5H5GQGAI0BlzhmQHRDtezrmR5D2ca3/YHjVHo8Gw5gd5njY8P5p8hr9xOPDPXTCDv2dhXEeN5Z+giQKw1nsfm3ROr0ZtwhaowM3r3gsQHAii/uJF/aSsx0Jr+H73DVELW+EPjg/dWrBsvfgQzJbcHhDcsLlqvZxR8wtYkAgBB7cewq9bX1DBnYW1g7qmYKs9GPnd8H4UzhctWB+owYDUhWNBxRtD0l5d
*/