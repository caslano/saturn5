// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_CMD_OR_EXE_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_CMD_OR_EXE_HPP_

#include <string>
#include <vector>
#include <type_traits>
#include <initializer_list>
#include <boost/filesystem/path.hpp>
#include <boost/process/detail/traits/decl.hpp>
namespace boost { namespace process { namespace detail {

template<typename Char>
struct cmd_or_exe_tag {};

struct shell_;


template<> struct initializer_tag<const char*    > { typedef cmd_or_exe_tag<char>    type;};
template<> struct initializer_tag<const wchar_t* > { typedef cmd_or_exe_tag<wchar_t> type;};

template<> struct initializer_tag<char*    > { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<wchar_t* > { typedef cmd_or_exe_tag<wchar_t>  type;};

template<std::size_t Size> struct initializer_tag<const char    [Size]> { typedef cmd_or_exe_tag<char>     type;};
template<std::size_t Size> struct initializer_tag<const wchar_t [Size]> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<std::size_t Size> struct initializer_tag<const char    (&)[Size]> { typedef cmd_or_exe_tag<char>     type;};
template<std::size_t Size> struct initializer_tag<const wchar_t (&)[Size]> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::basic_string<char    >> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::basic_string<wchar_t >> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::vector<std::basic_string<char    >>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::vector<std::basic_string<wchar_t >>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::initializer_list<std::basic_string<char    >>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::initializer_list<std::basic_string<wchar_t >>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::vector<char    *>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::vector<wchar_t *>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::initializer_list<char    *>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::initializer_list<wchar_t *>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::initializer_list<const char    *>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::initializer_list<const wchar_t *>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<shell_>
{
    typedef cmd_or_exe_tag<typename boost::filesystem::path::value_type> type;
};

template<> struct initializer_tag<boost::filesystem::path>
{
    typedef cmd_or_exe_tag<typename boost::filesystem::path::value_type> type;
};

template <typename Char>
struct exe_setter_;
template <typename Char, bool Append = false>
struct arg_setter_;

template <typename Char, bool Append>
struct initializer_tag<arg_setter_<Char, Append>> { typedef cmd_or_exe_tag<Char> type;};

template<typename Char> struct initializer_tag<exe_setter_<Char>> { typedef cmd_or_exe_tag<Char> type;};

template<>
struct initializer_builder<cmd_or_exe_tag<char>>;

template<>
struct initializer_builder<cmd_or_exe_tag<wchar_t>>;


}}}



#endif /* BOOST_PROCESS_DETAIL_STRING_TRAITS_HPP_ */

/* cmd_or_exe.hpp
/TWFTjlG8jMFmvNzFUmTQM4Kum1NvDL27cbBt/j1X3cBOk6l01RrMwXqPQN1neb6S5sVX47jb8I2/j5H2EceFxXeEkdaix7zKPKOlP+KNy3hVcJ2gjfuNUmn0iqOUHrA1wnrlT7wDYLS84luMB5av0/Z5wL0fjM/N/V+Rz89X8f3hZJZdXzrlcyq47tHyaw6vmwls+rzuiuZVZ/XxpTV0zo+JbPq8+qZMl2Xakpm1efFmTJdvzBTptcIOrP/fB3fN/vP1/F9Zsp0nffsP1/Ht1rLrpH9Wgf8+41kn/tkIR1giQO/XQdYYKMDlHV6TLmkW6a/Ea/nXpHvLCQ3vzO63UYnSB24ltV6P3q9uGtjqn/m1xP+NdavWDHRK8/H+M6z+2X3xrB3D+6ddXt68fVRxdWjBtev+N9av+IY6fe71O989eyxF44g7FavRVp69V7wFlgOdoEPw65wFewGX4bJ8FOYCr+A/eEROAAehwPhGZgOz8IMGOKdVGAkHAJLw2xYDubCKjAP1oDDYF04HDaAI2FjOAo2hWNgK3gnbAfH8X8XOB72hBNhCpwE0+BkOAbeDSfAqXAenAYXwelwHZwJtyk95HY4B34G74fHlf7xBFwIf1b6R4P+XgzDYFcYB5fACvARmAB7wQawN2wEE+FNsA9sBZNgO/g4TIFPwFy4DM5Weskn4Aq4Aj4N18Bn4Db4LPwHXAM/UfrFr5Te0eHi3gzD4QZYGr4Iy8J82ABuhLfCTfB2KOtnwJdhP7gFDoBbYbrSP46Br8I58DU4H74On4RvwOeVXvLvSh/5D7gT7lH6yE/hu/Cw0kv+APfCn+D7MNzt00+Wgh/BivATWA3uhw3gp/BaeAC2hAdhW3gIdoKHYRL8EuYq/eRQpZ+cDL+Gc+FR+DD8AT4HT8AN8CQsgKfgLnga7oNn4WH4IzwCz8HvoCHrVQC1XoUTloQh8BLogo1gJGwMo2BTWAK2gCVhOxgDu8BY2AuWhn1hGTgIxsE7YTycBcvCxbCc0ncqP+hCup1y637ZJ7qA0JA0HQkDCOPWBXU8/y86nqB+J6jf+SvodxasC+p3gltwC27BLbgFt+D2H/D/T8lJ0gsA/A7+/9fY6PSRBer0kQXq9JHZ6/SR2/v/Iw/0/0d2vv8/skD/f2Ta/1+nCTP1+/q44SJr2aJ9mxbdrceIsPr7K1lkYfsC5GHI7fXq/4gz9LrgA1zKh98H3h8hS+CfN+WRnDOUmNyXXaVvRJal/QTdkqalUUG+nefP09goSU9WJNQiaJ26jndYysqw1aeTTuvTp1X0/i1VkLRRlrRRAWVm+fSaoleX9WQl7hL60WnEEaoS/HUtKXFpSPiOCAEtE33WQ+J6xMn3JYTlYNHfLFS6l0Lv+bNkP0zvZ+j1uGkL+7TFzENqkcn79qv96yooW4f1HtIpniSm3gf+c2JZWMGwt3koy/6dH4p+Hz3wJaaPoLzDvNLO5oHyi/7GYQzxE6W8tujkr9E607dEVtL2PFKevV2E0pknSvxUiy6b60Hp7qdKXKKnjKuiw6KrzOORxkaHqewLlN52luTt6gm0T4hVevZ5Et/JE+cq4Sjqe4JPSppmnvdoaw3HZ66A/pPxdk2AbcRKybOT8fZ3o6g1Cz5SOlTdnr5puTmGedzHpD9r8I3B8qypmaDkXGUfy/lAh9rJsd7Rx7Bds0Dp2YdIPYZ57NYKePcT33cHPPwnPri67EbOSFZ/rO50Gbb2Esqm5EEpu42dnYBe62ChpOngOems7bDx/df6/iRJd7fnB8d642Nnttb3N5H6pDnnGwdtvq+lbEwk70SPmiPY1HWlyu7yEfG8vbUvU+m6pYyxHhu/e63Tbi0=
*/