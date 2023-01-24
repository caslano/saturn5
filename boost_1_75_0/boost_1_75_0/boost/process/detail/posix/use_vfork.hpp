/*
 * use_vfork.hpp
 *
 *  Created on: 17.06.2016
 *      Author: klemens
 */

#ifndef BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_


#include <boost/process/detail/posix/handler.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/container/set/convert.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct use_vfork_ : handler_base_ext
{
    constexpr use_vfork_(){};
};

template<typename Sequence>
struct shall_use_vfork
{
    typedef typename boost::fusion::result_of::as_set<Sequence>::type set_type;
    typedef typename boost::fusion::result_of::has_key<set_type, const use_vfork_&>::type type;
};


}}}}

#endif /* BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_ */

/* use_vfork.hpp
j4VPu9I2fME9I6XV64ZrVWg6RhggIJXIiZC3//d4XMvZNz0xFoUJoUWBG/IWs2PmotX9kFQo9pC+PmflqutBkhgH9d+b6w42PajpgAl6hcAOPcsOtaJY69GPm930mkqZHxKEwh8HdgDrnfo6Vuo67hzupyxLlc27B4O3IbNwxUH/D74OKzgPX/UmL2PiaOhG5Hk6o2gpG5NJ3PWrkubO730FsxdvWoO3tEZrl5P4s4i+sgxtCfCE0GTeX7nxFC2L5XfLLV6TTaISRHGYq6TZpTdjQYyM270WtlW9h8p62kh3FL0F6IUhMthcAiPXX/iATje5m6FCXNdad35GKlc5q1oaBfbVtVtw6bImD7/ROzYVj7s1U+54BrFs8lyUL+V6BfuMFHaxlXiZxoKBzHxJaXJZ9jejfgXRTdT9iMXRVv12n0VJz8R6iz+ZdokOLj1zYU1r5Emv0s+eew/DSDqpw1ZSmk5l51ISfJZWG8vsOaQBEMg3EdzZ4nSzSsXBWrR2UI9vhlHgrYxKLEUNsEUTtFCa+DwUUPZM21kv1Qj5IdpkJtO4a8wIUyuIQQn/DVpa9usavJtjasxqyF0PIcEwLnUTbv7kAtikO22frV7S2DSHqKsvmUKubNuykfgNqAVuTU+cJ6cW2adObrH/IOwTww5uC9UDSOSEDvN5Hb73vNbWu9McVGq3BaeUq1qFwWSqu8z0ZWrDjZJUseUg
*/