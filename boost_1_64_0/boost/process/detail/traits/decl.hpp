// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_DECL_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_DECL_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/none.hpp>
#include <type_traits>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handler.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handler.hpp>
#endif


namespace boost { namespace process { namespace detail {


template<typename T>
struct is_initializer : std::is_base_of<handler_base, T> {};


template<typename T>
struct is_initializer<T&> : std::is_base_of<handler_base, T> {};


template<typename T>
struct initializer_tag;// { typedef void type; };


//remove const
template<typename T>
struct initializer_tag<const T> { typedef typename initializer_tag<T>::type type; };

//remove &
template<typename T>
struct initializer_tag<T&> { typedef typename initializer_tag<T>::type type; };

//remove const &
template<typename T>
struct initializer_tag<const T&> { typedef typename initializer_tag<T>::type type; };

template<typename T>
struct initializer_builder;


template<typename First, typename ...Args>
struct valid_argument_list;

template<typename First>
struct valid_argument_list<First>
{
    constexpr static bool value = is_initializer<First>::value || !std::is_void<typename initializer_tag<First>::type>::value;
    typedef std::integral_constant<bool, value> type;
};

template<typename First, typename ...Args>
struct valid_argument_list
{
    constexpr static bool my_value = is_initializer<First>::value || !std::is_void<typename initializer_tag<First>::type>::value;
    constexpr static bool value = valid_argument_list<Args...>::value && my_value;
    typedef std::integral_constant<bool, value> type;
};



}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* decl.hpp
aR72POF61UjC5qaE8tPuKfLpgbYBole7VeLmS93mSByXrOX7RHWkLjFc89H6O3RdJc8szzss5HmAcJsntEhf+t22+ntlxyHlJHt+yT/+hIyxEpbyvYMwMcvaf+9KHQ+q/vOPkT4y/rxtdkm7+utryhefRnwLy3flUpJyk0xbm28lzauGmX+Iut6t+a+xxGepMWWNv7RIf+o3JM03RV8z1vOhrxllZ/WJtE/tM/PIdd7aiMCXupmNncEw+29HaXuClwm1Y63+04V9g3vG+dgLlgr4JsFbcaadQDZxgy12Bjv5O4NQ2Jf5wvyXH1J2B7tI8zYhUx2nDLJ3+DuLUEb5JCeZtggii1e+x9dfgA3Cqn2mDULfD8/X+3dUMqvev5mSWfX+jZTMqvevq2RWvX9ZJbPq/aOUzKr3DzFl9bXNwAfn6/1fEZmp91/3YWG9P/eAQnr/Ax/8Nr1/rFU/r+5t8cg+KsIfeLetf2+MXH9cL8j7y/5RvT9E9nfo/az/K//f5nd55RNueu772GbdHv3x9aQZtattKhP0/50c9P+9YP/f4foZgr/9vr8EtcaCrHvv5SUwAtaBJeGlMB5eBivCurAavBzWglfAxrA+7AobwGzYCA6D18BjcKZL/U5Wv/MLYCZhEnJ55jbwu4O3wWGwE5wEO8N5MBE+B7vBbbA7fAMmw90wBe6B/eAHcAD8CA6En8NB8BAcDM/ADHgW5kEPlRoKQ+FwWBKOgDFwFEyAo2EVeCesAcfCenCcsj+YAK+DnWBLOBm2h3fDTnAq7AbvgaPgfXAy7AnnwF5wPuwNH4az4fNwDnzJYncwD34I74cH4UJ4CC6Cp+ED8CxcDMsqO4OL4COwDnwUXg4fg83g4/BmuBT2gMtgElwOU+EKOBw+BcfAp+Es+Cx8BG6CL8LtcBt8Db4PX4efwB3wIHwT/gTfgiWUnj8W7oLV4NuwntL7X6X0/dfD92Br+AHsDPfB8XA/vAd+CpfAg3AV/BxugV/Aj+AheAwehmFKz19O6fdrw2/gDfAI7AC/g0nwezgEnoJT4Bk4A/4E58KzcAU8B59Tev110AFfhC5YAEPgqzAC7oFR8CCMht/CEvAkLAlPw1hoKH1+SRgHa8Ky8ApYHl4JK8AbYEXYAlaG7WEC7Aovgn1gFdgPVoWZsBocCaur72j8kr6/zM3Eb3TptdDrsT98Y1Dn//+i8/+r+HUGdf5/bZ3/TOasZRuDev/gFtyCW3ALbsEtuJ2v/+/7B+r/f6+1/5vZ6P6RBer+kQXq/pHZ6v6R2+r+kdvo/pFZdf86f8h5ennkWv/fsUsbdP7EaHmYlndt0awNz7NKHq7lnTrf1qF9S+txI0zbAS2L1DYHZtlRImvX4abb297eyZI/2rpmgJKVCFwzQMlLFvbp1/JSgWsJKHnMeWsJhCG3t0vYY/H3r6d04NeIDhz6/f13a7uEX/yuwJw9ouPlPF2pZGjkRNaF9QOus/f5310Mn3+VNkB/rHWAOe964593RxDfTOmJr1b6t5ES94y7Dr3RgjPbGw6HU+jdxRztScJxalneUZXvTCa4YiUfmkqpfz3Dw7VR1Jr5LaXsT91F+d4nSvxr7qL007sL+/gOHeRdMSPb9JmuI3UIUfv+Onm0TrW/lP+y20aHrNc0WPSerPnumMHIe5u8BwllcfqoTfCv+37JXm+aFawz0MXh1z1fKmWfddv64SvdfyNJ8x39rtun15qu/77Yg2j/+ARVn3Q5loejR5H2CuMW2NOYY1OXpg4bvbe2Z6glx3YU5R8vepgA33d1DGY7yRvnSXQO1OtO3yv1bal9zjtJmnfddj7vZaAh8bU977qtuuPBmSl56Xk5hmk=
*/