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
6m3K3/nxX+BttK0tEz1T6lZba+qcC8kMaMUUlKbqx59H044lAChnFbMPYTIErvV/dT+MpkRr/k0DWrz2dE5y1njSyrWGGvZ1ZWmgljhJBt/UnhqhaikCThi5x70Hua21GueqJ/98+qh8Y+Mwz99gE7UyOLLev0sDaT5djrJS2LSfCQnNYB6HRPDhArR00t36dHs4GWoh9kvFbAE3Ib6SmgyZeyJ/qb45T5SVDgA5SnRFSp6rWbXVVkPs/KJUo0qw9M0m3AlmMZ/goFucpJC+kwqbuwl62ZKnC3WBjd0lQx/DvuwHCqleucfoVLN9/dNJK3pG0SUkmmabxZXEtzAkSS/ya5YkhqIZXTqKvjzOT1uMVgavch7Elqv+PK0G9QNv9mXrZs/8te8FKvwT0k+S5AGXuZtbOK4ULiTseLNWuMhyslha1aslxHNOPXee0ChCdQmGVjKmkOgxiFFFYzIux+fZysS6uMyY+v2IaMRiE6VlWZ/I5457uQY15IyRi29kASZqkVkHbfi+uL2yGL5LbM45lboaWDu90/2gW62OEENlOHn52feR1xyDbg==
*/