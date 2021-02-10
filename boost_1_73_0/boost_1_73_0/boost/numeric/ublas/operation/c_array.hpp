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
Z4/Q1XuL8NVmsG+wqAO12P8BUEsDBAoAAAAIAC1nSlKE/zLL7QYAAKIRAAAiAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NzkuY1VUBQABtkgkYK1XbXMTNxD+7l+xNUPHDkcc+FRiYGoSJ7i4tsd2SpnC3Mh3Op/KWbpKupi08N+7K+n8QkjcznAMuZO0u8++a905+n5PA47g4BO7/zE++HYcE63+5In9NnUcfwb/D7ne4/sQSAe2LJ/jNhxm+QwtxxIHlOf0HceHgN6TbvSnQ5zvY/rEHWQjzjNV3mixzC20ztrw5Nmzn+AxPD15ehLBOZOCFzCzXC64XkbwPHU7P+fs06djw19GwC2w4jiImufCgFGZXTPNAb8LkXBpeArMQMpNosUCF0KCzTlkouBwNp68G4wuI1jnIslJyI2qwOSqKlLI2TUHzRMurr2MkmkLKkN2FJ4KY1FgZYWSx4jNwXK9MiSD4FlhFLBrJgq2QCBmIbe2NKedTlLpArXvpCoxnaQ2/zi3q40l71CJFbsBVVqwCirDIyDKCFYqFRm90SG4WVaLQpg82mqDUDLtKA2GFwXJQj7BjVebwyy4JyIyKFFjYelllDQEtc7Vao8Q/UhSskpLBEI/IFGq0M0RVDLl2hE7
*/