/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   settings.hpp
 * \author Andrey Semashev
 * \date   11.10.2009
 *
 * The header contains definition of the library settings container.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_SETTINGS_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_SETTINGS_HPP_INCLUDED_

#include <cstddef>
#include <string>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/move/core.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/optional/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/detail/native_typeof.hpp>
#if !defined(BOOST_LOG_TYPEOF)
#include <boost/core/enable_if.hpp>
#endif
#if defined(BOOST_LOG_TYPEOF) && defined(BOOST_NO_CXX11_TRAILING_RESULT_TYPES)
#include <boost/utility/declval.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// This workaround is needed for MSVC 10 to work around ICE caused by stack overflow
template< typename SectionT, bool IsConstV >
struct basic_settings_section_iterator_base;

template< typename SectionT >
struct basic_settings_section_iterator_base< SectionT, true >
{
    typedef typename SectionT::BOOST_NESTED_TEMPLATE iter< true > iterator_type;
    typedef typename SectionT::property_tree_type::const_iterator base_iterator_type;
    typedef iterator_adaptor<
        iterator_type,
        base_iterator_type,
        SectionT,
        use_default,
        const SectionT
    > type;
};

template< typename SectionT >
struct basic_settings_section_iterator_base< SectionT, false >
{
    typedef typename SectionT::BOOST_NESTED_TEMPLATE iter< false > iterator_type;
    typedef typename SectionT::property_tree_type::iterator base_iterator_type;
    typedef iterator_adaptor<
        iterator_type,
        base_iterator_type,
        SectionT,
        use_default,
        SectionT
    > type;
};

} // namespace aux

/*!
 * \brief The class represents a reference to the settings container section
 *
 * The section refers to a sub-tree of the library settings container. It does not
 * own the referred sub-tree but allows for convenient access to parameters within the subsection.
 */
template< typename CharT >
class basic_settings_section
{
    template< typename SectionT, bool IsConstV >
    friend struct aux::basic_settings_section_iterator_base;

public:
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Property tree type
    typedef property_tree::basic_ptree< std::string, string_type > property_tree_type;
    //! Property tree path type
    typedef typename property_tree_type::path_type path_type;

private:
#if !defined(BOOST_LOG_DOXYGEN_PASS)

    //! A reference proxy object
#ifndef BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
    template< bool IsConstV >
    class ref;
    template< bool IsConstV >
    friend class ref;
#endif
    template< bool IsConstV >
    class ref
    {
    private:
        typedef typename boost::conditional<
            IsConstV,
            basic_settings_section< char_type > const,
            basic_settings_section< char_type >
        >::type section_type;

    private:
        section_type& m_section;
        path_type m_path;

    public:
        ref(section_type& section, std::string const& section_name) :
            m_section(section),
            m_path(section_name)
        {
        }
        ref(section_type& section, const char* section_name) :
            m_section(section),
            m_path(section_name)
        {
        }

        ref& operator[] (std::string const& param_name)
        {
            m_path /= param_name;
            return *this;
        }

        ref& operator= (string_type const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            m_section.m_ptree->put(m_path, value);
            return *this;
        }

        template< bool V >
        ref& operator= (ref< V > const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            optional< string_type > val = value.get();
            if (!!val)
            {
                m_section.m_ptree->put(m_path, val);
            }
            else if (optional< property_tree_type& > node = m_section.m_ptree->get_child_optional(m_path))
            {
                node.put_value(string_type());
            }

            return *this;
        }

        template< typename T >
        ref& operator= (T const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            m_section.m_ptree->put(m_path, value);
            return *this;
        }

        BOOST_EXPLICIT_OPERATOR_BOOL()

        bool operator! () const
        {
            return !m_section.m_ptree || !m_section.m_ptree->get_child_optional(m_path);
        }

        std::string get_name() const
        {
            return m_path.dump();
        }

        operator optional< string_type > () const
        {
            return get();
        }

        optional< string_type > get() const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->template get_optional< string_type >(m_path);
            else
                return optional< string_type >();
        }

        template< typename T >
        optional< T > get() const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->template get_optional< T >(m_path);
            else
                return optional< T >();
        }

        operator section_type () const
        {
            return get_section();
        }

        section_type get_section() const
        {
            if (m_section.m_ptree)
                return section_type(m_section.m_ptree->get_child_optional(m_path).get_ptr());
            else
                return section_type();
        }

#if defined(BOOST_LOG_TYPEOF) && !(defined(__GNUC__) && !defined(__INTEL_COMPILER) && !defined(__clang__) && !defined(__PATHSCALE__) && !defined(__GXX_EXPERIMENTAL_CXX0X__) && (__GNUC__ == 4 && __GNUC_MINOR__ <= 5))
#if !defined(BOOST_NO_CXX11_TRAILING_RESULT_TYPES)
        template< typename T >
        auto or_default(T const& def_value) const -> BOOST_LOG_TYPEOF(property_tree_type().get(typename property_tree_type::path_type(), def_value))
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->get(m_path, def_value);
            else
                return def_value;
        }
#else
        // GCC up to 4.5 (inclusively) segfaults on the following code, if C++11 mode is not enabled
        template< typename T >
        BOOST_LOG_TYPEOF(property_tree_type().get(typename property_tree_type::path_type(), boost::declval< T >())) or_default(T const& def_value) const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->get(m_path, def_value);
            else
                return def_value;
        }
#endif
#else
        template< typename T >
        T or_default(T const& def_value) const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->get(m_path, def_value);
            else
                return def_value;
        }

        template< typename T >
        typename boost::enable_if_c< boost::property_tree::detail::is_character< T >::value, std::basic_string< T > >::type
        or_default(const T* def_value) const
        {
            if (m_section.m_ptree)
                return m_section.m_ptree->get(m_path, def_value);
            else
                return def_value;
        }
#endif
        string_type or_default(string_type const& def_value) const
        {
            return get().get_value_or(def_value);
        }
        string_type or_default(typename string_type::value_type const* def_value) const
        {
            if (optional< string_type > val = get())
                return val.get();
            else
                return def_value;
        }
    };

    //! An iterator over subsections and parameters
#ifndef BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
    template< bool IsConstV >
    class iter;
    template< bool IsConstV >
    friend class iter;
#endif
    template< bool IsConstV >
    class iter :
        public aux::basic_settings_section_iterator_base< basic_settings_section< char_type >, IsConstV >::type
    {
        friend class boost::iterator_core_access;

        typedef typename iter::iterator_adaptor_ iterator_adaptor_;
        // NOTE: This typedef must not come from iterator_adaptor_::base_type in order to work around MSVC 10 ICE
        typedef typename aux::basic_settings_section_iterator_base< basic_settings_section< char_type >, IsConstV >::base_iterator_type base_iterator_type;

    public:
        typedef typename iterator_adaptor_::reference reference;

    public:
        BOOST_DEFAULTED_FUNCTION(iter(), {})
        template< bool OtherIsConstV >
        iter(iter< OtherIsConstV > const& that) : iterator_adaptor_(that.base()) {}
        explicit iter(base_iterator_type const& it) : iterator_adaptor_(it) {}

        //! Returns the section name
        std::string const& get_name() const
        {
            return this->base()->first;
        }

    private:
        reference dereference() const
        {
            return reference(const_cast< property_tree_type* >(&this->base()->second));
        }
    };

public:
    typedef ref< true > const_reference;
    typedef ref< false > reference;
    typedef iter< true > const_iterator;
    typedef iter< false > iterator;
    typedef std::reverse_iterator< const_iterator > const_reverse_iterator;
    typedef std::reverse_iterator< iterator > reverse_iterator;

#else

public:
    /*!
     * Constant reference to the parameter value
     */
    typedef implementation_defined const_reference;
    /*!
     * Mutable reference to the parameter value
     */
    typedef implementation_defined reference;

    /*!
     * Constant iterator over nested parameters and subsections
     */
    typedef implementation_defined const_iterator;
    /*!
     * Mutable iterator over nested parameters and subsections
     */
    typedef implementation_defined iterator;

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

protected:
    //! Parameters
    property_tree_type* m_ptree;

public:
    /*!
     * Default constructor. Creates an empty settings container.
     */
    basic_settings_section() BOOST_NOEXCEPT : m_ptree(NULL)
    {
    }

    /*!
     * Copy constructor.
     */
    basic_settings_section(basic_settings_section const& that) BOOST_NOEXCEPT : m_ptree(that.m_ptree)
    {
    }

    /*!
     * Checks if the section refers to the container.
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * Checks if the section refers to the container.
     */
    bool operator! () const BOOST_NOEXCEPT { return !m_ptree; }

    /*!
     * Returns an iterator over the nested subsections and parameters.
     */
    iterator begin()
    {
        if (m_ptree)
            return iterator(m_ptree->begin());
        else
            return iterator();
    }

    /*!
     * Returns an iterator over the nested subsections and parameters.
     */
    iterator end()
    {
        if (m_ptree)
            return iterator(m_ptree->end());
        else
            return iterator();
    }

    /*!
     * Returns an iterator over the nested subsections and parameters.
     */
    const_iterator begin() const
    {
        if (m_ptree)
            return const_iterator(m_ptree->begin());
        else
            return const_iterator();
    }

    /*!
     * Returns an iterator over the nested subsections and parameters.
     */
    const_iterator end() const
    {
        if (m_ptree)
            return const_iterator(m_ptree->end());
        else
            return const_iterator();
    }

    /*!
     * Returns a reverse iterator over the nested subsections and parameters.
     */
    reverse_iterator rbegin() { return reverse_iterator(begin()); }

    /*!
     * Returns a reverse iterator over the nested subsections and parameters.
     */
    reverse_iterator rend() { return reverse_iterator(end()); }

    /*!
     * Returns a reverse iterator over the nested subsections and parameters.
     */
    const_reverse_iterator rbegin() const { return const_reverse_iterator(begin()); }

    /*!
     * Returns a reverse iterator over the nested subsections and parameters.
     */
    const_reverse_iterator rend() const { return const_reverse_iterator(end()); }

    /*!
     * Checks if the container is empty (i.e. contains no sections and parameters).
     */
    bool empty() const { return m_ptree == NULL || m_ptree->empty(); }

    /*!
     * Accessor to a single parameter. This operator should be used in conjunction
     * with the subsequent subscript operator that designates the parameter name.
     *
     * \param section_name The name of the section in which the parameter resides
     * \return An unspecified reference type that can be used for parameter name specifying
     */
    reference operator[] (std::string const& section_name) { return reference(*this, section_name); }
    /*!
     * Accessor to a single parameter. This operator should be used in conjunction
     * with the subsequent subscript operator that designates the parameter name.
     *
     * \param section_name The name of the section in which the parameter resides
     * \return An unspecified reference type that can be used for parameter name specifying
     */
    const_reference operator[] (std::string const& section_name) const { return const_reference(*this, section_name); }

    /*!
     * Accessor to a single parameter. This operator should be used in conjunction
     * with the subsequent subscript operator that designates the parameter name.
     *
     * \param section_name The name of the section in which the parameter resides
     * \return An unspecified reference type that can be used for parameter name specifying
     */
    reference operator[] (const char* section_name) { return reference(*this, section_name); }
    /*!
     * Accessor to a single parameter. This operator should be used in conjunction
     * with the subsequent subscript operator that designates the parameter name.
     *
     * \param section_name The name of the section in which the parameter resides
     * \return An unspecified reference type that can be used for parameter name specifying
     */
    const_reference operator[] (const char* section_name) const { return const_reference(*this, section_name); }

    /*!
     * Accessor for the embedded property tree
     */
    property_tree_type const& property_tree() const { return *m_ptree; }
    /*!
     * Accessor for the embedded property tree
     */
    property_tree_type& property_tree() { return *m_ptree; }

    /*!
     * Checks if the specified section is present in the container.
     *
     * \param section_name The name of the section
     */
    bool has_section(string_type const& section_name) const
    {
        return m_ptree != NULL && !!m_ptree->get_child_optional(section_name);
    }
    /*!
     * Checks if the specified parameter is present in the container.
     *
     * \param section_name The name of the section in which the parameter resides
     * \param param_name The name of the parameter
     */
    bool has_parameter(string_type const& section_name, string_type const& param_name) const
    {
        if (m_ptree)
        {
            optional< property_tree_type& > section = m_ptree->get_child_optional(section_name);
            if (!!section)
                return (section->find(param_name) != section->not_found());
        }

        return false;
    }

    /*!
     * Swaps two references to settings sections.
     */
    void swap(basic_settings_section& that) BOOST_NOEXCEPT
    {
        property_tree_type* const p = m_ptree;
        m_ptree = that.m_ptree;
        that.m_ptree = p;
    }

protected:
    explicit basic_settings_section(property_tree_type* tree) BOOST_NOEXCEPT : m_ptree(tree)
    {
    }
};

template< typename CharT >
inline void swap(basic_settings_section< CharT >& left, basic_settings_section< CharT >& right) BOOST_NOEXCEPT
{
    left.swap(right);
}


/*!
 * \brief The class represents settings container
 *
 * All settings are presented as a number of named parameters divided into named sections.
 * The parameters values are stored as strings. Individual parameters may be queried via subscript operators, like this:
 *
 * <code><pre>
 * optional< string > param = settings["Section1"]["Param1"]; // reads parameter "Param1" in section "Section1"
 *                                                            // returns an empty value if no such parameter exists
 * settings["Section2"]["Param2"] = 10; // sets the parameter "Param2" in section "Section2"
 *                                      // to value "10"
 * </pre></code>
 *
 * There are also other methods to work with parameters.
 */
template< typename CharT >
class basic_settings :
    public basic_settings_section< CharT >
{
    typedef basic_settings this_type;
    BOOST_COPYABLE_AND_MOVABLE(this_type)

public:
    //! Section type
    typedef basic_settings_section< CharT > section;
    //! Property tree type
    typedef typename section::property_tree_type property_tree_type;

public:
    /*!
     * Default constructor. Creates an empty settings container.
     */
    basic_settings() : section(new property_tree_type())
    {
    }

    /*!
     * Copy constructor.
     */
    basic_settings(basic_settings const& that) :
        section(that.m_ptree ? new property_tree_type(*that.m_ptree) : static_cast< property_tree_type* >(NULL))
    {
    }

    /*!
     * Move constructor.
     */
    basic_settings(BOOST_RV_REF(this_type) that) BOOST_NOEXCEPT
    {
        this->swap(that);
    }
    /*!
     * Initializing constructor. Creates a settings container with the copy of the specified property tree.
     */
    explicit basic_settings(property_tree_type const& tree) : section(new property_tree_type(tree))
    {
    }

    /*!
     * Destructor
     */
    ~basic_settings() BOOST_NOEXCEPT
    {
        delete this->m_ptree;
    }

    /*!
     * Copy assignment operator.
     */
    basic_settings& operator= (BOOST_COPY_ASSIGN_REF(basic_settings) that)
    {
        if (this != &that)
        {
            basic_settings tmp = that;
            this->swap(tmp);
        }
        return *this;
    }
    /*!
     * Move assignment operator.
     */
    basic_settings& operator= (BOOST_RV_REF(basic_settings) that) BOOST_NOEXCEPT
    {
        this->swap(that);
        return *this;
    }
};

#ifdef BOOST_LOG_USE_CHAR
typedef basic_settings< char > settings;                        //!< Convenience typedef for narrow-character logging
typedef basic_settings_section< char > settings_section;        //!< Convenience typedef for narrow-character logging
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_settings< wchar_t > wsettings;                    //!< Convenience typedef for wide-character logging
typedef basic_settings_section< wchar_t > wsettings_section;    //!< Convenience typedef for wide-character logging
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_SETTINGS_HPP_INCLUDED_

/* settings.hpp
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
*/