/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_IF_07162005_0818)
#define FUSION_REMOVE_IF_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct remove_if
        {
            typedef filter_view<Sequence, mpl::not_<Pred> > type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove_if<Sequence const, Pred>::type
    remove_if(Sequence const& seq)
    {
        typedef typename result_of::remove_if<Sequence const, Pred>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove_if.hpp
MLJTvuI4T35JwvInbMEHh5KTr6lEiDVggSpsrSuta8fcURoPbahXaweOA4PoE19hpQcRAQiO0nW3gH0UdvoCLC5Tc2NXlMg5oFjQCLJbhmor07r1cgt1kkTWZZf5xyHRIlmAm+syFVMQTtG1lKPKI2SKoyKt+C8OESv+zRh3wtMLiJTkl79thlm6YbWPVaZ/d9EPF/obRfon2BXQWi/CsZTx2KMtUnU6rP2bdd+o4xDKrgpLu/v6Tx61xNVExhjOs+o4b69sD4mGwV3UUhFKbAuYePfzPMu1/WGNtpuJYVeBGb56Pzh5sp+Qo9rO04Ms4wzgplZoilxtUE2RbM5FFNLcG/ZkhEG+NJn9uWijK6cn4yS9+0m+L9VHW1XRDDz3nc5bOkM6mwlZn7Hi0R/AbtDr3zGi3GXelA0mmQtcWb2rP83KbHjZzTQrDwXhrNwTgrPyjo0iCvqeLJqV2S6zLVu4vcqDuoNJ5lpW6WlTSXAgz/IaIhwdmgRyk2IoemHbOuVAwAgswRtCDWo9OsWNEmMw5j7mQvvLCJw1I8FhSZ9uilfC3QgenITZ4tpAW0csiTIbz5rYCsA/MkcpmDOg+KKxsBxqGBosG0aylciy8XJbH8XsLg3iUQKK2JdLDx3MHlrXbUMTHGgEDnSJDVT3hUW6YNnwIF64CBfetmwYjmf1cPYqxUsnQ6X10ieNtPbYCYXRUzGDw9vIXtzl
*/