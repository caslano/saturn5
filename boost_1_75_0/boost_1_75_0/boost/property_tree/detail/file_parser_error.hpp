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
3QjRKXTJtklsb1Nl3Eza7STaxtWNy5No90eFtz80/PZjvGKDZpL6gEakvHDlhBgld0cwW7FfFKnQ4XrjWYMOgNCCdDi4DqNDkdHhiWWqQb/p1s/pl1/W2LDypwzOfK/ieYpPvBdA03r7z1NM4GSY8p4fGYZU4ZTB6q9xtSuRUF1uf5+rXdj7TO0qOz/x+Htc7ba/p/ZNvMx6lN5/VajMKYNj3vXjv5eM4f6nLzH+S2C4fNcd+W+Bbm7pnggldOnxkkKCOXy+XfmnDeKU5IpsVfGiAOjssvihs56T4ceL/MhwZiXIMHMeR6XvbGzN3Hc5Ks+9qzNRlSBD17sclQ7vqmRYnZFhtXkVkOHxd8xkeO+LGhnuRzJs/CIjQ+W0wRYORoZ4wOBD14AMX+xMZLix8scLjnnHD/8pJvyn0GrBrWzgxu0dEpNRARMOnsP5jyedPNmJJ9vwJB5Rqux/4fIMDnd5xke6PJOjDA4YnYF8WNkpWt3AFtnL5ekxS+4Up2xTR8uQ0moqvPNDMC6ysuVuNrpjuFQD2OfnCMY+/dVB6vaMhh7+UBXuiSLQkLdPlPz45ED+2C0YCMe0K5LxX98KION9/RkomTPQ5rf8GKhmFRholpfL+hMzUUbfepvLeu7bt5J1IwMNfZvLuuttlYFmMgZq7FUZyBTZGs1xyUKzBHZ8QTDNZ2n+gsEHa9dVd/b7/p7apKjNz5u8sPLZ
*/