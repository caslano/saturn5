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
v4IqlhFE0NbZ755FosThTRD9ioc0Jdi4EaGbd2NHsW5f3F+LIlQnFIc+oEE9A1E8JwV3WA9y5ZauwZUnTGBF0uKYGIDj56HFtZ+sTzZZzNJ3SqQBSSXSMVyN6QrUpj08keqcrTdUrIl89Z/ta4yni+cMfEMPZUlBcrKW3oEoflfHVn+mY9+2Q1wiy050ZVf2+/owY1jAMbUQDGIgWB4ogJJ4VKJjtIO5Ih/Fw/+g99lw99mYGYzzA/33hml7AoZsVijPGrteGw9C43wfg4vOfXwlR3tLk+gQ8e4Z8DukldhcKU9bLl5zBrvL9orWz8yVuGqUnUPOTNKisHS7SifvCLuHdDbelJmb3VLIJfdIjoqMdUepSY5SUjyLD6I6TfI1OOYsDSqHLafsZPht+owtXLc7b7tsWPN9CtoXgRejWiEUOeXJXI+mhIIisoFQbM3Bk7g1lTupTPr76IAZkSXt9MDhvKhPoXWyWwO6NtjEIuLUr1bB0cQvx8+hyWTo+0/zFQvvoI/wihlinqd8/KjqUdnufTIqd41TPAjuR3mWmX6QzYrSqYt6/oqRup+xYcvfpI8LBBFAy8nipZKiOhevy+V4K09DT0tHI0uH8Hrqpf0Kri0KiYaLyQtOSJHW77vF9RI6eMmp0vlgd6hcdsWwhHvPbndXpJitt1j2M5YxEritaJaXlFC6usfA+n9Rg7/JzJyqsKL6RTsyy3wFg5bY2qyBXZBJDzS8uTlKmeWU6Iety0kbhplH3RULrT2bqOjo/ZxILQrRD7CT4F1ypEzYtgEm7i6p6kXo7nvOMZOQA8bykwYdne9epny6iVOFuwlr616oOSgTzkyTZxKT6LPx9bGUkyYdZeBbG2JdduDhXAFaJsmcw6tDh1Y5LhChILH9/yJmEkePOnreBaWOAkMOiEe8+4Ob1jXOIZ1uGp5riDLrdVwuNqxlH5nd9LcbS/dhL4vFB+rpH9fj2LXZclpWuwCnr4JOpSlk8ncANgZMX8NVVjgDcIIWqfOyhLmbuyN4ZHBaqMVL/DymGDIuL48xn9xkKi2d+Xq6L9Jwi811I+mu2E/YXD1FocHuywdwv2vMz1OpucK7uh2/K4m4D7qmYl4LMrLWWo9WUGoIqzHlj8L+XTnt20R68UbbMKh7irtrPicojYzceAtcCyRD9SKkjRymTErHCHZ0ExWKO+fo8wl88GZpV5KW2HZO/VU9oAcrxQtlqSrpY55ou+3JdDO5fiXOGDkRKVvPqy03r+gIZaDVXdSfwQ1TSzqsJE+5cQr6ukHCee8dKDvz+0rq0zGmOPxJbj942+fVx0MDPRfih/A3bAQz1FzMwyJAgDVi2dZFXrprPJoZGm4NZKEsRlLckZ9RgDirrZTgpREKRUZC0ZUDTywvBmLMg1Zz3hHqZmO8mDumQ0VBd5bLBMj9qVdbm60qAOFw8a5M2egmKo1ln37lQLXKTJ5Qh24AwXu14BuuDprVkW06TZ7swdp2QqIW7a/prETWVhOr+7tj7v/6DcjumU9bt3naqMhFCnZNpVeISDX7i322RBydUwMpZXVAYaMTqinNUc7UUkC5maaVCTZjiKPVCMmRsbwe1/AKLNHEtp46u325b+6hYfdI5bs6sxUPQJy1tkS0mR9DmXN0uQA2wdNV0Deq60u5N8Y8pHQEMtD95kz4UYNVpGpQEYGA9J5E+L/tqpknuLN5Ce8yaF1v5S6pCOmKJQmD/YmuXg/3SCSqRZ2X9/sLFW7LGIxr729oj3J3Gli3IqusURiyQ5RPNHtWjVKRs4HeOFu7AEK7oKfXwjd7xR6Kn1QhyRJLm4owLVg3Zo0/SyMNPww7/U5D5UDf7gqiFQ5VjUodXC2PCEn6EoUfrWQwSt4tLEnoQRxqdj9wooJejAopJGmy3/FuXqpKtR3acgUx3i1ljNxP1JCYAXQ8b9m881HA1MPtN/R3Rd5tMcxdNFwC3PaY83BM94x4oUiPoBOaVeD0jCKih/uGbd+U9pwGIGl1eCPQ9AfFToi9RJhDuCuYt3MaeTvc9gBNrJjmUWMqz64KKTSsbQrdjJCwG71REOowzGASg108NHxqo4FCtbhbbIkG43Co8Ts3e+Oc0YPtl8aXOR4dDncwcU3YUmEHr5r9Phs+aGfNI2oMqKlfMl50Y305taIU8Ml7gI6tOW51AOSnCUYLlhRGG9q5WDcddW8ZRb634ARGYjHMnt4hsuvAgOjTDhTsvPPgdI6tJ8B4mnwIUK3kMvv5RhkgFp29ELFUnj2qkFprFYgznamHlRu3q1mUfKW9xYaoclJfG1SGlE6ms9J5gGqhBprIGTLHNu9rO0WZdEB0us6RkkQSm5za2sVGtzgLNCqioSruKfD1NN3k6Nd3tXyl6bjLbWZY1XowPacX747dpMQzrEGMF4CnJcvPWlNgolK5SGKEw7SGPsKjQdJZJ8lZLr3ID193U0iru1ZLq04RDa4hJNommrY3dX+JvYSWP0LE2o/+7bsPoSCt2Ap43kBZ0GS/vN26N0MSgdxclCvuIzJBYqZR/t6pGlgmGEwUZypoeddoZg1QDnE2XlN0LW3Q8QpbSqs3opF1g1CtYf8yRSnD/4KMH/zE7TQ63r8/hDfPLXEJ8j2VR17zf7+PZ+evJhJgRG7+hP896y6U942P5sX4+7T9Lrfy4b+/mX9/9T/8r1J5xN2fNv2fen/KM+5P3iDx/8K85meMuC8JvIGuWy+pblq9BHrhikEv4C9/x1NSq11GvknHv60J1gD/jMd5P4yP+np1ZWsKPpnJFvS/9qT/UyV9/MeK16Fp8taPxnlan7Tq+AYPrx4eT2nL3jvjEHi69eftsVwvsfcg/ls5pqd5V+ekkLb0MpK+w4UowyxnYXm1si37S360mVeP+kGTPVumd0RV13+xyUqoip5EwIp8jngPBqJzr1KTBrpac+myRLKoPnd1Q+1vrEo/ZTeWc6LK6CMjioG7VnFZI/WpaY0oqRAp1ZCw/OqF6+cn/S7mRnIUZttqrID+Wb2BroX+HMoRY3RFEuOsjOAHUctTtDvnwZRXgcI4qWaJZpatFMlU64bvAhfONYUbbei+CIHBUoGbk8vlji3GtWLUY6pHNU6ZmStGZymhOd1IIoDUA28GU03tSI3mcede+4V7UDUbN7W+aQnNADetUjkcA4ruHPs35cEHrpcocKy3pgyIFFZlmpMSdyt0cXRo60j+NYdwqJJ0LpNM0koSCnAu3zzpM6fGkUUUhWeGtiVFsyS9xvd+fk0ajsqjaEvL3D3OPFp56JmJ/cri0ZsVLhgf61rvp9SDmeT4WOlAKDbPsTBZQTZFCR10PZ2JERtZko0z+Y6lrDJG2tlMXEoVXlkrNgoDb+iLGiKY6nq95rGvQrNXSLwv4mfSfTFiOe22uHUGQ+Zaxli5A53XOZl8C+rWyXRT2x2fB5x0XSVEoxewlQulGMdpUwvg2OcI12DXgWpIr6OeNQViaKqOninx9woZyhTELhYUeBEzMhGcmbvsXnskrHooyIpTQCfbAPBMzVna3ty2cPQWMhuJZr+/W3bcIdu62Clv9fJ+/0pdygnEHMi183bdqt2V3d9e/i8j2qr+dGEo2wD5JH2HXt/MNEurx6Bz3z17/6W3JP9dnYSAWnikDdjBgNpfHUGm0gwY0tRVP5fF6chRs/NN7EuufH24bmjxSbxVYJku5sJxItgqh9vgUuNp2095knp0/QYn54xyQ7yDpiTlQ4jRIxK+V3mHfrpiHOKj+KpYdpV80H2Pi8lqcgNMkI2bW0FlvK4nxO9L+MNmodTKGudeCq3ciVLZC/gzeNjr4vVE/r7sM3qno6KLxO7bH5BI+/2uvKgrrlZDmVEvO05++m2lEpXKSrF1Ysy0CQqXS0YLWRkPAeY5arMpr0GGAKUIIVrLUnQIDt5SLCbZnoLKPXslJ8QTOuG6yZnPzxeRMkFre6EHlAAYmXlPCuOdYDYu4RhkwarbhFZXsaZOmlmdtFqC+SZ+Z8dW8UoDqjPmkFG1EREyMVrXSYywfA567pOamIpCCKtxRAtukCycJr3JdHY4TLm9WzSFlh3PMxXC7T9FNoGt3/BpzldEbbZfmIaRID3PvAKIc+IgQv0M0VaigEYgVcbGV4onGuVYSDUq1VWb/Ly/nsbIfiLzsPfAGlUd8DqlqkiGndNkdINj1KwgHVBopL9u/fIfi6Af6QKX+1B7tnM/vrwFwsobP2U90kfHyagmgn07rsC5TFHOqcaekns6w+ej/HJL+kdvJnQMzX42Lt8kUzkdDATS5HLRhc/FX5bI18Lb4RuXClBh0nDLdjKaI1nyDK7lzqsknYlPPIZuutfHsn7o51rBouVS4iZGqHd1JVztm9OOvj4b26+7dx/rIakEHai8NrrsVBhpzo5FfOOzc5cB/9g72Ilxuq9LmcZQSL5NY37UN6x2Ic+7ZG7h+/Q8n3ZGF0LtYtMjWJOkHNaN6rQT5R3XwlRky06fICy2a0zkXMwXJAWEl8kNjj2Tl9P/8+Ec+DkKCc5U64EgTkefcfbvNtI7bXX4pVQuhmAuetx8Gh+txUm7SzJPcZFDa8JtF/8nXQQRwEO0xwqJ/UvixUv97cnpzGpNwFr9Xrpc6SuT3ia3CvoC1l0e5QAZukEnbq1DBGkY7jShPZowOnRnCQzvVq/eZkAmMtQ4T+Iq5sU52Zw63Gz4Wccohc0xJHqR8ltsVSWgxmk3x1Q2IbbBbJypxcMEWkfDj3nFw1PAsVaTnD3P+8/oI36L3HhggJbkVeIHzTd7aJQA8Yoi3OobiF8LO6Ot7zOIevIeeYBjg33lpV8yOiM0sqLVP48NoYoEPIVLLXtZoJyJpHlPuzWKZimHcxYEHV1qG7+vHrMBoQw2vYsBOkJZG0MxAlb5Rq/Mz2NTKpDQm4kDtImyQS88fySGf2uWJTGedbBskbX5yjfQy7TSPtDGuKp2m8s0aq03zZb8j5lMmvtsOGwUL1kcqnSijFxJdGetlBaMnvCccGJlw81mo+07o3MrVGslUeBqon1Fo3l1y3n+arUsp/H+WsB2oGzjjbM0QgHEa1i1MeQJaQ2+8ulbS7gN9jcVEULQcnx+UbGsKzU4SAyDVs02rkd7CT8qiVXmWoKyamP5kqfWCi5zLpL9kfe9ID6QwpZfCgPH534kygLh+9HDSWpK5xt/fHcXh4Hp4m4MjajPHJIYIX2tmVE9ToSf6R4G5KFA+47JWpoNmh0l2phUd/6qVkX9v4Itmq/ql73X4vaa2+qzj3pPvHSt4k8H/XRo02ZTU2oojweqKYr3s7zGLXmq96mlo/hw+ReswsxFqMjHBmnU45FagrcIiWaAkm4Dh5UvZIwSS44Iu4H+pH5RDcvBf6KdFD/u7H8L4tYh0F/wVXsL85Yud0ijn/yqS2KrGofcxwC7gxxUlBp5/0GO4WFKYQbbUFyHBU1f9ezr9UVi+MLNl3Csghf88i/GVviqjQJI1Lw2e2SVEToKXVu5cobI3WUUtYUhvq6eF8S/Y1dJ7g/g5YriVs/V7PHPVGpqkBkrXGJ9PQT71ysJeVJf3VL3taoJ9UAaN4Y4AKbyeGncRUx4PTNEh4p8CVtMKmzWO9HQM+JCFYeFYFp0ngzZoVqFSu+QyNAiVRZ5G+2Gx+al+1zu0mi5YKO1VEa6nWrzMI5NpuuV01cmLIrrMDjIiEFSutWqky8NU3WR6YFnRmftX7X4ppd/z9CSKrMAQEOixMoxp/zMs5MtlUSBV6QdGpmbbnVlf9TkLhYtIEQRNvZDqqip6HM5dThaeZo+biSEtxeN0blBf3dJbjUD+FzSXh/1/hEfZS+6tB+z1J3CeaWQYZmyuVnqr3xq9P3bmmE19S1E7FqTsIeKyt2SwxR0SvHbXCd87E5+2sqcmC0XLt87Lf4pz3/iW9mC2vJ+/iSKKRlHzyiRzNAVd7wcBxLs7kxr39ZBxOgHf0b0z+Q98I+tuLMLEualFxMd75MlIdav/pcI9H/kwhP4rX31kvwqQiVYWk7qyyT/3x8Pbu6Ort7NJ/3xXlv9WzRj95d+Z2LZmdMYKbvzrXdoHzruJpO2P7P/LQelQu1KS+sShvI16wKYxEuSMJf5H7xg6KzCwr8aR/x/5+El3X9JzszFTjePLPsHnpeVWyDc+kaJ/6Gxem9V973GXCAU0v1/KQymBNtPgJLzGEybTY5XHlvigCnUMC0ymfRbQzDl//woGJsma28MMRvGfBcy/x5xA9LtD7wfiI2v7P7mgpNk6f3sffL+vfQo/gUErmz/9xvktvpGvL0sWS6zljJjunohJsGJp9qAfiF9XspfJwywXOu3/sQcbkWvZjHyenE7fz4jn51+C0XeaavgjW2TXj9ufB/1Werr+ep2fxFozJiyeY9/qYnYRXO0xXXt4XL2HD+98VAowvl8ZSvuTQdEQNFFSskw12GkRmLgjr4k546cdAjxl57pOw5dgwh0R+Ku/YAnjb9S8ppttV9yTKf91Kh5xRLSKLkticBr2ZzVIbA+1fMdElkmL+OwzdE0a/1oJd+CnIfZOhJb56cnn7/UH2yP/MkHCGA2H/7/97DTyNsv/Nl7gIn0/Q9fQX3y/yNr6C0fNGqGNDXpiSQSXntqw/oPgRZuPHWir4vTPODx98L/NGz/P+tUO96R9yyAyM2b1T8Xa/X+HZerDBz52S+8EzftxfZ02xfdl8v1B/5b5KWHEtrUcRdtx/n5lrATKPFxlRjykRYr0jEB0gl0NbatVn8qJHNbr7pB6t2q6B3BpOUlYUI1stmJk47sqNW4xMsnFBmDd6RtLsxNhzVMBM8jEhERtYHpOD8iiuW1hWwBqc5XwGyroVMR4oSru9Iwuna9vXU9roIHAN24nQ3m5IalFlts2R0d91w3m65ymiquhixMRy2hqaSGcT19Nievjw8Lac/NKoOc6sMeXr1RAE6OibcIjSxAboYNoCw1NGjMC0r1ZxkkxijHWHfaKMffwBnhAwceJREQSi/h/kndRZfVnP4vBRn+nAmqbRlJBlXtmMQQbZgWJunqYFcO3t9PJbExgmS/4jZRxWJTcHj0O86xATpZ3BtvJ/bbIVsjG1/3fesxFgdVvQmmIKw0bzM2+28HRQMf8O180DuLLFyISv/yZZccT0bStLwreE2kK8kBn/wn48CtGQ28qy4dDto/LJE3rOKumZAMnqGYfxBB0u4jmoNwc1uBjZ3X+XUUvi4s8JdtwRt3agGIE6soU2WfdSpOG8sOGT1XLZ3CoBAmUKl6tewePR9pAkMZNyimBnMdHkNoUSrZk8/6/Hyq4xmtp/Hoxjg+lD1NlGY9Ko/s7X8Py5eBr+LkV0jU25X1HLm8wOmB9GnLGj4jwwI8B/2v8wDCrmXVaiteijNYqsCaQ9E8au+dmR9iwsjfqN1Krj/DF8JU5Y0n0tKdYLT22EqbxsEed5x7gXv87+WPSm/9X37p+0nDywv+LGXTwP/cTVf11yFJnDyLrROZYg2lda5bJQ5fyadttDYM/oI98qbapwYonG/a1jaucPU+Tr7MXMJHgT0uX89LAN4UTeQdXY1HCw1O8B6EX7lXfbc72J+6w1Ig8SYVMvhOHJPhmKivELoSlbfcZaUldVX5BobacNDhnA7W9E4r7+Mdj/P6JQ1X7peV3oJtrWyefUQXb3NLxbwnLYyLdajqi/uX1DLoKkPIjt+/42m6cxWJYtOZywKB4eY6l1djtB71vXYz0EnKMMYdLIkxLED5SVXg5+Gd1vBU1e68lRhxKOWWNhG5VM0ridcT867pVJSTp+looTOUAfXxoZbG5TpDvaU2cipxgRXcnpBodlj15NUKA77v7qkCovQ5YQtj7Fs5YL0HzPCmOcd6asIjKe4J3U1wiLs0lsGrBLVfJq/TZhDXV5QyOVbHh4jLcu+lKVbv2U4Y2wmTE/XWY7s/4Qae+v1NdcxLS/w878h7N8zh5uilnLZgKvXNtNao1Mf6IKZ2NQ7hxYtmYfJAaHUf5yC5OY6+O4Koholo71uYwq8q2LCKm4DHp9vFjjrTh3fVeaPCkdJ9D41tpw7hsrGb2oC6mfGucyVARUnqh0i9NeubmmDSB157qem7hP9sMFKjE/15z0c0LwVytG/iwmIvhR6mf8CO+aNQpW3iId3md2qrI4IlD+Ne8GIe0u3uoskk7GqakdwHVREoAWPYUu+7LJnufppTGM04l68bFGks4eJLKUdeG8rAL97DZgK8rRQ1kHqHRlg15R4dnMaPw1CD99WDSUQAACz/0zGhFWY4VyQBrVm/hCyLzjFqQOg9h5E3lypP7GGYZGXJI1JiMxfPSpyQ2ilSJp6F2o6SiY8xRPz5MjLkyYra7chtWYX3mYZISA/NVxoBbWoGU9HYrIZH0jivl/leh5iuQI0WxEBwnJvZqBgvoPNeepJTnb58Eja/QM37K/IxewWCv/qVqnkAxHMEQCq3eiiW1lI3+nKvgm6moXRlFXKhMAXgQoF+xUEGTiuW5wMjAhEqRj2fmfMOQQefO5WO8gCXKKVfHfSciJIk1r6bKoQUqjjWIOFJV6/T2JafZMRz7HlbcyxjmKSVXOWjA2ULR8BWB5OGYqT+FxlODm+drqgUK54qDbVV2z3qXKd+Bk+NwOtQe52Z487/3w+PDhBZ3LlDRpYIj+KMg3Frzk8cavedEfp/bPZU/1UloRS0dn3LffbeKH9u1ywC0b8XndRk9dW2OvQZp3b9oSHJuzlKW86kSfvmLaqKd9N5Vt6S3ZHv2zu+wsN/W6kcvfK89J89nSjcCEqrv+LFahhokv2jaEz/0Ng/ELoUahMgpgySN1NGqs9UnuUlYBj+uq1326wX+B+6qp28DF1CZp19yR6Lq7aQGzRLXr/nn5kZ33g6efnPhLLKpIaE0XuBScytrMr8zaHQ3zvb5Yqr3NFvW7Si/6PsoZIXl7CPVn930U1dHfdb0QA3wdG4NH9WOzDMzeRer/fJYO+yu7qD/vufYJZK84X5tp9n0phh7PSOnwZFe/efnrl20u7zH+kO0gd8/vMMJZRjBKUNp8Upwa76to6qJ5S50nRi1BdcX0/cOq5SMGh9RG/OMu0SMKd2ysPeIZ8e8B+mvY96UEy0MzkMmsWMTnGKii2Hz4zDmqN7GtB6yg+X59RMcj1ZCFjo5X1L4blZbX1O6BNeaHvL9+ugvTMj8BcJsOVTN8Xv8PI=
*/