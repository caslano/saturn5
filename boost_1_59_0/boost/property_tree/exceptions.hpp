// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#ifndef BOOST_PROPERTY_TREE_EXCEPTIONS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_EXCEPTIONS_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>

#include <boost/any.hpp>
#include <stdexcept>
#include <string>

namespace boost { namespace property_tree
{

    /// Base class for all property tree errors. Derives from
    /// @c std::runtime_error. Call member function @c what to get human
    /// readable message associated with the error.
    class ptree_error : public std::runtime_error
    {
    public:
        /// Instantiate a ptree_error instance with the given message.
        /// @param what The message to associate with this error.
        ptree_error(const std::string &what);

        ~ptree_error() throw() BOOST_OVERRIDE;
    };


    /// Error indicating that translation from given value to the property tree
    /// data_type (or vice versa) failed. Derives from ptree_error.
    class ptree_bad_data : public ptree_error
    {
    public:
        /// Instantiate a ptree_bad_data instance with the given message and
        /// data.
        /// @param what The message to associate with this error.
        /// @param data The value associated with this error that was the source
        ///             of the translation failure.
        template<class T> ptree_bad_data(const std::string &what,
                                         const T &data);

        ~ptree_bad_data() throw() BOOST_OVERRIDE;

        /// Retrieve the data associated with this error. This is the source
        /// value that failed to be translated. You need to explicitly
        /// specify its type.
        template<class T> T data() const;
    private:
        boost::any m_data;
    };


    /// Error indicating that specified path does not exist. Derives from
    /// ptree_error.
    class ptree_bad_path : public ptree_error
    {
    public:
        /// Instantiate a ptree_bad_path with the given message and path data.
        /// @param what The message to associate with this error.
        /// @param path The path that could not be found in the property_tree.
        template<class T> ptree_bad_path(const std::string &what,
                                         const T &path);

        ~ptree_bad_path() throw() BOOST_OVERRIDE;

        /// Retrieve the invalid path. You need to explicitly specify the
        /// type of path.
        template<class T> T path() const;
    private:
        boost::any m_path;
    };

}}

#include <boost/property_tree/detail/exception_implementation.hpp>

#endif

/* exceptions.hpp
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
*/