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
#ifndef BOOST_PROPERTY_TREE_DETAIL_EXCEPTIONS_IMPLEMENTATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_EXCEPTIONS_IMPLEMENTATION_HPP_INCLUDED

namespace boost { namespace property_tree
{

    namespace detail
    {

        // Helper for preparing what string in ptree_bad_path exception
        template<class P> inline
        std::string prepare_bad_path_what(const std::string &what,
                                          const P &path)
        {
            return what + " (" + path.dump() + ")";
        }

    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_error

    inline ptree_error::ptree_error(const std::string &w): 
        std::runtime_error(w) 
    {
    }

    inline ptree_error::~ptree_error() throw()
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_bad_data

    template<class D> inline
    ptree_bad_data::ptree_bad_data(const std::string &w, const D &d):
        ptree_error(w), m_data(d)
    {
    }

    inline ptree_bad_data::~ptree_bad_data() throw()
    {
    }

    template<class D> inline
    D ptree_bad_data::data() const
    {
        return boost::any_cast<D>(m_data);
    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_bad_path

    template<class P> inline
    ptree_bad_path::ptree_bad_path(const std::string &w, const P &p):
        ptree_error(detail::prepare_bad_path_what(w, p)), m_path(p)
    {

    }

    inline ptree_bad_path::~ptree_bad_path() throw()
    {
    }

    template<class P> inline
    P ptree_bad_path::path() const
    {
        return boost::any_cast<P>(m_path);
    }

}}

#endif

/* exception_implementation.hpp
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
*/