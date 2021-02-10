// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_LEXICAL_CAST_HPP
#define BOOST_CONVERT_LEXICAL_CAST_HPP

#include <boost/lexical_cast.hpp>

namespace boost { namespace cnv
{
    struct lexical_cast;
}}

/// @brief boost::lexical_cast-based converter
/// @details The purpose of the converter is to
/// * Make use of the boost::lexical_cast functionality and performance that many people have become
/// accustomed to and comfortable with;
/// * Demonstrate how existing independent conversion/transformation-related facilities might be
//  incorporated in to the Boost.Convert framework.
///
/// The converter can easily replace boost::lexical_cast, adding flexibility and convenience.

struct boost::cnv::lexical_cast
{
    template<typename TypeOut, typename TypeIn>
    void
    operator()(TypeIn const& value_in, boost::optional<TypeOut>& result_out) const
    {
        try
        {
            result_out = boost::lexical_cast<TypeOut>(value_in);
        }
        catch (boost::bad_lexical_cast const&)
        {
        }
    }
};

#endif // BOOST_CONVERT_LEXICAL_CAST_HPP

/* lexical_cast.hpp
eXHYgcAXVO/++LfxdDZ+OZ1NN9fRGJdtE+Y4W+SObZuqMjUs+NOryeZqNaffxrOrSbSSKGVcMBnyyXbxlvviI7FwJQ1HruZv54v38+3CXyz4OHI6pGa8nkxoPFsvcF96ufqMRYrRi0EjPerR3U70F1BLAwQKAAAACAAtZ0pSgo3zUKgFAABbDAAAMQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ09PS0lFSkFSLjNVVAUAAbZIJGCtVm1P20gQ/u5fMZf7cICM05ZKXO961YUQikuIozhpDwnJ2thrvMXZtbxrQnS9/34zuzYJUKl8aBDYzM77PPNsguseHPy0jxeQO/jhJ7G/CX7w2RlNa/WVp+b7BknyDdwPGl7j8wWh+rC1+pbsw4usvsGetUraWO/pPUleEO6akqQ/fTK+TugVJc6ytR+qalOLm8LA3nAfXr979zscwptXr499OGVS8BJiw+WS1zc+vM+s5O+C3d8Hmn/wgRtgZfDI4bwQGrTKzZrVHPC9FCmXmmfANGRcp7VY4j9Cgik45KLkMIymV+Hkow/rQqRF62ejGtCFasoMCnbHoeYpF3fOTcVqAypHD+g/E9qgz8YIJQMMz8HweqVbN5QEK7UCdsdEyZYY
*/