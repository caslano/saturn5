/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatter_parser.hpp
 * \author Andrey Semashev
 * \date   07.04.2008
 *
 * The header contains definition of a formatter parser function, along with facilities to
 * add support for custom formatters.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_FORMATTER_PARSER_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_FORMATTER_PARSER_HPP_INCLUDED_

#include <iosfwd>
#include <map>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/expressions/formatter.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/expressions/formatters/stream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Formatter factory base interface.
 */
template< typename CharT >
struct formatter_factory
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! The formatter function object
    typedef basic_formatter< char_type > formatter_type;
    /*!
     * Type of the map of formatter factory arguments [argument name -> argument value].
     * This type of maps will be passed to formatter factories on attempt to create a formatter.
     */
    typedef std::map< string_type, string_type > args_map;

    /*!
     * Default constructor
     */
    BOOST_DEFAULTED_FUNCTION(formatter_factory(), {})

    /*!
     * Virtual destructor
     */
    virtual ~formatter_factory() {}

    /*!
     * The function creates a formatter for the specified attribute.
     *
     * \param name Attribute name
     * \param args Formatter arguments
     */
    virtual formatter_type create_formatter(attribute_name const& name, args_map const& args) = 0;

    BOOST_DELETED_FUNCTION(formatter_factory(formatter_factory const&))
    BOOST_DELETED_FUNCTION(formatter_factory& operator= (formatter_factory const&))
};

/*!
 * Base class for formatter factories. This class provides default implementation of formatter expressions for
 * types supporting stream output. The factory does not take into account any additional parameters that may be specified.
 */
template< typename CharT, typename AttributeValueT >
class basic_formatter_factory :
    public formatter_factory< CharT >
{
private:
    typedef formatter_factory< CharT > base_type;

public:
    //! Attribute value type
    typedef AttributeValueT value_type;
    //  Type imports from the base class
    typedef typename base_type::formatter_type formatter_type;
    typedef typename base_type::args_map args_map;

    /*!
     * The function creates a formatter for the specified attribute.
     *
     * \param name Attribute name
     * \param args Formatter arguments
     */
    formatter_type create_formatter(attribute_name const& name, args_map const& args)
    {
        return formatter_type(expressions::stream << expressions::attr< value_type >(name));
    }
};

/*!
 * \brief The function registers a user-defined formatter factory
 *
 * The function registers a user-defined formatter factory. The registered factory function will be
 * called when the formatter parser detects the specified attribute name in the formatter string.
 *
 * \pre <tt>!!attr_name && !!factory</tt>.
 *
 * \param attr_name Attribute name
 * \param factory Pointer to the formatter factory
 */
template< typename CharT >
BOOST_LOG_SETUP_API void register_formatter_factory(
    attribute_name const& attr_name, shared_ptr< formatter_factory< CharT > > const& factory);

/*!
 * \brief The function registers a user-defined formatter factory
 *
 * The function registers a user-defined formatter factory. The registered factory function will be
 * called when the formatter parser detects the specified attribute name in the formatter string.
 *
 * \pre <tt>!!attr_name && !!factory</tt>.
 *
 * \param attr_name Attribute name
 * \param factory Pointer to the formatter factory
 */
template< typename FactoryT >
inline typename boost::enable_if_c<
    is_base_and_derived< formatter_factory< typename FactoryT::char_type >, FactoryT >::value
>::type register_formatter_factory(attribute_name const& attr_name, shared_ptr< FactoryT > const& factory)
{
    typedef formatter_factory< typename FactoryT::char_type > factory_base;
    register_formatter_factory(attr_name, boost::static_pointer_cast< factory_base >(factory));
}

/*!
 * \brief The function registers a simple formatter factory
 *
 * The function registers a simple formatter factory. The registered factory will generate formatters
 * that will be equivalent to the <tt>log::expressions::attr</tt> formatter (i.e. that will use the
 * native \c operator<< to format the attribute value). The factory does not use any arguments from the format string,
 * if specified.
 *
 * \pre <tt>!!attr_name</tt>.
 *
 * \param attr_name Attribute name
 */
template< typename AttributeValueT, typename CharT >
inline void register_simple_formatter_factory(attribute_name const& attr_name)
{
    shared_ptr< formatter_factory< CharT > > factory =
        boost::make_shared< basic_formatter_factory< CharT, AttributeValueT > >();
    register_formatter_factory(attr_name, factory);
}

/*!
 * The function parses a formatter from the sequence of characters
 *
 * \pre <tt>begin <= end</tt>, both pointers must not be NULL
 * \param begin Pointer to the first character of the sequence
 * \param end Pointer to the after-the-last character of the sequence
 * \return The parsed formatter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a formatter cannot be recognized in the character sequence.
 */
template< typename CharT >
BOOST_LOG_SETUP_API basic_formatter< CharT > parse_formatter(const CharT* begin, const CharT* end);

/*!
 * The function parses a formatter from the string
 *
 * \param str A string that contains format description
 * \return The parsed formatter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a formatter cannot be recognized in the character sequence.
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
inline basic_formatter< CharT > parse_formatter(std::basic_string< CharT, TraitsT, AllocatorT > const& str)
{
    const CharT* p = str.c_str();
    return parse_formatter(p, p + str.size());
}

/*!
 * The function parses a formatter from the string
 *
 * \pre <tt>str != NULL</tt>, <tt>str</tt> points to a zero-terminated string
 * \param str A string that contains format description.
 * \return The parsed formatter.
 *
 * \b Throws: An <tt>std::exception</tt>-based exception, if a formatter cannot be recognized in the character sequence.
 */
template< typename CharT >
inline basic_formatter< CharT > parse_formatter(const CharT* str)
{
    return parse_formatter(str, str + std::char_traits< CharT >::length(str));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_FORMATTER_PARSER_HPP_INCLUDED_

/* formatter_parser.hpp
1QmokUEnyqGrf+weKs2IOwIBarZT1PngzJk/kdBlEOiKFGCRCdEaKhwxv+m34RFaVcEduE1G9rfwGv23iRHBISWCMWQ4ZO2OQb+Pl28vif30NLigALj1ifrz4jM7tcTH8RO2nAcYlhvR3MLeE1uqcEUGvuxGiSCPXySwYCP4jVFBJcNH96HlWFea5THl8Ivtx85/leIzK82bebDm0MBjAfme6b7n/vybqM+iwi9f2OTUflYdZXFY/8X6ZjXrh8SCswu5UER2CXxGGwXLliPAvEcIkuellUWA+gcUYYwL0EmJQZI6R4QZ4mplMHBZeM/u5dt8XG9DU5l51/vbFekyShFRlwDblJ1Gz30nCwxEmO3Jve+EXZKOe8WeGFxTmgJihD8ebegaZ3IdZAYYioXtZb93OHAaNafBv9rrrDatE1Uf3UgZeZu5BHeA9CtZvxrf0UBLsD/o9a7i5LSwfapM/GyMnPWOAYn4mmCcDZY97QUtxLOORW/Nz8Zw7+xUnJ/Bd562KRMIeVjYivhbH/ten7odepdRKjs+G1hrzqZLQ19DD2/lOp6pOUdqd+ALiuAEUNDXCWmUHWwzVZzm/DgXLa9hXI/0ClsNPLX4Cq8MLQ5rM17im0k5uhcp0ZFbZzln7q5wimw5FsJI8N0VtPCPfYqAr1XdBt7v8wfLNzAcJBKCFJRD4jq3CcvRVXA+ppSdRE/j2HWfuOt5e79FvQ/mXS+FtJbhL+vQhTRfUTbkMwS4oLHPItRrJWqDNqt0Gmc7mQnarnnxez9NTfZu38KLR3lHPvshDGluOFH8kN04XY8Y6ZOlBxEUbf+68bOfUcVpBHSTNjmI5xmIBGpnrgcFoDWslkGQuEo8yUIO7gbJ5kniUlxMgoboRKwDHupp1eFX1T8OKS+ve8j/MKyM6bxJWZKf5XAVTBnDSinjkgHNS2Nnvp3FomTuLWnUclev+M/ryg853lqUQpEg7G7aoeeP80oj1RZYBPgkdAstuec3tLEtIPZp+X6G3yCfOuMUnWBuaSmt4Yj2JCYEAoxpZsGTxRFHKbWZlTzoXXbcMk5HsS+5XDRy02ED3DgF0S4CFh0ztbcz+jh/M6EAgkuKYMfd7dtYf0sxY3T9u3WYsZ1oknNspdfqfX4mUQV0J+Cqg7jnCvCFIX2HPVNLUYaAhzsPiIkgsLY34jVVbVhWJh7uhIV0Ldp6hbfnCpzJvR4EmgwOZ5ciKGPpPwsXkU7uyXWb/i78OV/bSpmvvW2EYRqhz6BBRrm6V24WIsNqG4y7a5ZdDMiOCPXrU4Vp/5Be+fyleIOZooto/W9LhsWvLfns8+qqS1ho+jjUJY1weL1nsTDHsFg7zd9yIo5Fo0SJne7fdvH8q9H+d7YNLipEPJKOSc13fkqIqOkEjNtjX9CJZWgxHzowfFbB7iEoyfVtlf9ocgHQssum80dQRyfVGkHY3BRbWVhCscR7H8P6GqYohx60+QnLKFIMlUeEOp0UBIZiO46xPek4rw0IcIKteUKjIX4P2DtP6ACB7Fz7Y6OgKVrZ+4NHqBCUVYqODSWK3dNqFy9iAFTkassoPooo+JCuQ9bv+cJxII/2w8x6MqGZwe2L4ii7+lrhi1xjpirlKcrkKGTIhV9PXYgkx9gHChkRoIhiDGWljAcmB/xHADP8z2Fvb70/pZjQA9lbm2VTPHkHBp5cob86eQBeoAkJfkE2Io3V+OKKlUSHDwSRSMeHEfmkjBXdpDMriVXtmMGHwsY6Km24keb2TGaULFxeMXmISzMs8T2PZr+BfQSrOSkjQ9SvH+niSEhxE9zQwLEoxyB1MYeXa+9Ok/RO6e85Tppw8QMKa3k2PQ8mCJ8tnQZCDK5WQgJ/rk8dRnGhB1CZ1yQvqKO6gTeVQBJ7O6HQDqeqvEbrVsJ0J0N6xWqAwSEHzFEorox8YOmMwLmkNC93hWbRdQRGZZu144GT9jjz6cJdL4DUoMrFzlcsXIE10TGGgC2ivoKMKQGw5K2hD5KLiJCONkmLlqczTf6lTXe9LUtefcKocn1T93SP+KcZFrGCjG4ePgLloukYWDCB0RSRUDimnvEHwykanmwZEi8nCTS0Ba8R0fj0KpArRKyCLvUnoVdiq4iX1weujnqas9CAwiBY6X1cHFiYm4PR3O51c8PmjRQZl/O10nGbY7AAqjMAEeEucGVZBcJKTTDSl7WI0Em97eVvKBl9JN+WTUjRalbt9pQ2RM2nUlEL8+5IDIFaaECjixXVnrV1h4m7WC2oozcjDyp6BYwOUWNPOUsqdq53FTODnA2fCkqt2j8hXHM+KGoK6kOVt5MfH3sSPoo66VS35bSW+kU7XIC194FIzO8fwaj+AP3BgLdweN9+HwjfiAfh9g/wgKb8XB/y4sDX/HGnkvpaw2+g+7lZWR3l3dT/PFh8c3z1/4NPvq3Sbk4BYUyLhIqNG0SiVg6yXNu6/RczPHznON/9En89VQdei8oLvR914BLa1lon6wrkUj/pACx2WjXghoS8j/mfaFWTr5/VK6mg5KKkYHYC8dChs1VFJBo5NpM7SAJSpMZqbQ4CFRVPUjp6RPZJI2N9ERYO2JhQjVcvXGLT241yTbB6NMSvLNil+TCN0yKAh1PzPq5S7ZKYJj/Cx8lO2GzTUepaUYFcvY6KJ6gm6D90BjvykYmEhh4RGoynC2btvWicz4Fki3c3IMa9WtsHcbA06JGlOGKNIX6bSwnYvJEDxa1a9hOGFQuWhK+p4zNbgmeBBilaIXlyNUFbQUE4oaI3r+se7IZi2fUq1tvOTjeaWjyi9Wg4pzlqRvtUcN4uN40upAPUmvxCUUajDUmedCw5eA8OZFA4ikeSTQ+KVkwAm4yFFbuClbRSEDASSU6RknLKDMhgdPdDlje34X22SsP2XccTMvbgxELkGJ4bryg+ZaGWICIXXXmB7e2eH1joXOd6B6dfMHkJraGpvjoAg98wSX1elWmBeMXAFGXZ4YZ/VZTIo/rdDJtUFSyz17oVYYHM/C1Qm4VoxTZ502F2PKkEw+aZxYJJ9voPMyKnn+P/bL3E0lc5tiLn5yhtG3b8Zs4wR8eqj+VuRrEcJqRcoDekxg/8ZDIphLVW2EIulvaPmXZ5SDHJicE5l9SOKx0kB7elXOiDLzEH/80Q7RmaD63XQHnsJ1E53fi0VRa18rVtVSAjerAtvU/NfCjtywacG07Psl05wdmf23IYwcs95dAMALw17JwM47jv8stT8nuOhItOo4ZFS3ubJ1UZhs9iol3zBDekmRG4Q1qDT5OKa9jPGe/+Z4XMeC6bd9b6sO2DKHxaHjI0NW7/FumGEIsYD0mnEkVEXn23qS3dnS+CJdVxCGZebdrZuap0I2RbTSycTulYODtCZ3sVoGTYwltVgDS1qNIioUnKd3ly/sBGZ9p97Gbpe5yqxgbTDtafurj1vTxuk+h7ZnU6LQshZ5WvTOIgHqpXk0l6KUaYfF6QIQUbrJ2Zh4ei8ty+1UG5/t9bbtiVfX6mh1FdCKj/yXW2x2rDnujLjV+wAIfdO04s/bhGi/8zmPsOtBzBgHCz4V1bZZy7+wXCr+Ev+bSF9cP1nVsZejjvTUcgn6jkhnRchQ55gq82IP17COZ78Py8+swD3LbsubU4tDUw0Pui2Zn0A/tXDTvUQ43KfwMgZlLdFOKr5HCcMHk0BzTctey1L9wYFiRJVIVEMs6CjYt81fYfd4O13065YWZUHpa1Dm5ryiW6x71pxRqUVjmdPqXSsqimtFrXN1KPbDplsxUYfGUkWRod3rsPCVI3zbJTV7S5F6wg/ifwu44C7HGu8LLkzgmcQbRY0jzhnmWB5glx7uJKq3swD7K31cfXy2ezp5QoFAG0qb5z46XW1K1EllILKk//3NXi8/tftioDhBdtLzuLAlBQIdaNVu01pxULdkxWRKwUckt0JKI6MOWSHYaPwS7Jk/3q3D8oNcwNzN8IXq+9bULqfK1LO3l4yYvaDh7lYpZ9BpotAE+5Wrr6oiQXrNqVRxyLidiPWimRd9ujA9Lo2C3guN3dxyG+6/SIG6o1ubO99ulxPb6Prd9x7Sv2DqrQYHLAbSX9QKiiRELK+a46faDmFcVwfMPVIehCnYAgqEQroPwQ2b7UB43AYRS2ECjMXQ/n8aHtL046/1mzWCyNNw9lsaZtb1yOP8L7XQQUGfVWtQj4kD6M1e72i9Ueyr36XvM+x1ZvVrevoHKyld38xO1vC9u2UG2pmyxxkZU0Kf3s7n4aBn2nIr2Fx8X4o9/gl3c8du1Q1f4UMRCOHtl8J5HeBVo8iNM9unQjpMbweD8EizsBGfWTr+Q/us3bQXifrX2gJIBx/0MrZ6kv1yQ6GJwUpvxV0iXOFMX0ah2/eiH3ylc8QdvWQdO73v0bI57nq+lg89YwmG5MkieV9UtDjZTXSq4WrzQzPFLyTCQ77VPAbW3ZwvZvV2Z/tzQwFI/e1QJK3IUplXQj73dZKqVNB4HotdNumIslr9FgPj98X8Zqy3M9RJWNmpQR+KgCNTVNloN2X74NP/r78LMdU1hVcOkROR93tOdst+vn1yk5u6B96mXQoXYrN5Sb+IRXi4h2rJSF47xw0Y5PW++uIz0DY9RnLtzgmb4K9JNzB5lL3/3IOdorvutlDMicdNbf5NwPncpgk+kqRECmAPqOAj7qSwvuzn33yzM0TVeqX6aD+Otw4QRqa+fcggCgYB/O9fWN2Z0HaNVV8pHKJxThZ23RwZYUvuSlC3iF5x3kklxH7EJ2h9NvTjQms1uN8cUYcYrTO6mctf/hXXoDwCqcGnkHB4AZMd9smDUDgF2wt2f1yPdhckteoHR2Sn7i1S/UypF4NPf3JdC23Vekx9AaBLv35yTtBSMwx3Zp3cxFR0SBZ4xMIHGGLbo/otNR7Gk4wIiEdUWFW7YJadzg72Cuz0653I5REyYUBKwZqVpN9i+Gs4j59rRQvkyq79fZbzGTJHcmNq3NBcE/m2yZGIng6wIauzY6sFGrx1sgU7prXtdBvJzFudZsvrnJGaU5iuk+8nrpTuI6JGRWY+TdSt2C6H9QnLSxZD8n6EZLnHawulFIunjkQV/70pPV8VkBc0fHd8afanYHkgwE9gNEzxXr8QYBgE4cSEgkxEw40IhkUNCU8IS4NO1T/OeFeDtS8qMzAMHVDynNVqEtOYtvf0IuqNpva5XgfiQTZodlkUZl8Z8UtehB5/TAJkm7jPCFOXQFnGNL3MxXW8x7CYgCxFRTM55pB1PmXQUh1M+aXvoDOEytDdxcvXV8HQsKZEoQIJ9UCiKnay+nm4s8zGg7J/gsmxD9WZs8R3Hj7fuL9FXaU7zSE1Slk1H/JkT1jiq+HU+itdvEj+UFYi+ltCBCao/SDDTDGGcS/uOqKj6XHMruRc8MAo2BPLdFSWr7CBYuMGdvAr6UuuirPQlc2eVD5ZZXlgeoJmOIVhdWHDEwpJiCt3pDo8pgqzM2ZN7bfDRnaebub/hY6SxBBxVjv1RYQ1NQ7zo2cJEKh+DedqQtTnbzO2o0FCcMsgic0bKQ7c1zH7CW6nZGCtAgFJgAG8eoHczQ56TLHuzDAj1KSZ8W6dcQgayvhOzvquUTuMncl3FadmUk0zkqOAZQ7HcRsKvwxmodewiZ11TBjLMwYZzB9kneizFQlNIizOlBuDlBZlSVdrE4gzW7ENhA+bHU+e5b3JE+LCbxDRha5Cbp0D+LjsvUVGjEnR5nzUR9vQW+FLiA4CW3N9iJoKucBsjWjn8+mk0LXSFEsruoLt+SbKxu0kz+RjVLF6hB1LUYq1h3tSk/HbhahoI4muV6KzgaP5oRwCpFJsNSGsPEGigz2+l0YAlcVpAqHOuJ4670htPLlcZVLoOWR6y5XMPSZWFr97mQFYu3o0mub8Dhx3MH6E060IbZzaIA9ERJm0xnFvKH56mCS148zSKr/x18V2ne3REYxpgeNAQOjqpt5fy7Nh3OZnxyCykmbFPRwFWNv+Ri90Dsl0mbCqVoLI9bovHKVmwaardowh/CzPhlS7WmPnblE0N47EkLs9TUKA0WuaqNUmS6zcCclupT2KEjWgq0NppMANddWkTiYswfy8JtlcQdQhDxSRPRzIrxk9lCJed+AABLNq6cLPtk2S5I2m0CWx3bNCaUbP6G7ZmKJpE0coeZnfinp4H+gsLtj4prmbCw2Q8hgymnv6/zRdWE2SCIz89ZbC9VBtqn1z+uKUavg3K/dEXiDoRWVFQG1HSkg+ikZ8rNVfKQCo/G1u+sY3JV8TQZk8NRJAGliOyzrlE8wBOclm/Cbkiz59VnuS90tWL21maKzPF294tKtngMBtISqV9iZyj+kb7ukdtc8rwY5WI/t7srb+eT2sl4qacWtAeLJAVZVTbVFOL4YVAkjbuuCRU33zfAsI7Xwl76E4R29YGcd2JKkLXT2U+44e0dQhZZ2MSpi/PJSHsUISJlKpdf5nk1g09cMGVi3XfJCCnnuCDKqN1S1roqGC3xN0w6jvMbhSxbxfqqM1RpmP9m0E9tlnjXw5Yhr0RV9NBp4tB4MubwcoQjHpemBHxqj9U4Wxh7VYTslXEQQVcB2yoFEJDK0WUARE30/GfzLQT6kV24ZouZ21M23+gURIAWwpHhNyJE8V8AM1hK9X3KKsy0IV4Hq9NM5WXImRRMqLWHNNHdCxqg0w2oKO0/gyWI3DZOP7/mTIgz1B0U60pqmi39M6GsDRuoged6Ei8lwe6v/G1K2RG0wI2JTjL4E8M6mhIdWTje44+eYXYKL7SIF/jU2RvnpISvVvMQmZKSFNHiskF2Ok7kPr06H8++HjrDwsh8gQU8Szu+vIXEEAtKZrVUFDbVNFJAage44XYjbW5gGa3IKvSFxnTug3LXBZnXnc3EvBGOTvwQqM2mstu8a2wGa/U9dtNSGIFMaAq/w1GxRb7wFMaLpFRbDGhEWE1m8o0Tm2IJ8CsU6VP3q5szwUOPjgBeNtF1DAnNZvnWH/0LdQe5w4dip6u02eBpD2BKVW/hfTRDk99ZRSYrxE0dOaZNmSgf48+YFoxFp05KuSQ4Jtq4mZM8OmVgNTOZmIQEt8JMdOxtr+FncuhqTouhW8mfqpYs5ZrWvR3JvPHU/RGaxSSHDQVHUP4hmDh5wVokAk/mq31xU3dHuIEuxYkHTXduMXrySAzO8tpeezMbdujYUk1JsQLH7KJE8CSqjsYVKZuNflv1MwQ7gwJsVt1er4w84rNZ1EtqQd8V7nA1eGtubg2J1WzUagyW44ReIfO7Gr4czojNDAEYIteb4Tli7RjxtLhfIU6gnbaUAL2s/bSthfLdmHbfejyrBT9Qk9u4KYL/VqF815SYjKl4DucRRpT9hoA+NT+ikvQ8+PBuwBqnavk/dny9XbVmYlyTuqSfZU9mD297mIBQays7nNEmgjLEOJHuCMDF6zj87mOQ84XjVvgkyVJ8jVqiL08SM7IhSMC00hVO0W9Qprf+3elVAl45VhLieONk55kWXYgKNn90CTnK4oga9yz4LaH3G6BMbB7cguvl7pI7SrxOooSJMnskdAweOsC3AmpSC391WJoOURdqDUYHDEaLVbgrLkuyRDmvcXiOSSrbjcC3eGNioCeLpySfyMw+Q+RUiwpi7SChY8z8i8Ct
*/