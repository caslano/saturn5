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
1Uq4hfhLppO0rlRlA6RimZuIb2UyEfOPom0F/w+PSL1Jc9Fs1Xg9Hdk7fGTMgDWV87O2ZsXjndYKP1fz2bv/hq0dr9JzNfnVIrwxPlzZU2g6XW5gH04AzpmD89EOsIlRbV6nGfo75SZFGpDRVYBx/VkjjOa5ae+cDQBjt3C/uWl4eKMC46SzAWAMCv9PMLY9wmGM/In2wf6Nw9j6Nw6jWEkYg37jMP5xlmDccdgPxtFhxnpWCOHLv5og3FVggHBTgRFCUS6erR4FglvQ4uE2eBDJoNLqbEsqEhyw++wHEbshfJZbz6TDO8apqwt99oXgBG0K0jUo6u/RTIe+qu3xThte1Z/OmKp6p7Gq9eByXklniNJ4TbJ9QVmNU6VCdniN3HwKhiFQF4ctBeOnWMU/1BrLllNAlWInytXDE+V+3isoJ8opb3m7RKInmFRoy12sI7H1KKk4236X/PZARmSraajR3vQPlfq7vKZIfKttmsQzytxlQVqcFO4ZFKmX9tqKNMPn7zxN0k7L1nHSP/xoFdUVX7DlLKN2XUYvlZW8yyr6xHkmAmJFIjDlNBadxNt1+1a8MVlt1w1bWT/FLGLznXKGsq2EUvfMKKy3pqm75R3UYMGlwS7puOjRNe0R3PZn502fL0W6rOkj3jTpY2GIpo/yKVUfEY9IxA4UchFm9L5OevB8DDwLzZ1Yo/w95T44IGh7ymFc4rN/fZrr
*/