/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ON_ABSORBTION_HPP_JOFA_100915
#define BOOST_ICL_TYPE_TRAITS_ON_ABSORBTION_HPP_JOFA_100915

namespace boost{ namespace icl
{

template<class Type, class Combiner, bool absorbs_identities>
struct on_absorbtion;

template<class Type, class Combiner>
struct on_absorbtion<Type, Combiner, false>
{
    typedef on_absorbtion type;
    typedef typename Type::codomain_type codomain_type;

    static bool is_absorbable(const codomain_type&){ return false; }
};

template<class Type, class Combiner>
struct on_absorbtion<Type, Combiner, true>
{
    typedef on_absorbtion type;
    typedef typename Type::codomain_type codomain_type;
    typedef typename Type::codomain_combine codomain_combine;

    static bool is_absorbable(const codomain_type& co_value)
    {
        return co_value == Combiner::identity_element();
    }
};

}} // namespace boost icl

#endif



/* on_absorbtion.hpp
FbE3vnXtgMWtGXVSzr5jhbxE7I3zOf6swU6QmITZmEbCgH/nrJ/eYB0RYNjjKukhYa5QK++4EORgp4Oaggr/Gpai/xsz4B4vD3p/TpYPhkMTmHj+YRX2rM6FolDNM0fEv9eQpHrbBr9FbsezGeS80aJwKyrOB/B3gzN4bBj8ZArnny4tgui93bl9LRBSpKT1gPEsLEuUkULq4c4SHvdV2diM1EMMlZkccIuzMzYERNQVuW2SbjnJqFT5jA9KowdAc0VDjiYosOIlPkCc8VLVQ6jFj8+uDy2reCAiyGRKtcUA/ogNIWPhNTDC3HvXIiyiBI+/cNF71H6p+CnUhObQOKav7WAgp4ByHhC8wr3gw/+W1EMgJaQzOfV9Neaal/34x0Kv6k7p9AuOYnO6T/9TJ/X8VEczpFneRjCad0uYaAnCWKjogvcGW55w7SpSO9MQnp1E2BH8InCQia8OtwfuL+2zc1rISxIiqy9Xs/DBJP4W0n32H04BKJMXSKssofx1FkVsdbLNAzhD0x7puJJaG7vEB1qXxEERsI1IJ49dIFkbPS7l05CGrAqEmQ==
*/