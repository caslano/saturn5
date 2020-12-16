//  Boost string_algo library find_iterator.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_ITERATOR_DETAIL_HPP
#define BOOST_STRING_FIND_ITERATOR_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/function.hpp>

namespace boost {
    namespace algorithm { 
        namespace detail {

//  find_iterator base -----------------------------------------------//

            // Find iterator base
            template<typename IteratorT>
            class find_iterator_base
            {
            protected:
                // typedefs
                typedef IteratorT input_iterator_type;
                typedef iterator_range<IteratorT> match_type;
                typedef function2<
                    match_type, 
                    input_iterator_type, 
                    input_iterator_type> finder_type;
                
            protected:
            // Protected construction/destruction

                // Default constructor
                find_iterator_base() {}
                // Copy construction
                find_iterator_base( const find_iterator_base& Other ) :
                    m_Finder(Other.m_Finder) {}
                
                // Constructor
                template<typename FinderT>
                find_iterator_base( FinderT Finder, int ) :
                    m_Finder(Finder) {}

                // Destructor
                ~find_iterator_base() {}

                // Find operation
                match_type do_find( 
                    input_iterator_type Begin,
                    input_iterator_type End ) const
                {
                    if (!m_Finder.empty())
                    {
                        return m_Finder(Begin,End);
                    }
                    else
                    {
                        return match_type(End,End);
                    }
                }

                // Check
                bool is_null() const
                {
                    return m_Finder.empty();
                }

            private:
                // Finder
                finder_type m_Finder;
            };

       } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_FIND_ITERATOR_DETAIL_HPP

/* find_iterator.hpp
IuhRI6J8Pq/Gb9Xcrhfa6ZlcfmZ0+S8N4HpSiYOJhGGAUhM4UmpysdDhCtPhFjomAlGYDuJM0XRorLttwBoDrFgUvMyg1Pq+4YtL9D2Cd5lFJ6KFMzXIN7kC8k+525RPF2WEfdfplGcIb2VumNCHECFEgiKi85FTrAojr1nhxblWhUcRijHniPenNTkHEHGLLuoiISIrTMT1OiUVKaiX3n711bFtBD41jz5YFQ5mnkdXQtbqTSPQaCkxus20H2ZWc0/BZS50NWDUHy4RxH81cRlLkWjWqD5HUh/UG9nWUpMONGABRlHPSFQRhddfTOHAYHV3jnU9aWT03adroFAiMq0eXkulNt/DRSepbjA5oUnP57XJNNaSz5bZk0i/+K6BmGwAgjaALmz/MuUW0iTaArb45dL/wb9i3+hWpk1UlP+HrLCvBt945ejFMt9E1UoCU9R+5/bQEXjQIn9UBbCvOoz9v5QmTF08C+VhJDn8RoXzXZoAi+NJ+aQ+wfIpfBW3Jyj+OcR72QnafAcGQuWPNjDX/p8u1PTAGOBdP1sL4j0dNi0fCFHisPb0CyW/V197LxHDp6+Vkxhc8Wus84anBvG6+PzgsG8Lg9PInv5idtTQlmdX4tJWPAN6LG1FOYHhvigM1wsGsSriNPP21hhMSd0mS39Ms1h/vFTr97pevIBrGez3rZs6Tnmyq2eeVTZBn4mdJOLSmjtJXHqY34MIdhPT1wlixHh1ZcbaKhskQzufrMNusiyETOwbkY8kp9rgMd5WlWBTGx+Kj0E4tsrTxYb3l1ZAlkfd1RsUbQA8bCtrYf9hmh9LFLFeJVt2vllLcWtqfE31dJbdpOs5Q+pZO5Pq+St+GeKZrlY90d7Wi2Goa8a3XNXiOrs3eIXNWFtlj/WGKqkPL+zCihS6XTFMv9w1d9fMc2ZlxwS6jg2f95ZxRQGfwPAzXQAo2gocoaXZjdPfgZhfZSfxwwbWqh5/UAxcpY24eQ4gCuV9urLl/uQIbGEv7ZdgtZ804Th3x6NUSdMzc7IrAhe4cWTsCy2eAy8MZRN1I/aXRvz9DGrEh9CIJ6mC1LBJpzu0zB102zzZOKo/CRXSKPrYHHOT8MnPuDgBckVo7saZDvesi0KBi5AeqsheMX1H9orAGKuga6Wgi62CbKqhi54jZmnIj7tGyF/7ppVvhOSLt/LtUv9smq94T+KMs6wc4/T4n27maFDBpjnwm1FhX5/9wcxwvpsk32+sfPvV5U3zeWhL9q6P/FDfHx8T+QaNhWaQoBlqodmr2nXhFv0e1s4t/xf2f2BJ+TLNrjtP+wrJK9wB71N5YCfGXhjVGtvhJmQe3SLPgZwzbyF3N3mPKJQXGTzZuxwLXIgtbkxyzL+QRbW/xYi/4Gl878BrfKyu2l9nbq4vQatcghRqpJcBGBx+a3AI9JwD3GrbqdJABvBTk46n2TKRJ4olSvgyPmbZ6X1YZNjVxffFw8QuD2VCmEUox+Yx1hXXx3qCI8QIwl1R2wWmDUG3GD1sbHhHnzwj0p1dP7O/P5gXa81vHtm2PBhzuI3lzVpSvGtUuGGIsdodKu++O2mPJ7tq+srgcJvxccYHbuPtjBVGpdu51LkiqTo4YFcSHm1/27lUrDdCy0LV3avdc1cE4tG8te2hpCdVqf19f2GlmrwgHlWol2breocYTb6Vi9bYFwqcFrzsNmqsnWLYQOfWjVPJBV28ev0UWnRrVjSGqN1qqhuPuWfRw53/GxUeoyJjsce5GO/dJ5U7K6hpqiuP2D6gufwA+8H2A82+d+ZifdA5Woa4Ih0+QfLkQp6xB6J38e44x9wHmK37kvnJ2a+wC2IFk6ECPcltr2rbbrvYbHY=
*/