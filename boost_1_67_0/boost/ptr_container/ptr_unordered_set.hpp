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
dIl7I7QWmVGsZ+7NOrg3J61nRtyboyrJDGVxZiiKMkNOqCmSzxvD02Iv1s0ZgHivUz2epfvz8tjnmE9//snHx2dsZw/++7S3d+7cuaKuru4pz2FwY53A61hexveL0FBZCGeD3dgxfyD2L3wHBhsmwP3EUoTabEas8zakuO1Elu8e5AftJzs4RP7gCOWFR8kOjqMxg3RbljbZwQnSBydxqZB8fbEB2YERrpafwgX6u4tFxhLu61xwWXCvR1rPGK0F5riYb44LueZozDZHfQZxn2ZOOt+cxr0FyhMsURxjgdxwc6QGmCHcTR87l4zGqV3zXvic/PfsG1k3k98/2V9H/srbnzZs2KBSWVl5l/NFbpw3cP7AceFFfLMm7gstTTVwM1fHLuXh4tzbk+sn4Iz2UoTZ7UCsy26knNuHLL9DyA8+jOKIo+QPjpMdaJId6JBWo/GcrUd2oE/+gDU8abesk8Q/cV/rTPmdCy5V2BL3+pQvsL+3oDFvQWPeAg3ZFsS9JeWVlsS9JSqTrYh7KxTHWiIvwgLpwRaI8zOHzo552DB/CNpbanvcd/dn4xyf+yAvL69N5t/D7/+c9kcVFZXZxcXF7dJz/7mOwGuaeDy8iO8X4XLbBfg66mHXElnsoDirvWYsXDSXItxhL2JdDyDF6xCyzx9FfoiGqMFWxOmQHeiiNlUfDRkGaMqiXC3lJPl3E8rtnAX/l8qJe8rhm3JNacxb0Pi3JO6tSOfxeh4r4t6KuLcm7q1RnmhN3FujIMoKmaGWSPS3gJPhDqxQfBu5sW4vvG+2eW6kk34gvf8q9+n/WtofFi1apJCdnV3J9WSOgWwHXF/kvumP9964erkNkT4O2LVsHLbMG4Ajy2XhqLEEIQ77EeemjlRvDWQFaJId6KA4Shfl8XqUp1GOTj/raYxfr3ES/LeX2aI6zZD4Jn9PvDcT703ZxH2mNcV6a9SkWaMqxYa4tyXubYl7GxRE2yA7zAbJgVYIPKOHdUpDYa+x5oX3ynbO7/Hh+ml4ePjO/jrq37z919SpU+WSk5MzpTVF6RxDf3bAGqI3bty4joQQD+xfq4ANpL32LRkO26NkB46HEefOa650kB10EnlhesSZLvl4E8rtHHGN+G9j7tMpl89hf29DNmBDsd4G9Zm2qE0nn5BqS9zboiLJFmWJdmQ79iiIsUNOhC1Sg20Q62eNg2unY7PyKFy72t7jvrrfN/PO/GdlZRXLvNr9mr/m9n9lZWXHxsTERHIskNYUed6J7aAvrvtDeow/jm1bgNWzB4h3h5sdXIwgR3XKyU8gzluHxu8pyvftSOM7kOanMZ12iny8FZpzbWnM29Kf7cjfkwZMt0N1qh3FCTtUJNvT/7MX3BfG2CM30h7poXZICLCFpfYmqCr8GVUFMS+8Jx773Jqamv7q6uo6oOvxX7eOxjXFEcHBwV40Vn7i/W3cWDP2Zwd89kFfKM5KgM5eVajNfJs02SDo7p2LVJ/jpOUt0VJogwb6WZHIebwVaUO6pvFen2lP3FPen+ZA3DsQ9w407h1o3DsQ9w4oinVAXpQDMsMdkBxkBz+nk1CdMQBepgd7fHdv7tmuOcaR31/dX0f8f964pjjUz8/PiXLkH6Q1Rc6VuB9fxPXLUFWcA2PNzTBYNQhhhqOR7qGKwnAt5IeboJz0e3WSDWrIv1cz0uwF71UpzL0jypOciHsnlCQ4oTjOify+E7IjnJAa4oBoP1vsWDoRe9SmkH9/8b3xu+w538vMzEzs7+Fft84maooODg66ly5d+o77jxvXEv5eO2hprECq7zG47h+Jk8tpzGooIcNTi3ShNUpibVGaYC/GeXliB++Ce2fi3hnF8S4ojHVBbpQz0sOckBDoCINDq6A6/W1cqMt/4Xdy3GddU1NT8xk9yx86n+51+7lN7E00MDDY29LS8iXXyrlJ5xhexjfXGPrClbYmJLrrwXr9aLFW0Wn/TMoZNZAbbkf5nAONcUcU0lgvincmSHgviGHuTyMj3AVJQc7wsNbEkqlvIcrdtMdnd/9+vj+u7/Kfo6OjF3Q+0ev297a3NTU1NzU3N38irSnyXAPXVF7G94tw41o7Us/biDMWjyq/I+bpA+wOISPMAVnk47NorOdEuyCHeM+KPI104j45xAXh3jZYqySLo1uVcOcF38v3w/VvRnp6um/XI7xur6D9WV1dfXV1dfVD1gXcWCdIc8P+eO+NWxS7M0JdoblhKrYrDcCR1RPharoHicGOSAl1QWrYafp5mq5PI9zLBjtXTCe9/w6utDe98DOZf85py8vL33N0dHyVZ3G+bl3tja1bty6mPr4pPW+a5xjYDrj/eX7tl+DOndvIjaPccctcrJr1NrYoj4apxnp42unA3UoTRkfWYeXMYVg46U3kxvu88HPYH3HMp7zlp8TExF/bnP6vsf332rVr5xQWFl7kugH3PeePbAPsD/rjvS8UZ8RCa9dSLJX/M8X5P0N5yptYJCdBnKfZC/8ffydrVdb8ycnJll23+Lr9E9rvlZWVp2dkZJRI16tK5xj+Xjtou1CP2GB3RAS4ITspHJfbGl76+/y9bHvFxcW3ZF7X+P632u8WLFgwhcZfOnPPNiDdz8J2wHtq/xFgvy+d24mLixvXdTuv2/9S++3YsWPHREVFhbIm4xoc+wSef2WN0B+fvwTs97m2z3Ob5H9e5RnMr9v/vP3n4MGDRwYGBnpQTt65XpW1Ao/Z/rj9OWD9yTlIQUFBk8xrv/+v2rimONjb29vuypUrf5PWFJm7/4kdSP1+Y2PjdxEREUP7u4nX7X+9sR28Q3m5Vnt7+1+l61W5lsBcsmb4uWA9wXqPtQX5/T39ffHr9i/VxHrVU6dO7blw4ULnelWuLf4cO+CxzzbD9kN+P6/j8163f0CzX/x/ZBwIjgQngjPBhXCacIbgSjhLcCO4EzwI5wieBC+CN8GH4EvwI5wn+BMCCIGEIEIwIYQQSggjhBMiCJGEKEI0IYYQS4gjxBMSCImEJEIyIYWQSkgjpBMyCJmELEI2IYeQS8gj5BMKCIWEIkIxoYRQSigjlBMqCJWEKkI1oYZQS6gj1BMaCI2EJkIz4QLhIqGF0EpoI7QTLhEuE64QrhKuEa4TbgBsLJPTEH4im79FP28T7hDuEu4R3iM8IDwkvEt4RHhMeEJ4SrhJeJ/wAeFDwjPCR4SPCZ8Q/kL4lPAZ4XPCF4QvCV8RviZ8Q/gr4VvCd4TvCX8j/ED4kfATAYTfKP9Tlkj++eTJk5sbGho+kNaU2R+8yA9wPsHnoHJeWVtb+0VCQsKfuz7qdfsVtz9pamquqqysvC9dr8xnXnJdh3NGtgeu83AOwdw3Nzfze/Bez+39+7X/3rdvn0ppaekVrhdIcwVu0n3aRUVFT2JjY+f390Gv26+6/WHLli2Kfn5+jqmpqVWZmZl1oaGhkR4eHttkXu3526/bv37jNYqv53Jft9ftdXvdXrfX7XV73V631+11e91et9ftdXvdXrfX7XX7VbTOSY1/arPvefmTjG2P629lZHtd/0eP68963fdDGRmVXtdvdr+ulOn5AXa9HpyvVbpdc8d0+4Cf+Po3Xdc/iJ6z7XUt23n9rbj+Xef1Z+K66wMk110f8FBy3fkBlZLrzg/ouO78ADvJdectd1x23rL0uuOZf5Jedzyz5Ha7PqDrWvIBktvv+oCO2+38gIdd17K9rsUtV3Zdi1u267oWz9z9mj+g2yV/QNftyog76HH9m+63K7nuut0+rmV63L64ftj98jfPX1f2urbrfv0fPW+X77fXdY/bpR7tcbvPXcv2ul2VXrdr+9z1wx7Xz99u72u77tfP337P2+3v9nvfbv+3/7DHda/e7uP27bpf/0c/17/rdf1mP9eyva5Vnr+u7H5t2+t+ew4GYd3dn5+vu/efGD52XddidDzsdd3tA8Tw6/YBYnR1+wDJ9cPOaxVx3cWQrbjuYrjjulJ6LbnsfASpP5F+QKd/6bjudJkdH9Dpjzo+oNNDdnxAl8eUXMt2Xj8U1yqd15Jn7rqWPLNt57XkmbsuJR/Q7Zo/oJtDFh/Q28P3uH7Y3R9DfECPCPFTr2t6Ztke15/1jDD0zLY9rtE7kkq2I/7LNznquSUE7vHfyIyWMLdM8uN1+6c1XjfKawn+W0byDvbfdvzd/w+Nz3t5k8DvNZ1JUJSRvIec33v0O5l/737ghY28bpCfeSvhMOEQYbuMZFjy8OT3cvP7mf8d+4FtfRphh6Ki4pnDhw/n7NmzJ01WVtaW/u44YZeMxBtNkZG8o/j3Mv8+52XyGJclrNu5c2eMj4/PD35+fvyuP/j6+v5obGzcPHXqVBf6d00C7ytYISPpq8Eyv/5+4Htnu1ZetmzZGX5efud4dna2QGZmJr8Hg993CxMTk9Y5c+Z40O/ynrq9hJUE3lPP+2zYfn6N/cB+XuHtt99Wd3Nz+yg1NbXz2XsjLS0N/E5uGxubGwsWLPCWkfQDvw+SzxGbQRjW8XnsR38Nje1+NGGDkZFRdWJiIr/jUKC4uJjPx+N9VMjNze38ewa/mzgsLAz29vZ3VVVV+R0pOoQDBH5HGseNEQR+Z9K/cj+IfUcEFTU1Nc/IyEjxnIyLFy/i0b3bCPa0RWl2HD5+9r545xq/j1v6OwweG+Hh4XB2dn68du3aCPqsEzKSmLGeMJswkvCGzKt/R/yraMyP4qBBgzS8vLw+ZfvmZyotLcUH7z3G2rlDoTbrbWycNwBHV45FbpQHPv3kQ3FWemFhYY9+yMrKQkREBE6fPv3e5s2bY//zP/9TT0YSPzcQ5spIfOufZP511uuxvuNz3jeampo2Jicn8/nPAh9+8D5OHd0onn3HondwVHUwdFcNgRHBer0sisPt8enH7+HmzRtijEj/H4PHBtsR+ZFPdu/enfxf//Vf+vQdRwibCLw2eYyMRGP8b/aDOMuNsHTTpk0BfL/S++f3nxRnx4tn38vvh1s3DFbbR8JpryzO7pcV7xT2OTACHntGIifIFJ88e4K7d2/zOxOe64fo6Gh+Z+Jn+/btS//jH//I70o/SthC4PX5rCnfkpHw8M/UUvxdPB5nDhs2TJPi/Jd8v/n5+aioqMCz959indIQ7FEZBIMNw+Gwj55ZYyz8dccj1GACoo0nIFB3NNwPD0WA/iiEGo5B7Dl9+n/v4sH9++Iz+LOk4M+OiYnhd8l8ra6uXjBgwABTGUk/sL5cTJggI9HW/6x+4O9hbb/Z0tKyjWMd+zQez8+efQiDw6uFzTPvjsS3j854hJvKId5mClKcpiHefqJ4p3zS6WlIdZWH1c7h2LzwLajNfhvnbdTx7L0HePToXVRXV4vP7Y64uDjWUt9qamqWkM8xp3vQIOwgqBAmEvgc1n9kjiHej0NQ3bZtWwjbJz83g/eSFKZHYZPSAOioDYUD2bsvPXukxWSkuExDlsd0et4pSDg9EfmBSigKWYhg04mw3jsMFjQ+uL8OqgzGhrkDcM54Fz54fAdPHj9CfX1953dIwTHW39//Oz09vdpu2prPn15KmCwjiUmvOsfgz2L/O3vMmDG6pGu/YU6Kiop4vxTef/Iuti4aiuMrBsN21yj4ao9HFD176hl55PrMQMa5qUj1mIyy6GWojluF1HOKCLOcgBjryQg2mATPY2Nhv3sUjNYNx5Glg7Fx7kA4627Eo7uX8eGH7wsdwd/VHexzAwMDfzA0NGyYMGGCo4xEW+8mqMpIcoxXqa3ZrnisbbW1tb2anp4u7oH99yeffASjg6rivTZW20bCW3Mc8S6HNNfpyPOdiWwfBWT4Tkd10no0pG1GYegCZHhPQ2nIbBT4K1LfTEeC4zSEmciJ/8u+8hT5jqOqQ7Bp3kBYqqvi7pVGfPzRh2hpaXmuH1hThoSE/MjaesaMGWfpHrVkunIMecIQmf9ZP4gzXAkr9u7dG8P+iJ+bwXun8pKCcZDGvPnmEfA8OlY8e/pZeRScp2f3m4G8kEW4mHdUvI+H3/NaFrsMZTHKqIxeiJrY+aiMVEJx8CxkeysgmcZKBPkLH63xcN4/GkYbh0Od4if3g9G+xbh2oRyffvqxeKe69B6k4JjB2trCwuJKtxxjH2GVjCTHYHv4pf6Bf5frGXMnTZpkFBAQ8C1/F8erhoYGYfcHFg+GMY1f98Oj6d4nSZ7dfyZy/GegOEIVVyvN0FruiNJ0M9xtCca9Fj9crbHFhQINVCVvRHH0UhRFLEBxCPfDHOR4z0Ay+cdws0liHDlSDDHaOAJHqB82kn85sWMe2mvy8OlfPhZnKbPe4vuRgmMGa0qy01sqKip+Ml05BtsDaxb2DT+38e9OImxzcHC4xTqNv6+8nHn4BDbqytBaMQiu5OvDTk2k8T5NPHv2eUWURK/EjVp7XG/yh5mmPHT3DIXevmHwdVyNnPhTaKvxxdMb8dQfvrhcYYr6rAMojFqBnOBFyPSdQ/5CAYk0LsKNJePCYe9oGJI9cD9snj8Q6uumoak4GV98Ltnnz/fE9yYF+yfWlI6Ojg9XrFgRLCPxk+wbBsr8vCbei0dYdeTIkWSOP2VlZQIPHjxAY2EQHHcPg+nmIQjWG09+fqoYz/zspbGrxPspb16gXO/EdFgeGwVXiv/uRhPgojcWdlqyMD86HNZk52GeO1CcbkO/Gybec3ytxg71mQdp3Kgg7rQcIm3pd8wnIpD+v4fGONjtkRXa4ujyIdi6YCD2r5qIutxYfPXlp+LcmsrKys77ZHCuxXUIJyend+Xl5Vk7/JwzLdjuWWcq0f8xJT/7HX8W9zHnNh88fYDAk7KIoPuyPzgMSY5TydfNEOO9PG41bjW44FZLOJwMZsJOWxbeZMuBNnIItp2MELvJCKKf/lbEq9lEnNYfC5vjo3Dq0FBYn1BAuPd+VGVb4lqlKZqz9qIkcgnSvRQRbjsOvgaycKe+czokC5s9FC82DYfGiiHYTv2wZ8V4lCQH4Msv/oJ79+4KDcH3y2A/yTqV7OGxjEQv9dfYX07+7W9/u4v67QHnKKzNqqqq8PnnnyHRbimC9EYiw30GfPRkkek5HZnkv8rj14h3Ud5tj0VVYQACnVeI5wxzmIJoso84V9JAhFgaJ3wd6TRV/Bv3jafJRIp5Y2F8aCTOmC/DvYteaMo5gCJ6/rIYVVTFrURR2EIaF9MRZjUOZ7WGw+7gcJjvHAa99UNxWPjJAdihMgrZYafx9VdfClvg+5aCcq+flixZ8vvOp+y7ibPbCWpHjx5N59oNfw6D3+dwoSgQCQYjyNfJIu+8EuJZy52TR0XcWuLdCfcux6GhIhIttXG4XB+FrOCNSCCfmEL3nUb9lO4l+cnXSe7y9G+Svgi1nwI/i0k4Q3bu47QF9y9Hor1UH+lBikg7L494Nzkk0O8nk1/I9puFvICZSHKdjAjr8TirMQInN72D/csGkAZ7CxuoH7wtj3TeN6OtrY3P9/hR5uX+n/+N84oFM2fOtKJ48iP/X+adY86z9x8gnL4rw3ocoixHo4h8VX7IYlTErhXvj799MQwuRnNoPNPYb8vAnfZU3GmNp5i3DZmkA7J9u5BFYJvh/uC+YNtgW0gPPYSMaHO01ATjTqMLskMpRiYuIDuYiyTSCiFW4+GhSzaiMRQeOiMRYj4eiS6TEWc3kfT2KJivH4RDS96Gj6WGuG8GazQ+B4Nsub/z6tk2pv7hD3/Y6+Li8oj9KI+juro68i9fIkR/MUI1yb6cJyKFUBi8EE2Zu3G92hI3moNgr6dI4300AqynoKnIBQ+v5+Dda5l4cDkZVYk7kUP+oTeyO/qB+6AsSQN1BadRkGyLspwzeNDmi/Lk9SiKnkt9OB85gbORSJoyhOKsu8ZoWG6nmKL2Fo6ovIEDKm/i2ErSIWuHwvXINFSUS+6dwed4UWysl3m5BhLvwyWs0dbWzktKSuJzvgX4TKGKJC84bxyGiBNjkUN2l+dFsS54PloLtXGp2hWWOgqw0qD81nwSIhynINFNAa2lDnhyuwCPb+bi3atppAF3Ivf8jOfA/VCfyZ/jjeZSD6SFHYOntQqeXItCc94R5ITPpvG1ALlBs8nmafyTP/U4TnFkx0gYqg3BYYqHm6a/hWUT3sDCcb9HZnJU573zu6hZp8lI6oovatwv7BcXLVy40IH0w4/8f9luuF7zwdP7MCD/cmbHCERSDMuhMVtG4zI/cBauVBgj2u8ADPYPhxv9W6DNZOHfUslW2ebby+zw3t0SPKV+eHQ9EzXJe557/ubck7jVHIxr9f6oTNOHn+VkmB4ZgYdX4nG12px8yEzyrQuQFzwbKdSv4ZRbeFLstN05mvgfhv3zB2O9/EAsGv0GPK10xX0zuPbI5z8YGRmpSB/0BY1rz/K///3v97u6ur7PvpJtnvOOr8iPmu6aDQPK69xI50SRPs1xm46KUNJqFO8vlxqhOs8JhhQHPSmn4zHMPo3HNds2c9tWYon375VRPxTjyc0c1KTs7Xz2C/n6uE/x4m5rJJoLLMgPKIh4YHV8JOqL3XDvghsKohaTpliAgvB5SDs3E5FW8vDSmgTrnWOhvWoUdikNx8op71AMVBDPzffO+OCDD1gP5si83Od1zl1QTlmWkpIi8k4Gn5mQHuqK3QsHwpi0l4f6GESZT0Y2jdXyUMpfyAaaco7gwaUImByRxTkT6fPLi+fnZ5c+Z0vhKXzwoJL6oRRPb+WjNmUfLhYY4tG1dDy8miLsJMNbUcRH1ghOumOQHKaJdy8Foip1K/IpTyiKWIQ0r3mItJ6Bc1pTYb5jAjRWjsGWeSOhOuVtlJfkd957x7uYeTnDy+Id2z3XDRZTXDxNGuFH/r+s7fksqCcPb4mzgw+Kd5aOhOdxyu0sp1Dcn45SssWikJmoStpEfioAPvYrcEZ/XA/+uz+/xM5P4Nm7tZJ+uEv9cKcQT27l4lqtG3L9Z9HzKwi/EeEkDw/KB90tlfH0eiwuFGohN3wBSv4fe9cBVeWVrZmVWS/v5U2MMbEXbNhQiiUoIoiKIGBiF4koKEqJiFekCCKXXi+9XHoTkM6lFxFRQKWIHaJYEo0vMW8mmUkySWaSfG/v/96L0dGYzGTyNCt7rbNOCv/99z5nn72//Z+z98k2QFmMLs3/PMJBmnDdOBM2Rmow0RyJzAgfgW9unZ2d+Pjjj0H+W1sp6BOIbYLGsGHDdvDeBa951nk=
*/