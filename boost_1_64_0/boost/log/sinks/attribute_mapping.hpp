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
CcwAJ4M54BTwIXAqeAicDr4FvgC+C84APwDvAc+BheAq9PNM0Ib+mw32AOeAheBccDk4D9wPzgeLwAXg9+BCsLKP/TgQ1I/jwCXg7eBSMBlcBq4A7wU3gMvBk+B94HlwBSgqYR4drAreD7YAHwDzwQfBmeAqcAu4GnwTfATE1LFYAw4G14JDwcf184FP6PUD1+n1Btfr9QY3gJWrYP4G7Ac+DQ4BXwD5uuZvO/V1/Qni6fyU45fI7wT6xpK/U3uB4+/k8b6Lr+vd4ChwD7gA3As+Db4GxiCTg+Br4OvgUJz4EHgZPAzO8sA8Cfgi+AZf30fBHuBxMAU8Cfa02fN5FNTzifO05/M6qOdzp5c9n6XgG3ydIx+6zt8HG4IfgkPAj8AcsBjcDp4F4/XvGtRqAUT/DdDcNhaxoK1FHO1mE3M6Wmhf2mqE7YNchlRBB8bMNPepmc50pjOd6a7dWSHZf9z6f1heH52eZ8cNs/3/bCTmKHn+Fe935EZCNP4t7tCaeE+9QmvFOw/pntS3W9+k0Xnp6bRGCRNW8E+Rc3xDKN7tyE9TzrsiH57nHEZh6bXwjuSLebMgnRX/FvpN/H2mn7c6zovvKFn2Un5nfw/iyd8qgSh7kXPZx+TlTBI3ybLnF+Tx2qQQ8AzFPSIaIuc+kA0QVT2Qp9I+QRi3w3sU/raIwb8DIZsgqrl/Yz65VNm89AJRNmd7yzf2Ncs24Su/Z1PIrxXasLKoJL95sW6Nv4lbUHgWSu4hekEcbV2Iln0uUp9zxd+Ktq6itk3AbY12Yj9vFzsEaCFpO2IBd9hV7oPvuQ+KvynXB0mpGOFI79oXcu3DJUpzmVa3d4WMhhxR9wfyV/dHLe6PTyj8imhAWimEUu8o+4Tzct8n40v18Aj0SZDsk/vIr60IddMnSRQ+kfpkkKJPNkfe+D5xXBcRNkGuCWfUGBJWE/7fOvVJdvok2ReyzlIfT3FD+VgTfXBstHexwddQfrXrhXyc1mX6egpyLThCPKQoEd+y5cqVlD6Zx0kk9e3ozJQx+YpxwGnpiunrF4V6n4JsQgdVFp4WDz9PS5XqVtcyc53L93M25XWzCKUVOf38al2jLY9I6gcqo1M/FHnxOlSIDTIUUq8Z5p/L6puXPjE9Lz9duNpIkeNsH8XtifpZVfXnvDRXeyxSf7SNwtsqx71MK6+h/IyprMeib0EKr8y6EdxH6NhLqaPkvOhayKVap1I6i35v0MNYL2TBXyU8trzhV4nrjatMPlM+pfAItGVV9nOkCUE7+pUbc96qflHYU/FW2F2RNlao7o57WzW7XVzOuCd/Y/eAvJ2IfO37qPLTU5NSMqGQRC8SRfl7m2y7BErTTNWHyE95L1P1GeIq71WyzxIpPEaO+XNh9My95ja7lvtMKRhtuf75yhnk//MH+73/OmPm8ltOf5eSMbweJh5/Jf/u/VLDzg8tbeyTG158T4urezHX46H7r73tdWvVeT89F7ntRGT0o73au5/37Efzqou7jbrlu9m/7j42IGFA9qK9u7A2yarHf3fasSO/fntv6ZTFtYNfWDIcZQ+g8u+4d/xfGi/ZOfps8D82fRtdJx4tatP9g6qk9Xx7wOWshvUeXDh9yjPfYo7Eovt3iEj/7u4RYxp5TBxTefrn6cfQ5uR/8r7zRzqnZzw285upo56PfBp5vCx0/5LOt4ZPiF62ZE9I22U+xb9cwpwmlSfs1elLfq47dPf8yb22zntl81HMKVF5nn5sfdfZVo9fOqe2fCb7XMsU1Jf8Ly+JeLjJa9k/z7yy7qVZ62o/S3OM8M8typr3bcnNR46t6BLe+Hwi2u0otefBKgG7kuLjD7S3NWo1vla3Gpg=
*/