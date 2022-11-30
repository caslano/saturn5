// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_FILE_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_FILE_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <string>

namespace boost { namespace property_tree
{

    //! File parse error
    class file_parser_error: public ptree_error
    {

    public:

        ///////////////////////////////////////////////////////////////////////
        // Construction & destruction

        // Construct error
        file_parser_error(const std::string &msg,
                          const std::string &file,
                          unsigned long l) :
            ptree_error(format_what(msg, file, l)),
            m_message(msg), m_filename(file), m_line(l)
        {
        }

        ~file_parser_error() throw() BOOST_OVERRIDE
            // gcc 3.4.2 complains about lack of throw specifier on compiler
            // generated dtor
        {
        }

        ///////////////////////////////////////////////////////////////////////
        // Data access

        // Get error message (without line and file - use what() to get
        // full message)
        std::string message() const
        {
            return m_message;
        }

        // Get error filename
        std::string filename() const
        {
            return m_filename;
        }

        // Get error line number
        unsigned long line() const
        {
            return m_line;
        }

    private:

        std::string m_message;
        std::string m_filename;
        unsigned long m_line;

        // Format error message to be returned by std::runtime_error::what()
        static std::string format_what(const std::string &msg,
                                       const std::string &file,
                                       unsigned long l)
        {
            std::stringstream stream;
            stream << (file.empty() ? "<unspecified file>" : file.c_str());
            if (l > 0)
                stream << '(' << l << ')';
            stream << ": " << msg;
            return stream.str();
        }

    };

} }

#endif

/* file_parser_error.hpp
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
*/