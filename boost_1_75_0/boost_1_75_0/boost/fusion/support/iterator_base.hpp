/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_BASE_05042005_1008)
#define FUSION_ITERATOR_BASE_05042005_1008

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_root {};

    template <typename Iterator>
    struct iterator_base : iterator_root
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Iterator const&
        cast() const BOOST_NOEXCEPT
        {
            return static_cast<Iterator const&>(*this);
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Iterator&
        cast() BOOST_NOEXCEPT
        {
            return static_cast<Iterator&>(*this);
        }
    };
}}

#endif

/* iterator_base.hpp
btbb8R9jagD+eKE51fbVejpTI7vZz4oEu0/Fpl2M8Xb8+ZuyFCJt4Dp3S01bHYc0tL/jMw0d4PhAQ9sc72roQMdsDW13vKahwxyzrerFoAhHf014jKObho5zdFbxi8WixhovtlhUQ+MlDXAOD40XK+W/flV7sXWWnzVebLnllMaLHXUO2Kiz6znC1Fxw2zsGc0F8AqV/yTyXb3qGCescshkZ1/JdGabzGUR8XMvE0fJa7tnRXEU560Xl/o/b796Rp6kb1//l8glzm3BfcGaz5TC9y1po7TLbmM2pCwxNCozNX9TshPFSGyuxIwqkKowa4sLciqF6H5lIhFZNxw6ezt/3841rVbLcv/0Lm+FnSO536uTKXy95hfzZUkiulAd8wqUf+V+W3D3InS2525GbnUl+zsHcVsndiuL0ldxV6RkW/z8Cc9sk/7dr5irx5+a4fNzcX2iT61xCUyPc3/FnZKv5ap655dEPQ2668BInbMtReKEtoblDdD60rr4Y6NgQPWYDTVnIyhkxq78V1agMvphrrgxurv3LzW1oZg7lhhqlor85LNIg2odznh6tchFBAr98bKnd9fIxq+PKR2pZH+UYm6OV7YNyXAT5+eou6/nfaLyYsNyh8WKCvGyOiyB/+Ifai53luPOj2outol/TeLF7Pg9oXmTfU9mjeYptrjpe7Z7Ki86kPH9Tvj89seCOvJq/uKbr6iqq2cTS
*/