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
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
*/