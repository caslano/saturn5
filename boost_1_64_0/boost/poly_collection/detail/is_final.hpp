/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_FINAL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_FINAL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/is_final.hpp>
#include <type_traits>

/* technique explained at
 * http://bannalia.blogspot.com/2016/09/compile-time-checking-existence-of.html 
 */

namespace boost{
namespace poly_collection{
namespace detail{
namespace is_final_fallback{

template<typename T> using is_final=boost::is_final<T>;

struct hook{};

}}}}

namespace std{

template<>
struct is_void< ::boost::poly_collection::detail::is_final_fallback::hook>:
  std::false_type
{      
  template<typename T>
  static constexpr bool is_final_f()
  {
    using namespace ::boost::poly_collection::detail::is_final_fallback;
    return is_final<T>::value;
  }
};

} /* namespace std */

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T>
struct is_final:std::integral_constant<
  bool,
  std::is_void<is_final_fallback::hook>::template is_final_f<T>()
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_final.hpp
KjO+0C1zylMfycIou0jlCk79Auy+xcIWmlJaep0428We0vTNL3NiiVvmlKbGfpk157hlTmlq7PvXnHMpE9rfbPv8wSydJYOu6Gzc4B72cVGZvvVs/sngQnuH6aq+P0+LHj6ly+ap47w8jLW12tqzLlyhfcwrnpJP13ZpMOrzwkTsdaYd1VNmY3ja7rZi0cfCdNXg9/GnQp9h//Pr8+liwd5vbGEsbZixoNumh/ibtGnWDm1Ttv0Ciy4NGdoxm6ZnVoa2eqlFE8t+LM3ScFVvSGGVUDN77ZUy43H908DZ+5MH09ntFjXZeVW9G26oU30miy08bb9YuLGnu7jHnmqavn7RM4QvNL229guPZ7GPOQXz8Y8+y8U/5tTal/HQMuGjp7zBc9P/UHYlsHY9Y/yWoiiK2rei9q2ttlqKc+9Z7jnnnk37SlFe33v3tu9x3+Ld+2gpitq32ndqF1saERFBRAQRSyOIiEgjCCJSIiIi4jfnfDPzzdy5r/X/p32v5/vNN9/s33zzzXyPIdw08wGTedtjBfbG23VVH3sJP92Uoeak/j6BvaltsSrjPyiNc1vM/QoP2DjULUzOA4Y5ctCFGSwApTAnnuDCnFnl/XD/YRdmDZ17DTPyMryedZ4Pf6ILuz6a477CT3Jh0Lt5XzpCmE1NFrre4qcQ3tkkmm/WIdxmzcH4bvcJ7zA/cN+Oq89vkf3hhXupA9WuU6t9jbnCMZQtYfTbXxwzwUnjKo6T3By4yxy3bzq/CwbO4sfK6TW4vqugErOLMK6Cqjdpn6cws/NY1cHGQmrZdhC/KYVYlbjrxNNZCODuTbjXGf4CzYQv5dozeV7XnKvgrM72+7r+nZY8K2nUDNoiUD1goz9hh55bWBisjdl5y47JMzpMRCtCh12Q+Vz7lDoH26gPvSnEkLJDv38Le1uJn+toHld+os5/MFk24uLzkqR7T90i6dx1ZEnWy+VXbGHp3QZpddb0a34mN+HKOFA2zF8Rjl2kYEo3nS2S/CZW8p1f3ajdG0eq/X5unyMRW0rBz2avZBPnQ2jlAQ70+nRGpPv9pfeqNkB/gZo7v7RKICXj1d8r+/qZyVOp1mk1D/zWhUNZ+ueUffKrH+b2ycLLs7ATVVny/9onJb/rBr/YC5MwzKLM7TK7JLxmgxx/iqceqF0/2idmc3DTdsot3E6pzYlkp2zeeoqA21/ni6KqJhvjmgz6Luhd0Ndqen8CwO0f/8Kf23G7CtPfTm0BbXJvjLR0B6Cmm91ezu3DWxDNcSTK8991S4mDbFipMDCU/9N3iOY6CpUyHNpKGHYyK/WJLxNtkyNSJW//VoR1d22FW7w14dxHqWotfO9tCLfZ057cDrGN8DSlkseBKsup2xJ96nBmfmO3I6xjOEvMVwnjOtqXmP/cnjCOqUaW8+vbBebGJ2pKl7gD4Z3HaSwu0B0JN3GcpjE/I8zkUGcxee5EGMe0wXXVazsIt+nxJItJdGcLr0uh72jfRWCo7uiBYLkmfHuG3x94MV0f0PQfa984NCI5PTP6r4/bvmPLhs7xR9c761QYPk/f8+kOXONkSOYPdkZ+tiWwEyH8mtsdc2Jqf9EswhQsLKq5HQNBrwN8IQdlfG+JGdaYNRCXyX17XtKuPV/TaPs4r9bVZUGjGMowl4nZlvseXVvhdGEE1HleN2mra0yetSGjNU7+Y+WzZ6SDVPBQwDhVeV7i9FqfZWk/rn0rmKIwUrrGlzW9scc0ywb3D29d1hhaI2Wv1nruNww+tX1meWk8gbv+eYYTw4MqY31pFZKd034CX3fyo+zR6sQYjapl+JxO4xh62q/+aax/0KU9umym9eyjDANjJugoNdx2l5A5GxM=
*/