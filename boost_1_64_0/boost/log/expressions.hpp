/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   expressions.hpp
 * \author Andrey Semashev
 * \date   10.11.2012
 *
 * This header includes other Boost.Log headers with all template expression tools.
 */

#ifndef BOOST_LOG_EXPRESSIONS_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/expressions/attr.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/log/expressions/record.hpp>

#include <boost/log/expressions/predicates.hpp>
#include <boost/log/expressions/formatters.hpp>

#include <boost/log/expressions/filter.hpp>
#include <boost/log/expressions/formatter.hpp>

// Boost.Phoenix operators are likely to be used with Boost.Log expression nodes anyway
#include <boost/phoenix/operator.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_EXPRESSIONS_HPP_INCLUDED_

/* expressions.hpp
tcZYCmOWOJSJXI9uolfc7encpryTeCQpe2PN+9450mCLPw2Ua/VkXnJ7ZV7fmAZil3vUL36787C8Aq+1/d4LPPblcfn9K0l/tmLSdoeIXcNcV203HrvX+O2q7VDVJDiH/xOVnqEucrmxVbvBRMLCVSyKqHBjprhhmhPrdOPaCjeoBBYVznGEo1Dp1THOlU08DWVpi7qn8k7XR1erezpPdH30K/u+pHVzqY+use+50hAzFd+tYuZMG8xUPK4VMx1nV1keEF35Ob4BOyVeZZnnl51VQ3p+S3T502VXbFeU/S1VPMMl3yPd44PSXfx1xf2kbFKZ7Ngj/Cb0d3vFfUXh/CVVPMf7lL325rU3jmfpRimHuKbL354qnuPdjjL86wq7uWSqXRC0G09U8SzvduTFdocb/KftvyjPgHGdzvfIi8AzcKN9T+LdXJ6BX+t7Oj66bd3uMOO/oLybG6vndus29Fb0y73yju00CuetceedjvtJZa+Jeb60I+1u9qeduFaR9yeqyL9yR/7tdNq3Y+Vwo1ahpL9pbcj3SP/As3CzuqfDrvNgp76vwxTUT0mXM/UyxKOJyC67vSs0pDWLfKV9p09fuZ8yuNBz/y1xzyd5pOdr6/RJU+YDdT/m1mr0YwiLsR+TXK/yHs+32/WfKW4rvls/psQRrznqvUB1Nc11XuF3z+fAc4Yf3LP9cO2rLy72CMxNQ+7E/nZjXE/db9lZ6Hm+h7gp7yEqzsoxY5zR1c9XptKVJtH03uRye7LSV02lsd5yup2jdHUTan7/Kax4Vmdofd2sGvsYTjt52o5ubo19iu2nIZ9JV+6pdNV9ikx1T6ef7lNMVvdVOul1Nznqnk4P3Z+Yoe/reOv+RJ6Y6fi52tR19Ss/T3cT9jJjGatef6IskJe6TOlm3Xxu3vdI43hnGmt/zOcFNg+MmSO77TbIGNdT9x9OFHq/w5U7yvw8FXflmLm9cZTHQq2rm1dz++JI2yUVdvjPY/3h90jbQPklHtxT8dBtUaG+p8Or+wNLxEzCFXyuqpytR5bo/uw9qYT1XHNeePcHZH8tZe8MY17gpk6rZSqtxDFjORR9yY9Voq+bWnN+YOe7p2+g7BI27umw6TRepe/rMATvtSlpGRmYG4a8S/uZEpSWE/mWl5U1zjp1G+xc29a0sdntdKfbqsMm3wEDHwmtU69PDNr/p3Hl/X/uJY0y3P5o90Pbcz+jmvmi9853he+EnEvYRs6UT+S/PYQvLyh8dKYqwqfKW5eG6jvhkvmseXauLX5d2bvZ6mNeLyfu+mSvfd230nsILPOXd19b/j8H2YGk0s+i/tb7peAYlDO7m/j/XtuQ+63xC5nb8NRr8O01crUWVqyRi5d0Il6kk8RLvqMVKD3GXlODy9CdTYLXRzZC7kPn0EJn2q0wlCHvfulhZbe+Ke1wt3p57u5r6rOzm4kyouYWIfvs9sIdbh1e19kIju+qnyk7A6zeXuvZJcxe8Y1bpPLb3H4sDOqP8dP9CW3/K6VTW659VoRyL0r3za+txhkuhnMUHGkoZ0VJWSA86rr9ouCycUKNYXut9fNeI9lomY/7z9049KvnXi2snzvgrcfuL250QfXXAJrXHnqvtXy7rn1/wBdJnbI/X3fpnSOnN/2o9s8v8l4T2qSeff+m3133yIvPLDu5tsG+Rl2jvhjvvabSvLax+mtLzWtCvdY8Vn9t40iVDsXNf/rZhknXTb+4y9Qb43pFv+e1xrP6a04bKPc3/eb6l99/KiVlw1NZqwt/cetH1V9zal4D673G0z/2L+MpMk6Vosf+K9bE1YGXwAR4KRwAN8NB8FqYDn8Gx8Cfw3Pl/iJ4OdwES+Dl8Eq4A14=
*/