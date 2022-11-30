//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_ALGORITHM_HPP
#define BOOST_MOVE_ALGORITHM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/move/iterator.hpp>
#include <boost/move/algo/move.hpp>
#include <boost/core/no_exceptions_support.hpp>

#include <algorithm> //copy, copy_backward
#include <memory>    //uninitialized_copy

namespace boost {

//////////////////////////////////////////////////////////////////////////////
//
//                            uninitialized_copy_or_move
//
//////////////////////////////////////////////////////////////////////////////

namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_move_move_iterator(I f, I l, F r
//                             ,typename ::boost::move_detail::enable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0
)
{
   return ::boost::uninitialized_move(f, l, r);
}
/*
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
F uninitialized_move_move_iterator(I f, I l, F r,
                                   typename ::boost::move_detail::disable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0)
{
   return std::uninitialized_copy(f.base(), l.base(), r);
}
*/
}  //namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_copy_or_move(I f, I l, F r,
                             typename ::boost::move_detail::enable_if< move_detail::is_move_iterator<I> >::type* = 0)
{
   return ::boost::move_detail::uninitialized_move_move_iterator(f, l, r);
}

//////////////////////////////////////////////////////////////////////////////
//
//                            copy_or_move
//
//////////////////////////////////////////////////////////////////////////////

namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F move_move_iterator(I f, I l, F r
//                             ,typename ::boost::move_detail::enable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0
)
{
   return ::boost::move(f, l, r);
}
/*
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
F move_move_iterator(I f, I l, F r,
                                   typename ::boost::move_detail::disable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0)
{
   return std::copy(f.base(), l.base(), r);
}
*/

}  //namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F copy_or_move(I f, I l, F r,
                             typename ::boost::move_detail::enable_if< move_detail::is_move_iterator<I> >::type* = 0)
{
   return ::boost::move_detail::move_move_iterator(f, l, r);
}

/// @endcond

//! <b>Effects</b>:
//!   \code
//!   for (; first != last; ++result, ++first)
//!      new (static_cast<void*>(&*result))
//!         typename iterator_traits<ForwardIterator>::value_type(*first);
//!   \endcode
//!
//! <b>Returns</b>: result
//!
//! <b>Note</b>: This function is provided because
//!   <i>std::uninitialized_copy</i> from some STL implementations
//!    is not compatible with <i>move_iterator</i>
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_copy_or_move(I f, I l, F r
   /// @cond
   ,typename ::boost::move_detail::disable_if< move_detail::is_move_iterator<I> >::type* = 0
   /// @endcond
   )
{
   return std::uninitialized_copy(f, l, r);
}

//! <b>Effects</b>:
//!   \code
//!   for (; first != last; ++result, ++first)
//!      *result = *first;
//!   \endcode
//!
//! <b>Returns</b>: result
//!
//! <b>Note</b>: This function is provided because
//!   <i>std::uninitialized_copy</i> from some STL implementations
//!    is not compatible with <i>move_iterator</i>
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F copy_or_move(I f, I l, F r
   /// @cond
   ,typename ::boost::move_detail::disable_if< move_detail::is_move_iterator<I> >::type* = 0
   /// @endcond
   )
{
   return std::copy(f, l, r);
}

}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_ALGORITHM_HPP

/* algorithm.hpp
7wHvg2RBOo8ub/h0+mclnjyegCTvRDVtJ1H9X2+BeM2dS0zlpven0y2UzMwrPGKAoTdfvST7gxlDotaEhwNwkp7lzoOJd0a+CE6JuZJBwe8/XaPJlb57Tr51uGh+t5E/d7QEynxK76ZC6w9Vh76FgkieMp3PtfSIfJ5m8V/PJfEg151PBZBlcY4Ns9b7NCcxCCjJ3lFHdxExM8nAB/hBxu2YnUJ9XIzNxz/YWcYysG+5yCOYtpJFg97QRAiw9Qr7LvsfRSKc1Ng4bmFHsem0K3Jo8hKLjKQBgj51aJe8I7KbVTgmC0iKCnqgkuFaaigxC+tUDBkaF/Hxbplo3WGlV8EZwFfcqJFLgJr/+G2xxSD0O2uN5L2JCSjVoPk0h2dfVz6v2jMS5ne/Y/NfVT8SvTzZG78QQEMm60ekXN1/OY9P/2VbiVEvXSEWksoaWnTZKcL2NBFBxRIOfwS2sZBeVzjZsS6zNv8HhZtSGnQ+XYUeMGrwLydqbl5RTbJwfWQyLvIlt824qnlrNPNX/NR8MiqjlZ28lIPTX6iSGHCeF8nJ/JmFxeZlysXCqCwR5xr1wol4czj1EziEahj03TlbRDAke9diEUJ8rSaeWDV4QQcDRPeoP4RyTcN6HVFGQRGlPkqY+eOkBoPLJnK47DussvA6pU0+6UspKhM6zTXOVwaTeDbxgz9P+czquI32H+e0gUZaIApXPIOMBqC2EC1hcH7wN6Gq2Rx3rrfux+j5lJMrvjUYVsN8KzoI1QMM/XO65+kZLO92ptyWGEj95YBSHn2guqRUf/SDkHLZicHGM6MZbmCStM1KMxl808y+N1/kPQPwPi4t4ItRjeLjWqNlgx7Pg6vOgkxsvpOvbGbD43sW0BaFqY7y8NsCdu9rpgwZWtbK+fjHgXJnQsCMEPq/b6OI2kw0N6mSixWeuJY4ToiBiHiVN/gScaH18nxTXMUtreAdQg4FcMLzsc2GHB4yBbN0AsZByWHDBrORjSQib4mE+shO7jQ5lbC9iHBvzYfFSMFZsUVPEQWrJ1lubhJJP7WzKJQkKQhSHfCCl9R71wek/AGh9s21sWQwPcz/LhjFAOGBZAZLtWQrt9C/Ii20sTMc+e8EdcAnyP+hjsPP3IZZUk+rhN6Y680ab5xSmsa2OZ9XgdUhz2pFl9i+AybLcxIfffwD+yGWPHPxexbPSCVa3cw249s0ztYXefYoolnumJtfDicHBCbZNKQKPe4wH9/Ss5fdF6zCf+iWH/kB4fGEbJFLz0e1XDVbZxyhTfMecog6B6WxxQn67rfYnzPdVRSMrz34eX0UKmlBe1JSUxT7dPkk+SHh5mrD66hImp0Ybn2Z5IdNn5zxR9uhfR/aXggqC5KuX5HrEiY15OpqKN6RFNiyfyZYuwwTBobxnswLgwlQLIURRGvroQJRmShlg94eUz0B2l/74nTfMrLrIbNrHVFUCKUr7n27RhFqbe5Tp3doDwVyJKi9WLKRLhfdeDiDlpx9BgRPqtvz8OV082QaReXAewoq7UlP6kZzZSlOfRSnnATNr29H1gh+ZVfPP5W0/o4ZyEvpEnsvSedSxwUBKWTsL+HVdz+22TOs3X8TW4qBqzxESLN0Yp760kVUrcbvF/26VXlSMKOT4w2eAzLdNeGTDjTnW24jaVUXSLbYtoQMliUBK3kvgB5ZMu+8QeAOE8lXv5qnra357AEOcH969GjF3/rXysy1UPTqISV41qHPI7CT2rTSxk+svJmAfqlftlJBcUz9DFuvQbSqq4ibRy4jgb+tUx1BODvIXqQfe00lXeNn+ATtKXIszjuqIP4pRGPy4Q24PH6O8vtQQU47QSdK+i9mK5CUehVkH+qj++e/icQyGpjD/kQRVN5zwXqAR1ADJtzS5x+LJR2/ZIx6vduAayoejvDzlsy10zoGV+GzOupc9pZEwkJRYWlC5MPIYgFP6CIC760ejvW/vtNKQX/6m5YC+fx8bDy3HvJMat2SmjKhq4g8qgjeBggRFW23Y3hcZ2DI+cym4DAxyfksawApipeyKJu4HUiDqtzUA4dNwQnvyN403zr/dB3D06NtM8x2KbcDGOp66XVW5lxilvP6TAG/XWOQO6kRpUrSG63phUkW2o0xtg6mcBL8yuEBojCepAnCXRkEH3ZggdV5R9u88FM7/zhxid1myP57c2y+ZIVSOj65QLoPOzRaa+2IXJffg5EKE1LYMo9txhPxfKm+XwQu9LzyddMF5h/nVJ8+gWgaY4ioM0KdD6sgruDah/qf5iioIVGiuisFEgtewVKfG4EhxfQ/ybue6IIDtbAx99F/F950qHa+/ySAB8urJJrIouBfw/Sg37JODlmgkdaOeoxDmJgjLL0uAJERoZ8uBfZXDrBhPyEJ77Oncb/L19oQCeQJzdaucaRWGoVBBPZlFTLhKt/mBEiPb75BKaMu6d+CaSxSiPQXAIDKG45NFOxUBKSTdKj1N0za6pRg710AACz/0zu0vJFmWjqLhz+n+ufJQhTi4UUl4Be5Q3gBC+3gbOfPBOFAbcQ/PGuGFit1jeyPzHHCH8TonvKS3CEOjOt9kJbMDsDWuhXLsElGdE6Wliff1CHBAACdHgTB1Zrb8x6P0MHsfy3cR7OUikIzwA0Im0DffPE2xcmKQiruaM57/JF78E+uvdU3OwHYYKF2Q4qDxCPWNvvmkwTrBUZHlheG0rEN/fu38M4EXPTuxOrp15foV3u5oV2eR0WWZ3q3KxNyXHW+5oDlIPzlkGWLOAtxqkBlqzigrQdVdzrpquP07XjiX9Sjniegd1FhF5BQu2f24z9y+JQhU3jO3z7E/CsDXWEDbQLaBskZN6C0EwLnQMXY4XWbWgUQy4G1EmHq98UkpJp7xwsDRpA1qGe19MrK9dMWmHVn/TWzHr/3Hrl52k8kWRLAJ699I6QTcfpqPtaMROGTFZ3f4u+Lv79nDEqxZelj8AyQ6Szs4N1tY4Z5Xp8gHMa13ZtQrhtslkpFXCXxP2K1lMh5oevFZ22kyhOjU3fFRWuoGFPQpSFfsYvMDcvR18u/l7Y4+CaezYd7RAu6akU3p9m+ru8y27cboykTkkA4jDsO3VUYe7s5+IgVg6WxKqsh0v4DnIPUAYDR8zbMTQwYpDNhTXJ/jhk3tyoJlzPCds3XqJY9eI3tf2socHip2D9IqOx1GAbxjI2YZoMKCvbUqekLDQ7Wcu5aSqe220xMD28C9q1E/tU0Kw/r6B/HE6ppuHDeMEcYIl97GDZb1g0UtVYJvys8NgE+nXAuf+LTLVdJU+421CX/zGxtWaTC9XnDHxSPaaxS36+MCqYyliPe+ghat5DCYhuy/y7JO/juLxXrmb1gU0GLDKreEpjTUoDdpyenSjTS0v7iQ6AZqQOxiYPkWXIba3Uo5aTGqyAVNeRWT3kit6aXRIDiNtsHWsQd4oHgF2zH503ZQ6hPD253JHzD4YS/StgOGJxO5omViQGJI1+Xjo4rxRpwM0Bdci7hxcxfK4LjOg6y0EMeafrW12SaeBUfBqCQpLnsDWORAhos0dDoTJaQavcXWf8vxeYnCSDUVf8g06oi7knueb4ggF0SpmHq9A6vEM+mRFPp6bNTshQnI+4kkZGQnt1Zj28rky4FetvAPJALlnphPhhfiH1bWHpo1+5QzhBrUD7O1MtKlIq8CzQIGtRyP5O43O0CYF7M3ORLj3rWCvEraV3Eiy9zOmXeXNoG1WLePIF5nsX12F5A82MMgeRk1V7zCQt9pbrVQ4YBYE5dF1aRIu8Z9KU+JU5dqxymBNlEonuSuvzak3am0aXMphvyg81PrwZobDoHLpQdfLBKMUNm6x7w7Z+e+pKWLiaCHanU+ygYLs2h5JrY7VU8tZGuwfPioFfFUEQ3UNwqehu08GN2X6EJUeHVUVz2xVTZYORLGE4gUyU8BFDEQMUzkQn3HugFxDme0Xn9GOyvFZTFbsKgKBUyC8h+gTd9VlAOWgGKZPLH3kFS2P1J3oSfpsqg+qsnypBuRFP9+g83T27r7EoUKlaoOPVPBfkYaWMseuFQQEXx0C0gLOY5qSkUmtFt69v2J6PeefkI2IAK8Wx0tkwTxx6py1fVM5qEyE23b/WlIelpq0C97mgAowNCfVJ85at4iLtcyKZC3/N7RFfNO4z07aN56SAL0iXfYWQ8C5zSiNPWW9mbbkhznGCiXuvo0MiE2XBojy2erUpRmVjiyfuwhHqXesSOZgQsM4+0A3GBdQtImPWojtqDTiIDM7fJKOYvv5mNWA5/btaUg4bGo9jTxBTHmnf0ylO+d2giHqxWq9G4ADuJsw3d1uIxr0tr+ly9TBWj5DEu1R094stcBGmMOrQYmkI2zArZzbm8c5wLBP2KtxA8YDTFEnSQLeEXzzLxhbp74P1wz9s5UDAGATfaFTrWckH9OgMsjT+8D8JFtvnY8YlpxZrUDuWzETHaqi0dX4rbCOUI0MULdZPacQ4YVz7zqFGr6SFE80UeMOvSdbn9S4rbRskR7Eas0pe+mMbppTHOF9JqaKGmo5I5mrhkq2811i55/rayaW+Guz5vR1nDaiaNyvkZIeIdkvz2Rv1nXWDMN5rNBhka5z8tB6C7VGQRQFCnSsPaA0TEbNeND9a3249Ongwj9McNB0w58mm6HV7XJNGluXQgEWdg4kSNcl7T3tdYJfHgVCjp8HLyAKNdZeOHBI+6Aw2TZ9LHaTZSYV34ESe/ywtETgRylo8xdPkstJNZL/lEj8oJi+MxNA+c613Fw8isT1jObA8sppIQNDSUaf1VZNl1qoTjT+xvBSzaPhLXXpJF/pDG/IeIIV24mkHkIRTzap3vQdb1Fmbkm8bTxYPKQVyByLuKx/nj2i7MRHK2nPQK7CSb5aHTcz4Y98d6q8zrRqRsk1IqSSCcmsAOm9GRtTjefyD/2cRH48QDAQ1F3g1IqrJfaKKYJIMWwpUfUgrWofHBtSo0TydTLjAgUuyuseZz718Tm2lam5khM1G6BpYXDjro02rDc9cCHO599dkx9yyumMRHviU4zK1HrCeggf83/2kLqd2zGskYbZWwcGIxF2An4ObQKynxcC+pFHloDRMQTLDIS5hiGMpfzg5vcgnQKc4cfVWHHlfHL+RvBjmZedcd5y6saH5P0TpeCrqXhbrspMG40nfOf4C4GFROEHZbmGIW9dafR3n4CU685jW3NlKYovMfFgZaTEJRREKMIB7dZJ9fkRHX+azE3Ck7PBVSMrlhpWSMSPNvG4TFlYKlORLg5e1I+BBRoQwSQaX6C4OBSqb1Cu4YTFlJXc9wdQqPWRxGoCa2RsJcX345SXFX2TQl7zs5GRUJexBIXff3dMSuMh3vS4vqyvxNt35E3+puXZRZkn1vN2/eLfwoZyYVuWqy1mXpxjNXpRtQWH+gosYhtdaKturTTMH3rTLOZkJaeU5vFzmjOIKOO6NQM4ePYVz8y2gZCFUXSErYfJI8lcokOvTEIAUw06Mo1i2CBOfJqDugqqTgzlQc5UDBO5gu/YBB0cEQEThRU/V5YtA2FVN6n8uq+dWLvysdqbEOFTO7aDN2wMfhXLOoCJFGCQ/akHBc5k/H9i3md2ObtiZqRLUw2SIOmFi3HuO46WXhNNoISI+rEP/+5GYvz8ZWGs2eCE7M/g+hON3JV3oIGlKQYtZ/6xRcvTsAJUw/2I8oPNMULkiO/EoRK2a0obUIxbm2Vs6lRSTXFhiwEQ8WF5/U3G4IX2FKIXLbLVWFUd7L8TTP9fxFnZjDBk1lecsfTAi2gK/Ai5IdEt2Z7P3/eMSed9V0sgxIEPFa4qvPgfJqZFgxhvIzC982sQZrx1K7x+veukPs8wDK3Pzr9vpFPCsbF1uoiHaN7M3Bog3EvhowoJSk8KYFt8Y2CwYKRLISB64k3btYqFwF85fZjUUzNwYQ0hWdiRWSlQuoC1hU4ZUIJdR9QkXi7k0evsO57iHySwYVSQDcd4/r01v8oUa5e0JuEAElshDqz7HGuhxHt+wfecB94SKcaArpUAn7sALMvywfY8QCBg4HdU3mzEUEVMvVIJ9xiLMBYzBjEVjw93XOGOMetSj+K6eJ2fPvEMtLCFSX2CNptviVhhLySwV/aUzIg2BKkTwtR/3iOoRh1DWCqGQXHcoRwmiHQy4RI++ovK3cg/BgrObs4sdMoId6S+lnPSih3g7B6QhYcKShMWbXKl/R1+qrJkfzoWfOR6ZKODwH5Slg14spMCZyvntwsWuXn/rYiNF1Aak1OTdMf2PgBBIIprzlFSWIXgCOx8AigI9BEVDCZtujQKVZnPNBSI2lVV4Y3Z6Iyq1E1GtNMWO0ca1WDGHqkx9UiHRSYdiIDRXBX1blbAaaI4Xr/ZCD243bhoRUueZjHNdsJ09orU1C3ayQ9iivSmPFl16GfSbAqD/OE3ajGqOEAGjkESJN7y63JzfSnPtvAzoYWwGcGuERJ97jdF4KlmT6AoeeD11kJL+9baTtQZcDuyjrC/HknH9kz9S/RW1pcIVtPMWmKus/2fY7VcVt8KT6FiwbZM02Q+TFL1UcU1X2B3+S4ZztyxWNzTXQCNQkL7blcTdovsegETh6IOzygcZZbr8CcdZ7YeMfIlYVtfwcTvKz18dzTQ8xWmMg0XiGAq3hqbhU0WEmC4FpgQHreb3M4uJR9pciHiZ/IVfgJ9EV2gGHr8WP/4geYUfLHX5NYC0NuommqllN3ZySwH++AxGGYTkQOk+FhyGZUUIxRwjl2laNWp9UI3BJq3r4ZkeJOqB9/+mjQjvywyevUxRRBrkDfZz6AndOgwze5Csjs8FZ2I3NHu1x8X3pKD5Qy0u+plbb6UAXk2xJYqp8mGyJE4szRKY4CabUF02u2TTOk09lmk9utdbtiV7/9zWlvqNiEDgkpuquGPcczLyaG0HrVgube011fOxgiqeBWtv3VYK96j3lTOwctgAAcywpCJk/Rb5K+6ZRXFmtiPSeUlGkCJgAeiHY79FUqL2UeLzawLGepr7tPe8/oJ74yam6Q/50KoypymRQI0MFxuo1dFbsPrTGbZFozae32WsfZvNKWManRoKxl4C2bsvoA3tyLBs5NDul5LMonsWMnivW2egmKB1ptuc6kfOSZGlcTHXNuCbPmHc3JVMAn+bBH+eqX42rPp7IuVaKYdvsbRD/Y9WEMJwvKTO1C+g4weElWg12QpQJjZiNYG47otAdlbVjP4+18zY1y+/Qv5yNh8XAPQWiPL5odPeDPAGT0jiHbZ7O2+3kx8PXK41FEou9qQ01W21MkU8OoJhP07i3smuEq0KQFoZ4sQMeHzacj2utfBsMhInydpeZsxI3eoj9snVP9dZOOqSjP04sCUIhrpBX5hovD3qQxm+AYEvKBMj2iuXMLEXq7Kebz5hbbKKj4Ej3SaTJix9IW5P9tPK5qbBQEdm4IjkjJhBl2K6HzNN4Ui6ol4sbN65pnm0fFIN37JVVmmVXonKDkE++5YTMlMOPCxitEfqi21fKRYty3MmorCA19oXunXpDZWjw9V9LDI+/iu02x3CRTwLWiSpcbshhfTZgwkxNySlrPzQ6+8FRo3imnLG8lV3u4j59N5qRsT2/0Sy6Iep9KpZpUyXXTLPEJQobY95tw41muApH/glb
*/