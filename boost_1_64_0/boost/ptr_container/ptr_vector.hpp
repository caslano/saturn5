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
qiZwyELyoB+BjbF5l+G7LhlAXvHXn+aD67/Gp7AHt9QTexJ3+Gh/w1jacw+ighhryPfUZ+wrh4ExyDf2XsN+TSG2gF8tv0Pvj89kncTUj4NppqJj/diB4fii9cSF6GVXP2cm5M7q4OeDs8GSxWCBPdgv1lJM3rlxO+JFH/m2fZGVDzP0xxfOno+tvAj7DNZcD2440ovshcD87Oeb+NQv0JdHwd/1FRnc1eYO27PwmTOaT79Ud96I0cl5PlTGvTJk6WXmNPITbD9YuHGAZ3UasJnP43N8zBX8OYQc6+i14Fni+SD2Nn85mOZC8gPTyWldSj7nWOvcLB97OICvfh+/VLMCXziO2B3bc90b5KXh262TGJf5n/UMSzhePWOFzp6Nn8slvrwPH3k2ePp4a//K9iWuQB5fG0qcB08XXIJ9juEbj/Fw/4k8JfdAtsROLGsFd+LzvhhntVvPcxC1V8BTfMe7p2SCATKIffD/5APb2Ivu8eQXsvGLMeLWi6nb49HfW3yrFPyOzXz7b5Yvfvd4eIJPWI8Onw9+SDyW4YHsyeu2yu//HWs8A99XRgx9PrYD3dyYQ64Snbscnnx7jseSQ/zgNvivVx/C/twBb/FHj5R6kD9rvl+AXVZ9gLw8iwySPzz0fMVDsNnR+CjmPRcM+zjxZ+5h8Jn7aWyN5+GTM/XZz3fH4D8uBwOTC35nB2IU7O5K8Olx5IHaJ7Im1vsX9O/bUdzPb8fuNGI3b8ZPnklMAo7oeZU87VDy6x7s1NvwExycsx82ghzJ2JPIY+HPf/M8Orob+Ir8Us0L5KCe5K5oIgu5JLf1KvmWUdCxky3EjFshV/leeDEePQmQswbrvr81cU0vNjxAXLWEuy/I2hMZ2NN/gLc+yuKZDO74YLMLtybm2Ak8TF+/moFePot93lVhEYvftV587fYe4lFkFDt68KusGVz99zdZxx5gsCh2DF3f9iB8EeNehr8JEVMejC++qjWLeAGegWkeIjYOnEdu701yZQdm8DwjOA6df60JHHW/tSdfYpMuVXfmqR/CXniwR4lWbCD73Y/sL/wFOaDZyJAHO3ox50NxbPQD8PYq1rGGOUSx4/eqZwHxz8cSf5ILKlmErF+IThyboTHL5COQ4RuRHbDMFedxNn8nuQPOuwMV6HMB+vQuOvse/K1knZx1js4HcxA/tq4iZ4Yva/0GvV1Ln8jWrLnIHXp2N/PMxpdm4cvbxpJfgPesh3MTbOsGYmzs7z213AnnPmhiIm6yRN37IdacR3/XE2ch60cxZvsu5Lz4/ZmJea5ir7bAxqxdhV5xNv+xwpQPwcso/uUpq87Qhdj3b1Q+ED7fgA8gx9HbbO3dvDD3Wd/l38j/UWWcYRIjtZ5ErvPP7Bnt48jSbuRcCn8G9j6G9X5u7cMG7ET7LbSrIJfPXryZT96ItTx+EXaN9TZzz9DPXs7ZEx/us8Y67gX2CH267FX8Ae1PJoccxMcfydh1xDEDGZxFqufu0IfqLHKIR6BzW7DP7Pfjs4iLsc3TaLf9ltjg0dgydSexzFrjAS/AwwQ48ANyAgNZ4Cvw7BRwwVvYmKYsYgjw77YZPKMCNsgjf8c6z7nGWsuk+9CFOdjy/dhTbP9nV2IvPNhA9vzwv3h47pY9AadkgGNGobfHvQhvv4Ov4Nph7MW15Jau4R5VDL80Cx9ewvwmIYMXMdaLuch4joqd1LOH6G01MoJszQArvkSfQ7BFOe9je/EH2yMH+czzr9TNWu7hfjOyDhaJ3gYmQYdfXAyuvh1bj01c/hyxzOPo7i3YAdrtPQH/SL/5l6EzN+CHD6PfsR4wLbqWAOffzf4sAfMi59fmoZPI48TdyevfTz8=
*/