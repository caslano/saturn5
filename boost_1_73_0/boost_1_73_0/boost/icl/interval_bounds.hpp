/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_BOUNDS_HPP_JOFA_100330
#define BOOST_ICL_INTERVAL_BOUNDS_HPP_JOFA_100330

#include <boost/utility/enable_if.hpp>
#include <boost/icl/detail/design_config.hpp>

namespace boost{namespace icl
{

typedef unsigned char bound_type;

class interval_bounds
{
public:
    BOOST_STATIC_CONSTANT(bound_type, static_open       = 0);
    BOOST_STATIC_CONSTANT(bound_type, static_left_open  = 1);
    BOOST_STATIC_CONSTANT(bound_type, static_right_open = 2);
    BOOST_STATIC_CONSTANT(bound_type, static_closed     = 3);
    BOOST_STATIC_CONSTANT(bound_type, dynamic           = 4);
    BOOST_STATIC_CONSTANT(bound_type, undefined         = 5);

    BOOST_STATIC_CONSTANT(bound_type, _open       = 0);
    BOOST_STATIC_CONSTANT(bound_type, _left_open  = 1);
    BOOST_STATIC_CONSTANT(bound_type, _right_open = 2);
    BOOST_STATIC_CONSTANT(bound_type, _closed     = 3);

    BOOST_STATIC_CONSTANT(bound_type, _right     = 1);
    BOOST_STATIC_CONSTANT(bound_type, _left      = 2);
    BOOST_STATIC_CONSTANT(bound_type, _all       = 3);

public:
    interval_bounds():_bits(){}
    explicit interval_bounds(bound_type bounds): _bits(bounds){}
    interval_bounds all  ()const { return interval_bounds(_bits & _all  ); }
    interval_bounds left ()const { return interval_bounds(_bits & _left ); }
    interval_bounds right()const { return interval_bounds(_bits & _right); }
    interval_bounds reverse_left ()const { return interval_bounds((bound_type(~_bits)>>1) & _right); }
    interval_bounds reverse_right()const { return interval_bounds((bound_type(~_bits)<<1) & _left ); }

    bound_type bits()const{ return _bits; }

    static interval_bounds open()      { return interval_bounds(_open);     }
    static interval_bounds left_open() { return interval_bounds(_left_open); }
    static interval_bounds right_open(){ return interval_bounds(_right_open);}
    static interval_bounds closed()    { return interval_bounds(_closed);   }

public:
    bound_type _bits;
};


template<class DomainT>
class bounded_value
{
public:
    typedef DomainT domain_type;
    typedef bounded_value<DomainT> type;
public:
    bounded_value(const domain_type& value, interval_bounds bound)
        : _value(value), _bound(bound) {}

    domain_type     value()const { return _value; }
    interval_bounds bound()const { return _bound; }

private:
    domain_type     _value;
    interval_bounds _bound;
};

}} // namespace icl boost

#endif


/* interval_bounds.hpp
9hQ2SsI1qCoQ3/pJluWf2gT+gNbe1G99shzVIWP8OG2isn4ci0GxI6POLkwraNtTrz45INwH1ICY2FOQKvgp5s3u5i0t+uUIoZ+Q5pO0YX/E7lxrf1nTUpZ15LVJUDezxtIb8er9mSOaeIf+AvQJRIrUnmwdTS4lZ4cJ7ed4b4SxsicIoohcQx7r593v8MsgDoZxgRFj2Z6h6cMP0jD6Qoy+fgmpwi8cDZOwFybh/8Pk3wiTsAmTcCxMwm0vRp5wDGAsqo8w0F31ccYmQ1eilxKshG910W9HT7tz+Y2C098OyAPi2TuQvLMjjmYEpOOH5sxicxoHqw4/0gyQkw46Tkodu9Qg/fKUV3P4jpXFKb6QVEe777YraRYxv3iiifeMqvde0OFNejychQPGwnaSsHRX7i965JfTPmg9kz+O7BgUHJ8r2Hogx4coKPbPdg1jhKP7jw6DCOk6pLwapcQYbogHQ3uHIdb+8VCUwQ6fapPeN9q8byjFLBSxkbxpV+NyrG9Zuj73sfnIciVjJESgC6q6U2E8VH6R6eyL4ptTxNCIgi21xCkEwwbH5BOdjeIgU7KDMoxTEXdNuHH26zHG3HlNAJ1CHtPqEPF5Pgg7/m4aty/lA32DK+V69uc/Wucx5NeVde2187zyN5q6
*/