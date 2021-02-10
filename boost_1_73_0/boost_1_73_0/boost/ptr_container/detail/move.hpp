// (C) Copyright Daniel Wallin 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// Contains the definitions of the class template move_source and the function
// template move, which together make move pointers moveable.

#ifndef BOOST_MOVE_HPP_INCLUDED
#define BOOST_MOVE_HPP_INCLUDED

namespace boost { namespace ptr_container_detail {

namespace move_ptrs {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)    
#pragma warning(push)    
#pragma warning(disable:4512)  
#endif  
    
template<typename Ptr>
class move_source {
public:
    move_source(Ptr& ptr) : ptr_(ptr) {}
    Ptr& ptr() const { return ptr_; }
private:
    Ptr& ptr_;
    move_source(const Ptr&);
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)    
#pragma warning(pop)    
#endif  

} // End namespace move_ptrs.


template<typename T>
move_ptrs::move_source<T> move(T& x) 
{ return move_ptrs::move_source<T>(x); }

} // namespace 'ptr_container_detail'
} // End namespace boost.

#endif // #ifndef BOOST_MOVE_HPP_INCLUDED

/* move.hpp
L3Rlc3RzL21hbnBhZ2Utc3ludGF4LnBsVVQFAAG2SCRgUEsBAhcDCgAAAAgALWdKUkfYzRsmBAAASwoAACUACQAAAAAAAQAAAO2BDLNEAGN1cmwtbWFzdGVyL3Rlc3RzL21lbS1pbmNsdWRlLXNjYW4ucGxVVAUAAbZIJGBQSwECFwMKAAAACAAtZ0pSTpspj3YLAAB1LgAAHwAJAAAAAAABAAAA7YF+t0QAY3VybC1tYXN0ZXIvdGVzdHMvbWVtYW5hbHl6ZS5wbFVUBQABtkgkYFBLAQIXAwoAAAAIAC1nSlLMgQPM1g0AAIksAAAkAAkAAAAAAAEAAADtgTrDRABjdXJsLW1hc3Rlci90ZXN0cy9uZWd0ZWxuZXRzZXJ2ZXIucHlVVAUAAbZIJGBQSwECFwMKAAAACAAtZ0pShjinQHAEAADrCwAAHwAJAAAAAAABAAAA7YFb0UQAY3VybC1tYXN0ZXIvdGVzdHMvbnJvZmYtc2Nhbi5wbFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJYgI894AQAAB0MAAAhAAkAAAAAAAEAAAAAABHWRABjdXJsLW1hc3Rlci90ZXN0cy9vcHRpb25zLXNjYW4ucGxVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS
*/