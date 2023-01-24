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
RQxby7rpJF2xZuiKnWwo9s+ZotibQhVr2LtRmD6QaWqkEWc2EXQPptY3zaq7M1UXhgBApJIybWOSbN56GyeZzKu4ZXxfvGGp4u7IKn/r6SxNzsS+SLvdcNMyTbH2d0NNmOy4jqVSrPlubnhOQHy1mVoD+CDn2CO4w60aUP2jnartGfe3fdYjp7JM/v7ODJUMVv8q2uCmj/iql8m4/+AmxotcT7O+WKWV1lVXD9bfdRm0zJAQpAP7hUudue516S3mz1VpM9cencVcXcL7lw00GM1h7npwoJ7oIzOAIbT8d4JKHNpSdHQGBNL7BH1pYXBU6FvfCU7/sEjg3I/ho6LCwPp1VZmqdwpnfZ1Jvzd9Aew4pClWz4xM8oFpDw9echbQN+5M1uz9L9HBQHR8Pk0bZxhNnY0z9GdjKeBesV4PdNdnANleSiOM57ncwaaOD+w6v4n61qtMBfgUjmGr45tnrq8MtIdadAMf4kab+LrprGg1TSonL5uTl4rkLZ1O0uYN/AZ/pKo0LuyaZabim0wBtO7jtMaj0Qi0W9iXY6IkF0RJE6v3dK2T/RKjJ+v86WJMfxPDi2zgYxqKwZpzPsbx2jcEjuLj09WRHs/TpAa20LbpuhY6xlsoidf+GJLyvBtqz5r5mEnji8msudKAYKcTtQUxKlUJvMRjgVSN15e4j5d4iPNkH5aYy0qEAuEO5Ldfq2wiz3ZfYLbJLNsV
*/