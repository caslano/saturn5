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
vYdCwIaeeNO7LKS50r3xpndiKLLQPPIGLQAUlOz4lTHbcACLiC04gmu4NhxCynzAL73pXUTSXENPvemdRgI09Nab3oskAAOPven9Ssp20r72pvc0KSLWPfem9z1JE6d+703vjVKmTPngG7DvCZNFjGoqkC1EN2XEFqKcEqB9tFOEs496Cmj20c8azD4KWmG1EA1R9gX88ps+PiJgg0+/6QMmAjL09ps+giIAA4+/6WMqAq7+9Td9lEWaPc3zb/q4izJv6vff9IEYZcaUD8Dpd0GLAX0FsoXAvozYQoBfArQP9Itw9gF/Ac0+8F+D2ScAVlj/2YkA8C24dXuzx+DWPVE/Blf73uAxuCqtPHkdp6/BlcSjeA2uRlk5V1VJUPsaXL0p+BqclKTtc3CK3tVF+STPwa16b/EeXAGj+YNwZmewSRtnsEl918lLlKelb8qWofzik5L+CKbvYPRvYfoAoeccoi9fvVdoHQGgp688DKdSWiEgvkoBjaL3HOp99VK9qvcQfeUmvbL3EDkmOkGup0ZGHsAjr7xzoWAegCN3MXJBrydHiXmgJw7ggUsbCXQcYwz0mkOM84vkp2wP4F57JU6NckRAgbRG/k4cAQXSHfnlbRSlfK9PgZKqABil8lqcCkQqAhikcrdXNR6O
*/