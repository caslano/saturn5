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