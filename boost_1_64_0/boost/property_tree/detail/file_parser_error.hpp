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
oDAbx5r70QiLjGwbPJoj3gOhIXkTijArMXYXHF+CgTjpAwxGla68QWsA1SuE1Nm/wURO2vHWJY/o9spvsc8jZfkFH1ewo+5Ad3yyPreGzzUiPf6t5ksf32gWYD8WSRaY7wbepeaXHpoJjG9kFN+MKCwypgdc5SOcgzJHyuvurHKXDsks1mT6Idmh4sBZlNe+7KYVxhIrVEDroceDnEXnWXTehCQ9zFvM70SF0QJRUC19wd2kNzysghNeO1+Ps/q0BTqrvJKShIE6mkG1lD3ulACQsQ/nfSqPZOD0ChXtIunjr0k2czMwO+RO44Ee+7IRkbIMpve7cYY6G0w4cuWxkg3VEIlSczFgta8XHbGXE1XToevZSmseLLRZSGNYB+ZVl9HR2P92ugUXDt0AV9I0DNeErqTgP/PwcyDwKPFCx01CJF0S+wKG6GWHflGuGt7exDYy7lgNeB2BCxeAKE2YsqhTo0r4YmpXZ/Q90L8FKDqvt34JmNjZUZZzV4CIIqHl6D1M8CbicSfsgVRxQsH4tJo6LKDXcKEbxMDn76F8+kl/CrjtiBgYRNU+iA==
*/