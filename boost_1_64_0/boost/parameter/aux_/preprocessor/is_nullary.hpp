// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_NULLARY_C x BOOST_PP_COMMA() 0)
/**/
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_NULLARY_C() \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <boost/preprocessor/detail/is_nullary.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) BOOST_PP_IS_NULLARY(x)
/**/
#endif

#endif  // include guard


/* is_nullary.hpp
y9y6w1Muqds6bfQ9Gx7svKwp9Pis9OeaOc+hc58L5jxHz32OmPNcOfc5fc5zytzmrKU/d895Tlz6c+vSnSPpPOfRfc6g8xzA9PfSON25eDIuqO2u2ZzTpOuVh/kxGNDjqFxeErnbVK4eBvTYngOWRO7dKncPDOixPQcsidxrKvdnlfuLITcpidwfVO6PKnfckCtPIvcnlTuhci8bcpVucro+eJhZMAA7QHtuWRK5f+j5Tun5/mmcr9FdTjpOgZ7Pa5yvOYncVXq+GTAgxzG5liRyXVWuQOW6GnK7k8gNVbkLVG6oIdeaRO4bKvdNlfuWIXcwidzjKrdX5b5k7i+RRG6fyn1V5b5myJ1IIrdb5T6vcnsMOetGd7lPqtynVG6X2f6SyH1G5R5Wuc+a7S+J3I9V7icq97TZ/pLI7Ve576rc98z25y5nrxv8A5X7odn+ksh9UOW2wYAe2+0vidz9KvdhGNBju/0lkVupcjUwoMd2+0sit0Hl1sGAHtvtL4ncfSrXDAN6bLe/JHLLVG4JDOix3f6SyN2lcmthQI/t9pdEbo7KzYIBPbbbXxK5UpXrrXKlZvtLIjdO5UbDgB7b7S+J3HUqdw0M6LHd/m5ylytWuW4qV2y2vyRyo1RuOAzosd3+ksi9XeVuhgE9tttfErkBKtcPBvTYbn9J5C5RuYkwoMfb/TL3N+n84Op3MGcS9zCu/0beiOFaHNaKYF0C1hiQ7+y5fqNLv33fTtjhW05vHYn/9jUk3orrR5zO2hHpzj9uxG0/zfnH5eveemtH/KfmJL9Z85EX0qbvxe3E7cedwOW922uNxs3FrcHtwO3DHcKdxPXaxPxlXCWuCbcTtx93HJe9mXWwcXNwjbgW3H7ccVz2FsJw5bha3DbcXtwh3Clc6Vb0bs3Me878Mr/ML/PL/DK/zC/zy/wyv8wv88v83pjfGzn/fyGvousaznzN//C8h6rekfT6rLDKimU1K1bXVNTWrVhEDN7ByTcCvy9kTQhdCz1bH6X7xtbcsO4oYoziKnllVH7J5CumzqyYv2oRa4kt1TWXViLPWjrLGow19SdL/M7O658RFr8OOvos5/X3zLir5LVVdVWNsfbQSAkvEdmQIRtS2eRrJJXGrZEUzkdXyUfimt2kT/1CcJWFn6aD+QG27cbrnPVzVHsJbhO2q4yz3aIVdavn1S20EmxnrEe2UOIXsx+hx9F+le3YZImEd3Oypy1bZF2VH6KsD+HuJY++gixvKOAlP1fnF2jYCdy782TPcPE/EzvaNktYe78BAR2ftutdPfLNcTZbXNVQMcyxrnWB2yTuOY62ajZt1c5aj82GbSZRlq/51DbF2MYXsU00bDC6NhIWtLKyQkHWr8f/JP79/fE2O2O7GWtBmnVtf8B+n0CKaQdqt9Y2dqvBDXesa93gtyX+hdb5LnWt1dl+djv/kYSXOq8PadhzDbJTAmrPwdjT7xP7FGvYWsL2hO3pCd5KaA5TxsSm0/BfE4ja1ONqU/8Z2HSi2nSHziOfqHOMJuC20H7zrk60KftBVNTOW7BMlopzrZeFIjfWya6qk1UrbVl0injMtkMkTi8n2yLv2AfY5dpDwkfynsfj2Dcib5fNATJ7JCtSNiHvkHBl7yBlo2GjsctjkTodDFDdw/vOhsOOItOLsC+Gyy03ODg4Jcsfys6O9CEaPrJD++0hlbLTdTrVT22VQp+8OTvWF+t7Ret2dFSaZSrr7tHBaFmuduqTJX7Qynbrk69OvZ+pvDq969LqFOrwWM1vs86ZH6L9wgWa3+Y2+dWOwSXP3eD7Raan1dE5z+hM3jc8KOE9nGxgy6ZaF1KxQbQd5+l89HNV02Dce2jHB9s=
*/