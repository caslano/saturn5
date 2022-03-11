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
#include <stdexcept>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/swap.hpp>

// Handles broken standard libraries better than <iterator>
#include <boost/detail/iterator.hpp>
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
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
*/