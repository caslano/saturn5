/*
 [auto_generated]
 boost/numeric/odeint/util/state_wrapper.hpp

 [begin_description]
 State wrapper for the state type in all stepper. The state wrappers are responsible for construction,
 destruction, copying construction, assignment and resizing.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED


#include <boost/type_traits/integral_constant.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>


namespace boost {
namespace numeric {
namespace odeint {


template< class V , class Enabler = void >
struct state_wrapper
{
    typedef state_wrapper< V > state_wrapper_type;

    V m_v;
};


}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED

/* state_wrapper.hpp
7wefWqv8D6ZcW5cXp2f9PU6bhzGI7z0xjz6zdjnxDGlg05WYy2wd31bZbbZH/HyuBs+ZiOYLNWiui779S2jD03BPeKGP5YfxVOZrLebN3+ekAV+wdz/ynV89pe+0mflD3XuZ6rOvoy/lfvOa6m9YjL7zW+p96jhiOXyXyry4lf2V6DvgleY78ubFtGLfGvmpSZnvqbbTdFqP+AdrJQ/SuGNCHn3H9GPC6bvouTb3jT/F98Z1
*/