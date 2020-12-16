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
toPfvcXZZ81Uk8kwfOyKp/XayLFMzUcm3cxi0NVo9sZo2rnMNyWxXA15cjSrpv1hoV0AX3eRvfXtpeOSAQDwmuTSfh3XgKHBYvmT78e15r2hST6RQF34yZxmVFCvayxqT/kHv/mbmtHPlmnkU5e/PXql1+7Uw6Mxyhdbtk/FCW/e0TXhccIjdVM3dcnzqme7wnLJ2R5qLI5LWNSXZuXXUVc0yKr4PtwUjBD6gpbgh/f5t/7B1wnBk9uec6VvFfxo8Zhhw7T+wfgMoRV8VmFnBHfHPDBrlNld8p6uQSjv6KsPIfsRQjgAgH/+SpZk6dw1S+1OWNT/K4vVz0clxeYHtsRN/sjjKSlzWltZDV6/qzmjfra41+LjfH7kQ37mTkF70xr3hD2hLmeeW5jw7x/4LF7Q8v66Am/FEZd4LdmP3hR4pOVNDRX5hS+sDrh8KOjK8xd5AACsWbTHXwb/Il/4VVDCFk1pwb6Q3KOnsawA0U2TU6+0Imrg2KFZKbGkzg+uN/bFGDBK3BzdqvMR+/Zbt2qOofvCySaGirJFu3zjQzBo6Rekf5oyEBBrvIbRYMvEjIQqoB+wFyH0M+E8rEutmzesDTloXzSTHfXkycXb9nOqsDOl3OnwlC/fdjvneKebB6/S3Z/fB5xn+YzEnI6H7+q8t5qMU29zyO3P4ks4TjbO8hY/bvLnMAEA+EueVzPSS9PLOHt4l51eJKv3U1v+TOgFV3olH3/e9f7gBRNedTIHLbMp0rhq0O8sleSXpY3YoDPGIjrNfEpMpdUd8BJ8vE9sPKXHe27lbJogXvBEXhiDr5BaPxhzjmkiN9f1G09Y8jvg5+v7x83wj4H0pc4YTYPJUDFPaThJZOWkJOuZtkvvetzCM0RE3DON+QoOKNo+XFMXI6mwrzCuw0Lk1NLxeMbnGVc5b3fx6/qSuMiP9Uf/+0uSb9zhnwU55KrultAaTe8WnefLdT7tONTv5X9+VYQ9TUXlaXOIoMr+sLdaUmlf0+en033M0w2ltbteN2m8NHK3PoN9f1zf+fbRsPWBptHz3gHZl6YX7fttnfjb+5l5EfjXQBlc5xAx21lTZJRjc6I1djklScb8S6FWvo5d41G7GWYY09RkXwTy5N+y33P68zwNLdW5L4xX1M5GGzJn7niY9JnwpOpHTtXFnQMlajlb6h9ZHHq4SVFxUZ9VP5uPL4N/2yl+vNr4DiQL79jwO6O1zzcPAfxK/EFoPjIJfhXfGPwlj5+zAQCs5V5Cz+suk531Eot8vu3b/1f26KkL8WgVAJAAAGGQ88LXsGmM1yfdVz9P8oMBROO4V5wdvIvbZb41ZZuGt3X9j1/zUKowHewZussJp3ytPaUmL9BTPpOyub4KzvCJ8gabfjzQJmbxmClm0XodzcMJMm88Af5i/IbPawKorLrGPk4ustjz4/hO6UwvhyPMVj7tbig0ugsnhs4PZ/CHPqnf1LOLSQc7E+ISytNkMSXSUsWwIxXKLt7TbsMdNSkGTlRXsy76ElVQBldKybFv49MCAMnS5TRt9+OL1S/Yr8imvqb6wS9WUuayLCtwNWZXUUyaQIe4vapIGBuMCXEatlfv3OVnCJp9rAhR1bMbutMkbq3KZKJTtt2fTnnIIyL/EGzwbaTTYNGe7dUlW9RHjPOE7HG7ci0AgL/k8ycaTxZNYfZHPn1/wYf0zbl45mdN8/WKlpQ3GO19L5NV8bhsv21sUuSr2ZeEJbEfJTXufD4+qyt20V6I8wRLmcM5CrVR95hghTOb3LN49gy951q1yAdzNsyTIMs4n7TI59t3RgIAVPCXuPfLXw9GgtM1GIReoy0qpHx2rEvb3cL8+Me3JPGUq0r3SCM=
*/