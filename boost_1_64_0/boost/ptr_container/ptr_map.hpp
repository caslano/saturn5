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

#ifndef BOOST_PTR_CONTAINER_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_PTR_MAP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <map>
#include <boost/ptr_container/ptr_map_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{
    
    template
    < 
        class Key, 
        class T, 
        class Compare        = std::less<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< std::pair<const Key,typename ptr_container_detail::void_ptr<T>::type> >
    >
    class ptr_map : 
        public ptr_map_adapter<T,std::map<Key,
            typename ptr_container_detail::void_ptr<T>::type,
                               Compare,Allocator>,CloneAllocator>
    {
        typedef ptr_map_adapter<T,std::map<Key,
            typename ptr_container_detail::void_ptr<T>::type,
                                Compare,Allocator>,CloneAllocator>
            base_type;

        typedef ptr_map<Key,T,Compare,CloneAllocator,Allocator> this_type;
        
    public:
        ptr_map()
        { }
        
        explicit ptr_map( const Compare& comp,
                          const Allocator& a  = Allocator() ) 
          : base_type( comp, a ) { }

        template< class InputIterator >
        ptr_map( InputIterator first, InputIterator last )
          : base_type( first, last )
        { }
        
        template< class InputIterator >
        ptr_map( InputIterator first, InputIterator last, 
                 const Compare& comp,
                 const Allocator& a  = Allocator() )
          : base_type( first, last, comp, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_map, base_type, 
                                                      this_type )

        template< class U >
        ptr_map( const ptr_map<Key,U>& r ) : base_type( r )
        { }

        ptr_map& operator=( ptr_map r )
        {
            this->swap( r );
            return *this;
        }
    };
    


    template
    < 
        class Key, 
        class T, 
        class Compare        = std::less<Key>, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< std::pair<const Key,void*> >
    >
    class ptr_multimap : 
        public ptr_multimap_adapter<T,std::multimap<Key,void*,
                                    Compare,Allocator>,CloneAllocator>
    {
        typedef ptr_multimap_adapter<T,std::multimap<Key,void*,
                                     Compare,Allocator>,CloneAllocator>
             base_type;

        typedef ptr_multimap<Key,T,Compare,CloneAllocator,Allocator> this_type;
        
    public:
        ptr_multimap()
        { }
        
        explicit ptr_multimap( const Compare& comp,
                               const Allocator& a  = Allocator() ) 
          : base_type( comp, a ) { }

        template< class InputIterator >
        ptr_multimap( InputIterator first, InputIterator last )
          : base_type( first,  last )
        { }
        
        template< class InputIterator >
        ptr_multimap( InputIterator first, InputIterator last,
                      const Compare& comp,
                      const Allocator& a  = Allocator() )
          : base_type( first, last, comp, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_multimap, 
                                                      base_type,
                                                      this_type )

        template< class U >
        ptr_multimap( const ptr_multimap<Key,U>& r ) : base_type( r )
        { }

        ptr_multimap& operator=( ptr_multimap r )
        {
            this->swap( r );
            return *this;
        }
    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< class K, class T, class C, class CA, class A >
    inline ptr_map<K,T,C,CA,A>* new_clone( const ptr_map<K,T,C,CA,A>& r )
    {
        return r.clone().release();
    }

    template< class K, class T, class C, class CA, class A >
    inline ptr_multimap<K,T,C,CA,A>* new_clone( const ptr_multimap<K,T,C,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename K, typename T, typename C, typename CA, typename A >
    inline void swap( ptr_map<K,T,C,CA,A>& l, ptr_map<K,T,C,CA,A>& r )
    {
        l.swap(r);
    }

    template< typename K, typename T, typename C, typename CA, typename A >
    inline void swap( ptr_multimap<K,T,C,CA,A>& l, ptr_multimap<K,T,C,CA,A>& r )
    {
        l.swap(r);
    }


}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_map.hpp
KOAKyo6fCn6E/t562xTldwB3PsSaYdxPrwMv/BWn6I+h/oGQDR48kP4r8u4wxd4rENNFHgpXu0TeJaDTE1xi4TWId4Q5pYIWDrnWEMefgnKgxcf3kDRgiin3ghfDE+DlYlNUV7rEhCNcogjz+R4yb59zwVfBo+483RBTwe82ngDe8Crwc4FLvNoMPIbs+PkMQyxHuQfBE1PAd979O86A/gkfte3gC2HQ5CbABrL2vYku8QLo+rhiIQY/BF7+jSHqShDnphEx90BLD2AdA0WGmA0ZET7YJUaCV70xDHwKfPyVnwG7k7CWteBDX0N+TAf+D8ZdVeB7xS/Aw22IlTJZiGNR9usS9LXBJY7qjzEehrtfwJf9JgH/vgSOnAMYH2+KDb2BV17QXb1LrBoJmTjMEGP7ucSZvwLW32KO48Hn0c5ajP0H0NLXC7H2kD2ngjYbgXcXgP+tnGGIUUFTTACeXws+2XC9KW7xgS+Apn6tghwFTv8AHP7sTPCNUcC1JpdYUQQ+B7oefZlLPPJPl9gbddZlucT+oOe09dAlXFjHVw3RsAF4Mxyy7Sh8A4Zj0iGfR2N84JkflAHH0F9vXLr95nxTnH0r5OZx4H8R8PUXgVsRyI5arOsql3gzxRCDazBPwODVQvgiYI2ngj/dew7ef4Hz9x7gmxlrXGINHuH/EfL0oJGGmPw3xHDbGz5c+0MmvWmI0xAwwXcv7r5OB28NIj4c+OJp0Ff+Dpw56W7wKPDS5c9irF+Cfq6CHLzHEC2QlYeDv41Yj/XfC7B8BO+VrcPfZwC/56CjjDHFuXeBjr4A3m0S4oaQS3RbLsA3DfEp5r4YsnfJcYZY8gFiJkoag+6x6ELEj3veFJ1fx/kQ4HDwT5j7NaAT8Jwa8I1K4MPMP2OMqTgrw1y/Wot1x9rBh0E0P4b1GetCrBG83Xkt9C/oZh9Dvm3A/E3oGJ+CJ29G+k3vCbG/FzgCXSn6MdbpLJwcvQa++yHaegd65LPg/dC1AreARxwHXAdffn++KQ5En08gPxNjPcmNmKOZmB/Ovy4Dj/hiEV7IAc4uH4ZzsO8QlxZ8+hfwvDuuhp52LPjRj+CDL+P9/6tABye5xPoh0FnAQ0aAn9z7Hngg4P7LT8AP8KgToCdlgR9c8wb0vpW467nDFEdCL1j/DfhoCDhxA2g9FTwZ9NFpBuQv+HhzCXgc+OXxteDnRYDnGNw/ugbtQWYcU4v1+yN0PODkY/PAH8/CmjS6xGjIwjLg7Yw7ERdtqSmikPtPFoL+jjbFe7ca4vW5WKsGjAe626vQXT7DvD7DWGZdiPswMdD+66boNQcyH3p3/3OBE4DrA5jTflKPOwP89CTQTSnkHWTYobmIg9sd822G3HhcqO9lGwzx0gsuMQ6yvwU86SUDeuIwyHHQ1n3vQgZXGWIVxncmeMpTWJ/alwwxMgd9Yz3fOQxRJftBPoFf3Xce9F6M/VTo0D+DJ3igvy5sAR31R7vrXeLFj6E/YE0fKoEu0w24fqEpYtA/Io8Y6q2t8m+AJ8cDF2ZA/74TsAaePYL5LHgIe4TLoLcshA8GeEAl5GBdOeD+DF5xxtw+HANfEfS5tgzlPoGOdqkhvggC9s2Qp88JkZkK+QQ+lIqx/QEwmAY8f2MZ+OSNLrF8JfAEesaQY7CPgJ525TyXCJdBpvSFftsEna4n5AXWpWUp1u1njOE6U2Q9j7WD/lgBWP21COUAq8OAcz98j/PkOvBD6DzzoatevwK8FHLto58gW7D22d+CVoFT3SC/h74IOV8PXUKAP0NHn1MCnP0WfPUIvPEH2X8xdJvyidKP2hQ/PAx9P9UU12Nv0zge85e41QXzPAxv8zeaYtU=
*/