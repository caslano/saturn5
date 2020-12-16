/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_20060128_1423)
#define FUSION_EQUAL_TO_IMPL_20060128_1423

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/mpl.hpp>

#include <boost/mpl/lambda.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        template<typename It1, typename It2>
        struct zip_iterators_equal
        {
            typedef mpl::zip_view<mpl::vector2<typename It1::iterators, typename It2::iterators> > zipped;
            typedef mpl::transform_view<zipped, mpl::unpack_args<result_of::equal_to<mpl::_,mpl::_> > > transformed;

            typedef typename mpl::find_if<transformed, mpl::equal_to<mpl::_, mpl::false_> >::type found;

            typedef typename is_same<typename mpl::end<transformed>::type, found>::type type;
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<zip_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : detail::zip_iterators_equal<It1, It2>::type
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
93p3h0l+1B8Yf70e1tb9HvUHZsfs04kO29F0YHy/uwuirNHGmcRvnCcPdqfexX6p3kF5NFtRd8X6ZhBaOpgnfw/Ye6jwO7qoO9OxfF2au6gr8mnwCTSbteZz79T/UxfKBYw/f+7K7XvRgsAczH7TWWhE04KVYFbq27JxaLFg9swellp2Bi0BrCSzDo+jk9FMom6DKvk9WioYf8Y+33zygfIU57y2tspHtAwwfida1ln3AC1L7DcvMGIeZQ3Gs85/f703ZS32K3p1uQKtAEzFbPSmuemU9TrzOr/982+iacDUzOLtStRCCwFzZrZdp7+CpgdzYvZyV0UPtDhRZzdx1g+0RLDizMae9vsXLVnURZ6ymo6WDmbHzHfxPHfKE8yN2bboGCvKTNTtnd8ggDID82PWKDz9LeWy3rwus99/eqIFgvG6c8HLYykXMD6HMI8zjpSLqDveflJ1tCRRV+Nt0QS0VFHXwj97L1q2qDtdc08MWh4Yz6WIe/sFaDYbzOseu4yqQb2DuTObH76G9gsRdeNmRVem3sHUzKb57huEliDqZt17exXNCMbP2arOjy5oyWAu/M6XDx+Ili7qlIun5lMuos6mcsN6lIs4p3tGxx5oqo3mn2nTVIMoMw2YN7+7KZpDaFpRV3lpYHHKBcyHWYihiBLNAGbHrLdnTiTlAlaCmd9fuV3RUsHsmXm6Rd+hXMC8mA27M5fmkCPOmeqRdYByEf2tW1R+BZp6k3ndxiLOjmgBYDzPHaZ2KspF1I2t1pdMD+bJ73WPyTvREsD4WfLuLzGimcB4nr+uT1uCliH2a54/8TlaNpgvM0PjQR3QFJvFn1O2XJtFcwdzZ9YsuhLlEgKmZLZ76teWaDowfs5lWdtKUn9gfszsPy0qTf2JukkN3/6i/sBcmB3bodpCsxU9FLHyjqD+ks3vWZ3tnfeiqcD4WS7/s4bOGQTG92swoj3lqQPjeXbN3HeP+hP77R3p9h0tEYzf6yT/EtfQkkXdAMVK6iENzJtZa6/r7tQ7mD2zXvVK053IE/2d2jxsPJp6i3l/HdYuro4WCMbrdqnPZqPpwdz4/KqdjkGLA+P9Tdjm0RzNCKZk9rx2kdk0dzAfPoebVXrR3MF4Lq47Gz1DywYryWyxa8UnaIqt5u+pI/J6TabewTTMns0ZWx8tBMyV2UnD7dvUOxjPxbnKvCloBjDe38gJ92g/IxjP5YJvxSi0VHHOZ5f/qU69g/H+Ki3f/IpmK84Zu6YB3V2bbeZ5TuzoPolmC6bk+82MLEa9g/H9nt/1nY4WC+bO7ETfxmXREkWdt3fL+dQfmBef0SG70mhZYPyzYpjX7aY0W7Hf1e/1vNA+ibqKFmXz0RQp5vu97j3nEpoGjNd1eOpdFy0gRfyZqUdKGzQtGP9sWiZhbSs0HZgHf0/ds0qDNhCMfw/4mfT5CFoCGO+vY40blEsSmA2zp+1a2KMlg7kwa6xU7kdLB7Nl1q2etjdapujh49fMMMo6RXx+WTPIirIWPQR4rjhKWW83v7tld7yvgKYGs2eW+MDZSFmD8axrn/t3OWUN5sDMrVGzJ2h6MB9mDVtsW4FmAFMyG+eaUg7NCObHrIH75CloaWB2zCalnL6OlgGmYRZot4L2yxP79XAplUO57DB/HhrUdbem3sH4fva++qVoQWD8nL2L3RqBFgXG5+evb+GFFiv2i9rVaD/1Dsbn9ytN9RotSdS5f9zaGi1d7BfTuZiJcgGzYmbX+dxGumdivyP723VGuyHqbh5Pa4CWLeo29P8UhJYDxu9STf+qd2gOYDbMDrlMP4L2Q/TQr3m8E5rNTvM6TYyS7oQbGK9buzfUB00Dxp+xduN8J6I=
*/