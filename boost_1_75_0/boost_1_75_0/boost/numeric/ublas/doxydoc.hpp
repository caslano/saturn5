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
r7l05ObyaF8AhkKKQBK+DlXZZon1rKxS+Ed95fVayXwd6vFq8qQ0XB4rNeBX2BLXZC++pwy8DrCwdf4yAPsgHTfLrLHMu1pW5rtmmey0XS+l60eE9IO5ngMifSHTI3LkSokL9ll4rRTS2xtjXy/gcHM+0x2A3pAKIQnZkfOZfg63jc90d6lLMemP2YnUSYzHxNBTqhyiH58CYAWkTQ6jTbqewg4OszatNcvInw/92EwCDeyUzGg8VZyQ8TPFKNPkmTH8H/W2XAMAYTfqAYn6i34KKHvfXqn7i7aDn0EtCsAffYvLbsqS5HNkpryf+YtmulGwMhMFw/ejIKw5FtG7MaFB958bDUjYupsIwAxIiyHJ9jhIVSCCSk/R0swASCfitOcw3u+UakmG1Vmal9cbyusF5fVoVd4hQMPiLp0A4EtI3xvlFdjKu2KWR2OrumRtPcaX2iiv7fblOKPa9xD8oK3C+COntMSOCiV3AJEb9J8OYQ11mG5iYuff4TO+5wvAGkgs/jH966iRV4FwvB4DxevJ46tY5OPt8ErkDfpePyHTeWwy3Sn4J4N/fwmZfwrcV5xuGz/oTs8GVaBJVH+IIRumEgueXpAZRDievsSO56q8hwUDTEMxYwNUwuvpj8PjL5CCnkxoWu88+iimj3H0MZU+/pM+VtDHRvrYRR8f0sc5+rhGH2Q1sIz9ziBKZvvebhQog79Qlr7vTcs7
*/