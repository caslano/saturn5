//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_PTR_UNORDERED_SET_HPP
#define BOOST_PTR_CONTAINER_PTR_UNORDERED_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/ptr_container/ptr_set_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <boost/unordered_set.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

    template
    < 
        class Key, 
        class Hash           = boost::hash<Key>,
        class Pred           = std::equal_to<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< typename ptr_container_detail::void_ptr<Key>::type >
    >
    class ptr_unordered_set : 
        public ptr_set_adapter< Key, boost::unordered_set<
            typename ptr_container_detail::void_ptr<Key>::type,
            void_ptr_indirect_fun<Hash,Key>,
            void_ptr_indirect_fun<Pred,Key>,Allocator>,
                                CloneAllocator, false >
    {
        typedef ptr_set_adapter< Key, boost::unordered_set<
                           typename ptr_container_detail::void_ptr<Key>::type,
                                 void_ptr_indirect_fun<Hash,Key>,
                                 void_ptr_indirect_fun<Pred,Key>,Allocator>,
                                 CloneAllocator, false >
             base_type;

        typedef ptr_unordered_set<Key,Hash,Pred,CloneAllocator,Allocator> this_type;

    public:
        typedef typename base_type::size_type size_type;

    private:
        using base_type::lower_bound;
        using base_type::upper_bound;
        using base_type::rbegin;
        using base_type::rend;
        using base_type::crbegin;
        using base_type::crend;
        using base_type::key_comp;
        using base_type::value_comp;
        using base_type::front;
        using base_type::back;
        
    public:
        using base_type::begin;
        using base_type::end;
        using base_type::cbegin;
        using base_type::cend;
        using base_type::bucket_count;
        using base_type::max_bucket_count;
        using base_type::bucket_size;
        using base_type::bucket;
        using base_type::load_factor;
        using base_type::max_load_factor;
        using base_type::rehash;
        using base_type::key_eq;
        using base_type::hash_function;
        
    public:
        ptr_unordered_set()
        {}

        explicit ptr_unordered_set( size_type n )
        : base_type( n, ptr_container_detail::unordered_associative_container_tag() )
        { }
        
        ptr_unordered_set( size_type n,
                           const Hash& comp,
                           const Pred& pred   = Pred(),                                         
                           const Allocator& a = Allocator() )
         : base_type( n, comp, pred, a ) 
        { }

        template< typename InputIterator >
        ptr_unordered_set( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< typename InputIterator >
        ptr_unordered_set( InputIterator first, InputIterator last,
                           const Hash& comp,
                           const Pred& pred   = Pred(),
                           const Allocator& a = Allocator() )
         : base_type( first, last, comp, pred, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_unordered_set,
                                                      base_type,
                                                      this_type )
        
        BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( ptr_unordered_set, 
                                                      base_type )
                
    };
        
        
    template
    < 
        class Key, 
        class Hash           = boost::hash<Key>,
        class Pred           = std::equal_to<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<void*>
    >
    class ptr_unordered_multiset : 
          public ptr_multiset_adapter< Key, 
                                boost::unordered_multiset<void*,void_ptr_indirect_fun<Hash,Key>,
                                                                void_ptr_indirect_fun<Pred,Key>,Allocator>,
                                            CloneAllocator, false >
    {
      typedef ptr_multiset_adapter< Key, 
              boost::unordered_multiset<void*,void_ptr_indirect_fun<Hash,Key>,
                                        void_ptr_indirect_fun<Pred,Key>,Allocator>,
                                        CloneAllocator, false >
              base_type;
        typedef ptr_unordered_multiset<Key,Hash,Pred,CloneAllocator,Allocator> this_type;

    public:
        typedef typename base_type::size_type size_type;

    private:
        using base_type::lower_bound;
        using base_type::upper_bound;
        using base_type::rbegin;
        using base_type::rend;
        using base_type::crbegin;
        using base_type::crend;
        using base_type::key_comp;
        using base_type::value_comp;
        using base_type::front;
        using base_type::back;
        
    public:
        using base_type::begin;
        using base_type::end;
        using base_type::cbegin;
        using base_type::cend;
        using base_type::bucket_count;
        using base_type::max_bucket_count;
        using base_type::bucket_size;
        using base_type::bucket;
        using base_type::load_factor;
        using base_type::max_load_factor;
        using base_type::rehash;
        using base_type::key_eq;
        using base_type::hash_function;
        
    public:
        ptr_unordered_multiset()
        { }
        
        explicit ptr_unordered_multiset( size_type n )
         : base_type( n, ptr_container_detail::unordered_associative_container_tag() ) 
        { }

        ptr_unordered_multiset( size_type n,
                                const Hash& comp,
                                const Pred& pred   = Pred(),                                         
                                const Allocator& a = Allocator() )
         : base_type( n, comp, pred, a ) 
        { }

        template< typename InputIterator >
        ptr_unordered_multiset( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< typename InputIterator >
        ptr_unordered_multiset( InputIterator first, InputIterator last,
                                const Hash& comp,
                                const Pred& pred   = Pred(),
                                const Allocator& a = Allocator() )
         : base_type( first, last, comp, pred, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_unordered_multiset, 
                                                      base_type,
                                                      this_type )
         
        BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( ptr_unordered_multiset, 
                                                      base_type )     

    };

    /////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename K, typename H, typename P, typename CA, typename A >
    inline ptr_unordered_set<K,H,P,CA,A>* 
    new_clone( const ptr_unordered_set<K,H,P,CA,A>& r )
    {
        return r.clone().release();
    }

    template< typename K, typename H, typename P, typename CA, typename A >
    inline ptr_unordered_multiset<K,H,P,CA,A>* 
    new_clone( const ptr_unordered_multiset<K,H,P,CA,A>& r )
    {
        return r.clone().release();
    }
    
    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename K, typename H, typename P, typename CA, typename A >
    inline void swap( ptr_unordered_set<K,H,P,CA,A>& l, 
                      ptr_unordered_set<K,H,P,CA,A>& r )
    {
        l.swap(r);
    }

    template< typename K, typename H, typename P, typename CA, typename A >
    inline void swap( ptr_unordered_multiset<K,H,P,CA,A>& l, 
                      ptr_unordered_multiset<K,H,P,CA,A>& r )
    {
        l.swap(r);
    }

}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_unordered_set.hpp
BDu3axd6hCzMKeaM+y3G+xy7MBYe4Xf2hHeX3Qw/Wfe5RewZsnbUDfhSzqjeZ9/OI4/0MD4uC9s/bmfy+TPJ/7MWdT5/NHv/Gnp90u7gjY3oMPu6Ghz1Jr7nql8Qjxcg2/iTaAA/+CD5hpX49m6w+fNazrmjDobhvKsU/e2s93DvAds3lViSOPbnITBbjLP7TCuGH1ivbC5nRWClIPmdX92NP4PHv1iHXP6BeDPEGQy55VEbiWGgnzCM+zvc9ezJBAsUMpctsAPk9ZZuwNZzz2k463+hGR9AXnMWf/9sMX7jc/wPmOnb55C1MdgxdGG/TmwAdWqZ56ijwLJTMFngwMtawUM+cAK6pu4lTHqePSB/0JVJ3voZ9noo+g7NX0H+dhVx4Hhy+eiCP8Y9uJ0zOEvHBo/GHmUiM/2c8T1hxSWnnpmpf2eTD/3bogzyfOSNfMS/6LlvCHdziW3qbrXqnvYu+7k3/mw2slkOtnkCfDuSfP908By+6zx4fOZvrDvFdcvI7eETTmfMKLihGj81AXuZWQmmm2CNeTE83eIhbA6Y+Nn7yA88b9EfPc767XuKPURXFmKjPwOP9HO2fsqO+AP+nv1r7O+j4Cpsw3YzMjyNb2B/Ofu6/mfYo4/xE5eQP52K3H3GfhyLTeoAN7zMOPiISmQpgC8tvwm8OIp9As/t/Dp2D2zavBf7pPzQLeSH4EnRaO7pPoJ8L8bv347sN8Kn6eCQVcRc+8GrX5JXuYYY5AjkElywuAb5Ih/0GHbgHHB0pJj87an8XoFd6uM8AHk5/Dv4eSznichjPlhrBmMNh3e9GWC2Z5CnbeHhGRYPduIsMv94zrOJi/rAUbvOhX/kTO7MyvBkrrL0blk2Z+/DkRtktnJX6kexIWCL5fC3aw37VgTePJSxfofNOwHMciB2j7jpHT8x3E7I9mLGxI9fyJnzX0pYN3HE8ZeC4yrI5R+Fbs3jDmU9Pml79HQZ52T8vWWRhevWYusejYAJwReTV5BL3Atbznof/S14Lw52Jt//zw3kFWaB37En449n/X5wCvM45WnOPW8AW3TiP24H33m5X4G81TOnI9YRR34B3sGO9oJlRq4BO6Ff95EnyliOvO+FDX2S/T0TnmE7nwaPVZ1Ovx3oHLmeMLHnsuHYbLBPqY+x4flhn4E3SsFb+K2q9+DdMo/OA/yePOfuL4M12OPfDgGHvEg+jjtSw+D7rRkZzI8cEfeBcsl9X4ufbDuRGPU2MP6N+OYN3KmP4AfA81vchPwx/zvfId9KTDohBOZmzm3kwCuIK/5BvqCcvz2/RGfxkwP4gJYQtuA0bM0F2O4/8vcZ7BP5h5PR/yOx22+gMwtPwe7OYp5g12NLzLku+9SIXncgb5lD0LXl7BO29B5k/zZihYn4mQM4w22fQ35/bIb2u12MeS933yfdyX7dCj+Y63XI946sG9Z4tl1A/E1euj2Gr94LPzyeffsbdhc9P2YqY4PTtljP3PC/WWCWJ+bjiw5Bdzjj8pLfirKuOYXIKnu33z7El+WcW7Ifuz5LbrmSsuHEt9iJw8Dpz6l7yUFii6vQc2Qngf++6J0sMAy593PIaxyGXCMzVXcTK+M3vuHfjxwIxlzH/jRwb4wY9/wvwQITyLsjjwvQ4TzsTga46J5JnBt70JVf8ndrJueAHmwl/gxePX8c53KvgokayV18gi8/Hz2Bd/6vabM7vgseXYEPW70P61Gx5Jbo2d7q23/kk/Ebmd9g2zrQt53Al89T935k8RliWPDesNHkIbCNXzdybqvuzmJDb3sHfdkJ+XiKvwPEEt9b+3c5OeGKVfDpIBVH4mNPxs8dwr9/Rt93E9PsT77oZDAYNvA=
*/