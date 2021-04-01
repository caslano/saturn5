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

#ifndef BOOST_PTR_CONTAINER_PTR_VECTOR_HPP
#define BOOST_PTR_CONTAINER_PTR_VECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <vector>
#include <boost/ptr_container/ptr_sequence_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

    template
    < 
        class T, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = void
    >
    class ptr_vector : public 
        ptr_sequence_adapter< T,
            std::vector<
                typename ptr_container_detail::void_ptr<T>::type,
                typename boost::mpl::if_<boost::is_same<Allocator, void>,
                    std::allocator<typename ptr_container_detail::void_ptr<T>::type>, Allocator>::type
            >,
            CloneAllocator >
    {  
        typedef

            ptr_sequence_adapter< T,
                std::vector<
                    typename ptr_container_detail::void_ptr<T>::type,
                    typename boost::mpl::if_<boost::is_same<Allocator, void>,
                        std::allocator<typename ptr_container_detail::void_ptr<T>::type>, Allocator>::type
                >,
                CloneAllocator >

            base_class;

        typedef ptr_vector<T,CloneAllocator,Allocator> this_type;
        
    public:

        BOOST_PTR_CONTAINER_DEFINE_SEQEUENCE_MEMBERS( ptr_vector, 
                                                      base_class,
                                                      this_type )
        
        explicit ptr_vector( size_type n,
                             const allocator_type& alloc = allocator_type() )
          : base_class(alloc)
        {
            this->base().reserve( n );
        }        
    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename T, typename CA, typename A >
    inline ptr_vector<T,CA,A>* new_clone( const ptr_vector<T,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, typename CA, typename A >
    inline void swap( ptr_vector<T,CA,A>& l, ptr_vector<T,CA,A>& r )
    {
        l.swap(r);
    }
    
}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_vector.hpp
5D/DiLuOOXqwVHDVDaVEi6RSevGXWBQgjSOFKlGClfaZA1V56W2UZ7/fHt283ao9DJ44KD5C0TiV+NuOr5CBEHxp9e4UATbZZotA+Ae7UL+mutGx9FqMolcyWiMkqioLWDTvAtZCC74C572LdI347IoFFc5+ITh65oJGIaKRqB1e11Yb6VVgZOeQodpl/7TTckFH0pqWttcxoh70mJcWqmnuNxiLs7hZNMRGlX1No9Shi5xIQ1EvadkXUbHa3IVNzfc8v24Go9NssGVVMwKvPXLWHTw2tHKsww0MYwdPHj9VGljuye1oMdmxdpoKts62PsEx8jjAWrPWX2YhIMajAkaiRGJjBKJFWTQiKeZ4QJoN/ps1uKxJN57c3jURKmjLtEWBZaP4H277tkTBapc4+tyq+pz4YRqjE5jDntJvgb6Do6h5tMMdauGpYXHINGpPAMx9itJKDsj/QJ5/Zl/fSHFLZaliMi4XFszxqhbTkPEiweLBjq0m5jGSo8Mgs3lpoQ21rPdfBpjE2/ic1YNmkuy1gJiX2OH2QB36mPZPV0uczboiscKYyHsEyQ==
*/