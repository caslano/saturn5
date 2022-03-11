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
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
*/