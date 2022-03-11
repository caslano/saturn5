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