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
#include <string>
#include <stdexcept>

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

        ~ptree_error() throw();
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

        ~ptree_bad_data() throw();

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

        ~ptree_bad_path() throw();

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