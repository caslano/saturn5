/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEQUE_TIE_01272013_1401)
#define FUSION_DEQUE_TIE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_deque_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename ...T>
        struct deque_tie
        {
            typedef deque<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T&...>
    deque_tie(T&... arg)
    {
        return deque<T&...>(arg...);
    }
 }}

#endif
#endif


/* deque_tie.hpp
TLzwIuSXr73YrrnABQcsLzY/dCfD/vCqZc9AYzZ0T70O2V+Bd7Me6X47qUAsHpfGlTeskFTnP6pnXNRgT8mTa88gD7SCcOkLpIKQyYXcwYcIWtAmeEqaeXrjgFAz04Rndn5zXNsB/VH2axbJnrWQH8wU4UF/BY/s74O1/rG3lxRZPCPdAZD97K+4Hoctr7BYXrQ1SjJ3Pb5uivcH99sSVOK2XUYrLlmPIs8vO3tpxRdR3s+W5RCkdcCz3gNcmYRvf/mtLeYNQGTYS0+3Sikl/Ug97QjmQ2upi5UVANfWVzjFKaUoXrYRPUVzj1J0w8KNEI6nBaVIb4s3Qjw1a1ffJpJwTdlDYupNSkFx+UY0FM2NSdEOCzdjF9tpKzm7iIo3QjycVZKizMs2IzOf7pETmJVtRlo+D1PL/tee/YTL/RCIrCGIB9RjCwjrMJacQqnXOjGucRxclcnSKTZnZOr9f2i1+cTJkLJKO8BCGFtrUYonJkrpscyNx/JtXK+f2oTTBiq1cZA3bYHc7FRTffaicX8l/rZPfiOm2BBLaX3ljOvUrDA+ml5GmJc6LCIlorU7zJkhFhZIUItcQ+DGVrkliGXFkmWHHVVoscS+Ah0+AKhCiT9RhZbQVoq1mGs3VclnxssKmlEhUzuN6KBo
*/