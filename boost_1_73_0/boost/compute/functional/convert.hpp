//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_convert
{
    invoked_convert(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// The \ref convert function converts its argument to type \c T (similar to
/// static_cast<T>).
///
/// \see \ref as "as<T>"
template<class T>
struct convert
{
    typedef T result_type;

    /// \internal_
    template<class Arg>
    detail::invoked_convert<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_convert<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

/* convert.hpp
uYJ99vRI62xmjNgvcY6xe1gfyrcNssQ+GE+aNcJaRGq3kMNHWA104jP54/nGsoL90SgJc515H/SVmDuSli90bZydZmPyZkylbKRcNQ+c3plnb+Ws1pji6y2E1fjF3wKrNmNAOv3mMZ6PWtbnnS2F477AV9/RfUSTCHvfLrqS1O8q/J5y/C4e6/WjFaseARiGQ/felbp379zW4fop7xezS9II5Gd+A96Rid6+y9GslkkKaR69
*/