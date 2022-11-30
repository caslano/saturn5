//  Boost string_algo library collection_traits.hpp header file  -------------//

//  Copyright Pavol Droba 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// (C) Copyright Thorsten Ottosen 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// (C) Copyright Jeremy Siek 2001. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  Original idea of container traits was proposed by Jeremy Siek and
//  Thorsten Ottosen. This implementation is lightweighted version
//  of container_traits adapter for usage with string_algo library

#ifndef BOOST_RANGE_STRING_COLLECTION_TRAITS_HPP
#define BOOST_RANGE_STRING_COLLECTION_TRAITS_HPP

#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/mpl/eval_if.hpp>

// Implementation
#include <boost/range/detail/collection_traits_detail.hpp>

/*! \file
    Defines collection_traits class and related free-standing functions.
    This facility is used to unify the access to different types of collections.
    It allows the algorithms in the library to work with STL collections, c-style
    array, null-terminated c-strings (and more) using the same interface.
*/

namespace boost {
    namespace algorithm {

//  collection_traits template class -----------------------------------------//
        
        //! collection_traits class
        /*!
            Collection traits provide uniform access to different types of 
            collections. This functionality allows to write generic algorithms
            which work with several different kinds of collections.

            Currently following collection types are supported:
                - containers with STL compatible container interface ( see ContainerConcept )
                    ( i.e. \c std::vector<>, \c std::list<>, \c std::string<> ... )
                - c-style array 
                   ( \c char[10], \c int[15] ... )
                - null-terminated c-strings
                    ( \c char*, \c wchar_T* )
                - std::pair of iterators 
                    ( i.e \c std::pair<vector<int>::iterator,vector<int>::iterator> )

            Collection traits provide an external collection interface operations.
            All are accessible using free-standing functions.

            The following operations are supported:
                - \c size()
                - \c empty()
                - \c begin()
                - \c end()

            Container traits have somewhat limited functionality on compilers not
            supporting partial template specialization and partial template ordering.
        */
        template< typename T >
        struct collection_traits
        {
        private:
            typedef typename ::boost::mpl::eval_if<
                    ::boost::algorithm::detail::is_pair<T>, 
                        detail::pair_container_traits_selector<T>,
                        typename ::boost::mpl::eval_if<
                        ::boost::is_array<T>, 
                            detail::array_container_traits_selector<T>,
                            typename ::boost::mpl::eval_if<
                            ::boost::is_pointer<T>,
                                detail::pointer_container_traits_selector<T>,
                                detail::default_container_traits_selector<T>
                            >
                        > 
                >::type container_helper_type;
        public:
            //! Function type       
            typedef container_helper_type function_type;        
            //! Value type
            typedef typename
                container_helper_type::value_type value_type;
            //! Size type
            typedef typename
                container_helper_type::size_type size_type;
            //! Iterator type
            typedef typename
                container_helper_type::iterator iterator;
            //! Const iterator type
            typedef typename
                container_helper_type::const_iterator const_iterator;
            //! Result iterator type ( iterator of const_iterator, depending on the constness of the container )
            typedef typename
                container_helper_type::result_iterator result_iterator;
            //! Difference type
            typedef typename
                container_helper_type::difference_type difference_type;

        }; // 'collection_traits'

//  collection_traits metafunctions -----------------------------------------//

        //! Container value_type trait
        /*!
            Extract the type of elements contained in a container
        */
        template< typename C >
        struct value_type_of
        {
            typedef typename collection_traits<C>::value_type type;
        };
        
        //! Container difference trait
        /*!
            Extract the container's difference type
        */
        template< typename C >
        struct difference_type_of
        {
            typedef typename collection_traits<C>::difference_type type;
        };

        //! Container iterator trait
        /*!
            Extract the container's iterator type
        */
        template< typename C >
        struct iterator_of
        {
            typedef typename collection_traits<C>::iterator type;
        };

        //! Container const_iterator trait
        /*!
            Extract the container's const_iterator type
        */
        template< typename C >
        struct const_iterator_of
        {
            typedef typename collection_traits<C>::const_iterator type;
        };


        //! Container result_iterator
        /*!
            Extract the container's result_iterator type. This type maps to \c C::iterator
            for mutable container and \c C::const_iterator for const containers.
        */
        template< typename C >
        struct result_iterator_of
        {
            typedef typename collection_traits<C>::result_iterator type;
        };

//  collection_traits related functions -----------------------------------------//

        //! Free-standing size() function
        /*!
            Get the size of the container. Uses collection_traits.
        */
        template< typename C >
        inline typename collection_traits<C>::size_type
        size( const C& c )
        {
            return collection_traits<C>::function_type::size( c ); 
        }

        //! Free-standing empty() function
        /*!
            Check whether the container is empty. Uses container traits.
        */
        template< typename C >
        inline bool empty( const C& c )
        {
            return collection_traits<C>::function_type::empty( c );
        }

        //! Free-standing begin() function
        /*!
            Get the begin iterator of the container. Uses collection_traits.
        */
        template< typename C >
        inline typename collection_traits<C>::iterator
        begin( C& c )
        {
            return collection_traits<C>::function_type::begin( c ); 
        }

        //! Free-standing begin() function
        /*!
            \overload
        */
        template< typename C >
        inline typename collection_traits<C>::const_iterator
        begin( const C& c )
        {
            return collection_traits<C>::function_type::begin( c ); 
        }

        //! Free-standing end() function
        /*!
            Get the begin iterator of the container. Uses collection_traits.
        */
        template< typename C >
        inline typename collection_traits<C>::iterator
        end( C& c )
        {
            return collection_traits<C>::function_type::end( c );
        }

        //! Free-standing end() function
        /*!
            \overload           
        */
        template< typename C >
        inline typename collection_traits<C>::const_iterator
        end( const C& c )
        {
            return collection_traits<C>::function_type::end( c );
        }

    } // namespace algorithm
} // namespace boost

#endif // BOOST_STRING_COLLECTION_TRAITS_HPP

/* collection_traits.hpp
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
*/