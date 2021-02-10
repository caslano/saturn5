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
TnD7FifG9s0g/tuXAOLoiIdbeVZ+GnMXYNigND+/MWr/ZMnCVV4dIsAhBfAIhAGpHu2YNHpFw4FHnPLYiHYjJK+ilF4lOY56HJ35dkWlvJlj9Oxq+Xf0ZM4W1WH5ofkegcFbQsG+e4SB1xQywD402vDLypzxVu3dsL3TT5M3xkZBjgGrSwQAvsJH4XfD3TvZ9QYrdrrk3Ec0sAe7kYxZWVFXLZoRvuSH5MqDwfyMBsoOoMONzoWSNLEPgkrvdQ4WK8c/gKHZeU+p3dvo9e4pLbezzhg1frVgigVCKA+b3IXn8n5SwWU7Dem3KTgKpicQ48ktzxIA0MNcHFJho+74XEKirjiceRKQ3I3lvMinT4jrP/fCFpclRCzNi5l8MnNfQLllUmmRNMJx02csyGNNZbkB6z4eptSDf7XiWaQuL+cTfHsXoz2nc3K9HyBC8UDCz+zv5HyEqU9ePn7MkQ7X+TJJ+tTvP4NRWJX5khDDo8wxwxZGkl7kwJ/V5mrGapYr6uGef5xlm5I4P4nsuWWOOYs2+JAb7Fip3ycGqN60tAssfvlc7yvU0XMtIDAsvji2Ywza2JRcJNXe7aljKW+09rW+2qjEGxTqyD2Vwz+dBo8xkedjzEI5XwbANRqHCSVk0DPqxJQTCSULb4v7
*/