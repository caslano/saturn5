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
D9r00DQUn/H1SZjQanu2YJPZutq/UOr5RF/VQj16tG0rgK93iRkr26Iy8oxzxhsAG74LQoFMgznBA0idosDiXU3Rz/x9dxV+XJlw7g2+L7KQIVg/dBuze8ie9pbeZrVxLXxpstqznzGQPtsQJhuTSdxcG+DGPSXXBsUAIDMRVcpbOLQcG/7YbRiOvQKNZaA1zreAE39sADHsamkD0hy2wBZVTKHIKwD10XdDF6o9dv2p2xXZqsMZSMpQ16iLiiyngPk84/e9x+2WA4jvlmbvsB156/EzEyY6TFZV6H65q2sjaEvIub7Sb9+/mU/164vrV2/wA5hPX13MPsYPCFGf5YgxN7ZN6xEK2+DfHMGmHqFP5Eo225xw+BWKp0fuwtY2SP1MhLPlWmKYQIBoY5e19bblNpVxsTTEw2qwznd9BSF6H6g+Mj3cvSve46og23OUK3WaWBnDbKgDQKUYIjtESh7xJ2DES8jqZWurQJnIGoeuRURAVaXEigl33RQfuNJVnXzv2ZzamEIapzeBkirAa9wWFAWyQsdmqujIcbACIkagSFGmbxZYBbfEMCvVE27YOV1W2QMoueupj5LLRWQqIObZKVqeBRy5h3JIFTtAENUCUfp8ZxDRKrL/wrv83gTxfGfx8dLU4DGApYEG
*/