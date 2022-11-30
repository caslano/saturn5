/* The following code declares class array,
 * an STL container (as wrapper) for arrays of constant size.
 *
 * See
 *      http://www.boost.org/libs/array/
 * for documentation.
 *
 * The original author site is at: http://www.josuttis.com/
 *
 * (C) Copyright Nicolai M. Josuttis 2001.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 *  9 Jan 2013 - (mtc) Added constexpr
 * 14 Apr 2012 - (mtc) Added support for boost::hash
 * 28 Dec 2010 - (mtc) Added cbegin and cend (and crbegin and crend) for C++Ox compatibility.
 * 10 Mar 2010 - (mtc) fill method added, matching resolution of the standard library working group.
 *      See <http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#776> or Trac issue #3168
 *      Eventually, we should remove "assign" which is now a synonym for "fill" (Marshall Clow)
 * 10 Mar 2010 - added workaround for SUNCC and !STLPort [trac #3893] (Marshall Clow)
 * 29 Jan 2004 - c_array() added, BOOST_NO_PRIVATE_IN_AGGREGATE removed (Nico Josuttis)
 * 23 Aug 2002 - fix for Non-MSVC compilers combined with MSVC libraries.
 * 05 Aug 2001 - minor update (Nico Josuttis)
 * 20 Jan 2001 - STLport fix (Beman Dawes)
 * 29 Sep 2000 - Initial Revision (Nico Josuttis)
 *
 * Jan 29, 2004
 */
#ifndef BOOST_ARRAY_HPP
#define BOOST_ARRAY_HPP

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
# pragma warning(push)  
# pragma warning(disable:4996) // 'std::equal': Function call with parameters that may be unsafe
# pragma warning(disable:4510) // boost::array<T,N>' : default constructor could not be generated 
# pragma warning(disable:4610) // warning C4610: class 'boost::array<T,N>' can never be instantiated - user defined constructor required 
#endif

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/swap.hpp>

#include <boost/throw_exception.hpp>
#include <algorithm>

// FIXES for broken compilers
#include <boost/config.hpp>


namespace boost {

    template<class T, std::size_t N>
    class array {
      public:
        T elems[N];    // fixed-size array of elements of type T

      public:
        // type definitions
        typedef T              value_type;
        typedef T*             iterator;
        typedef const T*       const_iterator;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;

        // iterator support
        iterator        begin()       { return elems; }
        const_iterator  begin() const { return elems; }
        const_iterator cbegin() const { return elems; }
        
        iterator        end()       { return elems+N; }
        const_iterator  end() const { return elems+N; }
        const_iterator cend() const { return elems+N; }

        // reverse iterator support
#if !defined(BOOST_MSVC_STD_ITERATOR) && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
#elif defined(_RWSTD_NO_CLASS_PARTIAL_SPEC) 
        typedef std::reverse_iterator<iterator, std::random_access_iterator_tag, 
              value_type, reference, iterator, difference_type> reverse_iterator; 
        typedef std::reverse_iterator<const_iterator, std::random_access_iterator_tag,
              value_type, const_reference, const_iterator, difference_type> const_reverse_iterator;
#else
        // workaround for broken reverse_iterator implementations
        typedef std::reverse_iterator<iterator,T> reverse_iterator;
        typedef std::reverse_iterator<const_iterator,T> const_reverse_iterator;
#endif

        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }
        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }

        // operator[]
        reference operator[](size_type i) 
        { 
            return BOOST_ASSERT_MSG( i < N, "out of range" ), elems[i]; 
        }
        
        /*BOOST_CONSTEXPR*/ const_reference operator[](size_type i) const 
        {     
            return BOOST_ASSERT_MSG( i < N, "out of range" ), elems[i]; 
        }

        // at() with range check
        reference                           at(size_type i)       { return rangecheck(i), elems[i]; }
        /*BOOST_CONSTEXPR*/ const_reference at(size_type i) const { return rangecheck(i), elems[i]; }
    
        // front() and back()
        reference front() 
        { 
            return elems[0]; 
        }
        
        BOOST_CONSTEXPR const_reference front() const 
        {
            return elems[0];
        }
        
        reference back() 
        { 
            return elems[N-1]; 
        }
        
        BOOST_CONSTEXPR const_reference back() const 
        { 
            return elems[N-1]; 
        }

        // size is constant
        static BOOST_CONSTEXPR size_type size() { return N; }
        static BOOST_CONSTEXPR bool empty() { return false; }
        static BOOST_CONSTEXPR size_type max_size() { return N; }
        enum { static_size = N };

        // swap (note: linear complexity)
        void swap (array<T,N>& y) {
            for (size_type i = 0; i < N; ++i)
                boost::swap(elems[i],y.elems[i]);
        }

        // direct access to data (read-only)
        const T* data() const { return elems; }
        T* data() { return elems; }

        // use array as C array (direct read/write access to data)
        T* c_array() { return elems; }

        // assignment with type conversion
        template <typename T2>
        array<T,N>& operator= (const array<T2,N>& rhs) {
            std::copy(rhs.begin(),rhs.end(), begin());
            return *this;
        }

        // assign one value to all elements
        void assign (const T& value) { fill ( value ); }    // A synonym for fill
        void fill   (const T& value)
        {
            std::fill_n(begin(),size(),value);
        }

        // check range (may be private because it is static)
        static BOOST_CONSTEXPR bool rangecheck (size_type i) {
            return i >= size() ? boost::throw_exception(std::out_of_range ("array<>: index out of range")), true : true;
        }

    };

    template< class T >
    class array< T, 0 > {

      public:
        // type definitions
        typedef T              value_type;
        typedef T*             iterator;
        typedef const T*       const_iterator;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;

        // iterator support
        iterator        begin()       { return       iterator( reinterpret_cast<       T * >( this ) ); }
        const_iterator  begin() const { return const_iterator( reinterpret_cast< const T * >( this ) ); }
        const_iterator cbegin() const { return const_iterator( reinterpret_cast< const T * >( this ) ); }

        iterator        end()       { return  begin(); }
        const_iterator  end() const { return  begin(); }
        const_iterator cend() const { return cbegin(); }

        // reverse iterator support
#if !defined(BOOST_MSVC_STD_ITERATOR) && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
#elif defined(_RWSTD_NO_CLASS_PARTIAL_SPEC) 
        typedef std::reverse_iterator<iterator, std::random_access_iterator_tag, 
              value_type, reference, iterator, difference_type> reverse_iterator; 
        typedef std::reverse_iterator<const_iterator, std::random_access_iterator_tag,
              value_type, const_reference, const_iterator, difference_type> const_reverse_iterator;
#else
        // workaround for broken reverse_iterator implementations
        typedef std::reverse_iterator<iterator,T> reverse_iterator;
        typedef std::reverse_iterator<const_iterator,T> const_reverse_iterator;
#endif

        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }
        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }

        // operator[]
        reference operator[](size_type /*i*/)
        {
            return failed_rangecheck();
        }

        /*BOOST_CONSTEXPR*/ const_reference operator[](size_type /*i*/) const
        {
            return failed_rangecheck();
        }

        // at() with range check
        reference at(size_type /*i*/)               {   return failed_rangecheck(); }
        /*BOOST_CONSTEXPR*/ const_reference at(size_type /*i*/) const   { return failed_rangecheck(); }

        // front() and back()
        reference front()
        {
            return failed_rangecheck();
        }

        BOOST_CONSTEXPR const_reference front() const
        {
            return failed_rangecheck();
        }

        reference back()
        {
            return failed_rangecheck();
        }

        BOOST_CONSTEXPR const_reference back() const
        {
            return failed_rangecheck();
        }

        // size is constant
        static BOOST_CONSTEXPR size_type size() { return 0; }
        static BOOST_CONSTEXPR bool empty() { return true; }
        static BOOST_CONSTEXPR size_type max_size() { return 0; }
        enum { static_size = 0 };

        void swap (array<T,0>& /*y*/) {
        }

        // direct access to data (read-only)
        const T* data() const { return 0; }
        T* data() { return 0; }

        // use array as C array (direct read/write access to data)
        T* c_array() { return 0; }

        // assignment with type conversion
        template <typename T2>
        array<T,0>& operator= (const array<T2,0>& ) {
            return *this;
        }

        // assign one value to all elements
        void assign (const T& value) { fill ( value ); }
        void fill   (const T& ) {}
        
        // check range (may be private because it is static)
        static reference failed_rangecheck () {
                std::out_of_range e("attempt to access element of an empty array");
                boost::throw_exception(e);
#if defined(BOOST_NO_EXCEPTIONS) || (!defined(BOOST_MSVC) && !defined(__PATHSCALE__))
                //
                // We need to return something here to keep
                // some compilers happy: however we will never
                // actually get here....
                //
                static T placeholder;
                return placeholder;
#endif
            }
    };

    // comparisons
    template<class T, std::size_t N>
    bool operator== (const array<T,N>& x, const array<T,N>& y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }
    template<class T, std::size_t N>
    bool operator< (const array<T,N>& x, const array<T,N>& y) {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }
    template<class T, std::size_t N>
    bool operator!= (const array<T,N>& x, const array<T,N>& y) {
        return !(x==y);
    }
    template<class T, std::size_t N>
    bool operator> (const array<T,N>& x, const array<T,N>& y) {
        return y<x;
    }
    template<class T, std::size_t N>
    bool operator<= (const array<T,N>& x, const array<T,N>& y) {
        return !(y<x);
    }
    template<class T, std::size_t N>
    bool operator>= (const array<T,N>& x, const array<T,N>& y) {
        return !(x<y);
    }

    // global swap()
    template<class T, std::size_t N>
    inline void swap (array<T,N>& x, array<T,N>& y) {
        x.swap(y);
    }

#if defined(__SUNPRO_CC)
//  Trac ticket #4757; the Sun Solaris compiler can't handle
//  syntax like 'T(&get_c_array(boost::array<T,N>& arg))[N]'
//  
//  We can't just use this for all compilers, because the 
//      borland compilers can't handle this form. 
    namespace detail {
       template <typename T, std::size_t N> struct c_array
       {
           typedef T type[N];
       };
    }
    
   // Specific for boost::array: simply returns its elems data member.
   template <typename T, std::size_t N>
   typename detail::c_array<T,N>::type& get_c_array(boost::array<T,N>& arg)
   {
       return arg.elems;
   }

   // Specific for boost::array: simply returns its elems data member.
   template <typename T, std::size_t N>
   typename detail::c_array<T,N>::type const& get_c_array(const boost::array<T,N>& arg)
   {
       return arg.elems;
   }
#else
// Specific for boost::array: simply returns its elems data member.
    template <typename T, std::size_t N>
    T(&get_c_array(boost::array<T,N>& arg))[N]
    {
        return arg.elems;
    }
    
    // Const version.
    template <typename T, std::size_t N>
    const T(&get_c_array(const boost::array<T,N>& arg))[N]
    {
        return arg.elems;
    }
#endif
    
#if 0
    // Overload for std::array, assuming that std::array will have
    // explicit conversion functions as discussed at the WG21 meeting
    // in Summit, March 2009.
    template <typename T, std::size_t N>
    T(&get_c_array(std::array<T,N>& arg))[N]
    {
        return static_cast<T(&)[N]>(arg);
    }
    
    // Const version.
    template <typename T, std::size_t N>
    const T(&get_c_array(const std::array<T,N>& arg))[N]
    {
        return static_cast<T(&)[N]>(arg);
    }
#endif

    template <class It> std::size_t hash_range(It, It);

    template<class T, std::size_t N>
    std::size_t hash_value(const array<T,N>& arr)
    {
        return boost::hash_range(arr.begin(), arr.end());
    }

   template <size_t Idx, typename T, size_t N>
   T &get(boost::array<T,N> &arr) BOOST_NOEXCEPT {
       BOOST_STATIC_ASSERT_MSG ( Idx < N, "boost::get<>(boost::array &) index out of range" );
       return arr[Idx];
       }
    
   template <size_t Idx, typename T, size_t N>
   const T &get(const boost::array<T,N> &arr) BOOST_NOEXCEPT {
       BOOST_STATIC_ASSERT_MSG ( Idx < N, "boost::get<>(const boost::array &) index out of range" );
       return arr[Idx];
       }

} /* namespace boost */

#ifndef BOOST_NO_CXX11_HDR_ARRAY
//  If we don't have std::array, I'm assuming that we don't have std::get
namespace std {
   template <size_t Idx, typename T, size_t N>
   T &get(boost::array<T,N> &arr) BOOST_NOEXCEPT {
       BOOST_STATIC_ASSERT_MSG ( Idx < N, "std::get<>(boost::array &) index out of range" );
       return arr[Idx];
       }
    
   template <size_t Idx, typename T, size_t N>
   const T &get(const boost::array<T,N> &arr) BOOST_NOEXCEPT {
       BOOST_STATIC_ASSERT_MSG ( Idx < N, "std::get<>(const boost::array &) index out of range" );
       return arr[Idx];
       }
}
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
# pragma warning(pop)  
#endif 

#endif /*BOOST_ARRAY_HPP*/

/* array.hpp
5pB/2Xd/wBUSl6Mopp+yootcem7iYYCnZ+I+37qW5jPTsrTCqtl6XLwvmeQ8weV6nkBm2Ca7a4PwHiOrfIEi3L56ShdZ2bF8ogHV7qWvjd4k51zlY/dgnK3H8DLZridXLBnrffafT3a0MZMukGmcljh1v1R8xEOf2yB47cNsI+D7wdsgXPKeVVdEFiuvgJyZD1Ey2UWCoDAREvj7A4UPC8BjmxJXrcHys0hbvGebgYiiF3b6B9kmJDURZwqx9G2uFdsv8YMYJ6/PutRZLUUudEUEQ3yXFacaEAS3iNNtNPYPng0X4GaUOF0XOIeHKb/24A9p4FnWRTFnI5J2M8CutZJrR+0ut6o0UW3o8xGTetRnmCH0WNDN9QESva5CiOL8CfP0Q9s2RNt3jU/tfoGb45+vOitkSwt33DItD5agJu8TtbFKfFSy2zz8/Gt32fCcjd2shXkCTQoinDzkVaXX668JgUqp6wj6m0W02UTQ8QpT6f26zEbbsvu9o68MM2koSzR8rJ4b2ThiPIJ7vOt7sePEaUWqgMDt0RgZmae3TlV88XLN4As/jwsbJyEZ1kft/eprMt5GMgfqhF/B9629OxIfwar3nDqybLc1sVOoFjiNyI/R2o785Nu8f4Wkc2++ynPSZdDBgFF7jYsSCR3q21ILaaw4QOSeyOYjijJfy/D/pNWYubAyt9EVaGPoVcf00mDO6rveToCYoqVv0zmJNK+mbpJ+DeXHlE5hIhRFujHRpilbHUJxgaFEcsP8a6osAv9ksjGTiMciEtki9Bx1SYnwfJQUk1QR4AUy9GOTPniv57Mz/PUM70KbywdbmdntvLdrKV6wmWOEFp0r4gYNBo5A2rPJ9zAeLgtUF2iDhE5HBJUEHqfk7ITvIAQ47qMRuPWQP/DnKzMfjl/oiGZJ/t56v1A3R5Va0Iuxrv10ldakMTj7aTJJoWT3Y+6AqM8/phfegrXzN2ofyjfpoEAJZ1dH7yPju3P0TAZGHKrZj4QkQRMG1Fgn9OdDGGlImNH7G6Wqoe8+oUSyDxkwGkKsn4Bq9HYVpPhTWlCvUtfDjiRUi5L0FNJqLBtdKqmn6tUPiAIjkz105Urphntx6UdKyqAiQk33Aqb0ZPAHt1SF6F3KHy4Uzymc25t6CIcWunhBVYV/MS16GXZmaz3DN8iZ5zlo8qOfJkHHC939OPadM6N+OUZ59HKv+thS4qm3TgIjyjS3ddgBnERWCNOTImRbml0Wk77WFOdzqlYI+/xBxOBwX72sORXVQouEbXN1ieVk54Z/NyeKRKBNrljIRLss2vMBuXsvdSNRHToMq8uZPbzYn/LuLH0mwCKPlctCsoSefKAZy6aXk7mKgjscwAUXEVnGyYloy3/Iex7vVfDdlbi32lwRAtIIjrY+HlrIUzrSeWbmVj8zQxHgCWabQPkYVX+OetBscD17OTn3uYf3Q3RXpFr6IvrcCmPd5L6MZCMvg441uZWhi7M30hbmLOKj3XdEDykkVvL3v+HJP6ibqV1pt2fU4/NuJD0N8E+lVSuGq8cJc6+3ofhKYD/MFJ95cIpBmIrxcf5XCN3Y+0VPehq+ppMNIkZzpoxl+J+L8FMY8Dg5tvHvOZAmp757Hpmt9GXKbM9XUr8b+JAaaQLp896RHVzxkHmBLa7quu9ZOubRtGbNbXWy2O9aeS+YOAVpfBwCDFu+xhbx+hSc6RKrtHx3NO2IvBqW+9E5ikxkiu7loEHDnr1RGiEaOxZ3WRr/Ak/QzqAnjNdAM9ZXnN1vAUznJJ7Qd+lpv0Lz5r57C7RAXWwwYYMQ82ul8Afbz7qREd8nqRjWkqia39a2yZ61+IuO/BJpRFNhymsDx2jGYjJM5FIgMTeZkY5K5KX0oMRSbps/zb2UBD6ZWGf4h+yaOz06WzhOZU5E+4bYTTovd2VuI5zct3SL43W3afJkkwGzfLT0oXhMrdbqjrb0Lgo3/4bpa9yYxoj04FbwaBJ2KKFlH+sD667ckEobBi0Dhe+SSoRCShb6L0wTEco6xPDEY1i7jL3NjxTEc3rUP2WE285GjlUqZBRBc4UFeCMuZxb5azwfh8jihxCL9fOwC37RiDK85jC0TFojNlF6EeFqYIBAtLMx/WDthTt/jN43G+H0PTVLyX18Fm61NSRzsHZn4UvbqpI3bb7kp8SzGQ4rywuiZrls0922YVP45rVdcmC7wlmmnv3uJTungApt7kbJJB7/BnUw+fXMex3sd6V++h+voq9lMD66Y7i9IDE36Nlx+Uqd40+Dc0muEPHiS/q4etZNKlS3ZAPegmkYacO6clKbiabkYf3rS9z1ncSliec6u7JnLm6Zk9yT8Uf9KKUGHX1JHw/SWxSNc7/HCYZkzr96Xy+mrZ09+X6RSZae+6tN9wV5onj7WTm2ct2wjVu+N5NSeJcW84wgTplUk6kQfc+jJ12DiA14GAR9XKH+3NFTLgGmpkkM60pltgwUThYNfjoYu8ElOdQNEe8HmQReDXmeSPAovtY+zLEer00ve8pFbYUfgI+dlsIQ5Fv6yXNxwHRjhnSrA83SX7xFV8/zHdrzA8mAUniFgYsMwhhyKcSm17NUVypSfVGfWjgWIHj9o+f7z76UzGCeXix0mvKixXOWCwokhuRnCOArG6pOPYld5KCUj+TQTZhVEiEea0e32gxch+g4eRvuVccH8env6OS9SozVTCHji/7AOO7UaHTqmzoIF7r3Wij+xa90O0GYjtG/TPPhS2sK8AcRHMwKXGqpJXiU6mTB6RNe27/C5HcnmAvDIWKeQoDiyx60+M8G7weKUkmEkZXXyVogxD4j0kCzicncy453Cy9QFLCQo5V6nPGeSeFtTPZ7h0EWZQ9cZf9uSKPA9Flr7QEDq5OG6zcBhy99MQpvT2RlH/MKkFQiY6PDH+vij5bsuVMe4RFrvXvSShd//WJdjbeO0MbeWYMqN9jSqUYruUM64wf0ALXupXQU2Y1XxAUHSmtiRGLwr4ReqvMurEdI15aOajico9hr8mlPZfNF6L3RNZoqP1vUE7qXOfoi1nt9htUpb3mjr0qlVMozPkbmgWArUw0/pspT4xH4F2FkOG9oCzcFMg4VI8wdmEba23Ds/Ul+uXg4TTNCVNzqg9XxPFx1jzs/gg0ZQnp//e3cRvk122UmDVZ6qJxdll3/oi4tltlenDepmuXaNvmLFgs0gUOibR5Sp5sUpEga7U4n3HeDn1664txUtKq+5HRxbu3czBOdaW6tryUPWBxQHM9m5xDInrR4xLeEjTkV6OZkSw8dRDDeqxWohp5VXsU1h5eZlYiK43gYsNRl9cmbZRofYi67xoUb+b44V+v6RLZc4s8zYmP2KyQK84PnfGU/HBh51cZPXCu/M5FomrllxnWczLcvd69M4KP08TK04VgSaH1OQw7+FB+MOk20iCPYvCFrUmfnit6vDDeXphGW+75TtpMA7vHC5UmxovAIH+e0vQpvkb/UNy7CJwOHXu7+VbgBgfWLMgy7LgrVKG6a3Js+4BPpungBrcWm2ZUuM662Vrzl79VfVBG4PIhDGNjK9E2l2TeLLKUCoFHDxI3SDsyFOy59Os/3c/0gVjyBAh7lagcXC4Hoyo6tNZQGFjnZRpH0VSJUXoetre0cFISENdN8srzPRH5F4w7c+WjYE47NwDxWYzp1FrYx5UJR1Dpnh+lC6mzIHBXT0uR5+v6M99dXpOkfnAulCbKnIsU9BtXyDwZaqiM9J/o86i54JFEtTVUSYoD5BvSrdYnEBUy93hhNfsKqmiByeSFZwumIEKYtTJr7X8kstA0ipQrmvAom1tK+dy9WSAxIzhdSS73ZJ2rsjLuctFfnNuQ/h0Bifd8owWW3RFe9f0b4leziOfVQgtp0msYQOmunStR7Ve7Oa816trekekZXjAuPL0gmNCoZ08JnbYo/SFBNHbfrs0UhkB5+C6iI4SxjN9aOo/ps+DnNgr8Vb8tXw/6IXIjUS7yhgnWYac+3CaFdL3UC0VdIKqKj66HdyyWmg6epvjdJX9o9QSQT86y9IJwJXLZ59kLkaFkysU/8lOvSydnf3zjpBuRXtoG3dGygXDasfuH6TzooyrFDYgLODWSnZh7KPBYPdXbIKUnLSX0wGNjo8pnukV8bZoq726Go4ceu6cX1LyJoCZhs5qclcB0mYijPkZ037AumqYjP/BMmmuWs2h8O4haoaAzfb9HIZWjyviGuQkaseX2NQd79qMhg1cBFOMtUuS7uQlxW6ut0wXa58FfGltReFvmz8D66NIO3iEpVWCcBVbMKJWX3wpR/TK5pWsUXJfF9up4lmyVBBK/tmcseZ3mi+dCuYFk8Jlcw8HPcwYvDFyefQCLuItahVRt/xBXDiBzXgXYStwcn3Sr2uMpCquoAzVas7Qg1z/k9Pz3wRdAQi7O8N4NqLIZueya+r8ne7mmxedAag7VBTc26ItrOFHvC8fzvG/UD3CQCkcz5U702qqLljaKY1ca+dcUn1nwjE1b2GN1YmGdybFYzf/rso5iw9VCBYQceciZ9tP0xku7O464K/KIyKfhceI90Dz3CtZB1eJY1kb0ENtEQ7ux3H2i+dHhqjjPPXSM6qFWm8JwM1GJ9N2PBdl9TlsbIAT9CkwvjlGep0bFcOsOOPtJwOHilyNYn5vNVI8PcHyv/G7s3gSJ6KsWnwxnJx9OysiNMnlT7z9h9N5nxd9D8RT8V75ohdPcTZGP2EhRstRKWoh4jnifaN5HDxad77/MGJ/zweTnbMky2lvSmy0drJ7tllhO/v3Fe67I6LbGmt1itGIPJc5Mxk8kim+xHCmVz1qrINwOBrKI4nswTYQk0LFnUby2VDQSu/OvurkxRvHsmAYUcurjoZShQCQvPEwxUGX/sD5bEW6HKqya9jG46SvyRBp8n+2scj8453A1qYtAKEJ9sNz79VQvvof+LxDYqjSGfurf+VRxYTbRMAVCeEuK50V4jf8qPp6xlKggiaLUg+KdjT7q8BS0PnSOQgzwTuUKy5RJKXhzn9nmucnw2dmDjPflmGKXyjuGl/30sWTbpMIEBlg+Z006hUu2MFia748+kQgJ0/ZqDVWoQZZfR/YUPKCXiJX7FGovO1Ttx48jJKheKfdA1fjk7Majcx9Ogppc2NiJydqTxYMADhXibUBORwTjvpbQK0frrC/K8YfUDVq/l9rZ80fT73OBf4qXe0JvMv/fcnPMM8/qUFvjRz+ijJj8mXgV4qPcCVHY5d//469Dyou+P2Skypp7WzfDvcZ7RrajewtmPWIqPpxrv/wLppckuKCE0PlX61GbTGuSsxl9VdpgLF9eMJbWKNBKDW/8hkKvL8Awr2AhiQqKQvD7HqqoyZ38Kh1uYme7BravB3NZqjJHNuRTtX5fGSkpAEQsya3AsruxWT3Ci71J9qNibu2jfQ+YkUDzw0L97y/GafpoBbspKVsDscem9APPtRyQFXgkbhfttHUHfUl4tN5187jnr9r6pmr5xbSmgbE1sNlrVMBi/vo7aGxGeqbqO27u62bxETwV2Aheqroeqrm11PrN3HLJUXkMuLkjmrrvqb85OKJ1JTyWIb/q9v/Uf9mHdFC0eMOie057uRp4dO/RbPR5t+lT245UPt+hyo7ED5lzRfob2UdDnuv26C14/Y5+rLy0frz5MdPd3lAdRBl4eeYMOj2nSoxK3Q7MvR9J20gPLFNIrtDuuPoRd61BUat+gihL0YB3ojzmTyXix+Tx/OisfZ1Fzz/8hEzEeXOkDJvuGRhwLYbDMI5ofeNaMFfcFJEc8RhT9fFtlDJdfDyCaYmWbu3G8IAszSdLA8ht49WKD8n1HpwhKdH8Umeck9aqf1vLUsoQ6sNKBZ6gqiHfK8Gz3++XKhZEW3+qDtc+rPzKKsVcfHFrvsVPWi/5Y/qb/aTsUJ9txXjspyTEXMcA1iT1obNlpT/VCvaWg8EnJPcGbPKwGjGXe+UR8A5R4DHAKhEPTFkcmTvoqBG095Lgnb+7cgoUkPIQ4dnY2rzmjdEdU06Snbbnk6ZSuna9EzewCfiHCL9+ppt1qTB9Yso+KG0u7MkP1+vDJbVdThAq0pYdWVC+kn+oUnzCO4pVbSePJj+8EPohUlwp01ceaCUmHzE31DfBYfQ9wnKQys+QUCNF1dduIOUvGrZ1/nqJ5rdNrVzBoivdau794ssvcU1JwsovnmRuBJAKTjaYtJLDEj5h+avdKF5IiG+GW3BMm+dwSISELE9N887S54Tkm8b1lSToZJ9lki5T6NfvZLTuKbPI0LBre0fXC4hf2LT7ePSWxXOV6jXjKUauKSyrYWoWWha+siJw/iJX5i+ZTv5wItrqwvGDszQ0sxE2MLubz9X79CtGF/dtu/YkFRbFkovmJvwdtHePkRlBtOMGjR+KXJfeYox8nBOCiELFovbTZpPxFJ0TuOQNljR9jjikHc1XUjUApyrkiaPaxpozofftjU8nDjeh6mV8sul5ZtR/2rgNjNsJpu2SkScrY6xa0z5WxPGppPZM7MzEpf2AjROamLx5Jp5dsRBJxgYOZplbSFLx6gBZd8LV+LEcP9zvOU8k4iy0X/FFjq3TjWZnvtBSLHmHYoBoOEdqCYJVC3zKGsfH+5VeozIkerWkyyGUMWY9OscI8bAIGGSFIcGiUpRxHCglbplaFfk9Ex9s9StcH3rAhJvC+zOfppGMKFp2QeybpNJFq+QCuHCF0zB/MXURML3xfgMRFmZZ+4In0rkLok/gI/DL6lBeFqOz68XQkjEUfUYuDOKLXwmmU8NwRNxPWUNksOFmH1HLQ85QyaVJ2a8isyYgfhuFaRCP1PMOzy9hPa7GOGFZq0pSfenI/Zjs17xfUPgtUlWcEkoH+Nvwmrulb8MFOKuW4TA0MkF9tVo5Y32DZENpmG5PRbHN8Ue799Cvcyvft7PsnAk85lcrpfukKeUSVy5O9QT3yPLJq7jqn9OlC6PhRc85+4aVLDPs2IRZCjwlblw6bYcsX4tc4UPrMzWwIVb5mAd4vGlyYfVf+YynNow91TrM5rOXO+RmhCxbm6pTdaDMVMU69/hZxHP3ej2uK4uEML+HX9jxfGHC7XshJx75m0uIkr9nlVbLmJqtRC+cBd3/9HDN2Ets3Bcev6olzpkoS/fhksBeM4lejGIBTvPf6Xk0d0R53jx/LgxHZytX3XjlEF7664sxkWKgS3BlgtnBmFb0MHLFkTidy6rIXM9VI9zW+akFZtcTKzaRUWD2omCdV9tW14zxHtwTdcZJT6yWR9rBC+bnxFJ1kUU7liHfmEZPOUHf9vsXsSeBLfcBRHrLuDcjOPPvQymXDIjW4OReg4731q3nQVXqwXe7g0+cP3QyJz93T4eyuf6FSyCkyo7TYla2sh4wkt2YZSDbnJCZ9uVcM1+NoM8Mf1/kN/cFFYYNqvl65+tMizZUiipKY/dfY0h6MQ2jnYnKpQWiZ0zPfMusph7f9Z2xs9tch301ECNH1S+VPEnspByOgED747PwmseiE+dX8OnOkcd88nL11OQdFsd5u4/i6MFpZC1m4Q0yE8HDfbjpEegTbHXMfDqXSatpJxBMqZfxd8LDGBt+lKglSa458rnyrmxh/cHfi4LnzEWfKIIEW43OELG1bNPsKEzGm
*/