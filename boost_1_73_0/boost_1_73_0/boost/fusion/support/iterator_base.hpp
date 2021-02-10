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
CTtASGUMuORi62++vhWk7kleyeXKM7tNnxWLT9OnQkSZD54Zd82K9yhLjmnNttx2Lcy4w2BUBZ7ReK3sFw0eP6fnvumF1mKwNX1WmEnR0pqwije8geGqjOYrrZcgyzdhpRcPaceqOL3Z/bLlTIV48W3sBYoJ6EFhK65zoAitBWImdwGIhrUph1UNFXowDyOwJjj0YDZLE9hagQEACxLfghlAQ2JNxZsAmi2AHbD5GoYzYNF4Hg8xxBJEYR7q7BAWtxBdNNrNEfA7jHmkaXAH38nnthTk2b56Kd8C20zUgIIiIwwa/HsOjcnw4wzAKwxU4HhGCKoVMNm4ogJ7/zPXWZ61MVoUadokMx1JDIbNBpVokUbK4oQgcxCGJNsBtwP+lSDdmXgPRZwIWAJbIjcyQqWD4USxLzmdR3k4ixw+EXaKkgWMrEWs0cMAKC9CVmMdkAXH5f/V5dXbfvfiFEmKtR5hhGsM40dAzOKiFWpa2xLc/RRMAXN2aOceoy6a6DpgCzALwlQtgM+Wy9bbOiROoLuIchKMgMpH5LKqR7j6dRxGDCGhbnfUDgLe6VCkUL61m1poQVh3Ot6o0H4ReRW6YPa1my87L2LyU9h+TQfQavRQ9Io9OJiaPPU68nMwZa97bzrq6ZOacagWLIYN
*/