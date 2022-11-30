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
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
*/