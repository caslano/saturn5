/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_DEQUE_01272013_1401)
#define FUSION_MAKE_DEQUE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_make_deque.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_deque
        {
            typedef deque<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T>::type...>
    make_deque(T const&... arg)
    {
        return deque<typename detail::as_fusion_element<T>::type...>(arg...);
    }
 }}

#endif
#endif


/* make_deque.hpp
HOqUX4TGKpv8HMbzOsDi5vb6vcW1RebkB/WQNfdn63GEJtDzIEo/s6gLiRQVOtsq3C6j79/0hGIHJQON4hrx/UOPQoMxNEByijG4Ue4GelepGn7Rumpn33VY2QSbx1X1iM1/tCpNdVnujHRDQT1dv/Z7bBqWhFGkm2yPeouC7kx7zHrPbHBoRl719ikCbT2Bzh8l6I5YnXGmp1ylZtAQYi054waTVSK5kRjIQgvIoW67JNFpV+nXcrRP+jRSY+9znd6O8Nz9iyMgeO50qSN8TpqvDFm697oftpW6tU5viF9fY8NiOdNXBxODRZ5Adkm+S9wKsrI8CRRt6HvZ7+AKlIIdDj4Zi7CXntSzFtNHIsl8K/Bu24JrkEloiIws/cekQUyjtjqEiclPw47cSscxrPc/A3OsvnKSlg1BJGxgKoqUitX3qHARGLN+nc+rvnO+z4qvDT6mLnViFTgfvxHXcQcRLsF6YweSjrHX9sebP4lacGV1OtVMyFEoo91W4G5A9Sj7w1LAiaIo8QrKk7jt2/vH4lth/LQch/KzeBz5PADLILAzXJMC8J4nwA==
*/