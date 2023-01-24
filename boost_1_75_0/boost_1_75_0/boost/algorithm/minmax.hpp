//  (C) Copyright Herve Bronnimann 2004.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   1 July 2004
      Split the code into two headers to lessen dependence on
      Boost.tuple. (Herve)
   26 June 2004
      Added the code for the boost minmax library. (Herve)
*/

#ifndef BOOST_ALGORITHM_MINMAX_HPP
#define BOOST_ALGORITHM_MINMAX_HPP

/* PROPOSED STANDARD EXTENSIONS:
 *
 * minmax(a, b)
 * Effect: (b<a) ? std::make_pair(b,a) : std::make_pair(a,b);
 *
 * minmax(a, b, comp)
 * Effect: comp(b,a) ? std::make_pair(b,a) : std::make_pair(a,b);
 *
 */

#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp> // for using pairs with boost::cref
#include <boost/ref.hpp>

namespace boost {

  template <typename T>
  tuple< T const&, T const& >
  minmax(T const& a, T const& b) {
    return (b<a) ? make_tuple(cref(b),cref(a)) : make_tuple(cref(a),cref(b));
  }

  template <typename T, class BinaryPredicate>
  tuple< T const&, T const& >
  minmax(T const& a, T const& b, BinaryPredicate comp) {
    return comp(b,a) ? make_tuple(cref(b),cref(a)) : make_tuple(cref(a),cref(b));
  }

} // namespace boost

#endif // BOOST_ALGORITHM_MINMAX_HPP

/* minmax.hpp
c4l1DlUKuYEUcTe5VScuwk7rN8h0OloO79y1gv4EWcFwwcCm07HZIP24RY5KmPMmwYHmtErgyKV6yCxVTjtvx/uVuSk0yguKaokqEb3NS36ckzk/4XsSWsnqLr/oKQYp4B5RMvFfydBKgR6IqCv2EfXl8zw0GpkvE7o5D2A74umQT9d7x5IowWy42dQdz6fe6JILCvj8uHT4tGDeYbyIzBXoBmW7AnmfKmuG3KeGNGMT6BYdJBgd5n2nLz8Mub6Vexsz+gDedgtHzl3j43R70zvT/+jYo8Mu+Rx7CRVA9tV6VTgI4UbPotI6rnpzNfqiXHo6iO9JOyR4b1GBjL12t+LF3PvQVbsprUhfvsZyIvEx2Pp2tgMeRV+uNNFmhOzrsk4l6PupN6zUJb4WkFYgy/cFjQWJomv14r7PHP33ncYlsQ69JEDuy8+MNxGuN/bpxApgQOyInxmKGtU4pyHl1hpT3arIvmKCc5m8Yt3+d7WDxQDcSrHvYP6hY3+W4MdUD7kLBKMkdXb/1133z9+uBxZOz9+gygYGPOnGIdOGG22+A30eeV4LZr+mpj967oSkKbzBzaHmC8n9LBnl7GHtb62gdjf/W09gQxG8zTY418hD/y1zc0OOYGtxEgglh6qEFrHXzRpf64TSjxIo4pQpJrQtz9lMz9Ifza70d2BofB4phW/I/NWaKAtNE2PCT3Gu8nSxb0SO3f04rQeX
*/