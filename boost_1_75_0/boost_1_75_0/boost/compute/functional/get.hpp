//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_GET_HPP
#define BOOST_COMPUTE_FUNCTIONAL_GET_HPP

#include <cstddef>

#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/type_traits/scalar_type.hpp>

namespace boost {
namespace compute {
namespace detail {

// meta-function returning the result type for get<N>()
template<size_t N, class Arg>
struct get_result_type
{
    typedef typename scalar_type<Arg>::type type;
};

template<size_t N, class Arg, class T>
struct invoked_get
{
    typedef typename get_result_type<N, T>::type result_type;

    invoked_get(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// Returns the \c N'th element of an aggregate type (e.g. scalarN,
/// pair, tuple, etc.).
///
/// \see \ref field "field<T>"
template<size_t N>
struct get
{
    /// \internal_
    template<class> struct result;

    /// \internal_
    template<class F, class Arg>
    struct result<F(Arg)>
    {
        typedef typename detail::get_result_type<N, Arg>::type type;
    };

    template<class Arg>
    detail::invoked_get<
        N, Arg, typename boost::remove_cv<typename Arg::result_type>::type
    > operator()(const Arg &arg) const
    {
        typedef typename boost::remove_cv<typename Arg::result_type>::type T;

        return detail::invoked_get<N, Arg, T>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_GET_HPP

/* get.hpp
60ms/TANwnrQLzfvRBOQ7ZMkKlq/aXgnB/MBhkjxWsvabqic0cvBVDYTNqkNgnrYSW7iQqtiJ1aPPFIlInXTWRnv01fnYSlelS+aCA1Zh60EDak1Vcn5Y1pgkLXXVfxYeARWpwA6caAvuC9C06QFP7bOxE765TlbtHL4LhGx9Bt2RUeVKsUWEPPPfxgj1aa87os4eyCoC73hT1lNevy8YdtVN37kasd6gMjIjT4ZJVCgo5QzdVM9FX9Y5PTbkBwap9V1HKtH4PokHNH9lWMXcgGNZnMOihH2nNUJs6jZhjYTSmjQbDHbaMFKpTd463/cBFxLgr6hQmObc0Sd7jSz3yvRktLcNyvKLxulj27FOGxGPdYpL0wkWcztL1ECtzZNb+T0BQWuqgKFCagZQ4A35jntsgAd7BCKCokyEcEdJ2JpwTZmT1np2sNPujl+5A6nam2pGdVVyBYiCcfeXUvOWYVU+bfT0j0/TBlkYnKy5yXwXdSChaQPdn1yI2QAVvmqf75zAqkpxXuuuSVTH57vTKvxcAdLB2m3IBlFy1UWPBmAN/1ZxKRuSRzvizFfSUlryi95kTKTPOGTiaPodUy1foGYqkPW+XdNMB4JxVCrenlcnW5qNaEU96JiolenvUmqJYjZf5i0m97k/sFpeHOaYKZzZvL33pYGO3t0lPMhoXezVkRBuy157gzB/Tl9jmJ/uDtzhpfWvr4wR9k3
*/