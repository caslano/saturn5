/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_mapping.hpp
 * \author Andrey Semashev
 * \date   07.11.2008
 *
 * The header contains facilities that are used in different sinks to map attribute values
 * used throughout the application to values used with the specific native logging API.
 * These tools are mostly needed to map application severity levels on native levels,
 * required by OS-specific sink backends.
 */

#ifndef BOOST_LOG_SINKS_ATTRIBUTE_MAPPING_HPP_INCLUDED_
#define BOOST_LOG_SINKS_ATTRIBUTE_MAPPING_HPP_INCLUDED_

#include <map>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/tagged_integer.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! Base class for attribute mapping function objects
template< typename MappedT >
struct basic_mapping
{
    //! Mapped value type
    typedef MappedT mapped_type;
    //! Result type
    typedef mapped_type result_type;
};

namespace aux {

    //! Attribute value visitor
    template< typename MappedT >
    struct direct_mapping_visitor
    {
        typedef void result_type;
        typedef MappedT mapped_type;

        explicit direct_mapping_visitor(mapped_type& extracted) :
            m_Extracted(extracted)
        {
        }
        template< typename T >
        void operator() (T const& val) const
        {
            m_Extracted = mapped_type(val);
        }

    private:
        mapped_type& m_Extracted;
    };
    //  Specialization for the tagged integer
    template< typename IntT, typename TagT >
    struct direct_mapping_visitor< boost::log::aux::tagged_integer< IntT, TagT > >
    {
        typedef void result_type;
        typedef boost::log::aux::tagged_integer< IntT, TagT > mapped_type;

        explicit direct_mapping_visitor(mapped_type& extracted) :
            m_Extracted(extracted)
        {
        }
        template< typename T >
        void operator() (T const& val) const
        {
            mapped_type v = { static_cast< IntT >(val) };
            m_Extracted = v;
        }

    private:
        mapped_type& m_Extracted;
    };

} // namespace aux

/*!
 * \brief Straightforward mapping
 *
 * This type of mapping assumes that attribute with a particular name always
 * provides values that map directly onto the native values. The mapping
 * simply returns the extracted attribute value converted to the native value.
 */
template< typename MappedT, typename AttributeValueT = int >
class basic_direct_mapping :
    public basic_mapping< MappedT >
{
    //! Base type
    typedef basic_direct_mapping< MappedT > base_type;

public:
    //! Attribute contained value type
    typedef AttributeValueT attribute_value_type;
    //! Mapped value type
    typedef typename base_type::mapped_type mapped_type;

private:
    //! Attribute name
    const attribute_name m_Name;
    //! Visitor invoker for the attribute value
    value_visitor_invoker< attribute_value_type > m_Invoker;
    //! Default native value
    mapped_type m_DefaultValue;

public:
    /*!
     * Constructor
     *
     * \param name Attribute name
     * \param default_value The default native value that is returned if the attribute value is not found
     */
    explicit basic_direct_mapping(attribute_name const& name, mapped_type const& default_value) :
        m_Name(name),
        m_DefaultValue(default_value)
    {
    }

    /*!
     * Extraction operator
     *
     * \param rec A log record to extract value from
     * \return An extracted attribute value
     */
    mapped_type operator() (record_view const& rec) const
    {
        mapped_type res = m_DefaultValue;
        aux::direct_mapping_visitor< mapped_type > vis(res);
        m_Invoker(m_Name, rec.attribute_values(), vis);
        return res;
    }
};

/*!
 * \brief Customizable mapping
 *
 * The class allows to setup a custom mapping between an attribute and native values.
 * The mapping should be initialized similarly to the standard \c map container, by using
 * indexing operator and assignment.
 *
 * \note Unlike many other components of the library, exact type of the attribute value
 *       must be specified in the template parameter \c AttributeValueT. Type sequences
 *       are not supported.
 */
template< typename MappedT, typename AttributeValueT = int >
class basic_custom_mapping :
    public basic_mapping< MappedT >
{
    //! Base type
    typedef basic_mapping< MappedT > base_type;

public:
    //! Attribute contained value type
    typedef AttributeValueT attribute_value_type;
    //! Mapped value type
    typedef typename base_type::mapped_type mapped_type;

private:
    //! \cond

    //! Mapping type
    typedef std::map< attribute_value_type, mapped_type > mapping_type;
    //! Smart reference class for implementing insertion into the map
    class reference_proxy;
    friend class reference_proxy;
    class reference_proxy
    {
        mapping_type& m_Mapping;
        attribute_value_type m_Key;

    public:
        //! Constructor
        reference_proxy(mapping_type& mapping, attribute_value_type const& key) : m_Mapping(mapping), m_Key(key) {}
        //! Insertion
        reference_proxy const& operator= (mapped_type const& val) const
        {
            m_Mapping[m_Key] = val;
            return *this;
        }
    };

    //! Attribute value visitor
    struct visitor;
    friend struct visitor;
    struct visitor
    {
        typedef void result_type;

        visitor(mapping_type const& mapping, mapped_type& extracted) :
            m_Mapping(mapping),
            m_Extracted(extracted)
        {
        }
        template< typename T >
        void operator() (T const& val) const
        {
            typename mapping_type::const_iterator it = m_Mapping.find(val);
            if (it != m_Mapping.end())
                m_Extracted = it->second;
        }

    private:
        mapping_type const& m_Mapping;
        mapped_type& m_Extracted;
    };

    //! \endcond

private:
    //! Attribute name
    const attribute_name m_Name;
    //! Visitor invoker for the attribute value
    value_visitor_invoker< attribute_value_type > m_Invoker;
    //! Default native value
    mapped_type m_DefaultValue;
    //! Conversion mapping
    mapping_type m_Mapping;

public:
    /*!
     * Constructor
     *
     * \param name Attribute name
     * \param default_value The default native value that is returned if the conversion cannot be performed
     */
    explicit basic_custom_mapping(attribute_name const& name, mapped_type const& default_value) :
        m_Name(name),
        m_DefaultValue(default_value)
    {
    }
    /*!
     * Extraction operator. Extracts the attribute value and attempts to map it onto
     * the native value.
     *
     * \param rec A log record to extract value from
     * \return A mapped value, if mapping was successful, or the default value if
     *         mapping did not succeed.
     */
    mapped_type operator() (record_view const& rec) const
    {
        mapped_type res = m_DefaultValue;
        visitor vis(m_Mapping, res);
        m_Invoker(m_Name, rec.attribute_values(), vis);
        return res;
    }
    /*!
     * Insertion operator
     *
     * \param key Attribute value to be mapped
     * \return An object of unspecified type that allows to insert a new mapping through assignment.
     *         The \a key argument becomes the key attribute value, and the assigned value becomes the
     *         mapped native value.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    reference_proxy operator[] (attribute_value_type const& key)
#else
    implementation_defined operator[] (attribute_value_type const& key)
#endif
    {
        return reference_proxy(m_Mapping, key);
    }
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_ATTRIBUTE_MAPPING_HPP_INCLUDED_

/* attribute_mapping.hpp
V4G8IaqP+OvTzZ1FMGDcLE0dXcDOqxY/A1ManHUBVrbBH7cxqOhHHxJxL6JTVkjKnrXSXkn6ZsKjc7IvZvGgojgKKclxzaDqEvyJO8PzethKqhyzN8wEXcuF++XxQ7oSkI9CRt9SCI1yZBI4w9Kc4IWPxi8Ewu28qC9Ued7X+XSZkI60IT+FrMB5xCIoDu3XEm5PML6nEEllAI3lXRgRQu2QIzse+5Z3jzZMAP3hkEm6JpluLmfZv06d56wZ8pM32xva72UgqMv6mlOc39KiensIfru7hPfvcCVK8EJ6VaxtS9GrlLVOejtIq7LYdTVyryPEGHPGLjsZBauFHDL6g4boMniT1soiD2LqZ0/rnWWvfzqkHStt6oFQiMXshrhK3j9nOjig8LRbMWz/FnDQx3qxmSXoBAls8FQIggP9m1uufl1rbBh0HZw51ECiOKri34UGiS8C5W8oOcFbTz4yCdzTcMBMyvFCJju9zEdl66N8YM1eyNcIncnYXQYnBxk/srTikRLNH2AtGwruEJv5+HgekbgtDlfJNhEaBa6CGb/u2SljVMbv016OmwqWfStaxczMZ6vKrUkQ7oQ95YCRvz0TOjFJpAjxh+cX94pfF4DjUcoZrkZo66RNmadCMzT+onEsXudocQ8xLzs9bfbaioDmJ1KdAEylC0T/Y1yhXhlLEBCS1sYu+ke3h+lzQ2taP3JMvfHhnden3k/+REmB3F5H8fGA//EWwHhI8ONOZ2B3Jy5Mmvov0/Yum26GfWpab5vEg6tVWqNT0xOamBjD/vbLXsBcK8/00CBQKbIwu9ejrm1piSeXziAThoqT2ZO6JmNx54D4nmNBbxku+bSXA50Bm/5arrzHVEXS6ZE5iL5CnPYa9T3SqC7HaIVv7BohyKf1FO0nXSYq0r0QQFcRulbWt0fow17Z7ZKfbBVc9ScwQD6mVT/c9Ekgs8rqM2eyXdktdGyEjz09bicwVbWPQbd2mWIbNY16BxtKqT1RSqsjS2YS8Qzeq5NKwShLeo0lP8diU74czhKAKm14nx3udBpS6ECOw+qk/1UOyxA+7Z9G1AUt0J4CTliH2cDsfxrBOxRIrqS+yoNuL5Xr3yf2B+TNfmFUmeynzmqHp5H1O7QnmeUsYfUchpmlD7sNLCc6NXduxqKyOfpBffQBUtruBGGl9YQ6j/9KAkqopW0+BiuHROqpUT0fCTvVrjtGeZk3mzYP6dBi+r7KMW5ZVrsLqmo28fX2xBpfFk0pYch2ouGcipVOZP6WPN3Lf334ZNN28355gTITHHm28gZeRjvwOpxBq1arDlJBewCXYULqs2mwd7l8Gctq9CgwFfN0NU7WSMLuivdpu8TpKyDNjU91kBxmC98PeQW2jVKU5C8SlLoFZQ46kjI9d3Gmd36zgDfbwmDz1DLeG+XKHpySQCCnQ0rm9m2CBeMXD5tPtlRs1WJd1ISUo0xwxIn5k0riX7s1KeRl4N/Ti66yx9Iu29sX38YJcZBYBw1knguEILpg7f6hc/b4K7vGUBPJ6FDxwRHD5kfr02QbfK8oqvD98/BsXyauvJkkbhyVKAVcUTmoWTjLFmGz0XEHhrICWOfoylPEd8JBQoyu1EBrUJ4PiCBDGTKlV90T+3lNW1iWNrbbkJqiyylXiKcRCqjIL2H1Yxi8Ew/1/QG1F/vJBV8114dwO0EQxqZxqo/qFaAPivdA85fdGJMB5vwbAEQ9hABXAGKKONKiV4jfUIbG0sdyTEHwXc3qoKDM0PzZ6k7M2POEikYx4Kp+xP9Woyne/UGOflLValErv5BoBCr3KMxiwhxM0HcvfK1ZT3gl82oYvYBF9Of89C4SUdEHeLfxAX55DZl1xJ8aCMo7xmm3GIs4E16wNUrTltSmnyiiBOcUlNg4CWUFO4vb0lG/OFLcw01qbRQdvSWe2ASgiCOXW4PU8mGU9KS9xeoubYUwBskgCIw8HZwxbhfGmEZTJ3PNQtxS1K6bZQTIRHcj43poPjs30bZ3pR67B4j67ieksd3BSXL6WZPPjZTE3bDMyS/75iJIkKZyM+Cu9nnRSWk9RcMQP7+VU725hyZeZOgtdbwL0Yc8MVaC8qr2zNt136dDBdiev9GGH7dWCzwcDoAIvqEHmYgFXlSpZOsfttDwlule2Lqbz9jIN5xi1ZD4ADodnWblowGC4UCqx9yq3POTE6NZfGKXG48Uv9kLc8nBmcVkgDEdF62fehkrJzTdTT1h81rGcAIwej+v2krhrqebL5pxb35U7isPTPtK+IY0fYeqGDmi0qzaOa0AhPUxUKLg4kPgi7Oi3Ehuss5r4oMYxs6oXAAALP/TsVuI6rrcTMI5Bv4z8LEbxNf+jA+Rcl/bfsO3flkyuf2JmU5NneW/wmNw9NV8Gvn+8T8FTjdwUSt4F4tPvOnQc3HuH1e2/ORqqirO2Ce4MNEk/PjG4QgiRZvv3+cCj7S8R9LO61qbvKM+4A3ke1disQLoQmFnO2U7LSQsDOFLrliBmuHyd9Pb87X72cQkKTJzSlpss3//Gr5LCmX0CaqC26k9+W+3nxXinj4OG+nYFPY5wjo3b2xLCW6fwDMKT+dB3eHnp5pmIS7Pe1/LLVLO/G49hoclnpRzjtZodB2CNBifEBXEWCMShsp31HinzPn1oYFsAvwfF6uBfRNzep8nyQWfUKQcRPMzFAzvbhejNCN5vFPyjyE/YdHH6PwWubYKCWjZIZeigntI3gkcYabZv0AizRVvOoRS5Mm/XyQcQgOwMGzPVD9ioOoTokNZPBKqKz3Ykjp1IlbQDnJHaV6jfQ0uTqJ97uhB8PfnEzcgE7mgkWcC6Le51+7AUyJ8cshYv/Umbuk6MSRRc+eiqzrtGkPVgy4PyshAugAqSTcZQlU4asljw4lK1zLWuST6mSw5NFVcvUbaMpsCLWX2xpP64e2sdsCcwO1ygPtkoh8+XFTCw+p0ROgkVENTFAIrjKdVUznSoIOh20mrsZunndd643mdaTQHDr5UQe3GYy50XWVF4d1kJtJIIL2SsAzf//ZOKiZiqqVxqJx+RSBt4+XQMAXfspmQ0N3PZ32A6AM4QsX/pur0Ds0tMQfhxbYC3UoM0eMEyr3z6zw5b4GYITJOZKfQHU5K6Zo2StUY1kmJvYJ27qnvyjjrrsMwfzzDPeXPgv6MxiBNdFrEvsw1n208dP1uFS6bD0Xa6fBN2c7sJQJQIzN73eRqDzYZm2zLUXIGllnJ4G0clQ4CCioLyPQo0RRYXrbvgnsNji4ldrOs7YXmLYbCAL6ckXZ2lgHgwYgI4L/0BwcrLAdOxjkBnxF7k0RSmydmLX02/A9GhcfLP6qvspuBx9wjdvx4r4JuYsJDz8HJY+x9mJj1N474KP7WgjQ+9VGkJ1kuWC1JEOB+AH5CUoAAfj++yrzBy+0AZg/edkC32m9eDkM3itGezo2lAjEGJTiF0XTtNA3Mi/dy7JRsgOSyWlpkSysh0HySq8bdwd0Welxo+qNURWSSX/9eYxkLLJYoo+508ksoXV7YxdduAqaSTj/ZFYXmu5nbC1dUXWPZ5Xyr3qMD1MgWez13iXus6nQu3PVNUMGaW68HrgCFUHFoRPQWcu1AzEtMVu4kq3C05q1cT8obA50qlfT2GhnREnRZ1XJ9b/XZLntxt03WShH1WlhVwkcTR/5hxNR7XuqVqAC9v71YrI3r5a5HrwAA0rka3vBlkI8eUIKPhn0c1Raqw32P0zlAZy5qlTSUZVpsYGrF2vzAZtyQX++dvDxvGENjRWI4PDOdoyzDultyFjWQtOb6AXuSXnLvVj0N+fk5NcOJvCp4jP67IpQ9S4o908H/M0rZmtlk9EnXPIODnsZ6Q92XFpjFtQ5WOV6z4RsSLvj8LCYgWr2GOh9SpeBfWW4BR5axeo/kvnsesyRulMMM9GU3pcXfIeSu7Gt8qCewpIc/ApQu9ZVhY8yZCLRyQ8HA8TzkyZmCH3awN7U25aNysJW98IbG8A+jLE0jTprBOnI3L48l3ZCKpqAaBPNjn42VzPYVy1O+6ScOiYWo6ZYNx0TIEboo7U9pzo22i5RSg3U/YM+iMzU9Pwc1App6KZLIQPmJWIUwZooVGRAjuNnfo0j7dCAhZ/Gnaz4N2Hgr3U9Z4be/e8hZIQF/WUaZkYLWIZv6xCUow2Isr1PFuAm0Pd3on1py/sJcl7dSDepmhGxvt/FhVuEsvTCT4GiRqmuyobYWZpU/jyLV9culm18Y29wzRMkP34Ci/az6GhT7KlCBAb89o0Ywt7kaqv9rLbqfhBJrI3dNESswMuoQmaD7wR4JOsFvTogewQi/IxgIWlIB1Nz+1kSmFD/w4pEUga3QznZB6ySKNBjIiWa3YYKVcFssu+/wneyb9AmZyrx23185frGTRawVkNMyhphE40Tf0YoG8mKONL5tOS4/0fmcnOQKbtC5fUy3zqcZh3h//TcKgJe6LKHYZWN60mOsEu+4nOArCuFNw9lSxUFaJHKyCRdTU1895TrqloNaZRIn7mGJiXmQFWhduR+92lR1nnPa39u9wFTNALTOY/xBwi37VMpge6f+Npyce6E6+YdaMSpcRGHQYl6tIXPjb6q/EOJIH0oGBZP2HgYcfD2YW1rHRF1/vHXIgKMTsjWZykUZrlxZ9qe/iGlV/AXj0rXSJ8nFH9lS2wlomUr/3ed4LfOhRpmyeS0PfErl1+cbvyjwvUorv3wz162ajHVXmZKevbVLMRyUNICI0IgULxA0SmTiAfgPM2pItb/4Q8pp3qwLeFAMwDdIkqldHcSYVP5B/voi3YKHdOnioF6L0ZSjHYlngVbSfIzyYZX50WhOjVCQGVreYlXtU5LTzbwrh0+RYThdkb28Wyj5LvKz0VaTiYEzTmm5kP4Jn6wZjviJZXhi1tX5nUhUb+qsxqEbXhAltmcYJrEC8AL1GoLUJgHq2VqPWEODjl7AtPywuyA+OytatMxVCeqGpbkisoXK0+zTLMnsjRVAjFtGaySzl9T0QzMx8Tpbuy48+v/CE9JpOWjIDmNzpbuPVI0mYSNRNCcLrfO6KLQcB5Qlnb8zNipdPzpzPUVCNMxGZmQaP9Pd5mOp4+mEKkHqrClDrVeX7rVIeEgqKxoaX1zun9moVfq40D5k7JI9v72Olz8rzvpcowzOwC9E5lRlAFrBKcQCQgSsJ3h9kYm+fCAv9VQZxVDbAFiYgfoQLfR1JgP5anoUo7mCSaJ5xFUWdiJ3WtCcYJtYyRnyvfafAgk/u/ya0z12WJ2NH+RTcru94VLHtGOeIHgsHeX0MU+7i4wBDo+0vajAAzVLo2yBIin0Gjs0RjOQeqrWKZgAkXkWGTFum5hyKKoZVd0NmWPdrjolRop4C4zUZblYVLPmJcpYzeWpP29aQCUCl11dK4hngJMW3S4Jps0z6tr0TXGbjhSmlXZDyNinrcpfLVRJVAq/+2obNHFnzV37y2LEOfyWBrL2QM3+zN1Fb6Dx3bvDkJ/FezNmNwhBeGwhf3FnA3SqFnD76GSuYBkPZG33akmQ9aesdBozb5TGCseYzrE4CqoN3nMVL73sl+JmFITUhs3YxB/Lm/Qmhs7WKnupwSmki/p4YM4GNSY9Ydurhn3OJM4nRO7Pqtym8hqBL3d3cLXcoPusWc0fafvNXTJUo3qmfCXr0vi+QZR3i1d2hbYpINTwDyBDYw6EcUN25z2muIwYLoLm1UsL4UNTF7/KN+W5jJjmC/iFVaDEMLPhrm8nDu1gOIW4MvUx96w9U2w1ddEIS1JO/sHEHYWRG3pFBjPAwJIWpCZNsnYYkgZH3fvM003qrpE1dTrVBFr3EKe5dsMe90xXD6OHpDfd19LmC3zjPzNtLb5TqwRyfTtOhhuC0hyEDj3YMLNA6hbetnnUzn08CI+ZMhZT0AavolT2FwFQ+mIurSJIOaTPee/GzU0IrMfTHbqDap+IR4PEEUK3XEdvfyE2w0JjDfRIAfDusPekyKiJPqG6VVneJyEPQzHokkZEoYr0ip8D9QW+cfxb6+GoDhQwASwz/FcuPR0BZA24MBOcTND/jjw0TKruAVMgQr4zR4M9JWAGEf/x8vhcC/t4CfdcKkSzEwsZn57xDO2Te38RrxwBg4oTcBkVRXw1qCiIGRuZzG1A1uYRkKMLOIUNc7rLhHfy7+GZ0BLFPoMbDFKWwJBq9yEz4WiVnTe1ter2eWhK6UFe4ebnD9/XCte57ouDhjTox7xUubDQ2RpOPFN8s3J3cU28nP/TInh7Je+68tRDO8L3WRFWy9XVoX4kivhnhCd6DfvOUAj+saTdq8kIl0HF3Dbffd8ieoZpTY8RE6JSearnmY++IbFQl6cDcxZIDDm+oHI8relGcZXaRt2regA/uW9ChYPFxBU2IolU0ZWRl2CHFj9Jf5aEs6Y3SvOVaeGzOEPxz0ZzHLU7ixH3ZmC3tY5USTBpGxSE5VTIXCTEOYTDDgJzGoBBEhDLFXUs30pPS2W8HCR37X2/1sJ0dU5ICt2JuPjJYO98Sqi1Ta+GNXthTHQFRrC82g9AuQQqR9ubrh6aGtvIFIlNwAi60PELckNnWdYFALBwnPKQtXLc9Uaj2Dmvb96LKEXDuRfcJhS6qtqrOjfRwbKcmPSDeFAtsTbO4ylnVP22u4RsvmUsBGfQ46PG3BL9VFYGaFWO8lFRW6+1H/OmdmiKF7/QH/rwDA3jtjQiRfX9NEFGG83evzujKpd7Q1QNi3+0IyRoVnXdcPtB0sl8jqHBWvI3Ag+o3rQp9TSy8MhnEJfEEVg9wOEdGmMhKWj7lKQ8ZtYfNwzqvXEmJn0PlEcCc1mpdECD3nv1jtnbVi1l/KhBCsTCEcb4gWtqCj5E8QviIwPsUfQqqwNedYLzGn4fCNCkzXmiQLqcZQMng0RpBOAuUcwSPE0/EE4MUTVCoZ7RPIVhK4E2F0RgMMXPcjFQSKamMZX3cZfe29WfJyBsdDb69hikuZvSSrUgZPHeAdDgBl4YzSAEuBq97bfsfZrVqu4eQxp8acgGzuUjLBNj4dsTPzgPBTLiqlHmI7USqXvu30wiuf14/LZrU57rdoxAbGp4rKg+u8waZvld9vM90xpJkk5Mud+aLYRr6KILrNGslBnLSEua6E5Piw/DIq8abkrOZSfKPXLcF+J6p0YSiSz67pU5bcKPy70d7U9aUnWmZDh/di6/Zm94qvnlks7tcUTR+93VtnzhIz+QXbe64exXBnbNN8m9QwkwMTNytMWIfIJzOKKp19N3u42DqUlE27C1OKUznbQfhevDiHO4oEjGskaTr/XusJGUkqy7rWii5pSe/3JpVjgO3gfUVmtIpTrqDDFE9kPW8jPnitRAJVtRksJ2Szy5eGN89AcVswRnldxdnEO+QLC/UMRC/zXYejJLSHPvt8Bta1KR5ZC61TQqTgvcJdA0faO/BH1GdpQ628+iRDnUtRfXDOsC7nt7Ut4TWPbyEK1Xix2VXGo4U34Ao6KrVbigGyE7ENcN7GZ2qRzDsEz5M8ks1+MseFIB7c/z1X9129wkY2/B+4mqGGLno3NWycDmXes75Sw2eAZpzcvnz//50H8Nymvs9VDP52Z7CMg+t+jhclS9QeICIQnsEBgUYjYczSvQOLsRh51Cm80jcn9zq/zRdmI6YNbsFKsgtE/VabcRBHjjI3P4uOHxluhVZmozc1wEhAoFe3fVOMs2NTsew8AcKfJ6Lbj0EugkIZAEwfWqkWJugv5Kbl8Sla2jIqBBu5Q/2RIO98wqD+de/bilgfNcHOz5t7NenCZChPf7Hk3uOQjgCbeQ7+Vj+SpwPlWvGjA83FarYbGNDViDXss83oFeVmPfHRO48J+EECDdGoAYBrZ7Eqlgnufrut3PxEJeJ5q6wE1ERKRV3DU3CGa09UH6+CSvbdmOykOFohVR0vAXMFLfPBY9Yqna/fGo6B2dNgpE9oeWOvwTzyRcbIIT1PWnM3PQtIwyetCFDm1T9c7OieFRAlh8MsHm0J2Ap0fTDQSrxCwBuIlON36GM0fnUE44HJS3N7nJTaJSQU7OQQx8YkK45rSX7HGrGZ2IQgn18ih5Xqt3HuLa7lruvVvG0o9beKgE6X210h3NIcWaj7Q71z4UxcVPClhykfiRl8E71PJO63fv02NtAaZZQn5bKb7Ia0C/qiTa11cuQf4tfPW8sTt/r7MeiwYV/snkCingF8Q0+bnKjzhzdy1fmOo5WHRM0mlNay8R5bpWgrrBqwsjwlR+DgwhPoFkbtqyqQZSrkro+jqunkp98Fw70ujCqCD4yZKChvQZhLi6/gZpIMHUQC4QrA+MOCY84DyW+91p0susl+fHElos5cS0Yg6E3rQl2gZJpFAEnng0rXuYSkyq2aI2W1gYIRE70FT9hVLVOnit3p5OU1WEEIbQ+1ZLtOvxzsGf6eWpZKJtvg84F5EYulTnS6vPbGsYZ7lZCMwentyvIr5QuNbe8dGsfMFzi326tfTC+PhRmYL0Wr9RlzI0Dmlc9ru3y9XOtWDZmBeXwdNIraMeRF5w1ppYvBPRmtDW1g5ckh2O7KCafN/rXekEyzcOzHNz1o7Yw/UKDTQ3f6fMoGChu39AYbgOLwFwVd1OG7EUCOsCAVjCOQVFPyQAvp/u3u+SaHwS79wufyyixZPXiMh9ea594p0ENgJbEUNDmX9m5TbllmoY8XdqXy1nOR1UeOU/fRhP8aDNrxbS9neeO7KPbL1QmUG5GqM7LT5YKe63yVOOAepKbRGEZomFZTRIDuUl8PB6nVaGN5YebjeO0UYmy7tw7Rz53uruFne85wum7rdN39oFxZh5v35+fgJkAAECfwX9Cv4V8iv0V9iv8F8RvyJ/Rf2K/hXzK/ZX3K/4Xwm/En8l/Ur+lfIr9Vfar/RfGb8yf2X9yv6V8yv3V96v/F8Fvwp/Ff0q/lXyq/RX2a/yXxW/Kn9V/ar+VfOr9lfdr/pfDb8afzX9av7V8qv1V9uv9l8dvzp/df3q/tXzq/dX36/+XwO/Bn8N/Rr+NfJr9NfYr/FfE78mf039mv4182v219yv+V//fi38Wvy19Gv518qv1V9rv9Z/bfza/LX1a/vXzq/dX3u/9n8d/Dr8dfTr+NfJr9NfZ7/Of138uvx19ev6182v2193v+5/Pfx6/PX06/nXy6/XX2+/3n99/Pr89fXr+xc=
*/