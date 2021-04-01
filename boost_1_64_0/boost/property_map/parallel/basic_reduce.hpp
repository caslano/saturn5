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
F1HN3+lutMDHkH32obJVhreRy1v2ADhX5gHDrVUeJK1V32DeZZHqdSXBotI8S0jFlqE6VpK3dY50iWeTSbVZCM3iODncl/d5dpGRXIl+7DasUZgWoiUUO8/bOTeBLLy2wjYH3IhdHYUdBOuvxg2KuMu1BG8Aj2iPZ4gpb9ESQPavUsveq5xc20YQ/POJASa+xQR/hPWyasHge112Bc8qH8QtEyB4oTxGOCViq5vpCRunrW0CQCDFm7k2qB/zqhstUxM1UvEW3gxDDU/7sZYEJfXdTLkMgv7dDKRib8ghyLPARbd16uLYha0Z3hTpALV1UtoC7vIoavpd3NacExHWRL+N6V9zFW+Fme4gO9i4E+cUEnxZ7NAT5EEWrYwD/51pDkKuLV7HwsYfnexMees0pCICVtnE3ONO+Z0y5gp/Wu5xKXAOnpYXmf6RNVzNkW3B/NdA8syjautN5Dsm2Co+FFur6Lg6XHOPjd3j00iuFrEf6oHWPfhCt0RcVtXhTYJ86v/l1j3yqzTSbVX0LJ2hq36X9ZbmHhZhkZDF9LUP9eQfrfwAmfYqyvb8kA==
*/