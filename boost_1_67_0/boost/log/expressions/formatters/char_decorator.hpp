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