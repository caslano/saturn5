/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09272006_0719)
#define BOOST_FUSION_BEGIN_IMPL_09272006_0719

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef boost_tuple_iterator<Sequence> type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
C/ldwiNV3DFSqGvCwYv4rcCDcDvJ13E4+DV+N3Qcbie5Og4HV/O7h0fhz2/wm6b+Jh7jd0znL+FsSR2egNalnJfWA5eRjK3UDLPf4ixwP1xUwxnh8jbnSI7ps7DHf/nG1eGGd/iucVnG7wzJ0XXg4uXUpg5Pkz64scIhj5JsPAq3ruRdcF8t9ZMm7QkcS+rxMFxMWvA43Eua9X1h11X8DuN+eIiU6Trv8rtOSvEEHLeGvxfw0Pv8HbeW88DT8IwN9EdrgIM/4hmd8zG/S5/w+4+n4NEG+olHPuV3jxTiMbiZ5ONJeJQU4bLVIReTMXgAjicF+izcSerx8GfMJ3VaZyN3kzToOFxNmnBjm0MuJbW6Dmwjx3T+5w75pomea81f8vfpV5wd7odNpBWX7fxdQ5p1HI4iLbo+nJ7kfD+jZniCBHBjB2uSZepf83cKGYJHd/LPYcg4PNLMPfmGO4374Qri13Vg7v/4HvEg/J2MxH27OAdSjsfgs7v5fvEE3LuHd9Z1vuV3ey/frD4LG0kQT8NFLXzXuj68/jvunK4Dz9zH96jrwylkvdYJl6a407rmfn4TSBc8BF8iffVZuI348BSs/IH9dH14yQF+G7UGWHKQ7xmXQw4ZSHbjAfgsSele8JzDnIeuDz9p4ze8kXp+dMiDP9FTfUc47Gd+w3UOfPYIv//MMX5xyDW/8fcFHvzdITNJLh6DW0kenoQ9j3Gv8ABcRQp1HF55nHuFh+AuUoDLH5w16YP74SiSo3v9ydr/cCfxxGnez54lxbqmkSWPnJ0lJepds8TfP0tK8fDALJl9eZZEtba8LGm4KUuqdPzWLFk0Ikua1G/PkrwHsqRZ/eEsGb84S+rUl2XJ4G+zpB6PH8qSlh95Xv2nLGn/K0tqcfk3S/Z2cEoLHuvolGc7OaVdazjTKctJK56EHTs7JXMb9cMrbU45pvXYnTKqv1MMxlODnLIlzyld8MBVTrk23yk5ePI6p1Tc6pQAnggyd4xThuPpe51y71inBHG53ykFZCQegmMfcEoIj0NPkVNKcT+sJGU6Dvfqn3UdePmD7IEH4TukWveCV050Sg0eK3bKH6QE901iTtgpCTw62SnvTXFKrdZcwnMvOqUZl1eogZR8zvcFN5NSPAX7RKkBDyhJBR6D585lLzwIHyenWCcCJ81zSgbjabhwvlPsuCxwyraFTjF1nSqnyGtOycbD8CTpg/sWO6WQ5Og4nE/ydC+4jeRrPbBTNb3DDbiWFOo4fOh1pxSrw6FvcL7aH1hGWvEY/JO048ab1B+jn7oXPPI2vdB3eccpE5fTH1xWcD6rnFKH+991yktrnJKLx993yhl13AftLXyRjNFxmL/WKUV4Al65jhrwCNxE6vEkfGyDU5q0Tth9I7Xp+vAB0qD1wIc+5Fx0TXiAtONp+P7H9FnHE07xfkINOh92bKDnX+Dwok/pOR6CcWLiSXjVVnqu4zBrGz3HE3BqEz3H/V86pfN27ioegbcnucN4FL690ynjdP1mzuJ/TgnrOruoh0zFZTf7kggehBVkJB6Do/Zwt3UduJ4EtR54XP+s+37rlJV7nbIMN75zyjBSruvACNmNx+E2EtNn4Tkpp1TpOOy13ymNeABuJW14GiZ/cEpK1z/glAkkiadguNUpUa0N7iAJXA5y30gcT8Dph7ijTTg0DjvlhNbT5hTLj05J42GY8RO/D8yJ/Exf25mHB+Em0gVPwYJfnOLD47DhqFP64tHfuCPHnOLXOfDjP+gzHvjTKUfJcNx3wilf/0WvdP2/GfvHKUO0HnjXaXqr47DHv/RW94W/kHH6rBjyEQnjaWUHQ1K6L/yYtOFJ6OpoSBr3wxJyQuc=
*/