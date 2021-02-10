// ----------------------------------------------------------------------------
// boost/format/exceptions.hpp 
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//
//  See http://www.boost.org/libs/format/ for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_EXCEPTIONS_HPP
#define BOOST_FORMAT_EXCEPTIONS_HPP


#include <stdexcept>


namespace boost {

    namespace io {

// **** exceptions -----------------------------------------------

        class format_error : public std::exception
        {
        public:
            format_error()  {}
            virtual const char *what() const throw() {
                return "boost::format_error: "
                    "format generic failure";
            }
        };

        class bad_format_string : public format_error
        {
            std::size_t pos_, next_;
        public:
            bad_format_string(std::size_t pos, std::size_t size) 
                : pos_(pos), next_(size) {}
            std::size_t get_pos() const { return pos_; }
            std::size_t get_next() const { return next_; }
            virtual const char *what() const throw() {
                return "boost::bad_format_string: format-string is ill-formed";
            }
        };

        class too_few_args : public format_error
        {
            std::size_t cur_, expected_;
        public:
            too_few_args(std::size_t cur, std::size_t expected) 
                : cur_(cur), expected_(expected) {}
            std::size_t get_cur() const { return cur_; }
            std::size_t get_expected() const { return expected_; }
            virtual const char *what() const throw() {
                return "boost::too_few_args: "
                    "format-string referred to more arguments than were passed";
            }
        };

        class too_many_args : public format_error
        {
            std::size_t cur_, expected_;
        public:
            too_many_args(std::size_t cur, std::size_t expected) 
                : cur_(cur), expected_(expected) {}
            std::size_t get_cur() const { return cur_; }
            std::size_t get_expected() const { return expected_; }
            virtual const char *what() const throw() {
                return "boost::too_many_args: "
                    "format-string referred to fewer arguments than were passed";
            }
        };


        class  out_of_range : public format_error
        {
            int index_, beg_, end_;    // range is [ beg, end [
        public:
            out_of_range(int index, int beg, int end) 
                : index_(index), beg_(beg), end_(end) {}
            int get_index() const { return index_; }
            int get_beg() const { return beg_; }
            int get_end() const { return end_; }
            virtual const char *what() const throw() {
                return "boost::out_of_range: "
                    "tried to refer to an argument (or item) number which"
                    " is out of range, according to the format string";
            }
        };


    } // namespace io

} // namespace boost


#endif // BOOST_FORMAT_EXCEPTIONS_HPP

/* exceptions.hpp
SdpajDCKRFoJDul9Sqt0jeFSCaWUjfg8m2VdW+FJZjnPxCzbSmGWsn51qiWyqdNH4I0EyaETxAC134Ca57RQI0qExqZbV1SUxjMtDMjyGW9BkKoa4dCVEjEcgUA0qmWondAgeyrVIDgTKtpDyeudjSjrCFR0LcNwKAvuyzkKb0DHctL2+3shtlFGlXvJ30jZM/ccOENWoFsROJEO61RQYcCtE1/6ixhurTC0vHgJ/hewvOWId+V4F1gbFKO2QDZNSwSyaIHWTUVJvhP8p950zYwvYb4IXT+IkzCOgiSywxs7TOaR/RccgX5wAn92TNX3Jx30iq5VAcCxeXRs7qNBzRKSisdEEKlSjS9WlUDg6BI869rWfoi+2sMEy15ptYaT9h6P36+xrsYb1INES88PIifSPlCWVV1O4FRFHSqxPNP6ABlH+2syE7UCH0uskQpL5UdEDKg4u4NMkK/TX/uQF3Y0D50gdnxPC1JMRTpswYrZMn7BUpkxZ6rvFXwoI0Y2cjhU1B9q72yOeWRSa8nXjghpYqspzj0/tldF8Hm4lQVJZYfVNMHbgA2EYjwFNwDA6CimqpI7pgqD1IjYF0dP+Yu1cGNtv58FoR/7c9+NNEWiN9l/W9eBa2smK7RBlz6Tv71QjTIqJygBLSbK
*/