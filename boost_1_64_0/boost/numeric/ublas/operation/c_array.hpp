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
d3AH3wnXTFOq7aLT/uW74jr/LGc7pBA7jJ+TnHBrdLotJPnW6/SFrIiaKLQa7+xoi4qm8CJzSIkkG/xQCzZo0cvMvmfX/YDMkXo576e3kj4XyiXoyllacB2tGfHariIouoDAswMGSpA2lIHrGG5FARFNAn9WWt+7+OUOxH1fP/y3x9bvpntIdse/ltdplAxsiZiV3tWV1ReeFMkELvjr/fnYeeF8ICCPcRso3FfPkuG42edvPC/rsLxoF8stBcLUGeYtaIAxJpTu08XTiLzC8zipGq92yJjEwxkPpW4nps3FSV34MAAyo3Xg3KLnTPaMG535xrZx/5Sx+0WdcZDVdpy5y4g2jk9uohhPYaGr7wUBNljnHM04NkbTLR2J7edVcMSIpAfpzYL1Hem7uLF+EkvoikI/AYNB/ImOXL/l1itVy7VaMdjvytlucgxk0a6ufo8t8NrI/VyvQ9CI6mIwTIYJ5RMB+0hD4FzVKsjRPlm41MumQ8fmSuNnPJmnJnUI3zWqOTY4EYHGfYwLC4G3Sas7N8hU8BUKCcPmLDQlQ5w0iTWL7LlHRjUhlA==
*/