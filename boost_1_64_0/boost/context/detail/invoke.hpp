
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_INVOKE_H
#define BOOST_CONTEXT_DETAIL_INVOKE_H

#include <functional>
#include <type_traits>
#include <utility>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

template< typename Fn, typename ... Args >
typename std::enable_if<
    std::is_member_pointer< typename std::decay< Fn >::type >::value,
    typename std::result_of< Fn &&( Args && ... ) >::type
>::type
invoke( Fn && fn, Args && ... args) {
    return std::mem_fn( fn)( std::forward< Args >( args) ... );   
}

template< typename Fn, typename ... Args >
typename std::enable_if<
    ! std::is_member_pointer< typename std::decay< Fn >::type >::value,
    typename std::result_of< Fn &&( Args && ... ) >::type
>::type
invoke( Fn && fn, Args && ... args) {
    return std::forward< Fn >( fn)( std::forward< Args >( args) ... );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_INVOKE_H

/* invoke.hpp
GL24G/VC5F30lKbP/y+kDPHNNB/QcQF96PKK9t1IKVcf6CjvGyRgDfp+4yc9YGTxa5Wd5BUC3pj/38KYeraxJb+DsnfKnQjRby77B9Mv9i7En1T/4b4K/maaN6j+rLIE3bVj7GHTvpvrfN28MnhvmM8dqHweNfL5myn/d22D5Gl9O0Q+j4nMH8I9ZUPz34bm40pT8ggOZ5wI2hq+J7v0MHNPltKrKu1Dp9LZQr47lylF6bfwYE42q1X33nVOFszB2H3DRQXxlw9r5T1hoOcx/PcJ4q0EH+S1J10rqW6NrhswXr//vKpyGs3R9wTRf6fXOHtz3e79zsG07M9J/Z7Wvz5NFINzSHNapzc3K7cPcXhreE52BLSn5gDlvrP8XIRtzhw7J9S12Er9ovMPWP8b0J1OOZO5QvbMjgLeW5H3gG0Eld+bOIh+/C9tVwIfZ1XEv7QhLZek6UHoAZukSTe1YJsetEVreqRNSpvGJi0tCkuabJPQJJtmN6UtFVCRG7kUEEGRQw5FDgG5BURFBOUWkFsuUZByKnI4b76Z/f47+22a4M/+ftt8b968mXnz5s2733M29zmxOTinqHWeypB/XB/2iPh91MIIhPG+X8F/aUxmf39kJPBZLg36LDrUxjJQOpSB8ZIj/HOce0b8H56VLI5gP1nogi8bq/FCa5tpg8YL3z0k70hrb0NrH6C1NWS8UxLJccfmAMuS1wAjwX6Y7eC7ygWu+qtA2Qg+SWWTOILLvLm8tRQJfDTBQvuFnxeab++d2S/ca0RmOGnCZN+6bwj1xz/UzzSQYW8n4wgXBhsiGaZHgja2p8C0OdDGzoxkvqG71Yw195dy3QpzE7Mi0A+S+5PmuDKLBPQJn+kfEAnawBNG8FiN8Y8eofjY9y/wvqRyszy56X45my7h56Y7PyLnVaHvsBBtVfKxyNhqTSToSz1VpPIzfe6na91WnngfxBKjW0u7Lps24Q2M9oFGTzjWwfJdbmQ4b0/QI8mwQuNB3xj/FSPz/oovc1q2f90E8TeExK+GeGfvNn6N2NtleOeC8NKxw8ER6EtD/+mrETtG8dNh3TwE7Mb5sDI4Q37X3tl3XseAJo5hkGZzRM/d7njcEyZ3q6Sv2kfSS59rGthqm/Fb7cZvdYBe28Fv/Uf81gaNl3w+YPTeBfFVojeMT0B8MqTcNkq53WDOgCcj2bgpI4sdz2zSeOk3jzfnnDdH8Lyy1BMpRztXtDUC74TAuJfyr22trUdM46tmDHiU0OnCsQjl902TXxcmnMz5N0nr4vBtq29ElBb0j4H2W4a2CzscpH2C0H7L0D4+Ej6ut2VxCuj6pRH0M/HfMW31TmZu8XRjhwUST+N75a82y/4P28HvSrisKFtWB7OyngP4mlfE/3VRZj/pPMEvD6HvYDYvFyg+0Ef84Yb+hSbvVtd7GfkvNrq048VLhd6dME5W/NFF/g/xL49k9hvukvj5EJb07HfuNPL8DHzbHNOP2Cpj958bmW2/75pI9vzFSDNmvS4i99pAvvWn+A9kzEMM867XOs444KelzmMdvxF8+u4jgvngohGMm+XTbxK9rYC6jP0ta3e3giwUj/NE/MN+9O1C280ZSl9O5gw0jHOgueeF7tL+OciAcyh3gS2E9RmrTR5+i7ZC4VEjTT02OrDrFfeBDrbCnI17r68P+sj8NhXYTAnFrzCy/FFkuQPqGeKvHZGZ94eA3tsh/eFHoL+t9NCndZi8Pg42S/kInR9/QnnqPSJmPvUpGIP9x8xzP23GUiWm3j5r6pTNz/MqH9MOl+9FybOjbefEy8BPsR8x/SIX32fovSr949KioM/xN9PneN34u79rPiROZXxRbOwNw9c=
*/