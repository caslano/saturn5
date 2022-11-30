//  Copyright (c) 2010-2011 David Bellot
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** \mainpage BOOST uBLAS: a Linear Algebra Library
 *
 * This is the API Reference Documentation. 
 *
 * \section main_classes Main classes
 * 
 * \subsection listvector Vectors
 * - \link #boost::numeric::ublas::vector                    vector \endlink
 * - \link #boost::numeric::ublas::bounded_vector            bounded_vector \endlink
 * - \link #boost::numeric::ublas::zero_vector                zero_vector \endlink
 * - \link #boost::numeric::ublas::unit_vector                unit_vector \endlink
 * - \link #boost::numeric::ublas::scalar_vector            scalar_vector \endlink
 * - \link #boost::numeric::ublas::c_vector                c_vector \endlink
 * - \link #boost::numeric::ublas::vector_slice                vector_slice \endlink
 * - \link #boost::numeric::ublas::vector_range                vector_range \endlink
 * - \link #boost::numeric::ublas::vector_indirect            vector_indirect \endlink
 * - \link #boost::numeric::ublas::mapped_vector            mapped_vector \endlink
 * - \link #boost::numeric::ublas::compressed_vector            compressed_vector \endlink
 * - \link #boost::numeric::ublas::coordinate_vector            coordinate_vector \endlink
 * - \link #boost::numeric::ublas::matrix_row                matrix_row \endlink
 * - \link #boost::numeric::ublas::matrix_column            matrix_column \endlink
 *
 * \subsection listmatrix Matrices
 * - \link #boost::numeric::ublas::matrix                    matrix \endlink
 * - \link #boost::numeric::ublas::banded_matrix            banded_matrix \endlink
 * - \link #boost::numeric::ublas::diagonal_matrix            diagonal_matrix \endlink
 * - \link #boost::numeric::ublas::banded_adaptor            banded_adaptor \endlink
 * - \link #boost::numeric::ublas::diagonal_adaptor            diagonal_adaptor \endlink
 * - \link #boost::numeric::ublas::hermitian_matrix            hermitian_matrix \endlink
 * - \link #boost::numeric::ublas::hermitian_adaptor            hermitian_adaptor \endlink
 * - \link #boost::numeric::ublas::symmetric_matrix            symmetric_matrix \endlink
 * - \link #boost::numeric::ublas::symmetric_adaptor            symmetric_adaptor \endlink
 * - \link #boost::numeric::ublas::triangular_matrix            triangular_matrix \endlink
 * - \link #boost::numeric::ublas::triangular_adaptor            triangular_adaptor \endlink
 * - \link #boost::numeric::ublas::vector_of_vector            vector_of_vector \endlink
 * - \link #boost::numeric::ublas::bounded_matrix            bounded_matrix \endlink
 * - \link #boost::numeric::ublas::zero_matrix                 zero_matrix  \endlink
 * - \link #boost::numeric::ublas::identity_matrix            identity_matrix \endlink
 * - \link #boost::numeric::ublas::scalar_matrix             scalar_matrix  \endlink
 * - \link #boost::numeric::ublas::c_matrix                c_matrix \endlink
 * - \link #boost::numeric::ublas::matrix_vector_range        matrix_vector_range \endlink
 * - \link #boost::numeric::ublas::matrix_vector_slice        matrix_vector_slice \endlink
 * - \link #boost::numeric::ublas::matrix_vector_indirect        matrix_vector_indirect \endlink
 * - \link #boost::numeric::ublas::matrix_range                matrix_range \endlink
 * - \link #boost::numeric::ublas::matrix_slice                matrix_slice \endlink
 * - \link #boost::numeric::ublas::matrix_indirect            matrix_indirect \endlink
 * - \link #boost::numeric::ublas::mapped_matrix            mapped_matrix \endlink
 * - \link #boost::numeric::ublas::mapped_vector_of_mapped_vector    mapped_vector_of_mapped_vector \endlink
 * - \link #boost::numeric::ublas::compressed_matrix            compressed_matrix \endlink
 * - \link #boost::numeric::ublas::coordinate_matrix            coordinate_matrix \endlink
 * - \link #boost::numeric::ublas::generalized_vector_of_vector    generalized_vector_of_vector \endlink
 */

/* doxydoc.hpp
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
*/