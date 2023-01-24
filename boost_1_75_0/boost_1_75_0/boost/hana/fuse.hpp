/*!
@file
Defines `boost::hana::fuse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUSE_HPP
#define BOOST_HANA_FUSE_HPP

#include <boost/hana/fwd/fuse.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct fused {
            F f;
            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) const&
            { return hana::unpack(static_cast<Xs&&>(xs), f); }

            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) &
            { return hana::unpack(static_cast<Xs&&>(xs), f); }

            template <typename Xs>
            constexpr decltype(auto) operator()(Xs&& xs) &&
            { return hana::unpack(static_cast<Xs&&>(xs), static_cast<F&&>(f)); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto fuse_t::operator()(F&& f) const {
        return detail::fused<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUSE_HPP

/* fuse.hpp
n+fH/Z+PSz5fRGWSTWTRrOAK56KWskVOt5S2nPaiCNqJWZFWBgClx2gmUg5zO6AWQuZ0f5p76r4rijl8lNdQTFw7uwkTZCwnJYixpsPTyRe0cJXYCkotFz4eX/yRqxDZ/LvhpyLpUFoSnPckR5xh4fYmBPqYIHhQlF77efrWIJMIIuP/BZQhQlAr+ygpZG7dZODGxbuQ7jaqbEvrQcHJXdaW7REdfN/AFehn7NzQu0x5jond5v1IQYQREYKM7C8MuQzNTUpwGd7FvXAEob89tXIxakY2ZSozTbAVaFjv5w6tF2Ik3vZk2VAEjv8ki9MnXo1ELk6Cag66pTpuQmovydU7tL4y+T/OO7yKbMpxtXDaM/hQ+382xVZAasebAVv1CnlOkNzjikSJhSBbPk5cQv+sSsHJ/i16dTaXNOoJmyIee3TGguRc8FEGuNm3IjEP6nKfECi31qPudjqp++tb6zRVV4SOwOfceLagr9UkYblt+2pXP7Su3nUtrlq5zFKLFEc1Ao4dSBl0zyKjL025zc+ILxMbWkMdLqm8L56UI4FeQj49l5cGRNccH62IsTiG4Ngc7jhaZrg+Znymom9R0ZnJnWyTKW+K13/rbDVuw5KfcNdHJnAk31up3erSbnucCp5xvDRuac0/6fp50qVZRb0tT5sOknWM7cDFZh73wkZKLe0xOvy95jaIZZVsT0t1XH3kdoxMkDQXgXrL
*/