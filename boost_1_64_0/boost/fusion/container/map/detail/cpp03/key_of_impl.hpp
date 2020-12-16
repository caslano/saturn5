/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::first_type
            type;
        };
    };
}}}

#endif

/* key_of_impl.hpp
42Eq7AqzYG+4CPaBi2ECXAL7WfODFSr/kEN+sDXs/3PgWmj2F2wH12uc3ADj4Y0w0P9Vqi/Hof9Xqx1XqR1Xqx1r1I61aseNcCbcAGfDm2AmvBlKj54Z2TcOen4gPT+CifAOeBncCq+Ed8K58C64DG6D18IKuB7eDQP75Zj0vOywX85gvXPg2bAjbAH7wXPgLHguzIfnwc3wfPgAbAkfhq3hM/AC+DxsU90+PTPRZof25UvvYtgWFsPe0Kd2lsCFcAksgaVwDVwGb4DLYfB4lJ59Dsfj33S8HIdt4VfwTvg1/DH8BlbCKOrbDU5Re06FinHUMwjXb4cYxyaN/PWfBi+ATWEcjK62j0ZFtu9Psu912feO7HtX9r0n+z6Au+GH8Bn4EZR9dFZk+46q/k/gBfBTGAc/s8aAavsUh+0P6Lz1KhwHfw8nwz9Y81Zq+185HH97tX0gv+E+uBQ+D3fBFxRb/GIwJlr3ynCAQ0z0ROXPmwL7wKkweF3Qdt0dthum8Xax9s/I6u10n8rfHLYbrbybY+FQOM6yX8u03acO+zVV42K6xveVGlcZ8CWYCf8A58K3oQd+CHMs466yNPJ+zVX9eRp389WuBXBgk6haY2oTc6OjMpE1yFZkF7KedXcVOsfbzvHaY269XuoLibttTAxtOyQQf5u42DkG17M4chzuBv62AzmAeLo1UUwu6x+k9UVsg5TyOw7WFKM7oag6TndlkT1Wt6KIdiIHka+QgSwbUUw7kNA8MeuL7bG7lcXh8butff4Y3kTo8dljeVf6qAcJjend6aM/4YswNLb3qM85vrddSXiMr6eEdsCVcBPyVV/qhq2NGF5YHfeLLKmO/R3Bv+cggRjgNfx7KxKIBa5aUh0PHLW0bjHBI1gvDTmaQH0wEBu8dWlofDDbLPXHCB+D3VgWXQr53Qt6YFpIvHBaqT1m+F0kcqwwZP1dyEHkGBIaM9x6mT9/TgoMxA17lvljhzcta1j88N5ltccQH2GdOFhTDPHA5dVxxCn8Ow9Zg+xAJrCsCjrFEr+7vO7xxM1W+GOKe0EzrhimwVJYjgRijB824ovhQYc443Yr/bHGAw3yOx2uRM6bwLbQGnv8ML8T4SFIDDITBNVxyHGr2JZlE6A1Hrl0VXVM8vERjYlL5vcqdOcSe45E50VHJSApSB6yHtmB7EOOIs3mE3uNJCM+ZBOyGzmEfIW0W0AsNzIHKV3gxjK75cTLd+X/z8freDLe/zf8//idSN5t8e8bleONzvJEBf++Puzvvqz5+X5//SGLv96nd/g/0Nzj2/IbxsyxvrOK97gO87Zh73Xbvj/mKzQ+g1JSZH6nKKg/T/7vX8Jz4BNwhvEe/xVW/XMNd5qpP73GOb8mLbZnmNvFFRT65jHBiNmaJw765qr9colBv7Dp/vPML2K57XsU8/lgU5avsMg/n1hKxWnYN5i/j7xS84m2bzJlezWfaM45v6h1usZo/lVtPqg2P6L5xUr53isyWd+Wu2De/KJiX639Hv5NNJs+nvmd9ZVnherLzyquw3vttenbJ307NKbuRS5DX9ncUH18Cq4O+kLHleabI7e3sbP+zOxQ/d6inCUnX/+L0n+f9FfomEr0WPUX5SwqXJJTF39IfY6rYB/IR++VDQsDx3WO1YYSL9vOa4gNzW02zLfN4++T7isaKSc6TDfGd441tiTbu6wOeUjPsb3rbky3+5fFBPNyFBdlh/g3PPL5/0OxO8chbef5ydBvOylyYqt/2+39n11YMI/cF77I5w75Fmw5AkbqWBwm38Lh+WG26Tt+dfF14NOoRa9H8QAZ6pNZ6pOEBaF6NTAbMCbUL6F2uHkI3DwE/zd5CI7NM5Y=
*/