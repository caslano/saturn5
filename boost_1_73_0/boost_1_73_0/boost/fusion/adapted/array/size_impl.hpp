/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template<>
    struct size_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : extent<Seq,rank<Seq>::value-1>
        {};
    };
}}}

#endif

/* size_impl.hpp
agUAALALAAAvAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9USU1FT1VULjNVVAUAAbZIJGCtVl1v2zYUfdevuPBenMKV03VA17UrpjpqqtWRDctpFyCAQEtUxJUSPZGy46377zukpHy1Q/tQB4nky/t9z7mMfzmiR9/t4/nWHX31k7rfFB88B6Nlo/7kmfmyQZp+ou4Hhpd4fkOoKd1afUqP6JusPtHYWaV9rJf2PU2/IdylTdL+mVrjy9S+QtJZ9vYztT004qo0NJ4d0ZPnz3+mx/Tj8ZPnEzphteCSEsPrDW+uJvQyd5LfSnZ97Wv+akLcEJP+PYfrUmjSqjB71nDCuxQZrzXPiWnKuc4ascEXUZMpORVCcpotlhdRfDqhfSmysvdzUC3pUrUyp5LtODU842LXudmyxpAq4AH+c6ENfLZGqNpHeE6GN5Xu3dgkmNSK2I4JyTYIxwyVxmz1L9Np1jYSlUxzlelpNrTCL031oKoLZFOxA6mtIaOo1XxCVn9ClcpFYZ9oEYTbdiOFLie3aSFgnU9VQ5pL2buDqeC6K4FT0ndrYjVpi+yFsQ+tam2j7UtV3VNEW3tHRdvUCIe2QC9XaPyE2jrnjdN3jRii9F12Lf/KyG5zz0nV
*/