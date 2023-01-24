/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_invocable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_IS_CALLABLE_H
#define BOOST_HOF_GUARD_IS_CALLABLE_H

/// is_invocable
/// ===========
/// 
/// Description
/// -----------
/// 
/// The `is_invocable` metafunction checks if the function is callable with
/// certain parameters.
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [Invocable](Invocable)
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     struct is_invocable;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     using namespace boost::hof;
/// 
///     struct is_invocable_class
///     {
///         void operator()(int) const
///         {
///         }
///     };
///     static_assert(is_invocable<is_invocable_class, int>(), "Not callable");
/// 
///     int main() {}
/// 


#include <boost/hof/detail/can_be_called.hpp>
#include <boost/hof/apply.hpp>

namespace boost { namespace hof {

template<class F, class... Ts>
struct is_invocable 
: detail::can_be_called<detail::apply_f, F, Ts...>
{};

template<class F, class... Ts, class... Us>
struct is_invocable<F(Ts...), Us...>
{
    static_assert(!std::is_same<F, F>::value, 
        "The is_invocable<F(Args...)> form is not supported because it is problematic."
        "Please use is_invocable<F, Args...> instead."
    );
};

}} // namespace boost::hof

#endif

/* is_invocable.hpp
vn52WeWuQm76wA1GnlhMGLSJy3nOKlYwPt89jrvD9BpsQXlWwRZZE3dRC/LIrS2lXtw7vHgI+pbXbDa11tm3trq6uuPlUvmTdY6hv3D3XbGlrf5zlHg0vVdveqTh3l9/EwSFrJyUr2zUXM2NpPlPPi+eHi+jnwUZG6PhzrXMvfNHKhAYhmM7q7V3mkL/9O3HU56dri7Mri/NlstsieW2PpWu3qwc+XNKpNCPqatR8fm80/AQUEAlj1qvm2ZwzVnbiHE7EnpnO2IQ2WHxheZo+Mgbg8JiVt6RdG3I2waagVmX7O+N8eYUPdnHJiELvXyJdlnsXZ2oHauamJ0sxh71hOBupsNg8nzMkPTcRyUBdY9RntK9yQM/tAmziIVjSnoROfdT8tnEhNY2DPCUa8cI0Sq2CdvbaUuctfBOT7LEGsMpFUuIlFD035F7L+e/I/ePLvLRozY60dJ/nbtMvsaRgXiKs83lU8iC3lHIg5vEnHcM1J2Dfkxr/Jm18C0ZKFNTWkmMxBX+UithmxHVWqaSY4zrVdgSf7asqe3lmNT1Du2apzdZ+XtdRwXGb6q2kU+hefuldRhzWsMx7/enbOw2n2U/+3Qnu6Q07PnJtZWSJtaHlhctFetAKIOmRzOJYWJCtdLC7Y/yVDNA3dc4FuInQkEMJVtnx6HlrhXPBvchC3/Eenl8ZJt48KnHtUKEuQTlxm9VUw1//EjjztzF
*/