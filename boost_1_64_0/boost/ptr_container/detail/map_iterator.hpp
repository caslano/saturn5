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

#ifndef BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP
#define BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <utility>

#if defined(BOOST_MSVC)  
# pragma warning(push)  
# pragma warning(disable:4512)    // Assignment operator could not be generated.  
#endif 

namespace boost
{ 
    namespace ptr_container_detail
    {
        template< class F, class S >
        struct ref_pair
        {
            typedef F first_type;
            typedef S second_type;

            const F& first;
            S        second;

            template< class F2, class S2 >
            ref_pair( const std::pair<F2,S2>& p )
            : first(p.first), second(static_cast<S>(p.second))
            { }

            template< class RP >
            ref_pair( const RP* rp )
            : first(rp->first), second(rp->second)
            { }

            const ref_pair* operator->() const
            {
                return this;
            }

            friend inline bool operator==( ref_pair l, ref_pair r )
            {
                return l.first == r.first && 
                       boost::equal_pointees( l.second, r.second );
            }

            friend inline bool operator!=( ref_pair l, ref_pair r )
            {
                return !( l == r );
            }

            friend inline bool operator<( ref_pair l, ref_pair r )
            {
                if( l.first == r.first )
                    return boost::less_pointees( l.second, r.second );
                else 
                    return l.first < r.first;
            }

            friend inline bool operator>( ref_pair l, ref_pair r )
            {
                return r < l;
            }

            friend inline bool operator<=( ref_pair l, ref_pair r )
            {
                return !(r < l);
            }

            friend inline bool operator>=( ref_pair l, ref_pair r )
            {
                return !(l < r);
            }

        };
    }
    
    template< 
              class I, // base iterator 
              class F, // first type, key type
              class S  // second type, mapped type
            > 
    class ptr_map_iterator : 
        public boost::iterator_adaptor< ptr_map_iterator<I,F,S>, I, 
                                        ptr_container_detail::ref_pair<F,S>, 
                                        use_default, 
                                        ptr_container_detail::ref_pair<F,S> >
    {
        typedef boost::iterator_adaptor< ptr_map_iterator<I,F,S>, I, 
                                         ptr_container_detail::ref_pair<F,S>,
                                         use_default, 
                                         ptr_container_detail::ref_pair<F,S> > 
            base_type;


    public:
        ptr_map_iterator() : base_type()                                 
        { }
        
        explicit ptr_map_iterator( const I& i ) : base_type(i)
        { }

        template< class I2, class F2, class S2 >
            ptr_map_iterator( const ptr_map_iterator<I2,F2,S2>& r ) 
         : base_type(r.base())
        { }
        
   }; // class 'ptr_map_iterator'

}

#if defined(BOOST_MSVC)  
# pragma warning(pop)  
#endif 

#endif

/* map_iterator.hpp
Mg1fOC2eHt55HhxsjeztkZLOHLUNkorKcbTU93oCKApbTZivf+ka+LbB64dbx91DthQlBOfF5HWaj8uQIV06raH8akbtc5zU5XXhAyjsB7V12OyqolCNSdmr6inDI19qO2HL7H2utlnrSkeJchXTMbPKhZjOnkHCVUblheG39ckOJ7k0706w87L1j6ifnU7Y/6S9ljyQddtalNfmg+Cn9jlOIp3TTw72Yo0281ungD0INtTHurVO5i8H+lY/bt7+vD5xe7ROzwveD51Rkn1PxJvpMwzzZ9l3Zp6Zlzm/JfXZWSJNec7oHIGzmLxcxjlP69n0Okw6zoU+znggXQ5R9ovyZPnohyLs8pDn7TUNBdb+yEtMvHRuxjyFcf9oxnkyT33HEPhmv2L87+DfG+wqsCN/iUerIuxmMHUK518FdrvBSgR2l8H2F9jdBjtYYPca7DCBPQhW7SIXXoQ9Bjb1FDBB9yTYZIcWF2V+2qQ3TNA9Z7CFPtYt357/i5WzW2P93nfyxL3KoY8n/NX38qL96guFjnofnJy0SQ3PA0q5WdXT3NFp2Yh9Q5yYRkIj/7l3TFn27GiU7w3P7Z2VryERe5JCu80rJB1NyZQmFmX4OC86N6i3P4qw/Qfo9BHBYLJP1ukH4pFk0t+qJv1YZ1CA++Kcte6mr0kT57EGRes8OGIsCHF6L+bulPUHCT+IwsTZmg2gyUxIuAaCHxsZujCd0OiGdd7ECs94K7+XnUfm+Z9NTVz5zn1Yh95BXYtLK6vMppvs80WbC37gJ2b5UVuIssWtofQfFL3T63/1rdE+q5b+8e/Q2m8oxb9Dm023XdfpGrdzrWh56C/y4QYOimj9OhkieZd+tAcI2tmlCXPE2uzGEv120KBwzJd5LmxLcDnPEs1YRHZ8+3RcM38S+FHpNh82SPouwcJVju3XmIGM79mI9iSuFa5jm3Kb/aIdzeb9cxFvx3Q7M2CkWERsbxdvhuQPEuubcm2zs/tUE5NmzxP5jgzTD66ZStdnLLg87yJ8rdizN7pYQp+MN/Kr8eAwTTruToSFgi/D03tYZJ1TwXPG6fEVYXK9WDeh0B+TrPCo64m9IHb/tO4bn2KHm0xCng0mXI9ZOCzeJt67nhrJj8/ytOxNAzd7dXW15MAuzHO5udOts/sGywZZbRkSijRmQFOblUZUvpkmPLyDPuT3b8DNXTG+syb9Sbvs4dsJFJ32ssou9+eE8SuNfNr3/cux3my7bpJYtIvNA5Nhdv1lRvLNwEg2aNey0qL5ifKZxcFcdliWRDxNIAEirRroLCIzpx3xZaHWVeJIkKjLoiAMS44i6+B++OAC8fQbaot1uJbcNNaksWC/d3p/RYBhhfSzd2YcHeXTGoU3Nrd2pMcCYT3aonCjdbPfmkwFNJTQv2dF3Ak9KOYuZD++GHMtHyTfSAlvcA8vXEm0+/UL7dYNveJosX6t0Da2mziR3djLpC0TE6k3JsWdMPOhbfZ9FdNIw380DZ+dUULp+3gGhfcQ1zY2C323j0nHzN0sahH7CPbLCDP3nsgzQRnh5q4TkfZBQZ6tqWQHQxL/rmdkTNwhP7e0fGQBvcKe8zuOePoSCQxvI95lu5iTlncRLPVfQi9MMvebVJ2GT1rYjmXKSrvdv8jDSvsEwsycm9Yn2pUQMrFT71CnUOgGwmA0/qhei2dOQtdBvrPJBIVWPuEjmGHYyYOyzklE72pEYcL9iMq4Rsu0sfOme0q9d4YONwHmZWt/dCZpzrVptGb6MRo9Fd3WdV769e42qSPPz+xHEJmLg3zzKOT8giCtmRQWlyrqqxdm5NEg8+icxtRZyupFAQ2BRp+YcyZh+MXp8BFCIYmxbhg=
*/