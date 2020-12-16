/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sfinae_tools.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A distinct type that can be used as a fake argument type in constructors filtered by SFINAE
struct sfinae_dummy {};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_

/* sfinae_tools.hpp
9ssoX8k2vQz36dn0Tmfd9H/neui3i+3vvLa1bp7T98vFf9zS76mYzNT1Z8f2l2Hp577+zc+E1bUd0PfNVhw8B5aFleFFsAocBdPgNJgOb4dV4UxYDW6DGfAVWB3WJs0asDGsCXNgLXgxrAsL4bmwBzwPjoL14CrYDj4LG8J1sBH8CjaGyqbc0A2zYEuYDTvCXDgANoUjYB68HjaD82BzvU56C/g0PB/+BFvBNFdRvg1864uXwt54acTeGDkiR+SIHP93x1nQ/0cOuerMff+/LED/z9cvtQn85iVp9vQO2L1n9H/yNuq/4/5/KXDQ+7I2k73cusBpTgDpOe7XZ/ZHu1nix9szie/bC6zMB15ZntOcAdIrPt4/Yvzwq4aOG6vTrATnSJg1dk3rgJN+Thrh7AqO+jnhw+rzTvvmEb5kff5nOZ+KHuqyHfRy4hdf43CE2cfvMamv7VZd9O+RKs/ory33yF5RagC1PkrW6qphxvAXSXoHkZAGf70taayz3JQ+ES01HdbFZalrtB2EGpE2yCjeJjJn4B3ehR+WNP8esC/YhKD5CgXv+/crk/oR/w12M2RPYMn4jAVczqMG/PGHDxh7Xaapo0OSfixXY5k0q8s1xpi9GI5KmASxJe2hTGvF/66dQc01IFTgfIZknUY3KccJq5DVaALtHkV6woWkq9d8kbw+Zuz7abF9VNDyjSIvi4ywuo+/KTKPyJK17DyvjL+qSjhL4t4uec+04tgjMI866GWlSbs3HY9Fg/JLu3MnFsnaqkMBMmNrCdbPjQ0lWtJubeZMROn6F79pvyb4i/YRjJfzN9vB9Z9l6v8NXf82//vq+6TI3FLfe0ljq/h32Db1UV76m1lfTnTByr512CSvTVZz4o6hLfarjZzTdgepp1PqXDSIS6it4WqklHEX6RfVV7QdkG5QH8uRuL3NfJsnJfxmK5V87lDnWCXnEdzPA/pxZmAetqSZo+roPC4S/wHrCvUT6xjFq6HYZSbB+bTqny2PlH03Zc+ScH1sve6lsSXklsKWIGUK8HfC77MlzNgTag+4cU+oPWD0nlB7wNV7Qu0Bg/aE2gP67gnda63bntC91jrtCbUbqD2hdoPv3w+1Gxz2y8x1HERW3G7wkV9mroPnV4jdYKdfZq7jxfd/3/5r/I1M/75oeVIY+0KFMPaFVAf7QqAtQf1OW8LzYktIvTz1peXnDm3pvv+mnbUKyq89O7aENpb+rdLvD5mwtqxT5l83Kx5WgtVhOqwHq8HGMAPmaVtBS1gDdoC1YHdYG/aEdeDlsC4cCM+Do2E9OAk2grNhY/gizIS7YTbcBwtglN47rQZsBu+GLWGSXbR+XRXYBqbDtrA6bAfrQFmvDl4Ec2AH2AxeDLvDfNgTFsCr4SVwEsyGN2n5LNgZ/hleCrfBLqdpaxgVsTVEjsgROSLHf8RxdvT/prlnavx/ecCa/Y/qdcP3eH8H4cuwFT+gme8E6P/k7bcAhNoAzBzxd71x3nBe4/4dR/3f6JGd5PxGyzde2FH80UZfKyNp30DabbSMt3WR7WCMotDJRkCeYfV7J3sA4cPr9779ubtJmOdMOS8Vf4yTvYD0HPV/s190Xzm/0vLpWr3E3x2NsKnlYE8ISm+cW9s8dB3uI7175Pw4U7aPpX4qGhvLKDl/l/WwOuA4D4D0jb1hZh3RsyTckaA98EaYcf07dX5RVpTqQ/cvZgMwbTdZwuUrtEozjrxVZO2tvuptrbf52vNtac/nyDlAbzd2j5MSr6zVQg1RqwO+Z7hT4vZUbt6u/Gs/jh0wYbB/D8BzJMxdqpi+H6TXt/KGId1KAfMcnpY83+Mum6YqS1h5sdXl3arSCf8QZzg=
*/