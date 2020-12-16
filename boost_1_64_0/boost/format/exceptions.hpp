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
6og36QvMgS/gH8zNRGFQiyjlnROah5R3ivJbjhFIYfeUsjsKtxjAYaOYPhH6SiQGEljy9uwUShWyfCJH74C6fDH+qaW4lPRo3wu7spbUsCI91mBbJmXqTFWmXs3tBpJIpi5+TdnRZcidw8ZHioOXVqAuwf/XMtX/1732zgfPLTWfD5ZfHMH54EYC16EXrrN9PjhpqULvf+6xdT6YZ66vof36PGp94+3VV/y8+fzzNQ5X+vdF8W8IgRr/5j678W8QVMa/GS2gwve/Wn7xaJv9/1xI/y+MxL7ujRD4DVMiGD/jnzPb/79abKM/mUFdtqiabAIMOw+YDr4nHxKk8IzxcKvTQVp72FPAHM0mlzycefZKW60jYBooX956ih0O1DLin7IjW5QgiY1P9wPhUYI+O1O1NYKZ9FMRKQKnrRCMHiNGJZLgSHqGaWjyuGiXE51DCTQFrQQaKUjGmvFwsxEQhOknUJ3wodV2dzQmkuWLSF1kgBAScIa2BlZ5M9FOy2Z40qU0w6IZqn4fmmGfQpUi8RVkcZm7v9qI0U8wb+/Ved4ANU9jCprxqaU3gbjvUYMeYYrOX6IyvtHE+EaF8Syt4RyFcSmvW3LeV6Xvmelq6E7gfJXwnYzL6G2qe01cZbrjkqg06Fa9tHNCW1HaaSgNC6gAKJyFALSMShQmvvAdf8zd6DIyQx/hq5OBfAm6gyAFoxNURoumqcHLgdEUV2gd0cY6wum7srVm4HmYbNQ2kxkTT58B6biZGTafQmeArUYanr5M7MifoOIYhIC8JpMVh87xSTNGOykCexpos5P6oFXV5I9ergtK7S3BYwjdwInQcfA/vj0ahW814M2f5VQ52WEe9Jjgr2RRxmUqc9IRWibaVGaPRRm3qcxyizIeU5mpFmVSjWUCQ80Fsk0FOqkF6KsylUgNKWEmtg5sf/A6hk9ofKaeCQb5AOqmDqCxUww3HX0s7oMXv5J6hq/EG/qV7DEN8T1hhrg7dIh7tX0TigU9fVR6vnlInx1AXt+rj/tr1GKbjcUOqnlbVnKrbZmy/0UelJArFr8CIQIddsyyoDbVehLnGkWJMm4hW516iHx1/5ssEpUNuC90rky0mseMc/ChyQY2T1KxvNkYxWGhOtWvMRY8q1I+pQhfHQX1mRbPZ2PShjdyoCvHTB2nkt7ZWJnDKYmvqxarbizmdlpPPbJ8FijwafZ5nO7G6lnl+UqWT8J/hXtIuXJgbnGww+Ao4C2UqQQjUwS4dBzrNVdgEr3fupy91wmBjjNCB2L8PXFRMhczD2204h42p+aquo5O8Psw/A6D31PwO2C1/rtqlf53z98/f/9cwp/I45v+l70jAW+yyCZp0oYeNEIL5RAKFAx3OS1QNMEWghaonBVQynJVbmmK5T5VakEREEF0RVZ3cb1FoWXVpaKAKCvgbVHx3L8bD0AFPODfd8xM/qQppCzs9TV8TP9/jjdvjn/mzXtv3vOff+5TorxUtJg1RXgmtTPjcDS/GtQ8PmW25hxx+zuV9AWSnkSlgKOcdJMhKVk78wQmfc5J10ASUz9fP3EkPF51qPtvW+n+23p1/+1+df9tNdfz9neRtETtorsur9NhpXkWes8WThFLjFaO35wE2iBlZnj64VYjSSmUZTJZqtrvPqVTka+kqqlLSVlmuZltACNYuhCyHB+RZVIQTV1R8buAHE1kDtJdKUgzvDqE+soArvXQeqx1VmCtO5eg+T6AaARjqBe1AFDSzxriiYZoB/zPNtCSXNcIrmtCqLoGYl14k0ZxM5PF7pQmryk9AASIdu066LpxQM8rLhflRfPA6cKgwyGmCpo+ItbnTJQqpSOUbJ4UU4FekJosY0X77w0=
*/