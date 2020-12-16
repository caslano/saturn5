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
0FOYvP142KPYX6NYF8c6KXYc5at8SCK2w9WV8lQ+iCBkLCxLoEfZOzhNmqYoqcja0suxaatHGUNOO24WlGlc3ra/6Cj9yk/olDufQ++jUNmGvRYiMIE8vuBs7KkDx3iUck6iRjKSAtEJ7llZRW8pKzjuB5Hsa7TsM2T2OXr2yZHsi2T2Gci+luPSItlnatltMrtdz949kn20zG5D9nqOe/8hI/tAxKms//eJHdX0eIj6LHT2TVGaOeGOh4xCviDqxz4O/X0k+9tmyl5K4/os/JGcKyM5n6CcX3HovEjOBznnAZ1Um6/l80byBTnFfv3spbiaKcGFkQTXEwlnCx85/RcqUzm6a6SGCXR2seHZVsRL9hKf+OTPBnCkce61nPv7hcw41QRDfo/OmecVY5/VeN0d5Z9RLyXPaJ9wLWVU/FznfVxoYksvAE04Q1nFgTWRmuh5eToc6B1ZxwnmyVyU4Nec4B4jwS5O8L1IgmKq7AMOPQ+h8gLpBuUQh/Q1QqaGa1czF8vvwVQr3YrzdUoT/hOlcSFNxuFKpt88loqIuhRYpM5KSeNkzZwsEcm6GELRs7/FHcv/8g8rCWDUIw7fGxGtSYGOqV2vMmPyFknl8t4XEf3RXg8t9IkTyANfqk9UNklBoFqEAI46FATS5etdJNBBcpvBpaQ5sZ5dNrhqpcy9U5mML4V7xD9GFhD6zFM5NDESWsniQdkLsxak3cDy2FgdLua1iRJ+vFb/0N/PdS/MKnpXmcsFPLtWh6XLKbNtwbnITKuDzG/X8//VyH8W8tuQH9CJcFXm/1cAEEnklH2J5XqpVH6nP9do5mpCU2wxVUj+wZyGaH+wOAdPZASLh5kCmuZ4lNQm/cSY9BM5fY45Nr3+fqpJXmQnSl3eBj9k7C/Cv+Anbvhp6sIZnqG4vH7+Pm28NF3Y2Ygu+oIS5NisjaFJMzq+36f2NeVkmajCiD9D+nX+S7soiOtAqJjSSxLEJcGjFn+2mqcEH/uKl8Phwcc+Z0dasBgaXntiGLEwxQVbXYGechgwJIkxQ9J++4YxhSgnR/6ZaOY/HvLFZio0cXsftH1de3MmywjjPcDgomFmxx1oQUf1cxOj/G0akuOKNITZHimR3xZGNeE8qkr/teHHnBhdniVSXoy8Xgq/BA/UlO6hwMvv05/KUR8mqAGVXecPWUtQEyzBUKc8cVeSyUlXU04X/01+fKDJ+ViL0+Rs6f/Etn4y7janjLP0Qtw9/U14vDPPBF1mGaQQwt+nqTIHpcpn0/OoQpr/dMVJmq+zcdZylNN3JkcF4A9XoWO8TIMK5Y7h2J+Ytdh11DoqNzer5Sk1F+M/93DOKLu/t2RWIV5jYqDiu8+WHvC74B9ZS347bZnzuZ/+/tS3QrM/QTGngvwfxw9Ne8OvSCV2Li/uW2X6bDO1U/GqdXYL2gVFEPTMUqujiu6MI/UHsivCUD+WO61mtk0tmZHvGVpsE+V3m01aMXSj6n7bsewYeolUKkaF5lMT7kNxzYrI6LL6cF8g/xxp9mMm7rZTDiT9yo7SwuOoaua8M4y7Yi+NOtqZzvr/51BSGuSf04E2nUaOHIna3e7BRbg+gdvCX2aMlYJuQFDUwHaBRqKNkgwY0RCX0lDooXuUc546HlZKLIR3vM6XwnMkdfbF3zDbW1MuA7tkIInk+nALcmUZuRL0XGtkLqmTLpJ8CyWffHIlPz0p+QhKfislP19Pzoo59RzumBzffgv4r/pp+q+eJHnczLBPu4Pzy8srKYXoDOMXLBlmDiTMxvUZrtfzpdTUT5ELV8M0YT51JNnSCm0ecT1jCE4xGqpU6ErPVIrifscrxV5jpVhNK0U4d3J2yUR/1+w=
*/