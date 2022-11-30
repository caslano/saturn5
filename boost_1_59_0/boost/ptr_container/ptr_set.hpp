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

#ifndef BOOST_PTR_CONTAINER_PTR_SET_HPP
#define BOOST_PTR_CONTAINER_PTR_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/ptr_container/ptr_set_adapter.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <set>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

    template
    < 
        class Key, 
        class Compare        = std::less<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<typename ptr_container_detail::void_ptr<Key>::type>
    >
    class ptr_set : 
        public ptr_set_adapter< Key, std::set<
            typename ptr_container_detail::void_ptr<Key>::type,
            void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                CloneAllocator, true >
    {
        typedef ptr_set_adapter< Key, std::set<
            typename ptr_container_detail::void_ptr<Key>::type,
            void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                 CloneAllocator, true >
             base_type;

        typedef ptr_set<Key,Compare,CloneAllocator,Allocator> this_type;
        
    public:
        ptr_set()
        { }
        
        explicit ptr_set( const Compare& comp,
                          const Allocator& a = Allocator() ) 
         : base_type( comp, a ) 
        { }

        template< typename InputIterator >
        ptr_set( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< typename InputIterator >
        ptr_set( InputIterator first, InputIterator last, 
                 const Compare& comp,
                 const Allocator& a = Allocator() ) 
         : base_type( first, last, comp, a )
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_set,
                                                      base_type,
                                                      this_type )
        
        BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( ptr_set, base_type )
                
    };
        
        
        
    template
    < 
        class Key, 
        class Compare        = std::less<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<void*>
    >
    class ptr_multiset : 
        public ptr_multiset_adapter< Key,
                                     std::multiset<void*,void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                     CloneAllocator, true >
    {
        typedef ptr_multiset_adapter< Key,
                                      std::multiset<void*,void_ptr_indirect_fun<Compare,Key>,Allocator>,
                                      CloneAllocator, true >
              base_type;
        typedef ptr_multiset<Key,Compare,CloneAllocator,Allocator> this_type;
        
    public:
        ptr_multiset()
        { }
        
        explicit ptr_multiset( const Compare& comp,
                               const Allocator& a    = Allocator() )
         : base_type( comp, a ) 
        { }

        template< typename InputIterator >
        ptr_multiset( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< typename InputIterator >
        ptr_multiset( InputIterator first, InputIterator last,
                      const Compare& comp,
                      const Allocator& a  = Allocator() )
         : base_type( first, last, comp, a ) 
        { }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_multiset, 
                                                      base_type,
                                                      this_type )
        
        BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( ptr_multiset, 
                                                      base_type )     

    };

    /////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename K, typename C, typename CA, typename A >
    inline ptr_set<K,C,CA,A>* new_clone( const ptr_set<K,C,CA,A>& r )
    {
        return r.clone().release();
    }

    template< typename K, typename C, typename CA, typename A >
    inline ptr_multiset<K,C,CA,A>* new_clone( const ptr_multiset<K,C,CA,A>& r )
    {
        return r.clone().release();
    }
    
    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename K, typename C, typename CA, typename A >
    inline void swap( ptr_set<K,C,CA,A>& l, ptr_set<K,C,CA,A>& r )
    {
        l.swap(r);
    }

    template< typename K, typename C, typename CA, typename A >
    inline void swap( ptr_multiset<K,C,CA,A>& l, ptr_multiset<K,C,CA,A>& r )
    {
        l.swap(r);
    }

}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_set.hpp
kX+aW5gJTNCPsy4Iiuw7Mdi+XSRYX22ATMAJSnsR44hYTTgJqgNUKOJwWE3YCN7lEX8o4xytJJAIjAE85QJhlIXBgBoQ4mxAF/wUQDlXAwmh4+ahjgKwlMDH6ATAqOPcl+OqAyQCdNpICNxYTWAJGMUhFsoE7pfjwgElQYtkAtOW4lAE0IAb1AI/JWAjQE2ICWKpEH4AUY827ffTANPLBGIqCcEB7wCQSgX4VIR3gEmumYN0eigIassILwB/pxIR9L4J6/4mIA3wrRNIUl24BKgBNE4JlEkKVhKgCDKOFMokAKsAcAh6DBjqyKYRyqkAt6ca9CIXqkgM9g0izkWgCerIlfVIVUANyGmBmKByCYGZwDQgiToufCkORgAO+D4DCLMw7BMEYVoxqEqBQHgpzkLgGoBEOVBnozZIomhppj1gq1rguZLQG4ASbGgPUe4hI1XF+AsfsP3QOajJ9+qht6dgX62wuflCXmJwNNa8nQOgEpBGLWCYN+BMhyKgF7hOBTDlGWAHas8NwP+umf4TUJdXbhhv8Cu2VtSg/ovT1YBQV4gHcmr77zwgW4eEr3cFUl1xgCh0GsqHR2y/I7MAX0BPh4DrTsGSp3QsFz/s3tghyOcoKH4s5R1+x2etvTJGSygjgUUmSNibgYY8jKxs7Y1SXudAXlozDLALbl5s3eX0vbvb8uuSH+Pe/KxuSCeYxyOo/qsywgc9GNgtL8CZ/N67PsLqzyT58ip+HGNAU7Z4vug9kfuYQ5MSjDh1oBaECq1CDOcfiNFwoEVQB7aAYoDv7y6IGPwplBcjcvOKJGeSPNYAOu5Y6MMENXqoToY/pwUAUp9Asz85L6G74nE8gWZ++4H7QCwJ1qPOXRUlcXMlMiHrN95A2y9sGhN997aZDDn3wkRkbQ0xSuA9zFT8LnI4CSuhLC75FhaAIE2CfTFsjJMd/rVc38Akz9JD/rZCD1uzIVSMj5SAaZR9NJbQYqb1zl5ipru+uBbV4U4z1QaYo6Tik+3vzPvss3yARZhxhlAmQVj3aAR8AhvbPbfYOfSHS1lqXK5LtAV3R3VewA8gDKJ9XTfPoHhwXjOFSnTICpsBXuu0Uxp6NWyHmQGWgCcRdpKScSE2WZ93rVT5OdAK54kWvdplaY/Oy10XyAIjAEx/Cbk8Z2flnd9+erL+oeJRsseNw5mYgTGVCJj5ECTijG2hjW2hjA2BMYXh0WaGaQFuAwIA/QL+BfIL9BfYL/BfEL8gf0H9gv4F8wv2F9wv+F8IvxB/If1C/oXyC/UX2i/0Xxi/MH9h/cL+hfML9xfeL/xfBL8IfxH9Iv5F8ov0F9kv8l8Uvyh/Uf2i/kXzi/YX3S/6Xwy/GH8x/WL+xfKL9RfbL/ZfHL84f3H94v7F84v3F98v/l8CvwR/Cf0S/iXyS/SX2C/xXxK/JH9J/ZL+JfNL9pfcL/lfCr8Ufyn9Uv6l8kv1l9ov9V8avzR/af3S/qXzS/eX3i/9Xwa/DH8Z/TL+ZfLL9JfZL/NfFr8sf1n9sv5l88v2l90v+18Ovxx/Of1y/uXyy/WX2y/3Xx6/PH95/fL+5fPL95ffL/9fgb+mxGn9XOFW3ehczpsRzYXsDKF0OxAFIPs+naXQLY5jE1TOj3hjBY5Q8smyka+eTcrs2HyhJKgIiFHGyDErat6wCaIA78b54IR3JxDcQb/TCK8rPumEMS5rmYeCXCTDNEK9+YS3RD3ohLdcNVPytZCmwk6V/vhli7aONaIoLnJUx5M7adHvVv7pSlSOnGUeyniFKIYaTKLCTCL6MP3T7Oz/bhnjwb043P1euziM9b7ussw7UsI2daSYnN+gEJDhojgU/zHrgMi9IKq4meRSmWCntgAr1aEnGZXsYtpRlqApiU59JkSaXVvknOQSliCnuHAnxaUleaOwIEIaDW07ATf0YzHRsfjnh9RRln4WqRWbzgmLeLJxyLcksVFltWMFtveUSI1YA9fUo8DjJKUxafvPpRsDVwvRB5g5O/EH94ydwPMxQgTphW9VVa8DuM/pIUIv6MGPl5qG+1sQA3gMlwxQGW7eE9RppamVcDti2ivz3E+jUVrHF2HyvT6hr9sMwJALm8OL5PVDHPUe0+zUpedF+bVOn+k38BZ337Y85d6mbMXyv13ABag/F9T5jL05lEl1JiUV2rlALCfUPD93yW1EsZWEzACSoEeoolreGVaBh6MBNGBHZ7UhhDssyhhbrsyhKfA5lDDVvQlo/yJdTGsmbnvigFOP6mCQQ+awNcsU7aSU0XIXVVR9kOfcBHo5ia/fir+EfGftaRkkzSEbcxmem9v4se6HOPwOIhz9/FhpQ9qHKEe0leuMKOOa8BJWvtUTam5kF1ApCc6IjrPkJKQ4kV1SmlNnwUaiamsprOuMTVZRVTN3we25Pb7olrVGbxyswkIubqAifSu0L0fs6uGa18L7O+G6TOnwex3aVp3CcHVJS1Hvw7PYJv2Plyh7LTmRe2Ychet8gwltsEN4j5AUhb8/8e6sNjWnCEyAvpZIHyef8hwijFfKrsVVgLiw5ixYpuZj+Hre2pml0Aqv3HthMBN5CgalZ8CoVEAA3xDmHLQwZjWfbEdxBNgA7lMXjQjJkZcdaY7/Hap1tslHrkZsEvRq4yLJRqMTG+jUNVkTVIAWnFAXf5k2VjTV9g4E9XEG/VUlGLaSQCaQDIBRJYgtI7QHYsKPs5eDHJtdikMH0ASXaARqF4T1hInDDegqFOiqLScoD2gC+o3Oeny0QTHh/uxEf+hDmaRi3W9jhrAEyCgSZO7wIXugWK6QuX4E6sE8KoBGp1IPbMKPiQn0cJZvOW+6nfwAJPgQ3Mcz//cds0u2t0Cs+8co7r0BE2eKSk/Z09WlQojKFM7JLYNYC97haEuYodwshvNWShK49SINf0OLvhhkMgmXRCSCUEucaxe5GYvRfvtu7oWzf2evup+/783Ftatu7qCv78yq7+gEPAm4RL5Ix93ANJATvsSn7eLl9HpJxjB/cENl/1svi4slOLMJtAlK3DoSZ1/86PGaIwCTCtHut01FUL3i3xlwXPCOwqLSm7im6ASmSNb9G8HUgBoK0neW2jr5wKaOSqJ1pHq1xFH3WO7pQ+INjTo/g97ky+xuA9zKyn9OKwBuhGucCbLfM0nzLTyF8BMMH+BX5Ge1WKfaxJjZwB0Yj5UJOaT3hmU58xT4iga0N4TfV2iw1tpt7cUCPoEmEkfGMV2gJmxxp9pNdV7OJNqvnoDrQCbtIlmcRpAkuGNJ2qcg7CrkM4J+u2sF3Fdb9zxGOmVO5iHP4WYl/DxRGOg1Olj5+OJHEcP7u00xZjf2FikSB/vTXojXr5fMK65+lkHqQM/fwBf6qDHr/nJ0L7N3X4GSAOYAW5RVGxTGYnM4HOx/hp2xAsWAdF2QwdtZOwqW/wTrVCL6rKt6Y4dXzN31WnIhYHcXZNHBRhryZrJnhwjRomywUayxUHzWx1DaBAfd8e38tAGGIlGo0NKXSgc7CdUG6EaltzZLZUAtG5SNQCx/WDe2lBUrotVSk1NCLXxkNGEvqMhGBrNoJd7uBiT1Z4T8JNd4WCiRFV1nhMxOUV+xliMsAMlShbEoJ0oRyi4Uycmqlp8tQCVcEvDqEJGKS6BmHMGdZZDtR5lJ9ZC9CXKVSA4SDlsvaEh0slgyFVVnoMBYfiGtDLpQDhdgoXIUhpSEOKcslg9SfJXplRW42+XX/Kgo5iJthGfcO4a+BY8DI0EVAcf98Uwjdw/t/yOho3WaAA+dT+l8RHtlGCbIjbsh2rsAY7x9wZKoc8dFy442vstZm5re2/0lX8bmGfC6qs94KCDR7BIax3pcgj2AXXJuBxGOkd9J6DMg7i7cFlp4HXb7N6YDe4Az48wO4ufV2XUQdp/I2DXkNqH/t1RRx5U9pFZHU8Wwg3CL9PcKjynDbdh9Fm8X9pBdm+VthJpGsd/CWaDfQoHF37rw0YvbCHZHrWUFinVe/bBXnGa7fWBYeGHH9E9Gb3FsSaKuN0BK4CLtcl93z/lNGLpLVQk96oxJoLxTwZEvwqqkx1y2DMk8hrjjFgTMAT6wJANAgDrfXMKGshQBkwYT1uhlIcKmYQqIgJS2YRkHIhmnzdCWOe/aESW6OkE9iBu8tYmjaGANbfsmBKwCeiiLr6j4EvVY/GAJzDcwJofrXGUY1qrJQUYVWahb594CZMDr2jZaXDInYWBBWsBWvDCiKERQc8wKQ4N7DaltU4PF0W1/B4u/zrHuSLROp0KHv0kj9Z4qW3q676gHsA02NVMupACiuf4BlfmUHt3c/cZnbeAVgz8D3zes97GqslTDG6SPZ7jzLyGSy64LR5EA5+BooHGJU5B7V/hkwgb3ndYosftUMmgUfANHvqYBLGeoAplUMwsuLwAtDc0B5ThpWPSy216KhDJf3yEyy6+J5U7+TKoH8iWRn+nlhb0G7M+IM72h5TykSmkdtZfJZEZD9lX3+IYdKuvn8qBbFLK1ySWpH4tKF8j+WrH+R7Niz3cSVngJkR1SscYh/A9g7ATLAilSRejiWoBnjxqiOwkSyDEqOqNswAj0EVt7N9smwOngQ0pEljjroCRQf5xC465wNCF/lzG6OAh3mksyfvULeiBqjuNgwluNwjUW9NSYtqw8ZmSzPEiN3Qstb9YBs0quKf+aOYQVHLBlcEPmEKzC5E9b1hDeyc5hjSph1wCF7YIj3koEZ44Lh6ZUiuNI/XQOQU5yf/mIXYrjtqTEYhz6Y/yvCSzRVh/VKlNX1AXtP49y6POE44GyrLA+CHfKsp8ct8d7rdA9Wox8hQWwd4Ujh4fifP8ITckpN6XbG5M2pdpDk3Jhyd5q+0l2k52GDXRRSQ++bqzLtsk9fjr/4Fk9Gzwr/MBLsMTx0yM3RBFjBxwBctLHJ+OkQxahjfFFyBz+4UcYVEaFTJbwj3EBZkIb+wCCVJVCT8rsXVJ3V63c8T5XPS8N8KU3dlVQ6rbt8Cv5uz6LiZwNyYX2SJ1aDi6PO/Q87Q5ECaLkKlnz3bJkEf+5vpPcMX4pgk+5j89CGc5SLifhfPQIhx+vvoM1NMEBUL5ElNycGhfvMOxm2E5R+UDwDFRYTPkynYfyyH7gb7riBVdjcmev7rAHNSRKRA82brO/m0FxhZMmBISilK/gjvhUWrPxrRpGj3FEyQ2+wPa2YG8two7NGGcrXlitNCNkUIynBqdbVMplTBDrD2xUNfoWKxLmUEQeNy5wIjmUQkwfyeAEhEkbP9qzBKzvpWTIR0sHlAGyBGgxFFJqxf44WBZ2Hx7tS7Vx3kNUjcGoQBk6kS3U8J1tr1nokTUroMk3+GIPZUmgdbnZNuqBnURfpht6ZHXoYwnDyJdfb/aHPlPyKWQCqWyKuih9qeXj+ET2bdj0shEYkzZuciLog2ah9KhBLUs6ABpgE3XB76PB/U2KH1AGN60D+ohBvcJq6sIHGWH035+fXgHz+Qd+M/N5whKWUuAcAI5roOL1KsWM4L4qkEZBJvbdfRl0BkcDM52yVb2VrXrR1cUwBd7d7iJSXTfIeTSFO4S3vypZTK58iJHP9kHKAOyegS/4dHMoe43txyfO+7Wyt2J91wH0uezT535bKiW2HFd5k82a2EMVLb1JQsMVYokDwxVqiSLgTBqJRMMVLfzOz3ASbkAJsHYSK42E63pm4zsP8+Ta54XyzwmxfOs4+L4NlBkkaIYt+FvLtCXs0ybbw+dRa/FiKfezitBvrfAPBwYEYWRyahPy/yjs7BrgLzjA9JasVqBvNfomZ+fHB48JHP9oKfuS/cEXZAHuArvVSH9Vtsf70f7zCegYP8YaUwRMCXYf63x0R9wbr3vkm/RGbq+J3xxX0PZOVeZuVVGRS1eG/nWQqZc8ENGZYYrhnBhhIB741QNQTF32bV1xqgOdJGDPFutItXRehN2kJnTxBZQR5v5oJnhVUL3w6g54BVJnD4ja1oDvTWAeiAJ4pqNQ6wth93UgRYvB166fjpb448z/NY9ZXTEga1kdTFhpVpEf1Ji0EulX5bYDfABuUitS4jQELwERRz+rNHq6HQvXvrH8myhTF4RQsC4bEjJd0MSinfXX2LGYUXXTmzx9esAY7H/hks4kR/9YOHPw0z+JhCQr1qDQZFFPvs5G7NSVGq/YFXnxczAu9vz76ZS4AETxJnR2iun5vZqa+wOYDnukHQFzIx0Fwf92sZ2Khnzte/xmr/8Moj0oQiEjwyU8uV7iu05necxpowV85htm9WSGr+Fd9vcn+zl65oXwot037clXgVWjrML/WBnM/1QY86MHfpqmN6Uis+1cqGwmzCpDBfZssPcH0AQ67uoNBbLOgG+zz4m3VLUU0IFrj/NtiW3SabJ5fHUNYZ1V04CMmURHKiKOjT514dasIglbjfgFgFD3jBbbBbFoMUMFqnxahlM2c14nuSDYVLwOaeHEYOWtmrrvEaCdeqyQq2UBHRT1Hi9uD+32h2dDko+5WiiJS/tTjMpycS3tSC8vuYc8qTCPhz52hGRzB4VmPp89c4Gfr5JymzdKEE8K2KSEquu0v1dXFv47Ej3zoESweJlfBRU6P6EcB4kKPSlHiFR3nfhIxjS86yeyTb8wxFPxdpjL80dQtf10H92z3ox1OanXUWIKN8KWX5buPkzBrpBEXfHbp2vsi/foK1sVJd/2ZrirGlNGtH9Jw/K8nLyc79bktJk5LQ7oinAeGon3alxrxi+vW7vitHArtVcE9YyS6wqp2Apt81YPYnt9TnaS1P8q1fh+9fTl6RurXvGmlj317KtZumxHP5vn6dvqqvxl1b304qvZLGNH395KiatoxXmdTEeOjwvx6GlZZ9GmwCXbks3RNNuPrX5TmD9z7SQ/V9bmdm6WLMXz1ByZEK/ri1gzSs3ju1SGHm4nqrvS19U4IJyvL7qFpvPEemcRbgM6n/cKxdNdGl7ruMfBfLaeBz4YRGFWmYXWXo5Uie/vXOxN+/X7Ha/qbxAYnbxWnnzy4fkTOM+D0Z0jjI0Maf32TY4wukKVkCB8ZqclffaNWCPv3qXZEXht828O0kysfwooLV8BR/uFiVbNfHaCipZqVKgUG000nyO5tJmKmjOaEgGmm6zx8wUr5bhQIDKQZTZ/xXEuWmtUj12tMjNQq6egYJj8DOFCmh2tmwn9D33cUaKJbQp29finNdUUOWegwD9AWO63+xYzl0NqQOlTEUHzSBb7/REfmfHhFJQ4P6T2K6njdjp/+o4Gp2KBYkls1eIIFcm4U/n7F//2Ca+yV8FjHbZok9z2hSqjiWyofKbV5JFpzZom7Nca6uEWWSfTRF79tA0A5YsGS4GbKyk726PyFlAtcBcrNtOm0MqtH0fDU/vSuWWtirJOEX9HQ11/sDgCgurGcl7c/d8HKqwAVSNExNGYE0GEgJxZ/KT/AdELv27ZvVlHHLhMYi/y8Y0FeoYkjGs+5a4AuhozHIMuyCKhpkoYHd2l5U92cMqCmujOWMGEtwWJtfuRfXq8LMFDXgMgFW7RsgwxqEYxFuVghNiEQdbn9rSsDyCyI4MjYWLGMhUx71exGNXiqJKf/vf35NgEGwyZlSERT6JYFMkP1Xp2q8oHiHvhJaGZsBNDg1NhdQlYd0VF7GSRa//uDE1i
*/