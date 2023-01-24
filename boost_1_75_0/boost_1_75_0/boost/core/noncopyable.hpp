//  Boost noncopyable.hpp header file  --------------------------------------//

//  (C) Copyright Beman Dawes 1999-2003. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility for documentation.

#ifndef BOOST_CORE_NONCOPYABLE_HPP
#define BOOST_CORE_NONCOPYABLE_HPP

#include <boost/config.hpp>

namespace boost {

//  Private copy constructor and copy assignment ensure classes derived from
//  class noncopyable cannot be copied.

//  Contributed by Dave Abrahams

namespace noncopyable_  // protection from unintended ADL
{
#ifndef BOOST_NONCOPYABLE_BASE_TOKEN_DEFINED
#define BOOST_NONCOPYABLE_BASE_TOKEN_DEFINED

// noncopyable derives from base_token to enable Type Traits to detect
// whether a type derives from noncopyable without needing the definition
// of noncopyable itself.
//
// The definition of base_token is macro-guarded so that Type Trais can
// define it locally without including this header, to avoid a dependency
// on Core.

  struct base_token {};

#endif // #ifndef BOOST_NONCOPYABLE_BASE_TOKEN_DEFINED

  class noncopyable: base_token
  {
  protected:
#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) && !defined(BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS)
      BOOST_CONSTEXPR noncopyable() = default;
      ~noncopyable() = default;
#else
      noncopyable() {}
      ~noncopyable() {}
#endif
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
      noncopyable( const noncopyable& ) = delete;
      noncopyable& operator=( const noncopyable& ) = delete;
#else
  private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      noncopyable& operator=( const noncopyable& );
#endif
  };
}

typedef noncopyable_::noncopyable noncopyable;

} // namespace boost

#endif  // BOOST_CORE_NONCOPYABLE_HPP

/* noncopyable.hpp
SdLcCv2BFPe9w6iAKD/1OgHiE+un79l5V70JC9poeUYbRDz9P3vIKeJpRWRMHf4yGDnOogptYCHIAKuX2VBp8YjfmVXm5BVcm5h+USSTsLckuJTqqujXlSBOvMPU8pT1IYAY8jz8z+dDkfzB1oHqv8xrQumreIrn9XmWdfWneR8hLjef7bhndEsaDDou7nw6/JncLGXjJusMbPMZinvOeqeyO5NgN/IXtpul1AFF/akjXmvNDpvIOryDoihOvj9A3EbXK0qwnKuVk1Zj72jDGCpq2RP4bYJli41/g9bAbFPnYGirWXlSUo6lUVXOMJtl9jN5SGNHyHpHrsN9awW2wcjLJn/GQN8Hz3LEj09kcqhyji5/yVx5ohjRu05KLSyT99jPc5YTkDkrAVJrSsP7+8dNylIZfYzhjAHRaxqydypnpZGd4QFhgq53sowOwjFshk5HTkodHcR/JJ7E3nyVcHhF9qtVAtV9pwKLPqutO3L1DO9jbdO0Z79e0KS/OTcJ4wq2Jc/maTmXq39ZN1XGPY7gvud7NxAgN0E1gj+EWAKGVrfOuuRudnmi+/UrKwa/6z501s8lgsXM0pktlyLJTntqQ3weoewUIx+vffD/jm5JrH+R5PkCQh1XSOlTfm93FR4J4qdveTB2f8AgrDJ/JhXk7KNQKmA7cerPQzPgaLEX4c/5i3GKJmnVSMcvZ4ry1GLCSZZej35WkjQo
*/