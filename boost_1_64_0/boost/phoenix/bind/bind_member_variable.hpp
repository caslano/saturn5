/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2014      John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_MEMBER_VARIABLE_HPP
#define PHOENIX_BIND_BIND_MEMBER_VARIABLE_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/phoenix/bind/detail/member_variable.hpp>

namespace boost { namespace phoenix
{
    template <typename RT, typename ClassT, typename ClassA>
    inline
    typename boost::lazy_disable_if<
      boost::is_member_function_pointer<RT (ClassT::*)>,
        typename detail::expression::function_eval<
            detail::member_variable<RT, RT ClassT::*>
          , ClassA >//::type
      >::type const
    bind(RT ClassT::*mp, ClassA const& obj)
    {
        typedef detail::member_variable<RT, RT ClassT::*> mp_type;
        return
            detail::expression::function_eval<mp_type, ClassA>
                ::make(mp_type(mp), obj);
    }

    template <typename RT, typename ClassT>
    inline
    typename boost::lazy_disable_if<
      boost::is_member_function_pointer<RT (ClassT::*)>,
        typename detail::expression::function_eval<
            detail::member_variable<RT, RT ClassT::*>
          , ClassT >//::type
        >::type const
    bind(RT ClassT::*mp, ClassT& obj)
    {
        typedef detail::member_variable<RT, RT ClassT::*> mp_type;
        return
            detail::expression::function_eval<
                mp_type
              , ClassT
            >::make(mp_type(mp), obj);
    }

}}

#endif

/* bind_member_variable.hpp
6FHU7eqjYXqw082YxJttzBQqnkIjmXKse4uDoXJIjPdWwoSOUlne1W8PYVAglqXrHYbuzLiM+fu7DYaIzUEo6HPRyGxTHdeYIK7BCCQZM/ckfIU2496F918WS+feYo78oElDAx+0kW5ImPssH3IwpPiavu7jDp28GTZQHu/8pEOH/QIvL0jCrj2oFp4jP+fgW0PUh8jP/AtED7s18Hz9RQejVN9Xab6Hc/FLhCFXEKkDx75MtJD7CWMuESbsLsKY5V8hTNhdBHYO6T5hyF3FlOHQV/V3dsWjs3SDGbvVwgRHXgQytvTXDWYMj13OTJnuzTIcPmswsKRY/uK36HvoOJrb/2ffIYxzrG3umX2X6JHH9cxn6fcsHJ28sSyrfxBB12d/VNZbf2hhUOeoaWELr/kx0SNdSIDT9foTiXO7MMu87ecWjgAs86nzEXQSWvPI/powjjtQj67f3yr6QtxBxLruTkpDekkDi9GJ4kVNHw5cf6He7rpk7G8ag4NySafz6t9Z/ujTLXok2tBPP8U574YwmDo4ht6uSDp5+TGf2TBO9RNzpr323c6ZdqNRb9RrhYWeaYOjOtM2/KqSX7acTDe8arFeq8TfM8KvpF7g3n799rXZBvihDEljQ53E7wpzx5BtYVEig12/xMFSa0dhj95NYjE/hfkavU9eQdjIcKesz93LFM51URB7Dfdy6JjMZfoLyx067aNovTt/pUNX1YZMJA/vPg7GNz2ZvmYl0W21MmVdd1+iR6oV87m0ysHR6sm8E07vlON0P+SfvdWh0brrKq3b2ZDvPGYn2hCR8dxedsHBsb+/yWvAxTh+sG+x7hSQpCKPnUIWf3FBDuNSjseLuwC+v3w/HIkVTmD2Rt0HQL/HwGYwX70QgaHHwbW8xxz/eqq7juZxk0OnEmEkZ1k+FMYQH8accjEkicQk52wM8oGFTPYGYT7h8BluIcxEy9dsU6YvRWI4Nm/ixgTo1iseqDkTKqeNLT04V7Q4dkgcPrhPZhLIspzetcjx0fK9p29Qd4CMP9svbB/dCetmGcfG6fqlwdEFiuCRhmF6JrIt7g6tmNP5gjg1NjjU8s1zjm35J0031+IIwb7Ds9MGMzW9D4sYcSf19Lvs8b1SK+F9jFpmweP7xJA/vvcQvwuSXyOZaxTT5XQ1m0Q9bN9soskG3kZPojSXZJp0MekVso1yvVRL+sPpMKaCzcGNuu2bgyt1QfIenefKd1t55nPlQq2CuSUikdn/OonfssAu8PryPG7dejf6Lq/dCRvnrmVEj75iaOaPrSsIF3vVj+2Yu64hbPiqobGZVq8iDF8zFLrF+U7dj3Cx1xE535H7EzZ8DZL6Hv669+aCkeAqTX/8Hx06zKzRfR0eX+906cEGq/EZD/jT03XqHstzjW4f+mOIFvQrkX79XzQG/UO5uovYiLt+H9BKFCRDf38df1dDFsdkDHjhCCww+Cf3Pgs3nDle+e8COvzv/OtGRs6L/J1i4mrDj+X8GzB054XutHA8khGbhlZg2oShtQ1Ny1v+gzs3qeJw/L/3OnMXjeIm/t8vLjjzEs9dpk4+4mLo0pPmcQnyET03Yd+XM5j/uhhiIvNZOudg6L6csVOZh5o9faJM/wpDp5gJhND0w6DLOQQNaOX/aue+GcxRZMNlOBJ1Hw0tLnkc+0sYg5YzOnD4D6H5EP2b2srhD6uK3shodaDVxj/+JrccLQzC6MJqIJ7EUDk16R8dGPyHXJki8VyGd0faByznPZ05nRSdTFHWzRXROMPnluh5H8XxN8mMPKuce1p0pNnWdfo7n09AIxslZ/r5n6x7YCbvb/+F08iAUXSPJ2HiAj4/bCeMttU8ekMPTdU=
*/