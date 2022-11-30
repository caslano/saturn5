//  Boost string_algo library collection_traits.hpp header file  -----------------------//

//  Copyright Pavol Droba 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_RANGE_STRING_DETAIL_COLLECTION_TRAITS_HPP
#define BOOST_RANGE_STRING_DETAIL_COLLECTION_TRAITS_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <iterator>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>

// Container traits implementation ---------------------------------------------------------

namespace boost {
    namespace algorithm {
        namespace detail {

// Default collection traits -----------------------------------------------------------------

            // Default collection helper 
            /*
                Wraps std::container compliant containers
            */
            template< typename ContainerT >
            struct default_container_traits
            {
                typedef typename ContainerT::value_type value_type;
                typedef typename ContainerT::iterator iterator;
                typedef typename ContainerT::const_iterator const_iterator;
                typedef typename
                    ::boost::mpl::if_< ::boost::is_const<ContainerT>,
                        const_iterator,
                        iterator 
                    >::type result_iterator;
                typedef typename ContainerT::difference_type difference_type;
                typedef typename ContainerT::size_type size_type;

                // static operations
                template< typename C >
                static size_type size( const C& c )
                {
                    return c.size();
                }

                template< typename C >
                static bool empty( const C& c )
                {
                    return c.empty();
                }

                template< typename C >
                static iterator begin( C& c )
                {
                    return c.begin();
                }

                template< typename C >
                static const_iterator begin( const C& c )
                {
                    return c.begin();
                }

                template< typename C >
                static iterator end( C& c )
                {
                    return c.end();
                }

                template< typename C >
                static const_iterator end( const C& c )
                {
                    return c.end();
                }

            }; 

            template<typename T>
            struct default_container_traits_selector
            {
                typedef default_container_traits<T> type;
            };

// Pair container traits ---------------------------------------------------------------------

            typedef double yes_type;
            typedef char no_type;

            // pair selector
            template< typename T, typename U >
            yes_type is_pair_impl( const std::pair<T,U>* );
            no_type is_pair_impl( ... );

            template<typename T> struct is_pair
            {
            private:
                static T* t;
            public:
                BOOST_STATIC_CONSTANT( bool, value=
                    sizeof(is_pair_impl(t))==sizeof(yes_type) );
            };

            // pair helper
            template< typename PairT >
            struct pair_container_traits
            {
                typedef typename PairT::first_type element_type;

                typedef typename
                    std::iterator_traits<element_type>::value_type value_type;
                typedef std::size_t size_type;
                typedef typename
                    std::iterator_traits<element_type>::difference_type difference_type;

                typedef element_type iterator;
                typedef element_type const_iterator;
                typedef element_type result_iterator;

                // static operations
                template< typename P >
                static size_type size( const P& p )
                {
                    difference_type diff = std::distance( p.first, p.second );
                    if ( diff < 0 ) 
                        return 0;
                    else
                        return diff;
                }

                template< typename P >
                static bool empty( const P& p )
                {
                    return p.first==p.second;
                }

                template< typename P > 
                static const_iterator begin( const P& p )
                {
                    return p.first;
                }

                template< typename P >
                static const_iterator end( const P& p )
                {
                    return p.second;
                }
            }; // 'pair_container_helper'

            template<typename T>
            struct pair_container_traits_selector
            {
                typedef pair_container_traits<T> type;
            };

// Array container traits ---------------------------------------------------------------

            // array traits ( partial specialization )
            template< typename T >
            struct array_traits;

            template< typename T, std::size_t sz >
            struct array_traits<T[sz]>
            {
                // typedef
                typedef T* iterator;
                typedef const T* const_iterator;
                typedef T value_type;
                typedef std::size_t size_type;
                typedef std::ptrdiff_t difference_type;

                // size of the array ( static );
                BOOST_STATIC_CONSTANT( size_type, array_size = sz );
            };


            // array length resolving
            /*
                Lenght of string contained in a static array could
                be different from the size of the array.
                For string processing we need the length without
                terminating 0.

                Therefore, the length is calculated for char and wchar_t
                using char_traits, rather then simply returning
                the array size.
            */
            template< typename T >
            struct array_length_selector
            {
                template< typename TraitsT >
                struct array_length
                {
                    typedef typename
                        TraitsT::size_type size_type;

                    BOOST_STATIC_CONSTANT(
                        size_type,
                        array_size=TraitsT::array_size );

                    template< typename A >
                    static size_type length( const A& )
                    {
                        return array_size;
                    }

                    template< typename A >
                    static bool empty( const A& )
                    {
                        return array_size==0;
                    }
                };
            };

            // specialization for char
            template<>
            struct array_length_selector<char>
            {
                template< typename TraitsT >
                struct array_length
                {
                    typedef typename
                        TraitsT::size_type size_type;

                    template< typename A >
                    static size_type length( const A& a )
                    {
                        if ( a==0 ) 
                            return 0;
                        else
                            return std::char_traits<char>::length(a);
                    }

                    template< typename A >
                    static bool empty( const A& a )
                    {
                        return a==0 || a[0]==0;
                    }
                };
            };

            // specialization for wchar_t
            template<>
            struct array_length_selector<wchar_t>
            {
                template< typename TraitsT >
                struct array_length
                {
                    typedef typename
                        TraitsT::size_type size_type;

                    template< typename A >
                    static size_type length( const A& a )
                    {
                        if ( a==0 ) 
                            return 0;
                        else
                            return std::char_traits<wchar_t>::length(a);
                    }

                    template< typename A >
                    static bool empty( const A& a )
                    {
                        return a==0 || a[0]==0;
                    }
                };
            };

            template< typename T >
            struct array_container_traits
            {
            private:
                // resolve array traits
                typedef array_traits<T> traits_type;

            public:
                typedef typename
                    traits_type::value_type value_type;
                typedef typename
                    traits_type::iterator iterator;
                typedef typename
                    traits_type::const_iterator const_iterator;
                typedef typename
                    traits_type::size_type size_type;
                typedef typename
                    traits_type::difference_type difference_type;

                typedef typename
                    ::boost::mpl::if_< ::boost::is_const<T>,
                        const_iterator,
                        iterator 
                    >::type result_iterator;

            private:
                // resolve array size
                typedef typename
                    ::boost::remove_cv<value_type>::type char_type;
                typedef typename
                    array_length_selector<char_type>::
                        BOOST_NESTED_TEMPLATE array_length<traits_type> array_length_type;

            public:
                BOOST_STATIC_CONSTANT( size_type, array_size = traits_type::array_size );

                // static operations
                template< typename A >
                static size_type size( const A& a )
                {
                    return array_length_type::length(a);
                }

                template< typename A >
                static bool empty( const A& a )
                {
                    return array_length_type::empty(a);
                }


                template< typename A >
                static iterator begin( A& a )
                {
                    return a;
                }

                template< typename A >
                static const_iterator begin( const A& a )
                {
                    return a;
                }

                template< typename A >
                static iterator end( A& a )
                {
                    return a+array_length_type::length(a);
                }

                template< typename A >
                static const_iterator end( const A& a )
                {
                    return a+array_length_type::length(a);
                }

            }; 

            template<typename T>
            struct array_container_traits_selector
            {
                typedef array_container_traits<T> type;
            };

// Pointer container traits ---------------------------------------------------------------

            template<typename T>
            struct pointer_container_traits
            {
                typedef typename
                    ::boost::remove_pointer<T>::type value_type;

                typedef typename
                    ::boost::remove_cv<value_type>::type char_type;
                typedef ::std::char_traits<char_type> char_traits;

                typedef value_type* iterator;
                typedef const value_type* const_iterator;
                typedef std::ptrdiff_t difference_type;
                typedef std::size_t size_type;

                typedef typename
                    ::boost::mpl::if_< ::boost::is_const<T>,
                        const_iterator,
                        iterator 
                    >::type result_iterator;

                // static operations
                template< typename P >
                static size_type size( const P& p )
                {
                    if ( p==0 ) 
                        return 0;
                    else
                        return char_traits::length(p);
                }

                template< typename P >
                static bool empty( const P& p )
                {
                    return p==0 || p[0]==0;
                }

                template< typename P >
                static iterator begin( P& p )
                {
                    return p;
                }

                template< typename P >
                static const_iterator begin( const P& p )
                {
                    return p;
                }

                template< typename P >
                static iterator end( P& p )
                {
                    if ( p==0 )
                        return p;
                    else
                        return p+char_traits::length(p);
                }

                template< typename P >
                static const_iterator end( const P& p )
                {
                    if ( p==0 )
                        return p;
                    else
                        return p+char_traits::length(p);
                }

            }; 

            template<typename T>
            struct pointer_container_traits_selector
            {
                typedef pointer_container_traits<T> type;
            };

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_DETAIL_COLLECTION_HPP

/* collection_traits_detail.hpp
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
*/