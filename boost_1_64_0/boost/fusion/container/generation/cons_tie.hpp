/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONS_TIE_07182005_0854)
#define FUSION_CONS_TIE_07182005_0854

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace result_of
    {
        template <typename Car, typename Cdr = nil_>
        struct cons_tie
        {
            typedef cons<Car&, Cdr> type;
        };
    }

    // $$$ do we really want a cons_tie? $$$
    template <typename Car>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<Car&>
    cons_tie(Car& car)
    {
        return cons<Car&>(car);
    }

    // $$$ do we really want a cons_tie? $$$
    template <typename Car, typename Cdr>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<Car&, Cdr>
    cons_tie(Car& car, Cdr const& cdr)
    {
        return cons<Car&, Cdr>(car, cdr);
    }
}}

#endif


/* cons_tie.hpp
qP2UUlBb/k5ALB2vIMMvjVhU4BGPAz13xo4Dy6gdybQRGWtGSgRv/GWUEkphf2ZLgQ4G/DPPPetoxpAMIy11l44de5Y5YCpLQNIWRYS+q47cS2yvDywkBiS3NdO4hLPrNklKv9fREj9Y76kmU/g4l9NZbvVxSXuVzu34JsXAQjP1XCHhk1primtzLOwenWsN1N7MOoqAoDNfQ71xf1IN5PVs9TO1ADS0tK8V+hZg1u5arDedeE3QKuKSI5/wju36C1uBEDoP5Eb15ZV4N/neppEjpQ05hWRzvtrBa1WwbwriJQ1saAyjG2vf/oHpLxDB57gBy5PUnhm063x4u5BU11UQ6Kz32L3r2rUbDvioiPsmETgzBzfdQhj9k/lcZPsp+KDBflTsNtLEbviN8e3fj9HgYIBpn6u5FAZmJ27trk+vKhroUa7DqV7o8uLzLjkAbT8dQeGbDEzXRm8gwvidtlf25DduhGJ5wJ5MzZYx1a2v5o6Fcuw+OPmK8dT16vaPERrrLqI4YSNl/IaeGxVaCI7l/OQrepEekMAvxWAayzqWfx43R6JYKDI0sQ==
*/