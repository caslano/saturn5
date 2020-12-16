//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_ROPE_TRAITS_HPP
#define BOOST_STRING_STD_ROPE_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <rope>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  SGI's std::rope<> traits  -----------------------------------------------//

    
    // native replace trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_native_replace< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // stable iterators trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_stable_iterators< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // const time insert trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_const_time_insert< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // const time erase trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_const_time_erase< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };


    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_ROPE_TRAITS_HPP

/* rope_traits.hpp
sslmB8d5lrlKgJA2sK/oQryeaMomt9eC/oNcb1v9tBKzg7oZVGdXIm3qBVFjzfJWBqFA+hsS/anX2Wrpv1IODxmk9LVtlom6PYCFTIRw4BQtvXDXYSap/WRdCQ8HnvXI0EiyK1qretBQukKITXsBisPBIDW5BG1MSI3/D6HXkbZoYu7lMO1NEmo51IrI3xGO+04kShPE2jfB2lQHBIrNJJDsbk1zyFjD1oJJCvUqB7+ACusLaQ9PesMGKOMCdH3EMJJdG7RKwPBIay14haYwVLIzevxGcT0qzRk0ItZIKzCnk3jXDuKoQhsqeHmyJhUZ7IMlUUeBkTUJuBhN2NWiHVipQtR7YPip2xqdpDz7QuYLYbMF4g+brUJ5dyOQUDvTlJNWrITGv2RsFarUmwg/8DDN3VYeIBvYuXQlQmUCiYUt6t8wVnqGbsrNTl11JQ0erO5my4BOtUCQe9DGhyoIJHdb5h9w3DGDRnhqbpY23c2oq14nj4LRPwdT1N1iqA8mKXYJFRTadMIJqF5X4DTBAEzlzEHCCT0dqocRPcFP0G0IrRAtdjdJG+TSJIzaAq4i9u81ezH/AQ8L+WBE1Emh0/Imqmh2EH5RSMx8iSKilyHucqgmlEhtQls3ggKraMjRCVhRWF0fR/uQF4lNQIXAT4nz4vlnUg9BdWDcpvYxbahJgotKdZJza+rEZGMDT51l5iqaRcucjRAG3+uVc8wy1TnqQ776d/tphq1+dn6ofkagelhUHy1O4cTGrXUvJ2np4bL/s/Pzjv+O/47/jv/+6norf5vx599Irbd+/bVAar31/tR667mbTqX11v30QeeC8C5eO6XFrhlLnIKM7NSHEDZ8LTuBb/0gWZKz/tbzuBZuSk96ZkkZrpOmXD5kL65lZ+c1JnGdPHTEZYtxLf/uffvej+u0b83Z/0TrnSX0udQxhNOOe92F2zXOZ3+Ihdsl7sLtk9UoUy3yESFZuG34CS/cfv3vWbj9q+vhn/8684bX3vKAxhHW/7iGrP/N5fW/g77U+h9xBet/xBGs/zEvKvOZFZUB5kRlITOisoj5UDmG2VB53Rj3C65/C7/XHk7jtyIO/I4g327UEfk27jmCfEefcjT5ngVKtHyv+fPgD2n53vWTax5z5Xsj9mmTfC94bc63Sb63v2vIxSTfexZnP0Ty/eHG2nEk35Gdz16h5ctcGxL3yPcX3x8g3z/deJh8N/zobZfvIev1Uf7ygF5Kffhrej3v44uj8RtLzdeFP5UtvvPviCRbI7XJ8ptPk4X7qnj++bGJOIrYyXzTlxHCV/PlGxshddCpz+aV+wG1Nr3hw7aoWRNkwdTCyj3qI+M0tMHdFCTH43oBriW4TsU1iOs0XE/FdTqup+D6TlyLcb3QKcnWK/f1H1tM3w/6zg34PMas62r7xxTcafHH1ourIzfn4IMofhw4/P03cAR/waf6UUDbJK7wJVtU/t2yCl/5hqzCV74pq/CVB+uqCFTCyZq668aurc3UqEDqGrpqpq6aVVdlqDk+DcinS7N16aC6qhw1x69L/bp0sC7NravKU3PydWm+Lj1Blw6pqypQcwK6NKBLh+rSYXVVw9WcQl1aqEtH6NIT66pOUnOKdGmRLh2pS0fVVY1Wc8bo0jG6dKwuPbmuatzWroz/SpIvLZKNE1VFsnGiaiRd/XVVo+ouGe1+F76Md1DwxoloasHcehtXzP+9v5R/7vnyIf758n2ufyavBv9MHg3+mXwZ/DO5Mvhn8mTwz+TI4J/Jj8E/kxuDfy4+Zv88/8vHvH/jjC8fdf9GcXr/Rgnv3yhWFy2W/Rslh+/fKD3S/o2F/T7s31h8pP0bM1B0hP0bi/9J+zc=
*/