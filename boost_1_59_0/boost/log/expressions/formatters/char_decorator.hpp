/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/char_decorator.hpp
 * \author Andrey Semashev
 * \date   17.11.2012
 *
 * The header contains implementation of a character decorator.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_CHAR_DECORATOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_CHAR_DECORATOR_HPP_INCLUDED_

#include <vector>
#include <string>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/addressof.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/detail/deduce_char_type.hpp>
#include <boost/log/detail/sfinae_tools.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

template< typename RangeT >
struct string_const_iterator : range_const_iterator< RangeT > {};
template< >
struct string_const_iterator< char* > { typedef char* type; };
template< >
struct string_const_iterator< const char* > { typedef const char* type; };
template< >
struct string_const_iterator< wchar_t* > { typedef wchar_t* type; };
template< >
struct string_const_iterator< const wchar_t* > { typedef const wchar_t* type; };

} // namespace aux

/*!
 * A simple character decorator implementation. This implementation replaces string patterns in the source string with
 * the fixed replacements. Source patterns and replacements can be specified at the object construction.
 */
template< typename CharT >
class pattern_replacer
{
public:
    //! Result type
    typedef void result_type;

    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;

private:
    //! Lengths of source pattern and replacement
    struct string_lengths
    {
        unsigned int from_len, to_len;
    };

    //! List of the decorations to apply
    typedef std::vector< string_lengths > string_lengths_list;

private:
    //! Characters of the interleaved source patterns and replacements
    string_type m_decoration_chars;
    //! List of the decorations to apply
    string_lengths_list m_string_lengths;

public:
    /*!
     * Initializing constructor. Creates a pattern replacer with the specified \a decorations.
     * The provided decorations must be a sequence of \c std::pair of strings. The first element
     * of each pair is the source pattern, and the second one is the corresponding replacement.
     */
    template< typename RangeT >
    explicit pattern_replacer(RangeT const& decorations
#ifndef BOOST_LOG_DOXYGEN_PASS
        // This is needed for a workaround against an MSVC-10 and older bug in constructor overload resolution
        , typename boost::enable_if_has_type< typename range_const_iterator< RangeT >::type, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()
#endif
    )
    {
        typedef typename range_const_iterator< RangeT >::type iterator;
        for (iterator it = boost::begin(decorations), end_ = boost::end(decorations); it != end_; ++it)
        {
            string_lengths lens;
            {
                typedef typename aux::string_const_iterator< typename range_value< RangeT >::type::first_type >::type first_iterator;
                first_iterator b = string_begin(it->first), e = string_end(it->first);
                lens.from_len = static_cast< unsigned int >(std::distance(b, e));
                m_decoration_chars.append(b, e);
            }
            {
                typedef typename aux::string_const_iterator< typename range_value< RangeT >::type::second_type >::type second_iterator;
                second_iterator b = string_begin(it->second), e = string_end(it->second);
                lens.to_len = static_cast< unsigned int >(std::distance(b, e));
                m_decoration_chars.append(b, e);
            }
            m_string_lengths.push_back(lens);
        }
    }
    /*!
     * Initializing constructor. Creates a pattern replacer with decorations specified
     * in form of two same-sized string sequences. Each <tt>i</tt>'th decoration will be
     * <tt>from[i]</tt> -> <tt>to[i]</tt>.
     */
    template< typename FromRangeT, typename ToRangeT >
    pattern_replacer(FromRangeT const& from, ToRangeT const& to)
    {
        typedef typename range_const_iterator< FromRangeT >::type iterator1;
        typedef typename range_const_iterator< ToRangeT >::type iterator2;
        iterator1 it1 = boost::begin(from), end1 = boost::end(from);
        iterator2 it2 = boost::begin(to), end2 = boost::end(to);
        for (; it1 != end1 && it2 != end2; ++it1, ++it2)
        {
            string_lengths lens;
            {
                typedef typename aux::string_const_iterator< typename range_value< FromRangeT >::type >::type from_iterator;
                from_iterator b = string_begin(*it1), e = string_end(*it1);
                lens.from_len = static_cast< unsigned int >(std::distance(b, e));
                m_decoration_chars.append(b, e);
            }
            {
                typedef typename aux::string_const_iterator< typename range_value< ToRangeT >::type >::type to_iterator;
                to_iterator b = string_begin(*it2), e = string_end(*it2);
                lens.to_len = static_cast< unsigned int >(std::distance(b, e));
                m_decoration_chars.append(b, e);
            }
            m_string_lengths.push_back(lens);
        }

        // Both sequences should be of the same size
        BOOST_ASSERT(it1 == end1);
        BOOST_ASSERT(it2 == end2);
    }
    //! Copy constructor
    pattern_replacer(pattern_replacer const& that) : m_decoration_chars(that.m_decoration_chars), m_string_lengths(that.m_string_lengths)
    {
    }

    //! Applies string replacements starting from the specified position
    result_type operator() (string_type& str, typename string_type::size_type start_pos = 0) const
    {
        typedef typename string_type::size_type size_type;

        const char_type* from_chars = m_decoration_chars.c_str();
        for (typename string_lengths_list::const_iterator it = m_string_lengths.begin(), end = m_string_lengths.end(); it != end; ++it)
        {
            const unsigned int from_len = it->from_len, to_len = it->to_len;
            const char_type* const to_chars = from_chars + from_len;
            for (size_type pos = str.find(from_chars, start_pos, from_len); pos != string_type::npos; pos = str.find(from_chars, pos, from_len))
            {
                str.replace(pos, from_len, to_chars, to_len);
                pos += to_len;
            }
            from_chars = to_chars + to_len;
        }
    }

private:
    static char_type* string_begin(char_type* p)
    {
        return p;
    }
    static const char_type* string_begin(const char_type* p)
    {
        return p;
    }
    template< typename RangeT >
    static typename range_const_iterator< RangeT >::type string_begin(RangeT const& r)
    {
        return boost::begin(r);
    }

    static char_type* string_end(char_type* p)
    {
        return p + std::char_traits< char_type >::length(p);
    }
    static const char_type* string_end(const char_type* p)
    {
        return p + std::char_traits< char_type >::length(p);
    }
    template< typename RangeT >
    static typename range_const_iterator< RangeT >::type string_end(RangeT const& r)
    {
        return boost::end(r);
    }
};

namespace aux {

//! Character decorator stream output terminal
template< typename LeftT, typename SubactorT, typename ImplT >
class char_decorator_output_terminal
{
private:
    //! Self type
    typedef char_decorator_output_terminal< LeftT, SubactorT, ImplT > this_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Implementation type
    typedef ImplT impl_type;

    //! Character type
    typedef typename impl_type::char_type char_type;
    //! String type
    typedef typename impl_type::string_type string_type;
    //! Adopted actor type
    typedef SubactorT subactor_type;

    //! Result type definition
    template< typename >
    struct result;

    template< typename ThisT, typename ContextT >
    struct result< ThisT(ContextT) >
    {
        typedef typename remove_cv< typename remove_reference< ContextT >::type >::type context_type;
        typedef typename phoenix::evaluator::impl<
            typename LeftT::proto_base_expr&,
            context_type,
            phoenix::unused
        >::result_type type;
    };

private:
    //! Left argument actor
    LeftT m_left;
    //! Adopted formatter actor
    subactor_type m_subactor;
    //! Implementation type
    impl_type m_impl;

public:
    /*!
     * Initializing constructor. Creates decorator of the \a fmt formatter with the specified \a decorations.
     */
    char_decorator_output_terminal(LeftT const& left, subactor_type const& sub, impl_type const& impl) :
        m_left(left), m_subactor(sub), m_impl(impl)
    {
    }
    /*!
     * Copy constructor
     */
    char_decorator_output_terminal(char_decorator_output_terminal const& that) :
        m_left(that.m_left), m_subactor(that.m_subactor), m_impl(that.m_impl)
    {
    }

    /*!
     * Invokation operator
     */
    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        // Flush the stream and keep the current write position in the target string
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        strm.flush();
        typename string_type::size_type const start_pos = strm.rdbuf()->storage()->size();

        // Invoke the adopted formatter
        phoenix::eval(m_subactor, ctx);

        // Flush the buffered characters and apply decorations
        strm.flush();
        m_impl(*strm.rdbuf()->storage(), start_pos);
        strm.rdbuf()->ensure_max_size();

        return strm;
    }

    /*!
     * Invokation operator
     */
    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        // Flush the stream and keep the current write position in the target string
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        strm.flush();
        typename string_type::size_type const start_pos = strm.rdbuf()->storage()->size();

        // Invoke the adopted formatter
        phoenix::eval(m_subactor, ctx);

        // Flush the buffered characters and apply decorations
        strm.flush();
        m_impl(*strm.rdbuf()->storage(), start_pos);
        strm.rdbuf()->ensure_max_size();

        return strm;
    }

    BOOST_DELETED_FUNCTION(char_decorator_output_terminal())
};

} // namespace aux

/*!
 * Character decorator terminal class. This formatter allows to modify strings generated by other
 * formatters on character level. The most obvious application of decorators is replacing
 * a certain set of characters with decorated equivalents to satisfy requirements of
 * text-based sinks.
 *
 * The \c char_decorator_terminal class aggregates the formatter being decorated, and a set
 * of string pairs that are used as decorations. All decorations are applied sequentially.
 * The \c char_decorator_terminal class is a formatter itself, so it can be used to construct
 * more complex formatters, including nesting decorators.
 */
template< typename SubactorT, typename ImplT >
class char_decorator_terminal
{
private:
    //! Self type
    typedef char_decorator_terminal< SubactorT, ImplT > this_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Implementation type
    typedef ImplT impl_type;
    //! Character type
    typedef typename impl_type::char_type char_type;
    //! String type
    typedef typename impl_type::string_type string_type;
    //! Stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Adopted actor type
    typedef SubactorT subactor_type;

    //! Result type definition
    typedef string_type result_type;

private:
    //! Adopted formatter actor
    subactor_type m_subactor;
    //! Implementation
    impl_type m_impl;

public:
    /*!
     * Initializing constructor.
     */
    char_decorator_terminal(subactor_type const& sub, impl_type const& impl) : m_subactor(sub), m_impl(impl)
    {
    }
    /*!
     * Copy constructor
     */
    char_decorator_terminal(char_decorator_terminal const& that) : m_subactor(that.m_subactor), m_impl(that.m_impl)
    {
    }

    /*!
     * \returns Adopted subactor
     */
    subactor_type const& get_subactor() const
    {
        return m_subactor;
    }

    /*!
     * \returns Implementation
     */
    impl_type const& get_impl() const
    {
        return m_impl;
    }

    /*!
     * Invokation operator
     */
    template< typename ContextT >
    result_type operator() (ContextT const& ctx)
    {
        string_type str;
        stream_type strm(str);

        // Invoke the adopted formatter
        typedef phoenix::vector3<
            subactor_type*,
            typename fusion::result_of::at_c<
                typename remove_cv<
                    typename remove_reference<
                        typename phoenix::result_of::env< ContextT const& >::type
                    >::type
                >::type::args_type,
                0
            >::type,
            stream_type&
        > env_type;
        env_type env = { boost::addressof(m_subactor), fusion::at_c< 0 >(phoenix::env(ctx).args()), strm };
        phoenix::eval(m_subactor, phoenix::make_context(env, phoenix::actions(ctx)));

        // Flush the buffered characters and apply decorations
        strm.flush();
        m_impl(*strm.rdbuf()->storage());

        return BOOST_LOG_NRVO_RESULT(str);
    }

    /*!
     * Invokation operator
     */
    template< typename ContextT >
    result_type operator() (ContextT const& ctx) const
    {
        string_type str;
        stream_type strm(str);

        // Invoke the adopted formatter
        typedef phoenix::vector3<
            const subactor_type*,
            typename fusion::result_of::at_c<
                typename remove_cv<
                    typename remove_reference<
                        typename phoenix::result_of::env< ContextT const& >::type
                    >::type
                >::type::args_type,
                0
            >::type,
            stream_type&
        > env_type;
        env_type env = { boost::addressof(m_subactor), fusion::at_c< 0 >(phoenix::env(ctx).args()), strm };
        phoenix::eval(m_subactor, phoenix::make_context(env, phoenix::actions(ctx)));

        // Flush the buffered characters and apply decorations
        strm.flush();
        m_impl(*strm.rdbuf()->storage());

        return BOOST_LOG_NRVO_RESULT(str);
    }

    BOOST_DELETED_FUNCTION(char_decorator_terminal())
};

/*!
 * Character decorator actor
 */
template< typename SubactorT, typename ImplT, template< typename > class ActorT = phoenix::actor >
class char_decorator_actor :
    public ActorT< char_decorator_terminal< SubactorT, ImplT > >
{
public:
    //! Base terminal type
    typedef char_decorator_terminal< SubactorT, ImplT > terminal_type;
    //! Character type
    typedef typename terminal_type::char_type char_type;

    //! Base actor type
    typedef ActorT< terminal_type > base_type;

public:
    //! Initializing constructor
    explicit char_decorator_actor(base_type const& act) : base_type(act)
    {
    }

    //! Returns reference to the terminal
    terminal_type const& get_terminal() const
    {
        return this->proto_expr_.child0;
    }
};

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_AUX_OVERLOAD(left_ref, right_ref)\
    template< typename LeftExprT, typename SubactorT, typename ImplT, template< typename > class ActorT >\
    BOOST_FORCEINLINE phoenix::actor< aux::char_decorator_output_terminal< phoenix::actor< LeftExprT >, SubactorT, ImplT > >\
    operator<< (phoenix::actor< LeftExprT > left_ref left, char_decorator_actor< SubactorT, ImplT, ActorT > right_ref right)\
    {\
        typedef aux::char_decorator_output_terminal< phoenix::actor< LeftExprT >, SubactorT, ImplT > terminal_type;\
        phoenix::actor< terminal_type > actor = {{ terminal_type(left, right.get_terminal().get_subactor(), right.get_terminal().get_impl()) }};\
        return actor;\
    }

#include <boost/log/detail/generate_overloads.hpp>

#undef BOOST_LOG_AUX_OVERLOAD

#endif // BOOST_LOG_DOXYGEN_PASS

namespace aux {

template< typename RangeT >
class char_decorator_gen1
{
    RangeT const& m_decorations;

    typedef typename boost::log::aux::deduce_char_type< typename range_value< RangeT >::type::first_type >::type char_type;

public:
    explicit char_decorator_gen1(RangeT const& decorations) : m_decorations(decorations)
    {
    }

    template< typename SubactorT >
    BOOST_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef pattern_replacer< char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(m_decorations)) }};
        return result_type(act);
    }
};

template< typename FromRangeT, typename ToRangeT >
class char_decorator_gen2
{
    FromRangeT const& m_from;
    ToRangeT const& m_to;

    typedef typename boost::log::aux::deduce_char_type< typename range_value< FromRangeT >::type >::type from_char_type;
    typedef typename boost::log::aux::deduce_char_type< typename range_value< ToRangeT >::type >::type to_char_type;
    BOOST_STATIC_ASSERT_MSG((is_same< from_char_type, to_char_type >::value), "Boost.Log: character decorator cannot be instantiated with different character types for source and replacement strings");

public:
    char_decorator_gen2(FromRangeT const& from, ToRangeT const& to) : m_from(from), m_to(to)
    {
    }

    template< typename SubactorT >
    BOOST_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< from_char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef pattern_replacer< from_char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(m_from, m_to)) }};
        return result_type(act);
    }
};

} // namespace aux

/*!
 * The function returns a decorator generator object. The generator provides <tt>operator[]</tt> that can be used
 * to construct the actual decorator.
 *
 * \param decorations A sequence of string pairs that will be used as decorations. Every <tt>decorations[i].first</tt>
 *                    substring occurrence in the output will be replaced with <tt>decorations[i].second</tt>.
 */
template< typename RangeT >
BOOST_FORCEINLINE aux::char_decorator_gen1< RangeT > char_decor(RangeT const& decorations)
{
    return aux::char_decorator_gen1< RangeT >(decorations);
}

/*!
 * The function returns a decorator generator object. The generator provides <tt>operator[]</tt> that can be used
 * to construct the actual decorator.
 *
 * \param from A sequence of strings that will be sought in the output.
 * \param to A sequence of strings that will be used as replacements.
 *
 * \note The \a from and \a to sequences mush be of the same size. Every <tt>from[i]</tt>
 *       substring occurrence in the output will be replaced with <tt>to[i]</tt>.
 */
template< typename FromRangeT, typename ToRangeT >
BOOST_FORCEINLINE aux::char_decorator_gen2< FromRangeT, ToRangeT > char_decor(FromRangeT const& from, ToRangeT const& to)
{
    return aux::char_decorator_gen2< FromRangeT, ToRangeT >(from, to);
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename SubactorT, typename ImplT >
struct is_nullary< custom_terminal< boost::log::expressions::char_decorator_terminal< SubactorT, ImplT > > > :
    public mpl::false_
{
};

template< typename LeftT, typename SubactorT, typename ImplT >
struct is_nullary< custom_terminal< boost::log::expressions::aux::char_decorator_output_terminal< LeftT, SubactorT, ImplT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_CHAR_DECORATOR_HPP_INCLUDED_

/* char_decorator.hpp
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
*/