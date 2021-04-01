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
Qz2+wHHVAVSwziWqgFsg5PdmKnAKevAjsADT3UWikdoTX6crzjbNC9NpGit3a3iM9YqAI9W2x221ZueMOWGQ/2MozLXUdroB7sW/jvnWE4Ogw4xhrHsu+pZCW+nLknJsN2ninTKJ/qAEL1jOV+MaL3qySZe+UHbHF+pkJWIP0J6EfKHa+0C6h2BP20Uya6JAddXXL25EXByHaPEzP6FkbxIlrt3+L4xbbpzwTM884DWNUB2Kye0DsngLR6lfUn65egrBjpg7pPKo88vXAAoF2aflxmUZ/L9suwVfhVpWADQ3Cjgccai535LQIsTyOcm07AYlpGsdN5Uofkgxv4/bOZH+vp8mfxTZH+GWqs627piVb3L/NRiLxr8/F72OuULt9MNHJUd5bHBAmyqKVrFJY4NbnHgoo1Sqi3hRUjvTfPisQ6Oj+9XCblo48lnZCozifAAX2pbTPTOxTWJoZ9VqdweL4sAWAokZsxROs6m5j5b5aNmTZ15Gz8TcZ8PMkyEnBGZYH6jmWy6erhgrkYL5lMGB5Hys9o0U6wWf0cG+DUyayY/nN7l5+9sYFA==
*/