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
PxE5Rn9Swrb0YKojX/Dj+GWrGIG3HPfeN0i2q67huVn02m476JF82auyyUzYdJp1cNOPmneetzWeqachWxu/flC4YOse9X01nteab9+8YnOT2KFfb4sOs8q+sNF0LNPToOxOpd/+UbvqEZdJtY6nX7rd4Btq59bqv+pnxL7KpvAYn+UH7r33cuDLU5f9Qo6dbzt2WnElvu6U/FpsX+iSq1Tnw+hmhahHd0RdXyifPfjFwpCHH5mZ5bAO9HzafsfA4mC71tPY7ZIEosYuiyIPduzZhp/M1tdnHrDsMRbm5btHk/qZT/oo799ceC/7p5tarclBl6M3ObSsLlNVxjINJxquZv0hT3v8ue8wd4S73uwrU8tje1Etl5YFpT3+pmIgcXmulXLUpfir2z4N+vz2lQVVaRp7lixUWnYhtqbxQj9R6WMz3JVet30bntZPeH/dhKAcC7pby6t+frXGEhuuGKuNwny3sbX5lMGX61vOOdC82/uclFfVlNg8LnXnfcm2Ob3+8rzRhsLjSatWJbIXv27O+CnzwY4TY19/vOnrsYUfnp+vtmvHOOrntfXIsd6B6+Evru05ePvDr4x4BMcD/XLnzQIXV/rfTbrc15Pl2x9Xb4f4f/h/+H/4pwQUXD09B9fb/9p1vqBwMPUwnHe7xsL1/d/qSx0UGM7miNnS+4oz85lYfMQ2Ys/2S5nuSxU8NQ7TgkH8zBz23kskLm7eQljW24H45rdEUwe9/dT6HOB690dz+xIHBgVDd+t3+xf/9euW0+WJiZPpWPwbZdGPn37WzWyBpp6p/G4K4i8vH5wYFzfTqVwfutXD6N+U39t5jVw0B+5aqTvK9JKViT+Wies4zZkXbrkMSRB/MTz+c9M3zw5/X93GR0s79//Fsq6bep60xez0NdCnUfy71/1uT00CXOz/rBqu8deiqI/PoahLzqOoe8CVevAjinqiCUU1uYh6cw9guo5/R16rA6ZmfScvJRT8d4ZOXQXrM2lBUTeDc+AOeHwF4m0wDmbnXxceFTqd3+9sl6sD1sH87+RJhTwTIE/qVVhvO5QHXAGPQcw1yB9QO97mGRUdZSTtEwo9+dgLPNkJcJdp6ndFcIvjd/X9mtmOKBi+sx002I5XsB1OkNdB8BhQr0M9gBPgDngMZueXHjFz8nVe4OnPi1lhx4bxeXGhoXDEv+kzNnVrRI8XYghdKgXSdPbqELG0H9ifmT4zRfpsud9cUGa6zIIxiQnxenMSwkIhLjNPcELcOpk06Xaw40LhTtX0DyXf5CGTOLtO2WTIVzZNmo9sGtQ9OxhuowUFBkdA9jM/M5zuHgfFERBnj6vgmISp20EJoTNxOEvP/PIhfqbOAwKDg0Olv097Jx4Q+tFMXOLqulR6G2omPptvwNSGQdqb9OioKOjR9zYOk2fHp8o6Zzxg6ngOCI9BzE2DLOBOWIg037npMdFxCbPxdeHxCdKT5Gw8OjoiEVYzUycBkYERoXCbLDxuevr0Zr8dD4DmFjo3HhkaOXUQv51nagfOHTdBvJ0m3ZGycZM3cenjeKQlg3PZesTb9MS3ZZeufnpceqYKhZK9G5ceV++kSXs0vBsPT5iJSzfhzTnr7R6Z2hfS2Mz43DYQEgb9OqAvYkKMdHNk096UcqqupOuYHZfOPX3Oks0P6vHNgt7eC9/U+3RbmvN8Omh/U8Vhw8ibx8AErmbDKhPefBZEBoWHJUYnxrOn6lL6RBuoz/Dg0NnzMxxiq6dOTVNPiwqdSYuLjoCEmPCY6YTptjibsfRYm1pZUPLUj9D+fObSYxKqWDrX7LKy6QlxcLMVajNEuh7ol/p2ngQ4rthTM04diIg5900D48ISp35kOjc=
*/