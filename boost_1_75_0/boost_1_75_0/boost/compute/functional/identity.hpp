//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_IDENTITY_HPP
#define BOOST_COMPUTE_FUNCTIONAL_IDENTITY_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_identity
{
    typedef T result_type;

    invoked_identity(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// Identity function which simply returns its input.
///
/// For example, to directly copy values using the transform() algorithm:
/// \code
/// transform(input.begin(), input.end(), output.begin(), identity<int>(), queue);
/// \endcode
///
/// \see \ref as "as<T>", \ref convert "convert<T>"
template<class T>
class identity
{
public:
    /// Identity function result type.
    typedef T result_type;

    /// Creates a new identity function.
    identity()
    {
    }

    /// \internal_
    template<class Arg>
    detail::invoked_identity<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_identity<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_IDENTITY_HPP

/* identity.hpp
p/unbUnRTNUh5lnHrcZvaArS9QqcPxM0Nxl2BeI/+Kq/SZDHgtNGSJ9aRoBSuryvsenEaBzfPGllXWH2+2Aj8T2i4ek/3FzDO1y0w8bLfqLti8+x5eaqIyHcHmwnKDdPSVNhptn93idu22WxmCOiSGBIx3LGPSH377calyyUrjWDNSJSuqeOcYuyGYgW/ovnsGtAuYlwu24T/3J/MWAQyP/pk5mOLGbCloppk6iP7reU/tGKK/G2HZ6fCSitAdXP4udOIIlrYZOeOK96C5WoOYJpYnlraUZIcPvaJ5J0g7MPDjb2sq+nJLRWPAcnvEOjdUVUm5O9Xace6ezamhdX7Mz0skvqIqII5OzRAc9N3fov4dRKGxa+8rqidNsm3FUppIL2CHdX2EIq70pWqO9QbPnbc6ykoHuPFptxdO7izCOlsBdrTVdqM2rEPOrPDo8yVL7peLdNFOhAHerK7evXDJlzXV+dtLur+5034cGn84xCrwd3fgk+HGp+8HLTvX8sy2fmE3a4hyl6VbIKyeB09/awmO1lg1ADq+m6dcV+iwYgMexlir0+/VFGX9ImoUU9YD6yxdW69/3bTfCb9/QWtVQwhri1Dy+zxD50qUKjL7pDyjPyo9JfMhLlZ24f6NKnWX4XQ5t6xDUuGoXCHclV/fohSbm57qGuRJkzOup3b4jZzTwTON6NMKCc4L4/1WiCeJ45fP2oxzWen+ep
*/