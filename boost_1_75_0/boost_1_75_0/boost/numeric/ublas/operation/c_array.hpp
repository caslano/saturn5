/**
 * -*- c++ -*-
 *
 * \file c_array.hpp
 *
 * \brief provides specializations of matrix and vector operations for c arrays and c matrices.
 *
 * Copyright (c) 2009, Gunter Winkler
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Gunter Winkler (guwi17 at gmx dot de)
 */

#ifndef BOOST_NUMERIC_UBLAS_OPERATION_C_ARRAY_HPP
#define BOOST_NUMERIC_UBLAS_OPERATION_C_ARRAY_HPP

#include <boost/numeric/ublas/traits/c_array.hpp>

namespace boost { namespace numeric { namespace ublas {

    namespace detail {

    
    
    } // namespace boost::numeric::ublas::detail


    template <typename T>
    BOOST_UBLAS_INLINE
    typename ExprT::const_iterator begin(vector_expression<ExprT> const& e)
    {
        return detail::begin_impl<typename ExprT::type_category>::apply(e());
    }


}}} // Namespace boost::numeric::ublas

#endif

/* c_array.hpp
v1PKhUj46vjbkrKpo37rB42G9GtD+Q7YOEqfWS1duGTZeVLR0Gtg3/lXkwTW+97krJ33YlbFev/0q9FwVnY++dwXv00gZsVF8NHeiqPh3Swc3X5nSHbPWpqzXunYo+4i0sGrd5d20vvkUOu90nfBLEWaVrg6sFI9RUZQcIGnf2g6/XaoQhalmPtgN8t4zPaUymW5qTjak2Tp8k9rPH0GeHTuUaU9jl6hKYGpXqEALT9YFVrpmb5ZX2zLXGdGf9Yp2d0CSjRNW3wbIWO9v5NETFXhaCrt2Bn1fl+8mWLzawULSwlVgvGQj5B5yexknor3wVGUCEoa5Z1JHg41+26WPKs3+9jnso2Jg2mfKHgGdjAxQAEd7OC6qIQJrej9L66NSCm/MLDTKVCCVHwYh/8Fp18GxZf7zVFwq+1eM232xfxZuzWpbrGpuBSecP4rUUoRu5I6XR+VllL7jNIonFWuO6LsqqWnli51ctnPXlT8Fn5Of70etaBz0y/M30k6qv78csIb4P/o2Z/xVXUkiNlP3FbRSvvc7neigmd5wn5UjPaXKVDeapmlifBhWu3Y/UCR0JGnU16eHi68v30v7nEkSDfvQCz/5U1ZFZ36yrR9/gvBRlsgMotNc5QVv/ugZORkY/xT8GzIVCLukrCIcZoLm/kX2aFZQkhiaOd+cyUpowd2xWrzOKb+yOLLcf5gqjbIdliUPcBVdjoMdHo5
*/