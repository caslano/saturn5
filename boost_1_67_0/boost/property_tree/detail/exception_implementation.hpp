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