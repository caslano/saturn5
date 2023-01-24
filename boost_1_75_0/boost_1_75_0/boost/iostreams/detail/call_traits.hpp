// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

template<typename T>
struct value_type {
    typedef typename mpl::if_<is_std_io<T>, T&, T>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED //-----------//

/* call_traits.hpp
U41NuYJZhkY9lIBOSxK2PKa1p9ei9/g8TyPW2v1E/OxiTnG+8IqvdhoLp67HzYKibfhjco2CugItqpKKZarSpYa0V7wDzVASR4TDaDOvvoClP0hpP+tGnRows3QlSP3apAwuwDug0vp2TcvER0FW8AUxuZ36YqqX4Ai+LEzJja1t6PefnikbnCo8Tb1ZNAzNBU1APLu3X2dRAB/pB6mXWTAyoU7SOh6kyCo1NoMrg3VjtprJYrlFpLnQL5chaRJxNstTRl0ODwI8VkGtcOK/Oct0MkguDeOmDrXwOrJxNkWU2JQA9q4cwrp4obd0OEkfKUC5ghTRxXj6OhCKsJJ2vFhnk61cDBL9/Ei0JS+4rSfeGOncMX9RuB40Gz+thV5AeigufeCDeaB3tOkfMoy8/TGHOCAOQSfR+gPTorUZvyNrZ/ma5Wz5g9WaZy/u76oTuYDY+X8kuxW5V4xia5vglOeFpZrVRbre9F86ZewGWf3o7afDbTaUBee+PlI/Uc6vBLvg+xGAJ9ulpZ9ElKy6kkQYap7Hu2KS3uOTSSeVV0nNr8a1LylB3jzM7/SMAIMr19WT1BBjLpefpniFAakEG+Vk0+dWpaspnd7RQaagwUtV0IR4eaUJTGs+wXLQjlb7JYP2N/iQI7hqYdd353blDZNtoSbWD7c+Hx2K9RYfsIOqyRr/iMN+r92fLMfcA48s83IVL/PvyHqeNThR
*/