/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_TRACKING_HPP
#define BOOST_FLYWEIGHT_NO_TRACKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_tracking_fwd.hpp>
#include <boost/flyweight/tracking_tag.hpp>

/* Null tracking policy: elements are never erased from the factory.
 */

namespace boost{

namespace flyweights{

struct no_tracking:tracking_marker
{
  struct entry_type
  {
    template<typename Value,typename Key>
    struct apply{typedef Value type;};
  };

  struct handle_type
  {
    template<typename Handle,typename TrackingHelper>
    struct apply{typedef Handle type;};
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_tracking.hpp
uANJ2W5RNBXSEpcEnNTsCad+Eec40OsS/TgeIf//Bgkd7AcIPrA+y4fH30//QFPagOqQuvm0xaU6J4VQXUnFkmzLZxnpTynjMxvrYSngvturjZ1zPiuxnPVWVLK/ayarvhNrzaKj9tb4d4cI+6PtuPaF4zrhvWFjM1bbqG5gJs4ElFI9oaABtVEbqB5Th8nX2ZxNwtvZFD7a7u3EmLEK9zGpvJ5E3gfgevXSPZ7GlazXa1FWTT9sGG+nH6be3TTy1HgmIZwVWv0gmEzAdgMPd5CL2S6W+8VjgBPGhIHxH1BLAwQKAAAACAAtZ0pSusFDeUUEAADqCAAALwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUkVGRVJFUi4zVVQFAAG2SCRgrVRtb9s2EP6uX3HwvjiBIiftgKxtVkx1lEaLIxmS3MyAAYGWqIgrTWoiFSdY9t93pOR5SQskHyrDpny81+eeO281gsMf9jiecQcvPrn95vjguTOat/JPWujvG+T5I/QfNFzh+YpQE9hbPeYH8CqrRxhbq3yIdWbe8/wV4VYmSfMzMcar3LyipLcc7KeyeWjZba1hPD2Ak3fvfoEjeHP85tiFcyIY5ZBqKta0vXXhrLSS32pyf+8p
*/