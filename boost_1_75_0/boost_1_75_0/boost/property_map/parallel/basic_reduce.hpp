// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_PARALLEL_BASIC_REDUCE_HPP
#define BOOST_PARALLEL_BASIC_REDUCE_HPP

namespace boost { namespace parallel {

/** Reduction operation used to reconcile differences between local
 * and remote values for a particular key in a property map.  The
 * type @c T is typically the @c value_type of the property
 * map. This basic reduction returns a default-constructed @c T as
 * the default value and always resolves to the remote value.
 */
template<typename T>
struct basic_reduce
{
  BOOST_STATIC_CONSTANT(bool, non_default_resolver = false);

  /// Returns a default-constructed T object
  template<typename Key>
  T operator()(const Key&) const { return T(); }
  
  /// Returns the remote value
  template<typename Key>
  const T& operator()(const Key&, const T&, const T& remote) const 
  { return remote; }
};

} } // end namespace boost::parallel

#endif // BOOST_PARALLEL_BASIC_REDUCE_HPP

/* basic_reduce.hpp
1jfCJ0PUELhxnHXH6PR76e1qTPBZSJPM0ezopcQK5AQI9TopbDaK222gyX9SfYbbHT/zidmf914GK4S9Fi3sUkYfwFAVH/ktrIm06WIVdos9wDRELHPJtqFfqR2007Y/sdOpvQ6zdbEmdjN3APmOu9/Ag2pBYps8faEX2b3S81KzIR25nbkOZojzIuKLsp2oqyXk2M08tpAfbFbxvEu4edAXZDXhxIdvVnnvJ5Fp/NOKAphTNDIhFXRFHF3pe1UiYkHwRSDHN5UQ4MYSRZU1C7d9fgR8d2Hu4B1cGfRFP0Me98G8iYbMZAt3UKGaXXiW5OTt1I7W6OO0cWdCespuOSz8dacZm+tM4uk1sXPTZTCvFMoF+vipFFpXpcPP3VTd+r3TvAT6YCKTSvzohVF8Or3o8flw3MbklF3IClGxw6E+x1tgIfOLb/pwcl3eLVzT4fC1uan6Ohet49hqMun4dYnm+hNLqiNlLfI2W6EO7rF4q9MY17MyefbQFaYGoPiD0d/0RQcGypaBfEDcfkZ+sKETR+/sogxB4V4DN06KHTBtilla8GMh5hQvyFyiqPlOGG4YvyJQqco0euE1OFRp3oNLge3KSIJCFa1svopToV2zTAKxAU1BOkOFqKxEIz1OQ3E+dKE+nbsw/tDGb4wVG+MDqZWwzofSfgNpE7zIUnPKNPN1HeFrtAvLcJyweKCOFrvMO42+hEo2FNJp
*/