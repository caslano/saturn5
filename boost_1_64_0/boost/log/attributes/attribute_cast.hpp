/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_cast.hpp
 * \author Andrey Semashev
 * \date   06.08.2010
 *
 * The header contains utilities for casting between attribute factories.
 */

#ifndef BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * The class holds a reference to the attribute factory implementation being casted
 */
class cast_source
{
private:
    attribute::impl* m_pImpl;

public:
    /*!
     * Initializing constructor. Creates a source that refers to the specified factory implementation.
     */
    explicit cast_source(attribute::impl* p) : m_pImpl(p)
    {
    }

    /*!
     * The function attempts to cast the aggregated pointer to the implementation to the specified type.
     *
     * \return The converted pointer or \c NULL, if the conversion fails.
     */
    template< typename T >
    T* as() const { return dynamic_cast< T* >(m_pImpl); }
};

} // namespace attributes

/*!
 * The function casts one attribute factory to another
 */
template< typename T >
inline T attribute_cast(attribute const& attr)
{
    return T(attributes::cast_source(attr.get_impl()));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_

/* attribute_cast.hpp
4E8YXCD+ngsHwJVwoNwfDQslPRbCOXARnA+XwGthEbwTLoO/E/v3iPkDcCl8CK6AT4m5pBvjs97p1knSLUnSrYukW1dJt86SbikS/h463fjN8k63Y5JuH0m6fQwbwU8k3dL1uCAU+879Nt4T+++L/Q9gA/gX2BoedZ6hKu7EGp6n18WdP4k7bzjs5VVh7x9i71ux908o6SnjQsTBkJ63oafeNWAr+FuYAO+EHeFdcAC8Gw4W8+PiTuksx3Mm4Vok7t4v7u6TdHgQJsOH4NnwYTgMPib9pVI4Hj4C8+GjcK6YF8DfwwX2tY6XjEXAoYZ4/VH8f1bi9aLE63mJ1yGJzwtwiJjjLn1S+bYuYwyrpX8ZIf2sLHmeZko88uFoOBtmwB1wMiyAM+A8CfcCWAQXwlVwEbwULoZXwGVwO1wBb4HnwUfh+fAwvAC+AtfDD+BGGG73e+Ak+EuYC38FF8Fr4Sp4OdwCt8Hr4A1wO7wR3gp/DX8Hd8C9cBY8BHPhYbmv25V82VfI0K7cJu3AnTAB3iX9z3tgG/g72FVdS/755HuufD9eDTshwySdz5B0bgzPgs0lnVtIuWgJC2FruBq2gb+AHSQdO8IHYSdYCrvAp2BXSc9kWAaHwL/BofAE7AFjCEMKjIM9YQOYBtvCXrAT7A07w7NgLzgADoEDYR4cBGfDdHg+HAKvhkPhNXA4vAOOgE/CkfAAHANfgOPgq3A8fBNOgH+BE+GHMB5GhNEuwWg4UZ+1LN9g4V8kn5xnLT8l/bUDMB4+A5vCg7A5fA72hC/AvvBFOBi+BIfCIzADvgaz4ZtwNnwbLoV/hqvgO3AjfBdeCo/CHfAY3Ak/gr+Bn8C98O/wQXgcPg4/lfeHE/BF+Bk8Aj+X94gvoO4nza04q211FWept4D/0P0E+b4HzzP0EyZLP2EKjIFTYUOYA5vDabA3nC7tzWxpb2ZKuzgLToLnwKViXgTz4SrXWbilEo4Fhn5SLwlHH1gP9oUdYH/prw2AafBsOBQOgefAoXA2HCnt8wg4X66lPZTvTZRZQ3v4iPTPHpX3jcfgAPg4fC/EM9t+yL12DsCTMFb22Ume+N+9107ef8B+OyfUnjv/XfvtHPkv2HNne4j77jR6nXPekGxkNbIF2Y0cRMqRuD9xfhySh2xCdiEHkKNIxBvsuYOMQxYhW5A9yGHkJNLyTeKP5CHrkV3IQSTiLc6RQ0YhxchO5CBy4q2avXtqfv+m9f+Mjp6O9f/NWd3wUirfJrAfbjHlYkUxC81XLplTvMJKwOwwZrvaO8yWE6KlS1ZYcuZfm9aWnquZJ/1SrKhfT2RnI9rubP98jszM3EVL8+fm+l0iGCssPV4VjQsb4pAQ1icExmoSfV5jFN5jC6+qMZZhn5319CW3d3j5mW7d9u946NVw77EU81iE15jA6fvGX90xHI8xKBkHkDyQvHHvR9pM3otbyntoK3kfTIDJ8t7QE7aFSTjSqF60lYJIf0X6KtI/0X2T4D4J/RHd9yiCJYj7zNijNjNoO1x9gy3SD5D99mjn9Vmv+pxX2nB9vmuEtMubXGe3SlvramP1Wa20p97ns0p7qdvBrR7nrubIGasZpE/Nr+ZX86v51fxqfjW/ml/Nr+ZX8/vf//0o7/9zVhWfjvd/+x2+XWtLz6PNCau8tupl+wykrMCajJGZEydn2LtyyJYcI0ekLrbwT68vM83bFPs+h16+YW6sSW+2aV4seqHvKeHUvaNz5b1AvlXmvawU0z5wMp/3c6UTqec5tyfNaiMdkI4hrO2SNSKBdW/qOkpf56vrWH0922tPCp1PseLBdPFkmuRTRrZ3PhVZp86njOzQ8ikjO7R8ysgOPZ8=
*/