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


#include <boost/config.hpp>
#include <stdexcept>


namespace boost {

    namespace io {

// **** exceptions -----------------------------------------------

        class format_error : public std::exception
        {
        public:
            format_error()  {}
            virtual const char *what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE {
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
            virtual const char *what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE {
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
            virtual const char *what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE {
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
            virtual const char *what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE {
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
            virtual const char *what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE {
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