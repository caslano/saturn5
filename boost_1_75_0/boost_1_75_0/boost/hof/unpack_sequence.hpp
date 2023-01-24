/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    unpack_sequence.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNPACK_SEQUENCE_HPP
#define BOOST_HOF_GUARD_UNPACK_SEQUENCE_HPP

/// unpack_sequence
/// ===============
/// 
/// How to unpack a sequence can be defined by specializing `unpack_sequence`.
/// By default, `std::tuple` is already specialized. To implement this, one
/// needs to provide a static `apply` function which will unpack the sequence
/// to the parameters of the function.
/// 
/// Synopsis
/// --------
/// 
///     template<class Sequence, class=void>
///     struct unpack_sequence;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct my_sequence
///     {
///         int x;
///         int y;
///     };
///     
///     namespace boost { namespace hof {
///         template<>
///         struct unpack_sequence<my_sequence>
///         {
///             template<class F, class Sequence>
///             constexpr static auto apply(F&& f, Sequence&& s) BOOST_HOF_RETURNS
///             (
///                 f(s.x, s.y)
///             );
///         };
///     }} // namespace boost::hof
/// 
///     int main() {
///     }
/// 
/// See Also
/// --------
/// 
/// * [unpack](unpack)
/// * [is_unpackable](is_unpackable)
/// 

#include <boost/hof/config.hpp>

namespace boost { namespace hof {

template<class Sequence, class=void>
struct unpack_sequence
{
    typedef void not_unpackable;
};

}} // namespace boost::hof

#endif

/* unpack_sequence.hpp
y0wEz7Dc4KUAPIN5l3ipLh4SQzNDDugPccTQrhAwx1I6xQUREYhvyYzqQoJYQax5VO/WoQRxl26P3p1Do+tYcSIU79IVKTaIqFuxR4T+kIQYqt9TfefQ7XqQk0sOnHsJMHJC/itvI/P/B2+V/ztvYoE7WG4iwNi5jn1BBFLp0aM/DCbuAveMMR5SXceKEoE4lshJsa5E3ao9zoSX/3vAu9s/MBrEXao9MxQXQ/9NDfzc/766ue7/Q44r//9jeTMN/7N22LRwMUcc1f8Yhc//7jho3f1/53hk+n+nLaP9/7go9P4P1hb/RWfK4/ID5wobbaMbrNJSkJf5K86P/NQTxRTgtRJ7WZthLjES/MssRWI/lAxsX1M6pD8cdogv3XH71DtLp3I6ItgvbIoAJ32d9e475yhXfY6jfLtjFMPDN1zgKZ5yJtRKX2jSS75vX9H53tab3SFdYIKcVyqZN772G+Wbc23jjeqj8rW5E3GH4NsNexYS8pAHDgK392YYHqFT87FVH2MgxoiZzuG7fPMFGeVx7PpfZkOj0GYixsj24ttX2nOLohB8pZ5ksn9iG8FcxmFGYDNF6m67khJjR+kr8B9WMZ0lCSIYj6na968C0mtHo7BHB6Vn3w/t6i/TxdBhnLZGfbOipDadFgvsgU2P/Oon8IvOFe1Pux1mHt0pbjhvjOnjvwLyWT4Oo2FlaWZmveaMpAvln2p9Us48
*/