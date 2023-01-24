/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_02122005_1839)
#define FUSION_FILTER_02122005_1839

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct filter
        {
            typedef filter_view<Sequence, is_same<mpl::_, T> > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter<Sequence const, T>::type
    filter(Sequence const& seq)
    {
        return filter_view<const Sequence, is_same<mpl::_, T> >(seq);
    }
}}

#endif


/* filter.hpp
20fYRA9mtUiziyKbzfGiD9kcGEkKEluWyhKlmitROBVvq9xg7KGTWy/g1p3Yuglah/qkfXCB5LPVb+4lvRc1SgdxJ4N4uQTxAgnixJ7aG2IliPf7QHKNMqB9C8ZRhm+/RqHtXgjwXR5l7F+ByApMzePp4e2/X0Od2Uo9dPHaKMKe+40I8xZGmP8fb28CF1XZPY7PsMk+uExibmialC0kWiBajIINCYqmibmRFlKZUQ425YqAMd5GsdXU1DLLNrNVFFNccsnCNUVtUVu8hJaWGq7zf845z3OXYWaY9/1937+fj9y593nuc8899zznOc9Z3xIMM12qFqzykcRwA83uOF4n7ZjKEbfOidZ8w2p+Rl+rag7fudLpJ+KUf+85XPN6RhBsyRXYyb7Prtc+C571WkW/npA1xeJGiGGEXt4kWI2mK/GpBNFVcDXG7IPmELMPNar8G9B8ysG5auNZXQoUH6QCjb5fo9Rf5iBbPREk7QntfE/YfSCKpiA7aLyAwQk4bwUJHSEfodDh+hAP9XQ4+yE11vLjb+/j5Z/eh83SyDsod8gePBtwh3br1MJBW6fQFbR1WskHqH+b7dMW0eCn3sbDb+yAERV5DkK2g/SzkMuEP2Hz27h3q3ybBhlDUOS871k+Qh/U4LGBinxUEAy0eSYTinVZQUi6yJcvYu8ZwuiIBIMJYIEK85qobENOGn0BCaWKM9pmsM0TjRFs
*/