/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/max_size_decorator.hpp
 * \author Andrey Semashev
 * \date   06.07.2016
 *
 * The header contains implementation of a string length limiting decorator.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_MAX_SIZE_DECORATOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_MAX_SIZE_DECORATOR_HPP_INCLUDED_

#include <cstddef>
#include <string>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
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
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

//! String size limiting decorator stream output terminal
template< typename LeftT, typename SubactorT, typename CharT >
class max_size_decorator_output_terminal
{
private:
    //! Self type
    typedef max_size_decorator_output_terminal< LeftT, SubactorT, CharT > this_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! String size type
    typedef std::size_t size_type;
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
    //! Max size of the formatted string produced by the adopted formatter
    size_type m_max_size;
    //! Overflow marker
    string_type m_overflow_marker;

public:
    /*!
     * Initializing constructor. Creates decorator of the \a fmt formatter with the specified \a decorations.
     */
    max_size_decorator_output_terminal(LeftT const& left, subactor_type const& sub, size_type max_size, string_type const& overflow_marker = string_type()) :
        m_left(left), m_subactor(sub), m_max_size(max_size), m_overflow_marker(overflow_marker)
    {
        BOOST_ASSERT(overflow_marker.size() <= max_size);
    }
    /*!
     * Copy constructor
     */
    max_size_decorator_output_terminal(max_size_decorator_output_terminal const& that) :
        m_left(that.m_left), m_subactor(that.m_subactor), m_max_size(that.m_max_size), m_overflow_marker(that.m_overflow_marker)
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

        if (!strm.rdbuf()->storage_overflow())
        {
            const size_type old_max_size = strm.rdbuf()->max_size();
            const size_type start_pos = strm.rdbuf()->storage()->size(), max_size_left = strm.rdbuf()->storage()->max_size() - start_pos;
            strm.rdbuf()->max_size(start_pos + (m_max_size <= max_size_left ? m_max_size : max_size_left));

            try
            {
                // Invoke the adopted formatter
                phoenix::eval(m_subactor, ctx);

                // Flush the buffered characters and apply decorations
                strm.flush();

                if (strm.rdbuf()->storage_overflow())
                {
                    if (!m_overflow_marker.empty())
                    {
                        // Free up space for the overflow marker
                        strm.rdbuf()->max_size(strm.rdbuf()->max_size() - m_overflow_marker.size());

                        // Append the marker
                        strm.rdbuf()->max_size(strm.rdbuf()->storage()->max_size());
                        strm.rdbuf()->storage_overflow(false);
                        strm.rdbuf()->append(m_overflow_marker.data(), m_overflow_marker.size());
                    }
                    else
                    {
                        strm.rdbuf()->storage_overflow(false);
                    }
                }

                // Restore the original size limit
                strm.rdbuf()->max_size(old_max_size);
            }
            catch (...)
            {
                strm.rdbuf()->storage_overflow(false);
                strm.rdbuf()->max_size(old_max_size);
                throw;
            }
        }

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

        if (!strm.rdbuf()->storage_overflow())
        {
            const size_type old_max_size = strm.rdbuf()->max_size();
            const size_type start_pos = strm.rdbuf()->storage()->size(), max_size_left = strm.rdbuf()->storage()->max_size() - start_pos;
            strm.rdbuf()->max_size(start_pos + (m_max_size <= max_size_left ? m_max_size : max_size_left));

            try
            {
                // Invoke the adopted formatter
                phoenix::eval(m_subactor, ctx);

                // Flush the buffered characters and apply decorations
                strm.flush();

                if (strm.rdbuf()->storage_overflow())
                {
                    if (!m_overflow_marker.empty())
                    {
                        // Free up space for the overflow marker
                        strm.rdbuf()->max_size(strm.rdbuf()->max_size() - m_overflow_marker.size());

                        // Append the marker
                        strm.rdbuf()->max_size(strm.rdbuf()->storage()->max_size());
                        strm.rdbuf()->storage_overflow(false);
                        strm.rdbuf()->append(m_overflow_marker.data(), m_overflow_marker.size());
                    }
                    else
                    {
                        strm.rdbuf()->storage_overflow(false);
                    }
                }

                // Restore the original size limit
                strm.rdbuf()->max_size(old_max_size);
            }
            catch (...)
            {
                strm.rdbuf()->storage_overflow(false);
                strm.rdbuf()->max_size(old_max_size);
                throw;
            }
        }

        return strm;
    }

    BOOST_DELETED_FUNCTION(max_size_decorator_output_terminal())
};

} // namespace aux

/*!
 * String size limiting decorator terminal class. This formatter allows to limit the maximum total length
 * of the strings generated by other formatters.
 *
 * The \c max_size_decorator_terminal class aggregates the formatter being decorated, the maximum string length
 * it can produce and an optional truncation marker string, which will be put at the end of the output if the limit is exceeded. Note that
 * the marker length is included in the limit and as such must not exceed it.
 * The \c max_size_decorator_terminal class is a formatter itself, so it can be used to construct
 * more complex formatters, including nesting decorators.
 */
template< typename SubactorT, typename CharT >
class max_size_decorator_terminal
{
private:
    //! Self type
    typedef max_size_decorator_terminal< SubactorT, CharT > this_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! String size type
    typedef std::size_t size_type;
    //! Stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Adopted actor type
    typedef SubactorT subactor_type;

    //! Result type definition
    typedef string_type result_type;

private:
    //! Adopted formatter actor
    subactor_type m_subactor;
    //! Max size of the formatted string produced by the adopted formatter
    size_type m_max_size;
    //! Overflow marker
    string_type m_overflow_marker;

public:
    /*!
     * Initializing constructor.
     */
    max_size_decorator_terminal(subactor_type const& sub, size_type max_size, string_type const& overflow_marker = string_type()) :
        m_subactor(sub), m_max_size(max_size), m_overflow_marker(overflow_marker)
    {
        BOOST_ASSERT(overflow_marker.size() <= max_size);
    }
    /*!
     * Copy constructor
     */
    max_size_decorator_terminal(max_size_decorator_terminal const& that) :
        m_subactor(that.m_subactor), m_max_size(that.m_max_size), m_overflow_marker(that.m_overflow_marker)
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
     * \returns Max string size limit
     */
    size_type get_max_size() const
    {
        return m_max_size;
    }

    /*!
     * \returns Max string size limit
     */
    string_type const& get_overflow_marker() const
    {
        return m_overflow_marker;
    }

    /*!
     * Invokation operator
     */
    template< typename ContextT >
    result_type operator() (ContextT const& ctx)
    {
        string_type str;
        stream_type strm(str);
        strm.rdbuf()->max_size(m_max_size);

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

        // Flush the buffered characters and see of overflow happened
        strm.flush();

        if (strm.rdbuf()->storage_overflow() && !m_overflow_marker.empty())
        {
            strm.rdbuf()->max_size(strm.rdbuf()->max_size() - m_overflow_marker.size());
            strm.rdbuf()->max_size(str.max_size());
            strm.rdbuf()->storage_overflow(false);
            strm.rdbuf()->append(m_overflow_marker.data(), m_overflow_marker.size());
            strm.flush();
        }

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
        strm.rdbuf()->max_size(m_max_size);

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

        // Flush the buffered characters and see of overflow happened
        strm.flush();

        if (strm.rdbuf()->storage_overflow())
        {
            strm.rdbuf()->max_size(strm.rdbuf()->max_size() - m_overflow_marker.size());
            strm.rdbuf()->max_size(str.max_size());
            strm.rdbuf()->storage_overflow(false);
            strm.rdbuf()->append(m_overflow_marker.data(), m_overflow_marker.size());
            strm.flush();
        }

        return BOOST_LOG_NRVO_RESULT(str);
    }

    BOOST_DELETED_FUNCTION(max_size_decorator_terminal())
};

/*!
 * Character decorator actor
 */
template< typename SubactorT, typename CharT, template< typename > class ActorT = phoenix::actor >
class max_size_decorator_actor :
    public ActorT< max_size_decorator_terminal< SubactorT, CharT > >
{
public:
    //! Base terminal type
    typedef max_size_decorator_terminal< SubactorT, CharT > terminal_type;
    //! Character type
    typedef typename terminal_type::char_type char_type;

    //! Base actor type
    typedef ActorT< terminal_type > base_type;

public:
    //! Initializing constructor
    explicit max_size_decorator_actor(base_type const& act) : base_type(act)
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
    template< typename LeftExprT, typename SubactorT, typename CharT, template< typename > class ActorT >\
    BOOST_FORCEINLINE phoenix::actor< aux::max_size_decorator_output_terminal< phoenix::actor< LeftExprT >, SubactorT, CharT > >\
    operator<< (phoenix::actor< LeftExprT > left_ref left, max_size_decorator_actor< SubactorT, CharT, ActorT > right_ref right)\
    {\
        typedef aux::max_size_decorator_output_terminal< phoenix::actor< LeftExprT >, SubactorT, CharT > terminal_type;\
        phoenix::actor< terminal_type > actor = {{ terminal_type(left, right.get_terminal().get_subactor(), right.get_terminal().get_max_size(), right.get_terminal().get_overflow_marker()) }};\
        return actor;\
    }

#include <boost/log/detail/generate_overloads.hpp>

#undef BOOST_LOG_AUX_OVERLOAD

#endif // BOOST_LOG_DOXYGEN_PASS

namespace aux {

template< typename CharT >
class max_size_decorator_gen
{
private:
    typedef CharT char_type;
    typedef std::basic_string< char_type > string_type;
    typedef std::size_t size_type;

private:
    size_type m_max_size;
    string_type m_overflow_marker;

public:
    explicit max_size_decorator_gen(size_type max_size, string_type const& overflow_marker = string_type()) :
        m_max_size(max_size), m_overflow_marker(overflow_marker)
    {
        BOOST_ASSERT(overflow_marker.size() <= max_size);
    }

    template< typename SubactorT >
    BOOST_FORCEINLINE max_size_decorator_actor< SubactorT, char_type > operator[] (SubactorT const& subactor) const
    {
        typedef max_size_decorator_actor< SubactorT, char_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, m_max_size, m_overflow_marker) }};
        return result_type(act);
    }
};

} // namespace aux

/*!
 * The function returns a decorator generator object. The generator provides <tt>operator[]</tt> that can be used
 * to construct the actual decorator.
 *
 * \param max_size The maximum number of characters (i.e. string element objects) that the decorated formatter can produce.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::max_size_decorator_gen< CharT > max_size_decor(std::size_t max_size)
{
    return aux::max_size_decorator_gen< CharT >(max_size);
}

/*!
 * The function returns a decorator generator object. The generator provides <tt>operator[]</tt> that can be used
 * to construct the actual decorator.
 *
 * \param max_size The maximum number of characters (i.e. string element objects) that the decorated formatter can produce.
 * \param overflow_marker The marker string which is appended to the output if the \a max_size limit is exceeded. Must be
 *                        a non-null pointer to a zero-terminated string.
 *
 * \pre The \a overflow_marker length must not exceed the \a max_size limit.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::max_size_decorator_gen< CharT > max_size_decor(std::size_t max_size, const CharT* overflow_marker)
{
    return aux::max_size_decorator_gen< CharT >(max_size, overflow_marker);
}

/*!
 * The function returns a decorator generator object. The generator provides <tt>operator[]</tt> that can be used
 * to construct the actual decorator.
 *
 * \param max_size The maximum number of characters (i.e. string element objects) that the decorated formatter can produce.
 * \param overflow_marker The marker string which is appended to the output if the \a max_size limit is exceeded.
 *
 * \pre The \a overflow_marker length must not exceed the \a max_size limit.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::max_size_decorator_gen< CharT > max_size_decor(std::size_t max_size, std::basic_string< CharT > const& overflow_marker)
{
    return aux::max_size_decorator_gen< CharT >(max_size, overflow_marker);
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename SubactorT, typename CharT >
struct is_nullary< custom_terminal< boost::log::expressions::max_size_decorator_terminal< SubactorT, CharT > > > :
    public mpl::false_
{
};

template< typename LeftT, typename SubactorT, typename CharT >
struct is_nullary< custom_terminal< boost::log::expressions::aux::max_size_decorator_output_terminal< LeftT, SubactorT, CharT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_MAX_SIZE_DECORATOR_HPP_INCLUDED_

/* max_size_decorator.hpp
ji/Wxo9Rx5eYK1XN5NrfaHeKC7FHRohF25S+uZRaifrlM5JyJfzC6sJG7cYJYwCpoSWSfk+Nw9wJxgr8qDw+wybfDZgw9N5EnRdvAnjPefc3Wfe7z7s/4dZGgwdPNY7glYwj2ju8vn14RzdqN+vF5xhv8istkwlhTMZaafs3GcGHknGXQ6TvjLss045pmbSFuRCJ4R0vyb28j0dMBCYNq6eOl3yHpBu9j0WkEb64PFR9TBI/aBU8lFwt6NRs3l9Icjb9fDKREx/HJnvqhk6rYrZBrLL3sVSb8cLb/o75M4iIDsed77R80tpVB8BJK8+gnflyj4xIvZy2hYfsO+SuRH1372MFAmzC+7hEG427yGpGGb8B4tzqH+wnUZvvojGI5INiR9QejI5MUj0WexQuRVjeqpa3CVAWPirsBeeO0Egfej2SSHgVNztpoQo3OzLFszNOfyYSRNaJre/mb8El2vixJFvRQ/3tWqCzkGhCXil86jsL95Im2ZZ5sFQMLqxfd5UImOliW4lYwh8tEiGrYBmbTnQlg9zMXLJ19lSJIpOxLD8B1zfQaUwoOL+LZRJ1JXZ3KvQrnQDO71EF4ExsKyYQQLvKMgeEr4P6hBtpbB+xpGfwUU1Ke0H9g5HdRnQ2qohthNnu5JOm3rIxGJ0N5CSRGUJf4/7NUAjMrBDqdd1Irg/DAEALH8abRhB4UfNbGAF+vYxkxzOx2ENI9N7x5y4jXoU/Ueo4aoRJjy86zlnOxaKJCm8oQhjifv0+uI78rXlY/t+tZNP6ln1Irk+uv+CcYhfIq40joRBT+xB/cW+tVVdhXWOreCKEGyvVOMpAF2ZL8+mrsBv0o1+Y8UFi1FPp2XrZsmT9twtEZfYgUu93OhDgvJ3mibNBIjXH2NBaLixDx0LBWGCd/tc53UZRBym4Mf9rXvlFmbbUetW/Vv/PbyBMhiBMViOESHkx83/J8UoSDI7c0uS1bOBEtDv9oU/Du/hXa8prmYxSJme9EplF6jmLTVNHMujR769ELhTfBuFV2badqf5ETWnP4OyxWHk99x1oQg5wA2lk10KZ4rpVHCBmjsGQ18bkevNoc+AEDYfmVVvsKBOzIdSDdfoP55J60Kc8FSah7czaju0ccNL2LHZgTo3Re2ikCXuQEYXgbkXYWlIUVFpHlokCLCzw/+F2RguwSd9oa1jh2CdlQcUYA+PWyhqx7PNDanljWLsV2fFxf30Gm+GKgTfDx4h1Ifb+xQL1pLVGXCY61WHN7wkS1zy/MTezp5rNSh3HC2Om5qV8kiJNQV2JiUa0CgseiwvohHqS95WJu9ISzae7UGs3cj/Jd2oG07rZWzEhpJ7NrsnuQxtszONm8F+dfuj7pqt02/BMriVr8tD+XmV2JkCjwoAUGnhgq7lpHyMlitXEFoRYxt4B08SixxTcT8zVOU7VRmZyWSUNPbgrP7SltmWgGSVWAjob1nhbKnliPWGF2rk8E/WtZN2K9W+ODkSMv/JlllduKvdo76CxT3YuB4oFMUtZT2+jZarvgNgpezO0/XH/emEgetFcsNFiwdbTgn2EleCiE0fM9If9Sm2u6n8RqZNiwaiZXbRI5AaTUyD2ZZ3+T9LpdPkXqX3ZIxGEJMlwCNEbi6hZbNsYTKxarifnFnPaKDqsIJGadEO5lzmriQcvUm36EStVQ+O5UjwQV3Zm+ttIaKYZgxmzs3AnfVkqvjjLEMFLB19upJUp2aQqYzErtRmqMgHFZvjJczHAq6+zCPEs/e//1kNqGJ4uHXpCQpo/hsQ3f2NMwbIHhUxfBPlumrc8T77HHG0PZmqusiARrUIoIvLTCKCcDmmqAet0k6jLYGoIt8WzoconbvZuY0HTWbF7KWSj7Ird8/H+jzgg5DemC/naKQR/krRxGkJ+kovm8St5LrZEXG79WFjbBiKg0nDKG3zn5Oxwy1Y78zqPsnyaTcrVMqN2k59mhon0qe+gvQiGhkALUEctp0w7ZASl2KSxWpt4QQijWE7ObLxPCzRo42bEHrYEToRKK9tm4CXly2nyLoUqbSo8JGOzNIo9YEkPJ3x1y+hgtGujTS0Bxmh47szyiuzEK2+gSUXaKWqaibCz4EJTWhBd5/C34BIMyl0Zh+C+NykDlzdqk2akD6yAq2dyUtV3D+2eCRcMrdUamhIfG+Y/oZS6pB95FZAx6c7v3t49N0m0m0Tn5mi3ACox44vNNxc5oo+YKo3Bi6Ltx+kVAebW+j+YZiMEiHKOtZr0OhOxBVgJzYUyJdRdK1s/OIJaFBDTm3oS/nFUId/6LfFIWN1Fosy7x9lLOndeOhS9ttI0YkXYiHUvFwsuIC4qWDSLh8x22KrFeUK1iduVHcJ2lfbbGGp6IqwtMyum+uLz5GwzzybJtvT3vubQSZP0h9g6BUQ/QPrhLmlI1NCdiDp4nS9rc2Eg3m31pOyYzI+9kjFj6F1v6kLTyRdpet7X2BrE8+vbvsmxpYuc87SDc2e1dByzIFGEceX3/4NKxBh0fGUwUwRloiKQycGgsiZ5X7r1wCoALUS3SQWilVnX1Zuchj6skq8WnV7ZQwLmJsrreKiYsKo29kpOO9ZlWIYKxmg7ZqVNs4CcXM+iDu/bTIGu9cpAc6+oBhnyahUr8L+LlByYQTSbZEcGZltiiPb0ffiln3aXE+/eX3/rS8OISdn2qk/kRM/AahSRjlVMEPJGtrKkwCZnpGWbKq0TemZhH9M3NMIt4vHxKXE/9TI7ZFyFTIoL+WQG9Rmv5NpmKp0Z7qdWCM2lqENIg+nFZUXWHzL9tP1CReC7wR/8tVpm3L9dxM0KRri91DQ39WCa4m5mmrUpprk9yTRbdmF4GhagqANQvn+AqvbwDOk678MRqZ9JSXjsRBzKBxCNeHi2e11tUJ9PU9ZSya3nS8tJ3uRk1qXi9PxQU/iErGC1bq/0feEOKSuLIEFPIGCltaDrGcnrgnLLntjiEWA6TPdAfzYlGQ/HvWmiGUqMBickKcmf7kuDKS0tJRJqh8PHXQVM1hRwd2fQqqHcmSpupuwQgvJ1mr+7cCVWT9EdQf3Nl8VaLe9njG6dhUpCW+hOWE4fR6I6N1z+IFg7a3CFK5nn6rJ1Gwm+OgTfOPzgLiQFwlXbqY/tNCPUrvcxXZGvptFmyFdQA+JQ1CLJaeXeTN+DQfpzFZ2LsUdwLvalVVPVrztiHV5Az7NN/gptECANDhrPmIvSVxw07Hias2kpBfN8u/uwv3ZxDXezu5FViEJdXiDWysqO7ISvxZPe5doVwgeSoe0260XRsTXeRoPIZviFsgqR7TFzJskTVyqvI7fEpiyYDNv7ulbDLOeNBIm5Ld0Duq3cseQwFjOpXsjvFiXKiYRN4CY3/LnLStnsQXr8SSq9dq0Yd1E61YG3XvStVePB8+a2rKSnoscn/iyq11xGdHbe+cN4QKkRQCJzeSQz0kZy13eM5DufWyOe29d8bq753FfPms9NUy3gvtAmErNHPbrvUkl6oFipFXW4584CmtKUGlIqWqabsvXWw6RrCY4kcWL6Qf0XJKglBlicJ5eDM/UP2o0ehXhLepK+r/VXDyN2wruhhPWJv9jgpKP7rqfOiEWqfN1ilEkedbFKmUz6hOMm4EK0BGscOur0DmGNo7yVtInDhZ3KV1necp00DjZT+spdpHGUu0jjKG9Pb6NlqzuYdsYztINxfw1rHOXbTY3jVqFx1JDGsQ3EM2RC9DHxPMjEczsmXRBPamYXLfCqk/lVwdYs7rzOetvJ/x9vu4Z1hjpvwIMX9qAO8PS2wukeZVeG+jwcVr5dyzO0XepKdl711E7TAzksevjBvDR6iLW2fYIi2brUlw6Y8Hb1RV61zSh2GCVOo8SVFJNKhYcupAa6ERrAfMykAO7Kp3F2iRm6K1ESNAWaAJNLI2MmRD1X/YU4EOrBXBWfN9f3qVSknBkvZSlnrpeHTZ0asbOZt1tbkWIDST8/iOso5UyZ1Mu3S+qLO3rRHRng2QeoI+pjhvXTD/gntsm+XVQ7Kw1i30XPNjaDQ1XsxKf+9pKuVNI48QbhzYP7yS88LrepK+FA00pGaMUjzeRuRjnuFBEn7q3+bvfWQCep9iJ7JtpdFslagVUe8y7HKKefPphJhUg9EIAwdVJfXqVgMHkEk/nrBek6XB5Xo0clb63cU/QJzEPlzTgDn7ornwQ7PSmg6X1npWU0B79YoJTnZ8q3eqcXyGN4ez1coE5vVae3oeTz9GSR+lZtOqkobWpmYb3aV73k/wEAAP//pL0NeBTV1QC8m2ySBTbuAglGRIyKggaVdsGyLtTwMyGgixvWZEMlhFpI031ti3UGYskm0Eki02EDVVRURFFSsdUWK0IUjBtISQIpREWNJa3RxnrjrjbYFGISmO+cc2c2G7Vfn+/5fGQzP/fn3HPOPX/33Duq0J/VqHqYYnaGI251U1OiyeQ+In4ZWjs9FIzW1dWFhKi3jo3LGNJUIarmd6ueXiVRGa3m92W1q0KX4ogcrvebUjaqnqHilc6/3M3uLBptaj2SaVK1fDWal1egSg6/+lX1OSmFykV8qmDzqUVWRRgKCf1ebX2mUtSvpeceGOsImAImTRpST2lSP5tyVtMCictLlEuqw+JY+0GPzX7wncaPHGOOK0utEYtcYjUpDyK4zvDdxStbj9h4jwV+NWhVF2Wcb1fPqqf2msXR2jorm/zQkBaxs1z4E9C86kn24WtJJnihrbP42X05ZlPxyqIjFt6CHF24O3rtBIfzzwCir8Dv1BAH6lklGFWCvUqwTwkCvC0Ar3pFx8GxDtdcdvcEhzSROXIHNTYGftRsW6nlAZPJq73zHL5zzY3yEl8sghI9i3iJJL0EvlOT1ZPatm1mkwmvmoXDySaTSQm2NwtNU1aPczQLbavhgbZtFZQIeQ7n+dW5udD1odHjTCaftjZTe5/Xa8r4ttIBMy8TSCgI5UdDtQsToB/zslIzAkCl1BwxYC4ILRX5LRDCXGq2QBsHtmNL7+9uWjHBIfdrosMbMJVmxL0JjJdbNC/8V7rDN8EBLbBRtiEtVLsPWzUX8Pa0dZla+kIA2MtuPDmoAUHTSrtnj3OoLeyvVw/hvQXYL9EZzlZq7krkSNC23YtNnGQa0zT4o/TAH4PJPvsBMNlRIpcqWAuAODWdMCj2Di9bhGVjbTjDQFwrJy7QU/1K9VjZ1n9CkVMsZzQw9qzTvwASnFI72As9g5omWX0FiK90RHHxyrtjnAG8bAVGTmKTsoCEm3oRjQVpWZsYXiyzuNuDCeoReKLMt6g5adpaC7s1Cr0INjnTNAxCQGPXxB7HnsrRKcNcBwPyh2qQTE5NETrdzfaqTwDbrrJMe1UnXKi1aThPT0lpSsMUuFIaMul3EvxGvGpNH9TMqonCr//x81+pJ3OVGizGTn+paUoNlnXTg0pbfH21BuurtfS+sTxBbVToSWBSSOjye1n4F6OhDPUEooAaUIReXktusilCX8AMJb0BM7Ji1yQAtFnoTiFOZmzci4Oai/qpTAwkFvsDCdqB1QChlt4EaFY9nQEzqxg1RDR2/mUlS1nOSQy4kBvuhWom8Rp/qHYVjuP8GxoyzSjVAX21aMssegnpw2L5tzvwymBAzbsKeJL+qidX9rz1IRCOSAndS1b1LPsqZ1BbvlzuH71uNMqFRz7UtEhSKMeiJKvJwzIhD9nGec61vlC8wbW+VLo2tGi6VxcCb7ZBf5FU9U4rtngbO6Fpmvui9C8ghGBVQJyttfiqz4nfVXOs6tYwUm+sX/27eotXewhhrA5XjAWG9PtYToIVEDYEz0xycMgkHsffu6VR+JbNgSGjmLOYAhn1F8rHOtjVa4AcglX9wBu63aLI3Sbk/62AQBk7AfQkqtmZAGQ3AAl3c0L3g0jvqqsLaHUBE9KpTku/91UYAJUH0nm68ojtew8aD+m2D27lQ/tNSIGpamLI05mnntC8U7QZqopP5TVDJnYwGSnXKTf2MtcoEHJWAC6GPB/xc205ku76n1pMoZVi9RnxWnlDpkm8MpKmHTAh350oYI8/aTFptXgnN+CvqfIfnL3sf6xJI95Ens5qWSw3NCUgX3mGpMnqgdXI9g71mHpLyDOUp+ZaWWsXMMg5KQoqrYHejleb1ds4CFTguotQQJN61AMbv1F5i14Zpr4uY+ToHcOTEyZugV8RugH3Tk09624GgTBmKjB3mc1e/TrSN7lZ2G+Ok8D78/ylY8bp6EShggoFZOJIjTKEaBfq+dyWwxcVD3O3VCYqAlODfVnBqE+9YjOQK5CuvZPVL/8ryRVkwTSs0KBXcPdXjlf7I3ZePFZOPak0ZCDqfw5jBjLXoLjykkhGStMF0tip3a3CqDxDAAgs99PKbJqANfmoyK2mgKW+fRLw2+J7gN/Ols4GDRMSer2vmUBvsZZ5QHdiAVTdaSByJYcm2WAmlO59A+X9ztdhxnl6gTHUXjY5BW6OsfehpSMOQ6aeVWtwygKLXqN6HNWt4iR1cSb8SVc3Hh5mZHejveos3Pr5zGaXfZwCiEZRo22rwqnuseryq1/+KsX+YBPif0pob3qSIzdyc3ZkuvxbfGuKXM9FWOTyLJJgwBm1+DexRakl8TkK6KvokhB/q1sfsDjfjiSob/GKvFo2CPvR9CociQlKd7MIwo/kHxvzxiBqosEhTcsiuczxbv8jUcvr9QdQt3kaoJQx/LTSJNK9cngOJ8/MA6h/isC02dadluT4FP4Nwr9EGNN4/d9ncP9v+KdLKec5mBKuWU0imBu3ul5GeCu+a39TsHlZtHa0aXmg7PHl579yH6u4wuc8U+KSbH77zqNqPxC9oMDH/g8Y5E7py+K7QRGDqHEYmml6PPNbfeoHzreBK10P40jsVb2A1QJXvk2c5tqGWBcz1X341/2lOIFQMbcTtN0BfASz6nMV+Fkl1UQ25mmwMRfXuTwd5XbV0+VWUXXZa59AuRKeo/ZyI9QL061OF7ezECtvIqb8KMZgIt2fqb2nythkrkvoCNpcQld5ijMMNknkRlXGBuFJRSq8q7QGyLaJpKtCx+PnD+EAAqYsGenjDVjUE6z0gkbmnpa+4lUUm9J4MI5RfZT5kcG7qbPilYAwNEN+tIxPEcPy/Eo7iLQs3ffDcQ42eSJMjd7ly0H2F/hQNexCEQ34cA9omqvIerc4Rk0pAGN321ozSnxQH1PVmv2c5a8gWaGLbodai49pRjGPeYjbNt5pcUYrt4JcNSgWxRywWQNmv0J33Cpge8HecVVkite7SHSKKQDIyoF4M4m4z+8fwXmW2Oy/feVoUwkAmSgly0GHSfSoShPNDnGB/EChSUyWHyg1id9TzaH83mWgHVShV1vbh4IBcFm6n3CZxC6YURpkKGYuElhq4qCmW36sEXo4kmYKTKlfkAod/hX8CPUr9uH3BzVvyBNlzw4MoGmGLRKBJBt75DjMLika8rSzkj1IN+Z1nindtgYFVPsC7+aiIaWIsYutZGGO1iQGBp/vY01jv+aN9jIPNIpc1Ost9WI1T/sxYSiB5e8h+2ISDEIu6zOJ473sg80wfarDZVYvNPKTL7C3bm9pBu/LqxR1s0d5P2mlaIOXotkO/AKFr/1I0+Q1XaRySztW8wqsNAZVF5SZfREb7PSW
*/