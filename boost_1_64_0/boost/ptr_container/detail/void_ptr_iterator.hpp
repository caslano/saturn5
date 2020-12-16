//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_DETAIL_VOID_PTR_ITERATOR_HPP
#define BOOST_PTR_CONTAINER_DETAIL_VOID_PTR_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost
{
        template
        < 
            class VoidIter, 
            class T
        >
        class void_ptr_iterator
        {
        public:
            typedef BOOST_DEDUCED_TYPENAME boost::remove_const<T>::type        
                             value_type;
            typedef T&       reference;
            typedef T*       pointer;

            typedef  BOOST_DEDUCED_TYPENAME iterator_difference<VoidIter>::type
                             difference_type;           
            typedef  BOOST_DEDUCED_TYPENAME iterator_category<VoidIter>::type
                             iterator_category;           
        private:

            VoidIter iter_;

        public:
            void_ptr_iterator() : iter_()
            { }

            void_ptr_iterator( VoidIter r ) : iter_(r)
            { }

            //
            // Remark: passing by value breaks vc7.1 
            //
            template< class MutableIterator, class MutableT >
            void_ptr_iterator( const void_ptr_iterator<MutableIterator,MutableT>& r )
#ifdef BOOST_NO_SFINAE
                         : iter_( VoidIter(const_cast<void**>(&*r.base())) )
#else

             : iter_(r.base())
#endif
            { }

            T& operator*() const
            {
                return *static_cast<T*>( *iter_ );
            }

            T* operator->() const
            {
                return static_cast<T*>( *iter_ );
            }
            
            void_ptr_iterator& operator++()
            {
                ++iter_;
                return *this;
            }

            void_ptr_iterator operator++(int)
            {
                void_ptr_iterator res = *this;
                ++iter_;
                return res;
            }

            void_ptr_iterator& operator--()
            {
                --iter_;
                return *this;
            }

            void_ptr_iterator operator--(int)
            {
                void_ptr_iterator res = *this;
                --iter_;
                return res;
            }

            void_ptr_iterator& operator+=( difference_type n )
            {
                iter_ += n;
                return *this;
            }

            void_ptr_iterator& operator-=( difference_type n )
            {
                iter_ -= n;
                return *this;
            }

            T& operator[]( difference_type n ) const
            {
                return *static_cast<T*>( *(iter_ + n) );
            }

            VoidIter base() const
            {
                return iter_;
            }

        }; // class 'void_ptr_iterator'

        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator+( void_ptr_iterator<VoidIter,T> l, 
                   BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n )
        {
            l += n;
            return l;
        }

        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator+( BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n, 
                   void_ptr_iterator<VoidIter,T> r ) 

        {
            r += n;
            return r;
        }

        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator-( void_ptr_iterator<VoidIter,T> l, 
                   BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n )
        {
            l -= n;
            return l;
        }

        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator-( BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n, 
                   void_ptr_iterator<VoidIter,T> r ) 

        {
            r -= n;
            return r;
        }


        namespace ptr_container_detail
        {
            template<typename T, typename U>
            struct is_compatible
            {
                static const bool value = boost::is_same< typename boost::remove_const<T>::type, typename boost::remove_const<U>::type >::value;
            };
        }

          
        template< class VoidIter, class T, class VoidIterU, class U >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            ptr_container_detail::is_compatible<T, U>,
            BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type
        >::type
        operator-( void_ptr_iterator<VoidIter,T> l,
                   void_ptr_iterator<VoidIterU,U> r ) 

        {
            return l.base() - r.base();
        }



        template< class VoidIterT, class T, class VoidIterU, class U >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            ptr_container_detail::is_compatible<T, U>,
            bool
        >::type
        operator==( const void_ptr_iterator<VoidIterT,T>& l,
                                const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() == r.base();
        }


        
        template< class VoidIterT, class T, class VoidIterU, class U >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            ptr_container_detail::is_compatible<T, U>,
            bool
        >::type
        operator!=( const void_ptr_iterator<VoidIterT,T>& l,
                                const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() != r.base();
        }



        template< class VoidIterT, class T, class VoidIterU, class U >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            ptr_container_detail::is_compatible<T, U>,
            bool
        >::type
        operator<( const void_ptr_iterator<VoidIterT,T>& l,
                               const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() < r.base();
        }


        
        template< class VoidIterT, class T, class VoidIterU, class U >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            ptr_container_detail::is_compatible<T, U>,
            bool
        >::type
        operator<=( const void_ptr_iterator<VoidIterT,T>& l,
                               const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() <= r.base();
        }


        
        template< class VoidIterT, class T, class VoidIterU, class U >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            ptr_container_detail::is_compatible<T, U>,
            bool
        >::type
        operator>( const void_ptr_iterator<VoidIterT,T>& l,
                               const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() > r.base();
        }


        
        template< class VoidIterT, class T, class VoidIterU, class U >
        inline BOOST_DEDUCED_TYPENAME boost::enable_if<
            ptr_container_detail::is_compatible<T, U>,
            bool
        >::type
        operator>=( const void_ptr_iterator<VoidIterT,T>& l,
                               const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() >= r.base();
        }

}

#endif

/* void_ptr_iterator.hpp
vGd+nlHw53dMUeMszDGVT2qNL8poDLZ7hyt+5wi6jp5WJc9oNZGa3CjT8T3pMuKk6IbEdvijLSXpK7404AvukYDttMcDxCP9g1inYd35i8XE1GvIm/HHwdiFTNhj33yofid8hMX3JkHEYeTHDVgL8b+MTdtNHk8N7Lq9jjGOcaHW05O12DHNOYb/74hP7WAjxt7Emg42vHcUPps4/DIxT11sUwni4yDipyh8wyn8XkIxW4qx/3e16L+j7z+P3YZNyEIofXH/VX7fdP913hvqvDdlH+T+997l/IvvwPqLvEc7+/3A3q6L+69zP5J/Hw3UuP9w/jOmmO9lT/Cn5EZWJGsjxMfFE4jjj5mO9dJRJnF7KOPJ2C9522bkpg7kzbwmE0+Mj7c56pFf4c+a7UvdPhwnhgzp9eJcjOBdRsE4mOL+34zLtBRjQzvmIuXYOMaD/v92TGZwPhYWw8/j4pGd2lc5+m8wJrbf1az/phyd/4fyU/c94pBVxF0c+9m3LrTv8xO74Rey1sDGZmaPbz2pvvVEVrtvZZ8Nv7CNOc+O3uNbh3jab2HiYznPdw3Ozbk5N+fm3Jybc3Nuzu3Ptws/kPe0e/G4Cc/ZvNKVvtObWKsl9SBf03QcLzdM9tmqpnHs8zx2cew37JLj/evaHPudbeT4sodyv3sN5XfOGZa0qyHtfXfJcX9tX2mknB9+UfajB8r9Mt2X3yGjZf8sQY4PGSbX3fSWfZ9ncnzmfNmzvuPYp6ssvxtvsaQfgTbZb5PrTG/5Pa2vvNeCzLIvNE+O+7WQ/pa5IccvXpHjvtPl994b8vvRfLl/uK+0L+Qv5xMvO57D3zvI8eRIQ96ziBzPNsiU8QyQ6yddk+Peeh//EY721PXSyP6wnHdtL9fFbLPJdQ/leFxaaX+tihzf0l3uG/uRnB+k4+Xra0j/XpHf7RvJPniAtC9VXX4nuaWR6x/L8SPfmdLPfHK+WDE57x2jcpGbvf14mLQrs0Ll4YQh/e0sv9+qLe2CHxsyjvUskYO1Npm3ZTqfN025fqvK2RFptz3UlHn3lvukWajyOVP2/lNNOf6l3D9ogin9P+Ui/bA5ruObNDkeouMf/IlN7qv976/z5vqyyneiTe6TyRD5z2XIvKZXuV1hyHXrLJGrknqe93Kc72fI/T8y5L4P5Dkh7Szp9/s26a8pz42bZkp/V1g6/4bM+7dyfIjKcaFNLtLuok307oEh/Zmm+tNG57+o3DdbQTneXveuGfR+U2R//InqQR9T5OBTuV+Ci+xXjZZ91CND5OOKJePjLvefFK96/8CU37E6Dl3leMwB2U8z5bpQfV6a3pZc94rcx7epJeMwxxD9U7sxM176WW2R/M6UXt93iOwb6rit2myIPKwzZVxy63ioXJd5w7HnbwFM6cdtHU/tb6Kldqi8tEtoIHtznz43VvbD37HJ+3dzEXkeoPKyTuXI35LxOqhy2F71o6vsb95Vu7jRkufeM2V8RprSf51nf53npN0qZ8NUXkJs0t8Ym8j3VWm36mPH+/K3qrKvFKP2qIkpvxuZMv8F1K4EqZ1TOXprvily1Fz9wBlD3idR2pfJbcj9rlryHqE6v9vl+nGN1E6r3fXTfvtHyfFnMSrfX6lcq91dMM4m43Vajhc6pn5io+z94tSe+Ei/Lq7U+9ZQvX5Z9s9Kq70+bsn5odJuyzm5T6kImzx3v87nBtmPflOOr9uscrbcFD9yyZB+bjCk/43kOeFrLOkve8f5tYbMXzObyP0j9S8LLZHDby2RY7Vf947Kc8Nr6nu3t+S561SOZut4FVJ7l07tpcp9n2XyPLOwjvd+m/Qjk/qJEobcP53ev76Os9rf9gPkeLU=
*/