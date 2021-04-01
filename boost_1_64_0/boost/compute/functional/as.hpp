//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_AS_HPP
#define BOOST_COMPUTE_FUNCTIONAL_AS_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_as
{
    invoked_as(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// The \ref as function converts its argument to type \c T (similar to
/// reinterpret_cast<T>).
///
/// \see \ref convert "convert<T>"
template<class T>
struct as
{
    typedef T result_type;

    /// \internal_
    template<class Arg>
    detail::invoked_as<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_as<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_AS_HPP

/* as.hpp
83aaL3krGWWdWvnyBiVfZ2V7Vymp/dIcaZNGIIO3wadDw8DhRXteU8UJGq18GF81bsxDXQ0oqf7xiW9twZTSXheoddq6S0wBT1OdfooqkkHAya1z6jUt6CnpewfYOLKVrQHJXwYc5xGbGrPUlREqLvRy/Vj6yFcpwVZr29WmleBGTwLmPj3EfLIAuOt0mDkYqSNAjJ8AILxCXENdYB/30agLtGiY+u9xmr1MShl4w6gh8c/fuB1bppNHa9GgqSLQR6YMTS6oUs4X5XDpfbeduSxSZf2pLVxGE+U30ivbGVfse/lHDKWS8fyrlnYdxO73MY3sexTYMMWVHld13Z7fR12hYMJHCfORSbjmaGz4Cju3x5JAhohQ4sm4XcDDVrUiFNHQCTHSetEUCzrAPEijlcb1EwixaoRA0QtYPb5tTah7ZbGOlrGF+tpJhAcMHt915YnX0pZvBLKvsDSE7umqGxCEZEqsUuPpbCbsxzsgQvBmWnXWULtk4zwpMslVlUBiqYRYn8AIAMkN/nqcC5Bo5hc67t9lkZOyRkgpHRxfnp4Kci67VzjNeK0v5w==
*/