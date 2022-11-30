/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_extraction.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * The header contains implementation of tools for extracting an attribute value
 * from the view.
 */

#ifndef BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_HPP_INCLUDED_

#include <boost/mpl/vector.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/attributes/value_extraction_fwd.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/utility/value_ref.hpp>
#include <boost/log/utility/type_dispatch/static_type_dispatcher.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace result_of {

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 *
 * The metafunction results in a type that is in form of <tt>T const&</tt>, if \c T is
 * not an MPL type sequence and <tt>DefaultT</tt> is the same as <tt>T</tt>,
 * or <tt>value_ref< TypesT, TagT ></tt> otherwise, with
 * \c TypesT being a type sequence comprising the types from sequence \c T and \c DefaultT,
 * if it is not present in \c T already.
 */
template< typename T, typename DefaultT, typename TagT >
struct extract_or_default
{
    typedef typename mpl::eval_if<
        mpl::is_sequence< T >,
        mpl::eval_if<
            mpl::contains< T, DefaultT >,
            mpl::identity< T >,
            mpl::push_back< T, DefaultT >
        >,
        mpl::if_<
            is_same< T, DefaultT >,
            T,
            mpl::vector2< T, DefaultT >
        >
    >::type extracted_type;

    typedef typename mpl::if_<
        mpl::is_sequence< extracted_type >,
        value_ref< extracted_type, TagT >,
        extracted_type const&
    >::type type;
};

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 *
 * The metafunction results in a type that is in form of <tt>T const&</tt>, if \c T is
 * not an MPL type sequence, or <tt>value_ref< T, TagT ></tt> otherwise. In the latter
 * case the value reference shall never be empty.
 */
template< typename T, typename TagT >
struct extract_or_throw
{
    typedef typename mpl::if_<
        mpl::is_sequence< T >,
        value_ref< T, TagT >,
        T const&
    >::type type;
};

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 *
 * The metafunction results in a type that is in form of <tt>value_ref< T, TagT ></tt>.
 */
template< typename T, typename TagT >
struct extract
{
    typedef value_ref< T, TagT > type;
};

} // namespace result_of

namespace aux {

//! The function object initializes the value reference
template< typename RefT >
struct value_ref_initializer
{
    typedef void result_type;

    value_ref_initializer(RefT& ref) : m_ref(ref)
    {
    }

    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        m_ref = RefT(arg);
    }

private:
    RefT& m_ref;
};

//! The function unwraps \c value_ref, if possible
template< typename T, typename TagT >
BOOST_FORCEINLINE typename boost::enable_if_c< mpl::is_sequence< T >::value, value_ref< T, TagT > >::type
unwrap_value_ref(value_ref< T, TagT > const& r)
{
    return r;
}

template< typename T, typename TagT >
BOOST_FORCEINLINE typename boost::disable_if_c< mpl::is_sequence< T >::value, T const& >::type
unwrap_value_ref(value_ref< T, TagT > const& r)
{
    return r.get();
}

} // namespace aux

/*!
 * \brief Generic attribute value extractor
 *
 * Attribute value extractor is a functional object that attempts to find and extract the stored
 * attribute value from the attribute values view or a log record. The extracted value is returned
 * from the extractor.
 */
template< typename T, typename FallbackPolicyT, typename TagT >
class value_extractor :
    private FallbackPolicyT
{
public:
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;
    //! Attribute value types
    typedef T value_type;
    //! Function object result type
    typedef value_ref< value_type, TagT > result_type;

public:
    /*!
     * Default constructor
     */
    BOOST_DEFAULTED_FUNCTION(value_extractor(), {})

    /*!
     * Copy constructor
     */
    value_extractor(value_extractor const& that) : fallback_policy(static_cast< fallback_policy const& >(that))
    {
    }

    /*!
     * Constructor
     *
     * \param arg Fallback policy constructor argument
     */
    template< typename U >
    explicit value_extractor(U const& arg) : fallback_policy(arg) {}

    /*!
     * Extraction operator. Attempts to acquire the stored value of one of the supported types. If extraction succeeds,
     * the extracted value is returned.
     *
     * \param attr The attribute value to extract from.
     * \return The extracted value, if extraction succeeded, an empty value otherwise.
     */
    result_type operator() (attribute_value const& attr) const
    {
        result_type res;
        aux::value_ref_initializer< result_type > initializer(res);
        if (!!attr)
        {
            static_type_dispatcher< value_type > disp(initializer);
            if (!attr.dispatch(disp) && !fallback_policy::apply_default(initializer))
                fallback_policy::on_invalid_type(attr.get_type());
        }
        else if (!fallback_policy::apply_default(initializer))
        {
            fallback_policy::on_missing_value();
        }
        return res;
    }

    /*!
     * Extraction operator. Looks for an attribute value with the specified name
     * and tries to acquire the stored value of one of the supported types. If extraction succeeds,
     * the extracted value is returned.
     *
     * \param name Attribute value name.
     * \param attrs A set of attribute values in which to look for the specified attribute value.
     * \return The extracted value, if extraction succeeded, an empty value otherwise.
     */
    result_type operator() (attribute_name const& name, attribute_value_set const& attrs) const
    {
        try
        {
            attribute_value_set::const_iterator it = attrs.find(name);
            if (it != attrs.end())
                return operator() (it->second);
            else
                return operator() (attribute_value());
        }
        catch (exception& e)
        {
            // Attach the attribute name to the exception
            boost::log::aux::attach_attribute_name_info(e, name);
            throw;
        }
    }

    /*!
     * Extraction operator. Looks for an attribute value with the specified name
     * and tries to acquire the stored value of one of the supported types. If extraction succeeds,
     * the extracted value is returned.
     *
     * \param name Attribute value name.
     * \param rec A log record. The attribute value will be sought among those associated with the record.
     * \return The extracted value, if extraction succeeded, an empty value otherwise.
     */
    result_type operator() (attribute_name const& name, record const& rec) const
    {
        return operator() (name, rec.attribute_values());
    }

    /*!
     * Extraction operator. Looks for an attribute value with the specified name
     * and tries to acquire the stored value of one of the supported types. If extraction succeeds,
     * the extracted value is returned.
     *
     * \param name Attribute value name.
     * \param rec A log record view. The attribute value will be sought among those associated with the record.
     * \return The extracted value, if extraction succeeded, an empty value otherwise.
     */
    result_type operator() (attribute_name const& name, record_view const& rec) const
    {
        return operator() (name, rec.attribute_values());
    }

    /*!
     * \returns Fallback policy
     */
    fallback_policy const& get_fallback_policy() const
    {
        return *static_cast< fallback_policy const* >(this);
    }
};

#if !defined(BOOST_LOG_DOXYGEN_PASS)
#if !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#define BOOST_LOG_AUX_VOID_DEFAULT = void
#else
#define BOOST_LOG_AUX_VOID_DEFAULT
#endif
#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param name The name of the attribute value to extract.
 * \param attrs A set of attribute values in which to look for the specified attribute value.
 * \return A \c value_ref that refers to the extracted value, if found. An empty value otherwise.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
inline typename result_of::extract< T, TagT >::type extract(attribute_name const& name, attribute_value_set const& attrs)
{
    value_extractor< T, fallback_to_none, TagT > extractor;
    return extractor(name, attrs);
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param name The name of the attribute value to extract.
 * \param rec A log record. The attribute value will be sought among those associated with the record.
 * \return A \c value_ref that refers to the extracted value, if found. An empty value otherwise.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
inline typename result_of::extract< T, TagT >::type extract(attribute_name const& name, record const& rec)
{
    value_extractor< T, fallback_to_none, TagT > extractor;
    return extractor(name, rec);
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param name The name of the attribute value to extract.
 * \param rec A log record view. The attribute value will be sought among those associated with the record.
 * \return A \c value_ref that refers to the extracted value, if found. An empty value otherwise.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
inline typename result_of::extract< T, TagT >::type extract(attribute_name const& name, record_view const& rec)
{
    value_extractor< T, fallback_to_none, TagT > extractor;
    return extractor(name, rec);
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param value Attribute value.
 * \return A \c value_ref that refers to the extracted value, if found. An empty value otherwise.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
inline typename result_of::extract< T, TagT >::type extract(attribute_value const& value)
{
    value_extractor< T, fallback_to_none, TagT > extractor;
    return extractor(value);
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param name The name of the attribute value to extract.
 * \param attrs A set of attribute values in which to look for the specified attribute value.
 * \return The extracted value or a non-empty \c value_ref that refers to the value.
 * \throws An exception is thrown if the requested value cannot be extracted.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
inline typename result_of::extract_or_throw< T, TagT >::type extract_or_throw(attribute_name const& name, attribute_value_set const& attrs)
{
    value_extractor< T, fallback_to_throw, TagT > extractor;
    return aux::unwrap_value_ref(extractor(name, attrs));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param name The name of the attribute value to extract.
 * \param rec A log record. The attribute value will be sought among those associated with the record.
 * \return The extracted value or a non-empty \c value_ref that refers to the value.
 * \throws An exception is thrown if the requested value cannot be extracted.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
inline typename result_of::extract_or_throw< T, TagT >::type extract_or_throw(attribute_name const& name, record const& rec)
{
    value_extractor< T, fallback_to_throw, TagT > extractor;
    return aux::unwrap_value_ref(extractor(name, rec));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param name The name of the attribute value to extract.
 * \param rec A log record view. The attribute value will be sought among those associated with the record.
 * \return The extracted value or a non-empty \c value_ref that refers to the value.
 * \throws An exception is thrown if the requested value cannot be extracted.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
inline typename result_of::extract_or_throw< T, TagT >::type extract_or_throw(attribute_name const& name, record_view const& rec)
{
    value_extractor< T, fallback_to_throw, TagT > extractor;
    return aux::unwrap_value_ref(extractor(name, rec));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param value Attribute value.
 * \return The extracted value or a non-empty \c value_ref that refers to the value.
 * \throws An exception is thrown if the requested value cannot be extracted.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
inline typename result_of::extract_or_throw< T, TagT >::type extract_or_throw(attribute_value const& value)
{
    value_extractor< T, fallback_to_throw, TagT > extractor;
    return aux::unwrap_value_ref(extractor(value));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \note Caution must be exercised if the default value is a temporary object. Because the function returns
 *       a reference, if the temporary object is destroyed, the reference may become dangling.
 *
 * \param name The name of the attribute value to extract.
 * \param attrs A set of attribute values in which to look for the specified attribute value.
 * \param def_val The default value
 * \return The extracted value, if found. The default value otherwise.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT, TagT >::type
extract_or_default(attribute_name const& name, attribute_value_set const& attrs, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< T, DefaultT, TagT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& >, TagT > extractor(def_val);
    return aux::unwrap_value_ref(extractor(name, attrs));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \note Caution must be exercised if the default value is a temporary object. Because the function returns
 *       a reference, if the temporary object is destroyed, the reference may become dangling.
 *
 * \param name The name of the attribute value to extract.
 * \param rec A log record. The attribute value will be sought among those associated with the record.
 * \param def_val The default value
 * \return The extracted value, if found. The default value otherwise.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT, TagT >::type
extract_or_default(attribute_name const& name, record const& rec, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< T, DefaultT, TagT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& >, TagT > extractor(def_val);
    return aux::unwrap_value_ref(extractor(name, rec));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \note Caution must be exercised if the default value is a temporary object. Because the function returns
 *       a reference, if the temporary object is destroyed, the reference may become dangling.
 *
 * \param name The name of the attribute value to extract.
 * \param rec A log record view. The attribute value will be sought among those associated with the record.
 * \param def_val The default value
 * \return The extracted value, if found. The default value otherwise.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT, TagT >::type
extract_or_default(attribute_name const& name, record_view const& rec, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< T, DefaultT, TagT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& >, TagT > extractor(def_val);
    return aux::unwrap_value_ref(extractor(name, rec));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \note Caution must be exercised if the default value is a temporary object. Because the function returns
 *       a reference, if the temporary object is destroyed, the reference may become dangling.
 *
 * \param value Attribute value.
 * \param def_val The default value
 * \return The extracted value, if found. The default value otherwise.
 */
template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT, TagT >::type extract_or_default(attribute_value const& value, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< T, DefaultT, TagT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& >, TagT > extractor(def_val);
    return aux::unwrap_value_ref(extractor(value));
}

#if defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)

template< typename T >
inline typename result_of::extract< T >::type extract(attribute_name const& name, attribute_value_set const& attrs)
{
    value_extractor< T, fallback_to_none > extractor;
    return extractor(name, attrs);
}

template< typename T >
inline typename result_of::extract< T >::type extract(attribute_name const& name, record const& rec)
{
    value_extractor< T, fallback_to_none > extractor;
    return extractor(name, rec);
}

template< typename T >
inline typename result_of::extract< T >::type extract(attribute_name const& name, record_view const& rec)
{
    value_extractor< T, fallback_to_none > extractor;
    return extractor(name, rec);
}

template< typename T >
inline typename result_of::extract< T >::type extract(attribute_value const& value)
{
    value_extractor< T, fallback_to_none > extractor;
    return extractor(value);
}

template< typename T >
inline typename result_of::extract_or_throw< T >::type extract_or_throw(attribute_name const& name, attribute_value_set const& attrs)
{
    value_extractor< T, fallback_to_throw > extractor;
    return aux::unwrap_value_ref(extractor(name, attrs));
}

template< typename T >
inline typename result_of::extract_or_throw< T >::type extract_or_throw(attribute_name const& name, record const& rec)
{
    value_extractor< T, fallback_to_throw > extractor;
    return aux::unwrap_value_ref(extractor(name, rec));
}

template< typename T >
inline typename result_of::extract_or_throw< T >::type extract_or_throw(attribute_name const& name, record_view const& rec)
{
    value_extractor< T, fallback_to_throw > extractor;
    return aux::unwrap_value_ref(extractor(name, rec));
}

template< typename T >
inline typename result_of::extract_or_throw< T >::type extract_or_throw(attribute_value const& value)
{
    value_extractor< T, fallback_to_throw > extractor;
    return aux::unwrap_value_ref(extractor(value));
}

template< typename T, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT >::type extract_or_default(
    attribute_name const& name, attribute_value_set const& attrs, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< T, DefaultT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& > > extractor(def_val);
    return aux::unwrap_value_ref(extractor(name, attrs));
}

template< typename T, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT >::type extract_or_default(
    attribute_name const& name, record const& rec, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< T, DefaultT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& > > extractor(def_val);
    return aux::unwrap_value_ref(extractor(name, rec));
}

template< typename T, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT >::type extract_or_default(
    attribute_name const& name, record_view const& rec, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< T, DefaultT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& > > extractor(def_val);
    return aux::unwrap_value_ref(extractor(name, rec));
}

template< typename T, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT >::type extract_or_default(attribute_value const& value, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< T, DefaultT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& > > extractor(def_val);
    return aux::unwrap_value_ref(extractor(value));
}

#endif // defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param attrs A set of attribute values in which to look for the specified attribute value.
 * \return A \c value_ref that refers to the extracted value, if found. An empty value otherwise.
 */
template< typename DescriptorT, template< typename > class ActorT >
inline typename result_of::extract< typename DescriptorT::value_type, DescriptorT >::type
extract(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, attribute_value_set const& attrs)
{
    value_extractor< typename DescriptorT::value_type, fallback_to_none, DescriptorT > extractor;
    return extractor(keyword.get_name(), attrs);
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param rec A log record. The attribute value will be sought among those associated with the record.
 * \return A \c value_ref that refers to the extracted value, if found. An empty value otherwise.
 */
template< typename DescriptorT, template< typename > class ActorT >
inline typename result_of::extract< typename DescriptorT::value_type, DescriptorT >::type
extract(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, record const& rec)
{
    value_extractor< typename DescriptorT::value_type, fallback_to_none, DescriptorT > extractor;
    return extractor(keyword.get_name(), rec);
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param rec A log record view. The attribute value will be sought among those associated with the record.
 * \return A \c value_ref that refers to the extracted value, if found. An empty value otherwise.
 */
template< typename DescriptorT, template< typename > class ActorT >
inline typename result_of::extract< typename DescriptorT::value_type, DescriptorT >::type
extract(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, record_view const& rec)
{
    value_extractor< typename DescriptorT::value_type, fallback_to_none, DescriptorT > extractor;
    return extractor(keyword.get_name(), rec);
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param attrs A set of attribute values in which to look for the specified attribute value.
 * \return The extracted value or a non-empty \c value_ref that refers to the value.
 * \throws An exception is thrown if the requested value cannot be extracted.
 */
template< typename DescriptorT, template< typename > class ActorT >
inline typename result_of::extract_or_throw< typename DescriptorT::value_type, DescriptorT >::type
extract_or_throw(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, attribute_value_set const& attrs)
{
    value_extractor< typename DescriptorT::value_type, fallback_to_throw, DescriptorT > extractor;
    return aux::unwrap_value_ref(extractor(keyword.get_name(), attrs));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param rec A log record. The attribute value will be sought among those associated with the record.
 * \return The extracted value or a non-empty \c value_ref that refers to the value.
 * \throws An exception is thrown if the requested value cannot be extracted.
 */
template< typename DescriptorT, template< typename > class ActorT >
inline typename result_of::extract_or_throw< typename DescriptorT::value_type, DescriptorT >::type
extract_or_throw(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, record const& rec)
{
    value_extractor< typename DescriptorT::value_type, fallback_to_throw, DescriptorT > extractor;
    return aux::unwrap_value_ref(extractor(keyword.get_name(), rec));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param rec A log record view. The attribute value will be sought among those associated with the record.
 * \return The extracted value or a non-empty \c value_ref that refers to the value.
 * \throws An exception is thrown if the requested value cannot be extracted.
 */
template< typename DescriptorT, template< typename > class ActorT >
inline typename result_of::extract_or_throw< typename DescriptorT::value_type, DescriptorT >::type
extract_or_throw(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, record_view const& rec)
{
    value_extractor< typename DescriptorT::value_type, fallback_to_throw, DescriptorT > extractor;
    return aux::unwrap_value_ref(extractor(keyword.get_name(), rec));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be extracted.
 *
 * \note Caution must be exercised if the default value is a temporary object. Because the function returns
 *       a reference, if the temporary object is destroyed, the reference may become dangling.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param attrs A set of attribute values in which to look for the specified attribute value.
 * \param def_val The default value
 * \return The extracted value, if found. The default value otherwise.
 */
template< typename DescriptorT, template< typename > class ActorT, typename DefaultT >
inline typename result_of::extract_or_default< typename DescriptorT::value_type, DefaultT, DescriptorT >::type
extract_or_default(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, attribute_value_set const& attrs, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< typename DescriptorT::value_type, DefaultT, DescriptorT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& >, DescriptorT > extractor(def_val);
    return aux::unwrap_value_ref(extractor(keyword.get_name(), attrs));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \note Caution must be exercised if the default value is a temporary object. Because the function returns
 *       a reference, if the temporary object is destroyed, the reference may become dangling.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param rec A log record. The attribute value will be sought among those associated with the record.
 * \param def_val The default value
 * \return The extracted value, if found. The default value otherwise.
 */
template< typename DescriptorT, template< typename > class ActorT, typename DefaultT >
inline typename result_of::extract_or_default< typename DescriptorT::value_type, DefaultT, DescriptorT >::type
extract_or_default(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, record const& rec, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< typename DescriptorT::value_type, DefaultT, DescriptorT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& >, DescriptorT > extractor(def_val);
    return aux::unwrap_value_ref(extractor(keyword.get_name(), rec));
}

/*!
 * The function extracts an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \note Caution must be exercised if the default value is a temporary object. Because the function returns
 *       a reference, if the temporary object is destroyed, the reference may become dangling.
 *
 * \param keyword The keyword of the attribute value to extract.
 * \param rec A log record view. The attribute value will be sought among those associated with the record.
 * \param def_val The default value
 * \return The extracted value, if found. The default value otherwise.
 */
template< typename DescriptorT, template< typename > class ActorT, typename DefaultT >
inline typename result_of::extract_or_default< typename DescriptorT::value_type, DefaultT, DescriptorT >::type
extract_or_default(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, record_view const& rec, DefaultT const& def_val)
{
    typedef typename result_of::extract_or_default< typename DescriptorT::value_type, DefaultT, DescriptorT >::extracted_type extracted_type;
    value_extractor< extracted_type, fallback_to_default< DefaultT const& >, DescriptorT > extractor(def_val);
    return aux::unwrap_value_ref(extractor(keyword.get_name(), rec));
}

#if !defined(BOOST_LOG_DOXYGEN_PASS)

template< typename T, typename TagT >
inline typename result_of::extract< T, TagT >::type attribute_value::extract() const
{
    return boost::log::extract< T, TagT >(*this);
}

template< typename T, typename TagT >
inline typename result_of::extract_or_throw< T, TagT >::type attribute_value::extract_or_throw() const
{
    return boost::log::extract_or_throw< T, TagT >(*this);
}

template< typename T, typename TagT >
inline typename result_of::extract_or_default< T, T, TagT >::type attribute_value::extract_or_default(T const& def_value) const
{
    return boost::log::extract_or_default< T, TagT >(*this, def_value);
}

template< typename T, typename TagT, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT, TagT >::type attribute_value::extract_or_default(DefaultT const& def_value) const
{
    return boost::log::extract_or_default< T, TagT >(*this, def_value);
}

#if defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)

template< typename T >
inline typename result_of::extract< T >::type attribute_value::extract() const
{
    return boost::log::extract< T >(*this);
}

template< typename T >
inline typename result_of::extract_or_throw< T >::type attribute_value::extract_or_throw() const
{
    return boost::log::extract_or_throw< T >(*this);
}

template< typename T >
inline typename result_of::extract_or_default< T, T >::type attribute_value::extract_or_default(T const& def_value) const
{
    return boost::log::extract_or_default< T >(*this, def_value);
}

template< typename T, typename DefaultT >
inline typename result_of::extract_or_default< T, DefaultT >::type attribute_value::extract_or_default(DefaultT const& def_value) const
{
    return boost::log::extract_or_default< T >(*this, def_value);
}

#endif // defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

#undef BOOST_LOG_AUX_VOID_DEFAULT

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_HPP_INCLUDED_

/* value_extraction.hpp
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
*/