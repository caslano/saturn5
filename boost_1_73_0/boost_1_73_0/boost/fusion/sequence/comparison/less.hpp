/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_05052005_0432)
#define FUSION_LESS_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/less.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    less(Seq1 const& a, Seq2 const& b)
    {
        return detail::sequence_less<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator<(Seq1 const& a, Seq2 const& b)
        {
            return fusion::less(a, b);
        }
    }
    using operators::operator<;
}}

#endif

/* less.hpp
zukb4VRVZjT6Napq7+qK77fgoHx316yeTsDLfeitOi/mn9Jp1LYOJ5OWuPjSZ8oD3/v9ezqN4jG+eXxYgtC50GRqQvrHVy9yY+lgTqRTBQvIFZvxvR10/1nN2dV6uLdN7fKc7ufCfWUu2ZawXI9VVS4NjSq0N4yhpK9jUFq6ukyAV7WRG7J0s1iSlUWOkRsgowwTxVt++ad9P1kDf/xT+2kcodtA+6I43NnyE/y+sh0PhszOr4uscegOMmk+d4gYq7H6QzRraIwDBX67yoaQ+zKlu+46K1XRhSr84ZjDLqVYWmjWb79tYOixkh1Tkx/j3wPTF7xeYIEvdemLSlDLFxl/e4TmY7JjjPmf0zEkVgTnmewXLlFJJbLlqbAE3XXRS3vKYqgaDPvq6GyHpo72kF/XkcnbBAet+9fr3hAsoJt+0B985tv5XKbCQrtIyfqgiz26qoPnehZpepyjqKM746jjLG+7ogLf5OwInxR3QS6njszQKadVlWXJJZp7iFcF5oGxp3yRZ3p3itpLFe7Q323pkFHocCcFVpBgVvi1py/uJJ8wZXzrhylQlz9QR1CGCq26gN9c6CAgO7VSF1P8WlvysnKTZc/hIL6ar4q9uo3c00EPWVRJRm8MOUzGN0UnjgiQVsdFU2EjgZox
*/