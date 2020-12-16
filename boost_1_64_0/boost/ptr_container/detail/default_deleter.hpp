// (C) Copyright Jonathan Turkanis 2004-2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// Contains the definition of move_ptrs::default_deleter, the default
// Deleter template argument to move_ptr. Uses a technique of Daniel
// Wallin to capture the type of a pointer at the time the deleter 
// is constructed, so that move_ptrs can delete objects of incomplete 
// type by default.

#ifndef BOOST_MOVE_PTR_DEFAULT_DELETER_HPP_INCLUDED
#define BOOST_MOVE_PTR_DEFAULT_DELETER_HPP_INCLUDED 

#include <boost/checked_delete.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_bounds.hpp>

namespace boost { namespace ptr_container_detail { namespace move_ptrs {

namespace ptr_container_detail {

template<typename T>
struct deleter_base {
    typedef void (*deleter)(T*);
    deleter_base(deleter d) { delete_ = d; }
    void operator() (T* t) const { delete_(t); }
    static deleter delete_;
};

template<class T>
typename deleter_base<T>::deleter 
deleter_base<T>::delete_;

template<typename T>
struct scalar_deleter : deleter_base<T> {
    typedef deleter_base<T> base;
    scalar_deleter() : base(do_delete) { }
    static void do_delete(T* t) { checked_delete(t); }
};

template<typename T>
struct array_deleter 
    : deleter_base<typename remove_bounds<T>::type>
{
    typedef typename remove_bounds<T>::type element_type;
    typedef deleter_base<element_type> base;
    array_deleter() : base(do_delete) { }
    static void do_delete(element_type* t) { checked_array_delete(t); }
};

} // End namespace ptr_container_detail.

template<typename T>
struct default_deleter
    : mpl::if_<
          is_array<T>,
          ptr_container_detail::array_deleter<T>,
          ptr_container_detail::scalar_deleter<T>
      >::type
{ 
    default_deleter() { }
    template<typename TT>
    default_deleter(default_deleter<TT>) { }
};

} } } // End namespaces ptr_container_detail, move_ptrs, boost.

#endif // #ifndef BOOST_MOVE_PTR_DEFAULT_DELETER_HPP_INCLUDED

/* default_deleter.hpp
UYnmUnpdtDrHXsuIjyXPSiZy5PpT51HCstR0XhbNJX3nMjRHwKNBvv41PEqCXQ82X2ALDTbOx7rFN7aTBNup7bvkY320xTnap5lC6QLvBc9X6t8lIty+j69ZhiFDMqyFsIrgbZxw+JD2vVujsHR/cHr7aWmXjOf6In+jzdDKBwPkm0MpUQYpgx3g3ip/vxA17i7fzDJ8Jt/qYvm2XOv2xnAznz7IIeu/MgwnMNQvOXF79PQkDkRiDmWvnHDfGLGDUaMe3mlG+onJ/R9xaQWDHc2Hvf1+Bx/6+za8u3yoj5OfJREfRP772n2Dx4p0MYQ/tz80wMbN37NB8uIAEybbV+q0g+z+SgZyb7veHwbNXXsFewu26VYdGX3Cxuw6tsk6dj5WJjlZh8NygjMA8oBAwsyzx+8D1kc7w23Aug5H58DL3wXyOtTI8Nlgl4L19bHu1Uufis+u18recWujl+akx800XxMFjMp8GWHiTc4is8U1y3e8IpYuc5x3jUUT9wbodbE02T7ADbF0mesEN2b0H7omjS375q2Z4YxuxJnLzDB9u3N8PD3tkQ67g7CO9samRDCpkJL53ZkZD3Um3nkjjKajz+khavRWdGYchD4Ku88KmyrK/5CVF0+6pPnysAgTV9NEci7CxbPwad4/mq2XtErC/4q5h0F3lXTeu/fQfSRwoYKekkosbE3z7/GQf3iWtS2pjDZ/IspX77SHv6aXiXc1BI2c/3nKpGsG+rpfPQ924z70KX/8Yfrai2Cvg13oRdjLhm6IT9eteX5WnbPsx0mxevNt0mbpUB93sGYOs94A5Ixuxht17xLXN5SLhB18H8ynLVzJlVJVLfJspP2eWuOyRFN4b0NnNDStIYrbJ2tEJ+Od5hz5/ppZZzF8hEi9sB9jLui2M9hnYBvuD18F9pWh+70D1j19V6dtTRbPz4vl+Q9+GYu07PpHGrgly1wQG/mRRBPnCe0Xj8R4+ObMM7opfTJB5OXKdGiswIAjhOIut3UsGnOlLUMFcxDDXwUSOnLdXMvWlhTNmh6zb3w9K12+jLnlDQjPjBp0S6mzNpJp6LFUVPeNRZhx7hIt4v7BHkH4jJKqqTOLjQpONtXrKXYpc5vlxp7dnDJZzBf1tGhGhJ4Cy2IhH3tZNPF8jMrfJ6CfNZP9OQFtQa0c1/e108MhlXc32+HktLCmjhKJNPpBE7733oClw5Jl3G0zgHDp19iNKecdB+bKN7iieuRGOK1snssS/B1EONNepGzt2hT+1ZCsckjqyOZsJeos/eyh4JccQLg/59I9HVmX7Z/cHut3bZ+r9whQIrkllfpZ4TH1i+Z5rD4TJYa8xtLYLBB3ukt+B/KlJUvmly9oZK+XNCMzaTAamiTDZxgd0Zi+KeZq0mHRkVYRLto9nm+EyzaXTNG+6DjCiw4K7OMO3dprzYBBK+K48fojseP1CbmW398aKSP5HvmvAzodGqqpwSJM1kMOPtL7lTLi19NBhM0zfJIjCnmedBLhzx1MX/VlpFuyXR9zjvnpWNk+PuvMN6UQflSR4Y+4z8wqc9xZYMJtnghKKSMlufb5XOhMvacStujQwO8Z3i07XL8o3g6/LOou7mozdaM1cF4jv2a6j+v1rag+MwIsXkyEbzJT00kxifyo3+gwY8U+te/RCE55hLSVmjYaqqbXC9J45BcNFnlbPJ+6wshhVzQBibmfjfDj4XmOr2e6x/OGVOzdie9ZPLfXtfRMRcx98kvrpY6aJ+VDT+LU1Im3TmPOxwY3IeH5ZfgR1bnhOrqeJSSTiP+/JQzXd6Hsk3uA2WnqXTlZe3bkuVxNEcyrEf+tPwTj6BHd4iOTtwWtY7Nt0uex/XZJbrQ=
*/