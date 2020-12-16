///////////////////////////////////////////////////////////////////////////////
/// \file is_noncopyable.hpp
/// Utility for detecting when types are non-copyable
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_IS_NONCOPYABLE_HPP_EAN_19_07_2012
#define BOOST_PROTO_DETAIL_IS_NONCOPYABLE_HPP_EAN_19_07_2012

#include <boost/noncopyable.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace detail
{
    // All classes derived from std::ios_base have these public nested types,
    // and are non-copyable. This is an imperfect test, but it's the best we
    // we can do.
    template<typename T>
    yes_type check_is_iostream(
        typename T::failure *
      , typename T::Init *
      , typename T::fmtflags *
      , typename T::iostate *
      , typename T::openmode *
      , typename T::seekdir *
    );

    template<typename T>
    no_type check_is_iostream(...);

    template<typename T>
    struct is_iostream
    {
        static bool const value = sizeof(yes_type) == sizeof(check_is_iostream<T>(0,0,0,0,0,0));
        typedef mpl::bool_<value> type;
    };

    /// INTERNAL ONLY
    // This should be a customization point. And it serves the same purpose
    // as the is_noncopyable trait in Boost.Foreach. 
    template<typename T>
    struct is_noncopyable
        : mpl::or_<
            is_function<T>
          , is_abstract<T>
          , is_iostream<T>
          , is_base_of<noncopyable, T>
        >
    {};

    template<typename T, std::size_t N>
    struct is_noncopyable<T[N]>
      : mpl::true_
    {};

}}}

#endif

/* is_noncopyable.hpp
QxzTrdLv4Yqx0vkqIXR6nVgh/lIf18cgF4fBfuQdZulpHvoRsTnFxsf3gMW2MgEbCrYT/Jf0aaFVVrax/k8PmE5cBf47kf+zAz3kfoC0K4GGteh8te4t0LxZJUTVhX0by3h0Ag5g2B4vWI4JxxZoD8z3JR3WnzhwxsBZxbXNo9Cn8Ak43wpQSphdne+W13V49xB1enCEieBNysUADn6GI9wqwbUVvw7r9I4TcVirro/e12G7q+NK1w8f7OhI7XwLB5pvs9F8Fdlqm2Nlgnl8MhoHp/1Lm+snpH+2V38/TlZmWJ8vdvTNlrSkMbHPvxaPOZKgK/e34vL0FsmVQfAfHHAxBOfgKnnr/XFchz7PEY6NX5zE0xe3FWZP4Q0LfQmfNJauc8qDbRo/llCP9B+XerJ0o3JVp5yhnQhs6V6ODnGF9lq1lNnzx9sjGvXU+6sMNrpPjuWeaQJ29jqJeWLSWK91laYVCSsyuCpnGtPCLfu/Fye+ozWUZ8O0gJc2k1OW/SfidXxreHZUHs6qRBdZSopjtfzv5enK8ope2xQmK0tZ5THD5fX4YZRWMF7rQtVWwoMhNCmJrYZJQ9rfRWk5M3kjtTEp664GsQYWjeMdpQVBBLeNqfxD5aYXJeJd3t0rwrijugDBbv8pse0UhP3KTSYZ8jkKfED/0Dtcef48nCFbYVifmz41bgtbibzKG96WyV8+522yaAu2immDzwMuVFpZFsShfkWJ7t/kokZ1G3aicjSsKVOeNznEi4SBRR70/U8v+aAhlTpeX0NeKGsqy0rZvGYqju9EVVzoQKHl+nXEq2a2aGQhuQn+c0HpIrS2L9BJsZD/FvFqbeeyqqhOrCJy7euu3fVpvbtTLWTCs74uXz/5LKwNT4v7LVMqUXXzP+rvOQEI2u/TuOcRz5zJyvA8L3Mcj4syqnXQ0PYCFLayH950o7pZVlhdF01T9t9s+kJqrGTQDemVR1UgbSyRD4onkBM+E/shT2RLP434aCabkqeZ/q98WgsHwucfEZ+U1ZmsClFm/5UPnByI3s4Dnh73na0qXqpU9fmc3EIr22Ge9HipWqYpF8IPSCdX+R8mHcpm/0B51awubJlbWzB/DkDjYnAeGt+N/0rT8YxljUpybWxrd2QmS8bNuYX391s+o7euKlOUoubAY8m4a4ZHcO9WNHx8F78q4pWx2pQVVxWwCku0P245TlrSmIrBj5mMeCRMm1w0UpbAhKzvKUp/qO7MFk17XmV1LjKVu5QQILrLLcV2fybFW3D9l9kiVQw0w9NWJLu+NcbYcUQWt0fTnauzzMha5G2yZG8P4Z1dyoziGzBPNFldQ5UuoUN3VPHcoS7Xw37da5M8tWVZlLzXJluTro4PAJ95M5iDn4c3x/l1x+mn4bvia+HNMeh7DjaUUBq0Mu8NtPCu6DVEHXVLWKkgLdJvReiYGt8lX4vvj3AEtJfId/R9KpOtZACUUJbbdt/Fhkq2FJYT9U99uHPMMtBuT2iY0ueFOqjoKBb5YQyuzoVsaJOgo6rkQCqx8bRmi9LujDRlejSMzSUVv5SFpL4cGIsr2RRai40qdWX23+8L38Ffp5ahXe+PfgmFNVvKYH0D/QFIT7a2NpBI2vehXtd3Y+B1dMP3h+H3pKoo/uH4PdUbmwT/CP9dbIFHW4I/68eMEm5MlKrrh/X4u5akbc61tOYpG3rQJJubT7EbMtDO+zbF2m49ren674m+/9TGlh9F+F1gu9l4zMlQlw0LZcZ2Vvh9y4Z80/abl9EOnrKRNKS8GdJAMtej5UgDqRzQSP66pYFM0lPg3f917vvfbghz0O395N3/US4m21scbXrd/J70vInXm4eLktiduNM=
*/