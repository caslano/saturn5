/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SIZE_TYPE_OF_HPP_JOFA_080911
#define BOOST_ICL_TYPE_TRAITS_SIZE_TYPE_OF_HPP_JOFA_080911

#include <boost/mpl/has_xxx.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>

namespace boost{ namespace icl
{

    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(size_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_size_type 
      : mpl::bool_<detail::has_size_type<Type>::value>
    {};

    //--------------------------------------------------------------------------
    template <class Type, bool has_size, bool has_diff, bool has_rep> 
    struct get_size_type;

    template <class Type> 
    struct get_size_type<Type, false, false, false>
    { 
        typedef std::size_t type; 
    };

    template <class Type, bool has_diff, bool has_rep> 
    struct get_size_type<Type, true, has_diff, has_rep>
    { 
        typedef typename Type::size_type type; 
    };

    template <class Type, bool has_rep> 
    struct get_size_type<Type, false, true, has_rep>
    { 
        typedef typename Type::difference_type type; 
    };

    template <class Type> 
    struct get_size_type<Type, false, false, true>
    { 
        typedef Type type; 
    };

    //--------------------------------------------------------------------------
    template<class Type> 
    struct size_type_of
    { 
        typedef typename 
            get_size_type< Type
                         , has_size_type<Type>::value
                         , has_difference_type<Type>::value
                         , has_rep_type<Type>::value  
                         >::type type;
    };

}} // namespace boost icl

#endif



/* size_type_of.hpp
p5HVKfw/SvJVLHK7hf8rgAx7dLFYzWXzUXP78Odu476pE/Ngh/6f6DRODViUSte+ZPbm1xj22BuPmX/NZPLF/OES+VBLZp79o+1Aj+Fi1yKS3uytsFeuHUifoXIjzKHjPV3ln3FHoslK4FO+LRxFd7n1K73j6PRBpuNuZNG3Siz7un5ZHH/Hky3H85LkHN4l46PT6WrtifV0ZOug1mKWx3/O25CxTDz35NJd3G7KkcNkPmdMZI1YyJdqteWPeDbRdymKwquh/HCR9VZmGNdbXIwbzJ8X06PbGLlr7bPp3ojsQowvERMyT+Cb/FBPyFmlPR/rzNlhv57r2s/1aid7rvSXDicmqwfaCWPFxfVSP6bXDJKfifxVYy8XyF00xa46vjb+UBVb2fJqEV31n1QsZ/W9HWOPRBnXlh36G9njI/uIaaFxxn8h9wvI7GF837H2bEu5jRniNIm/18ujtxLlkXqzU/8h8k/W9722gm+HGnNRhf0XJWdz+ZXfPxnBb+wc1ZEd+LM3f1arqXQtE5PSWH4zPpJfnhLjxX3IJC9O7p1mjcli/Bt97nb9DdevlRNV1mzChrvCPayIfGMP9RTPLLnKN/P1L6mXZxX66vhU/9t4EAfp2L0b/2jvo8/LyJgil8XwiUyxs79GT+dPTB5nzYH2nbgNM+eGEfJzhD52va5dIA/PJnO8NjXc89gTw6eL1OhE5+2cX07eVZPVfDo1pvfN9fSYYE9OlGfseon+ZfrTcG+qtZLVXv13jBLL3vRLkLPk5RSqFwX0Zuu/2nOdR9fKWcdH9fU3PnKgfrIf4sOe5rxVxLYwz/modOuxcZLj+ahyrc9Qtdbx1lZq0mC5KEeKrTcPszANseiZL1+n8ouxS9LQ0xzcjB14FJe69maIO326mvP1NHtTrMrz6MV3CQ38LZ5n6l/TSW53lIsD7E86fZynXy25UN+WaDKmm+f4jBp1Y5Br1eyOJz9JfnQgP4ttE+VSJnsi1QHymxh/Qp06NIVO5DdP5E/tvDzr0qdXIRnheSY8U2iPa632tOETOr+IdfgjUjzy5WeGPBGvI+SP7WHv0flGcdlcJS6h5o1XJ+rka4V6PYx9o/ki2708XRzL5GuSeiUnFmrX81s7lPWTr9Y7MFyORfFBuIe2F2ssw2Vi0SLX/TmDDWw5me7p6np1W/rx0yB++btIjpE/hu57a/hOnbwtXT71Z7txp/QN//8DHdL4jZ8W81k3e6+WfiUpfGDMz/yWVyzf8brrKzI9HySz3fWIYWzDm0PEXO4WFVlbXj1A35ax7qWl7qWp9lRHNoylK3azrb+2DXtvxCfWa21vnFPDX2xdVMafZBw/Tj0Jz3HqZYP2RHHYYF6U4wP9yODjTfH0Nvc2fc2t08O8pDx2TbCuMaX8NJ3cwwXqVyQfJaojCdp6NZS+o+RXZrx19PXnu0EjwbaYHDpXGlPFFv3zO8jNSXwijvsrxILspvr69qJnibFT6Kn/pUT25+izD7eRU+f6OfRvQp+x9Eq1Z4sdnzZYrrLniDHNivnGGtdlyw/rb+eDZ/AzPrHGPmv+Xkr/Ns6xnx57yZzSIOe687txjdGL/O+rrEePK2Ps4WF8gxp2/xWrtvczj7+fdlzB5qxieZpkvVS+qlfX27ierLbL36Ep7juOi/TvpOsMOpTU0kMcn+/qmMyrjdsir2L4PNP5tcavp8eaenpOV1PI+5D/Pw15Okie8fVFji+Reyns7JonlqXh38e3r2P5pkxeV6sLxvbR172ETeLSqpN4WuvfFH6zh/6T414v31qOlcP6S+Idj2JrLvvL1EN+LTRmhDU6yd0YY3+wl5Nr7X/XsvPpNkbOFciFGD631ts=
*/