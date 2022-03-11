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

        ~file_parser_error() throw()
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