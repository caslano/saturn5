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
Y+qMSBWMny6V14msGl+JKxrfFgfkyd1JHcUJNe2EceUYEXmjHMhS41D+DRasv1mtyd3bWk1V+xpynDG9l3kcc0xUJHQn+3KNq5x+bzEUHHBCNnC+//9+xILLXtn6RYIjNh8VCkqnn49q51+lBs+29ng8onRXa8u7rAP2WdHf0D7HHl82795k7nH379YDfabss7T/if1KVzOHr2dt5bJ385xt1/mn/MWEfQ/m1llq2r2rBGLIOve/70Otrfvah62Tc1rTrMEZ84COY3unX1dc1Zp0NeuUx5d9j69Z2CfL1tX15++G7nBEjTGhx1iD2fuhvMR9TqjJrUdVO3xV+7z8nP/7nQjrWtq+0Wu5wa+tnvTsM+fMQei/379P5MwT7SSd66qlWKTJhLCxhx4bChr2W9de146SInJ34xfr9Jlzxt9bKfzQui22xH0xT5MRocfLjzO/UA+2tSPW2YR4RIEmI0L+pvc6UZJkKNBgSPAE24lyQI46A5Zc0e+Yb9P/p7kpxo7kK6bE2T+tWWLH7xkH1uzaEx1H8CR1f4ocr6y+4gkVWsbaEVf83vHhW9wTefdJ3HwgSpJjyrSJ+33usRg80Fj/+z1I9dMuXdk18LfMp6zoY5hTg9M5815rAWf0szRnc1cxJ2xPkqVKn9BVjJlt9jl7N2MSk2LiJ9Yd7QVxc+6y/nfD6om10HwM/hF4jfU+5VvWQ7G3/r/f48myY780FWZXl+v/P6OsE72G1411YxNXzKu2OPY4dE2vt1c1dpKkTj+rvJZjGLJ+bXP+/78rE1zHawwHL9c3O9onVzVvGRBcTb2JkqZCyj5b13We07VXPJszNs8HV1dzdklTpMOMM9eQ5/XUTaz8/3dkejdSh01fw39Lnd+lBktrmVpUb249ce8OWXLZP5/r9Gdl5OHeJPkyORL5s7pyTIUuU1b/4n0QSY4p0WbKyl+9zyFKgiMKNBgSLGxnj0MKNOgz48zfzhVE2CdHiwmrf/c8cdKUaDFixd+72mCPY6oMma4b+6u97ln/d43rkAIRj1d/7hh2iR56nRULtBiz8gt5skPhW7aLy6Hzvktt36OuP5QPE+12xPpt3V2Q97/hr/EK66KYPn1fdeI1XXvOmW9bG7iiv7e9OP2e/EfdF3cwJ9h4qfcCts3Flcc6B1GSTO94Du8XvFa19W88TfvXtbssWP28XImyT5YKbU7+7b0gi4/qv2Fsnzduv4ScUoPgC/oh7X4rftrYGdN1XwQttbR/yL7r2uVnWb+ZsvpP43W+zlOtxQ05MtGuisEdzum9mb7//zlT+4O2sfIh/bLLATnqxMv6Y6C9EEN1YyGiNpG32M4RFXrMuexb9UuaKj0WnNHvNgfkqLPkimXnI3b6uZa4/IfXd/fCFjuvcL5/mBtikYj2/pe9V9EeUV+e/qyVY//5v593mD3be3lr5yYNBiw48xz3BHtkKLH2dLXx3vno09aOE7VjxfVNU2bria4XPe21l/kahpPP8UQ1eKX33nQce/xY/VgfS2KD2lW9FxDXXYvqo2xjaB0PPVoONMzDpLG17moMtPPWEWvkjPjdXQ9rQ0YsMmbjLd4L7Lo2YkzMUKTJiNA95EOMDCXazDhzTzUjwTFVuiy47L3MdxrOu/Iv7z3E4PTrFbZI2nZMmS4z1mJqZttZsXZVtWHOmasZG3tkaDNl9eqeJ8586bX/n+cMoqQp0yf4l/uLOFkaxK5vfoql6//vZ2PSFCj+1XvrH1rHxchPXDtKjF56+rUhp20OvQYEP/V+mW1SFJhc15wXxwQ/s50IcaZfcZ19PZXRbjEmNPZenRgZKvRYco2fe540RdpMifzC+chQZMCSy/7S8e8xlm8=
*/