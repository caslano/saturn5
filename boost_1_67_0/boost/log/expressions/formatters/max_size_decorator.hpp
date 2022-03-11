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
SEj6Bf0ZnWTzzSMC0W0mIwiG+VEuYP39/rE7EzXa9pWXNvm0/qaj28aN4N+3YLW56i4/k3Xkn80XHj3GRnE1YyIfW5fCrf3TSl/2pSV/oLfh1fLFCMPy3E5IDeQnVANVllU+0gUXWEzPta2ikxSPcV1VRHKrAEjeJnSjw5hb33kS5BJolI/zWwhQ1/A+/cXOhlozyG6+hwkmy5SFJapoQCPzYpxKmVLhoKvEp7ctc2ujGDCJeaRe1FjUHv3B0n02/D5Nq8svVPEyfNPalBrGB3+2rDNOrSUqoe7BfI97aK2D1SQPQsu6l9rGmWcUQMC+EUOO9U2NczAU2LwQgIFbnVIuw3XLfmhwUjWEEEwthmEBG+HXtYWwZ/NotOFiI85YCYWpGLRFnF3F0t6eRZ9DYQEeol/sZTWwNWAZaqi/vsczAWRW2SgMYPZSb3Jc9vcQ2u1hJIVQKBRTUjL4eymVSueMpD9RfiRE/x7o43goXC24yg5E+x6D3czzPEkhGDtiN0nQ4WCE0OPnXNqnGmZRlF919kj1fDxzqnQhV8SJ9JxBJ0GLd0QlsoMyBk89GY8B/gvUjZ45iO1mipm3a4YJoBBAUf5Pkdz2mybg3hoWgrzQh+JF+Z72T2HlBlPmea1Ok9OzG05tY7iCeRl40cIJOaRW9ou1rj8MvIUhqIY5L3/XrYUPq8+lsKaU2XxbqW+IE2G0U5YJnEkiCW/p02eb1KDL7g42rJQzN+AwJEDiD+f9z7havF9gr5EwrBTkCY7/0Xy0R1euarXtgfmilPsNQpXfw8iq2rLe01TEFED1k4YsbsCZwD+tuF7/yTU/r7agULqPhCOylxPxmM6vkHnyi87kDuDnoxkdzmSCcHcF9X+c+dUzFa8dO0g8RTERJ03t0PExfwprHxRRuaDQrjHjtd4x0jwBRq/c9OIkLDXO9oqQeNEf73AuR+yvU5yC8PzuavkdI/xD4MGLpjXWT1X6zdQrZ+JRAEs17NKPuN4H0KW99sHW8EuE+8BxhMd6V++AjCmTQrdVbrCTQUI5yu1u6rsQZFVZuuawPpKprvKF+WEDOwNBK4fuzi+8w/SkYHlvIjW/HFvcuUynmWvFpm/deCn+MsmjWr/txBPilKs3lDhTinYlg8XqW5NcPW63Ce0Ift+S1KhcV+UpM8pii5VcaPK2W+X8cWLFUMY0kTh2Aj5At7djlB0Xb/wuFmcDgUMVF1sfp+1HPvX5G99pQB8M8YpHkBnNXavuaXWgZc5UFuW/zbtaOqiL5ryK9deDAqPyBgIQIOp3AbpZ1xuuwC64qrI4SNYPJd1fz0DTX3Sg4D4YfX9MpirbE3FK5DD1KQG8NLnSNImsHT+7cepAYsePXnugTbPx5lCqeQ6vwwumBP+fZrrAcnNqrx4kxdwgPrv2VpMeME3/rcPc/n86WjKEmeixSXqNizsjLrmUOkxZ6BcNceiROiiqcke1sPHKM/33Pl4HZkkhQ9Xa6UhW+w7h+MlwRd4fLujKikeFximI3Ygn5dL+FGTTbcxz6VGsm5NPal6+YwT8E7KLJrruB8Vd3dS+stSeC1yiHVk4szHryN4VkreHVejo2CKa/ZoeOo5YBvmiG4F07TEkuGyZQS5mQWvjYNwQVlFHu4FPMe8XU+zEKaMqHmwB4o6FURwkFI2lSuWro/g9aq/yq3k8QzwFi3FebA45QzMkz15cRnqa1fyCrazmrJt+0a9u9afeS6wxwdjrmlaPvoDXBnHlz3z85X/P3obbvsx47mFP4nh/cOqcqRD8hjE9e4mEC19k54qbssH1BegjQaYaZsVESzxUKdGoiXLwSvgMMtAEWM2nfLrifVyoEXhD/hN+f2bWWYrMNxOopTs3loZHn7JCydrzzSnQ6+Z2UXZCLevlWF/eb8oCJXu26UREG1rGILA2+5u3jubxXjH5JE/FWas/x/2H8TtR8+aM7GbDWkFpLpUp2VHqXrLSW77Nfjr164u3FJn1IQVaGDPykZEArMPmrVWzUk5DHSREmInd5jbhmVLQJCnf6c3VnscaBd0ro3XkKgzsGRMYmPdaKF/ueG02PAC9RwoMDizUetHQUBHwCl6+ODif5FgDi5k9+w90uH6ScRDUwb5ptv/CUrLySZeeqDpBUukc4Fvbquyx9vRYVIoLpdV2zSuec5NS9Xsminz8nS7bhNNv/hZ95jrRMwUaEOxkMIpnitk1K58ma6AM/IcfBA9cq5YhJut+9eWzIr8Y8fjVafQ59oYgWKPmjM2ZU/a8U15Q7ZF0i803V9dfTASCSHy88t/GR2tdHyKjv52h6eLfpQ5ieFYtXuErfNBS4DuREsiZj28QGmb+wKfthmv8dMoYJvKF8Yl2MGjctsNB85biKCRlTRJhGcVdcZuLx6M9NSFdaM6oG6+AB8MTgfC7WfHb4BnYVh4bUQz5pA6B4xS+S8pa/Ky1vfNp/PZ+Xd4sHe70WkPwTqT0pgPx4zyAbnndOSoh6wmSLhxx/Npf0/iR7n5ZvuV/LHL9nNCPoUWC7eznL1tfIlH9zsxvkD7OY2DHY3zc6GxN5zPmtOdFCu5J6fWr7jDOM3fwU8qWBIZXkYTrwHud8bivYX5f9iHiXsfcffNfaZ+f9v9pfdrap6d9fdrap6d9f9qAZ1sCf/BSgIdRg+xz2lbSBu8UEI0kiYakJgiOdw4/PSO8SJPGVRPau91hl8G5ovC6bPBCZ+Jhc6jzvjozuFgfra71zxCAChQnR7t5yuVt82wzNauXZbNNqbJ47fbzKGam7F54rP2+eP0Va8ftI94bQob3cHgx9pgDfx35QPKMyHsf+c/1QSpv8LtsWni3W47Jj8fTttRZl0/+/A4ZQy47S+bLH06Cf00nod8/i1/dgM9tTpXRX+Gvtqvq+ex5G6WR11siNNizMa/2p6/IEAFiUHtJUvNAOn8u8yQTnVf723v7IYwU/LrPHRC2PyPLqPW2m9V9BQPLPFgdRrQfaHQ2m85ffmslfV7LzGuNo57zQIhfwAgQ2IESt73/sM5cnF+z8LDiGZj6UOu5sP5uI71ozG7bb42Hy2G6IfrsPXZMHq9XM8S4fd+yu4CqR9ij6Lu82VNhqFZ711c8LFYNMN/o6x1Xpc89GMzN0yi2m81YVAgDbcRQTFQ+X25efuqJp6TDzP4PwZ2VmbuBEU16rhNM0461/FuI+OExYc2UtB344A+JkRoeUTa5Me94UYNUPr6nSTLPfzfp3+zko6pMZTWeaKooPgbL1L1vEjxoFWJ9YYT5Pr0/sfXlerGDR4+zTxE4HpA1fZF8Hzy9dyJren/chqarbfJ7r7BbLdu16jCOUvlvhCCg670fIciB/omFyDTNX++i5kdeqdJ3TM6x2ooc0wdBwGKzXzx8ex3u+43nsX4Z9jhor0QsGoaPTWoHvzE1urzvTUZ+A6lbEr1pinuR9zKyLCd6nh+YhVvKiZyo246d2qC9ANxhb2Wg/UAG+zl+HB/Nttwb/oEH8r/9yt2u8ejLqVbJlSf3Pb2BR2vnJ6+0zLt8+UmbKmgwpcGjR0S7eovacJnb17h0+uv6u8tICVkHraRTzOk/cX3zH1LNG6h9Ggrbzb0t2e+kz6U4nTQc7zoln7IttTzJjo8+h52844n8FKFaGSsc8Z0hsJjVkDlznzVKkGPbwk+Fngo7Z3M4LqbbNJb0jRrGPt6f80NbAi2laucddB0Lu3+t9ukPaJ+X/yZ95B2Qlj3o1QxPfRVBDbDDOwp6hyOxWD7sEFkxKvsIAYlbzTrA2Gvb8s1F0YWMyC2DB/cLemyXB37pg6GORZbXx8uNg359O4Fx4q57XdPBLbn7uvgekC3bh91HpK6k4hYYJiHqxqx9QCxMNejeA6CXI2Qwnunl5SmWj8/vZ/9SVRWN76ENv6bHz15jBACqoyDnMRGuucMUTo+XS0Ps5GZmfz4mBaNDCjNUENjgtTPPJe3oPekcLdUonzvgCwBD6FOiarx4gPpE1zTKb64h9PvAGz7VIdX8sn4rhxIXpRbNGwpZsv2lkCJykfh+egbdqYp7wOOBGBM72uMRQWyPvf0FAIxTYoiQwxc1jXtctoBctQl63gNrMUeu2m7mq/QsnuJm2fzdp8JIVbOq7YmftcY+WReCdiqySqC9BEqyjIDvhmtmUYe88Q5/6Ekeo4DRTDqUX1HhJuXpBW/PeCZjvBtdbqMmrPxKfR9EShlVO1wPz7DFyIyyd0bP9kRrEn0/V1fSpTGPBWnkISFCUlDkxuxupUV71NuPRgotLzec1YtCRVExYBXXV1IEqmT9Mi8/4zWt2fT5fFuq3l47+w3OzV4chMdGHy2PBqodsXhYao/Vw67gCSPtZ0eIP+L4wTj8z2QnBWEtT8xHyPq/vjKRyPTprcFCBsV2WI3SzHZHaBxf+TNTFRXrK6oX2/3jLeTHp6/XseSWa5XOmf9HzHb/8yA0Hrpe9/qYaSvc3pxvTn2OuZA/t4g5Lekz7h4TxwzrPBW2Wby/NNh0OT68bxqDd8oeNBAXHUVrDTehMTLEEvoTxnLIfkJsXxd0gW1NmKu8Bq6i/oPZkorfiIHHZTizF4UN2SQNX6DyWxdUoVD2iT06hjH2/BS6UeV3irG2T45fu0XQfrwDIt/jaNL+aGE5f3RNaFcTOflEHnM80EssMW/qFee+Ea5/c+SHi4DyCB761tZSW55PYxoT9okuJpAdE4rlSkWesePFDFWlJLcSJJJJMrA6vwqZkbZfZhCKaDaAnZ/htXN383XLlvZzlurw0oKFjCQGk7I112EgLOOZzC13DVMeoiJX7pJ/0ftSCXJO3FU1aMWlz/ZQO2tkkxWWVcTs6LpqoRSA7xNudNtXz2XI3hiDtCz25ompiRRB0NewJ4US+utLmjMckkfQgdPPHrz83jDNPH0U2Zbwbe3Edrk07PfgjyLb8xwqYX/cGf7lxULnjnVrceXj06OhXclKrEjDky7PcvqXD+y+J3fL10YcUjzT6YStV37Fkj8wpYwlIBHs9SAYCob1ZkwnBjTFX6yn2+3bVJuKxHfQlfMJ6oXa/YyUGT+XWe6wGfX2JKdt+bE6ecSxhA6Nu/Nyz2nXlmSf9FGCN0vL36f7yX4pi3aDtoKO5SZnZ9Gj8jVP78k4nfZ5gjJt2Ja5CyZ16Vsd7Rq27t60iVFjcnEYlyfmJOgkN5D3NmgceqgZzzTiD5RjRddEgm20C7hC+NRGBYpeNZ+qCMp4TCRnKxJA0Ryxc0vQhgrj7KFvqyH69Q+bZ89JUmH2WKaLVxk6wYw/7wZqn0ufvUdT6CrQX/jnp9e+/zYA5N+cNJY8IiiCLfbh6d0PWBBwWlqF5if+Cfn8vQO7pQeZn6zl0gmMMNub/U0V/Y/2f6eB4/0nUvO2LNF39pisQx5R5+c/2P245i8aXzPKJGeJBJVprciDYcdoQjucE3tWU1cHQ7MMfJt4CUMlwpFyQEZYghINrYPJevaYQoSlU97abtMUU6uqR4QuT7eV7U88CR2Zvwme5oSex9fDWP6jhntp++wz/S6bEGQ/7hf+TcnkMMtAuofI4su2sNdssZR3kv81rmn4fztlfveVXP/1wpL52hwE6uRR8SHRZKoYNiI8+uxiskEvM2Wfz+R/wYa4/P5BPIglmvfSNiZuzR5hEEEC0w9pJyY6ZqkVqaiT4vPin9udB6cHy2n1oh3tZw8+IqxntX/381N14y2a5K31hr223T7WwOU0hMVSs3WJrwKN5mkpvEvTJ4Zevk4i6SBsrz9g0BRN0awM20tmFjf/LBHPqT/+ZgURal3HjHhdKtrg2mCqHdeVPjIMzdvxg1o0VgZSCYqc17HqWnNZ9871pmmXIerDXe5QDPpzIqPrqGDOwspsKbKakmFkdLybkjSlBQA56XRwZ6+H3tGxjRXujFaWsGV/J4D3NcPn+dhn9zxjPTulmcD5koNq48jGrBkKkL5Tjg9XqVxuXqHDuZMdQNiYOMhudxDwodhRgCLRXRPOzDKmCiWcivl/xWOxAezb9s9/22rf5H3eI44izbvVkjHQkqtw8VNcpqRYEIbSViI2d/x9W3Pr56ergQz5rrPaWUpYE0NBMpp1I6rCk1+q/P7/vQJYvqUPyDrvv33+YczUjhRrt/n/Bl3U2Rc5VRLZy5JKmxDffeRfvkIAKYxd3AJCCVv4bE7o9K+3n3BSC4ooGxYEivIPth6scVPV/RG5+UegmW3pD+JD+/cmv4g8GNnilk1e9vYZLk9u6sPsZHAgZKIhTAVMwwiUBQyle4IL2YIi13WNUaZZBVDTCI6mesuUtnAyC4w9qNiZ08SH25iva2QGESP+iiruqeiyEGW/FzVPMTFUj9TYqfEODpGnAWDrqpIDxPUAZYIvkGp/Ubr+NsS612YmBF8kqmZh1hBvOMPSQfzD5CQ5fTPx2HEEM3LUxU8WJtrvW6a6Pu90wBrv2qQ0SEK6TInZTiLN7J77IxbWFeJu0CR1hfuhjjm/MUyAU/afcrMkFIjtsjFz65wbzEQa4LqVgECEVz32RIUVTAZNEy8L3IPNhef/1QJ4J28Hxd+yioQuZbDUaGLfL2OIBpT81CxUyhDZbAu/V16jKPknm/QXdXF1p+/ma/ICKIPOX0gcKnRfVgwe4ykLMnaD3Ri6Wa5xN3RXvq/h2gQjn9X0ESiLSNT1y76TUkmsOIDBcVt+K7sYwJFJiQAgO0gqp6eSeSLkc6qbmTVMfpDaXOW/REYPDWBypzTksaXulGmXRCd4dXa3HUFgUClwuEGGqItFkQj9Fs2oU3oidMYpm7o/hnC2On82IHc8UctPmTC7Gmx2xO0s0kDMUVk/CrLtDtVWpWCRHjnmfNb5ck/j/CohmRKE2S8//tq+YgRlFtq7JvZDsR74QoUJTYhQh7K48g4RIg/FoU7QSni0aLy9FUqOwpgv6q1uhzf2na3zkRRN6c/nM5oa58Ua2bPTQdseK30BqBfjMGBujDP/BB5qzciKh8/eIYwCLRiB+Ym+WX/UUWlM/Dyub5TgO8E35hl1+XnmWbSHCf/ZSHWHBKVyTFPR8CViaB+UBH5CVRSiRHI1D+A2yYfO973Y3WML2ocAA16UyBrpAmHSJBp7ZB8pDmytKLefus/gYPAjzN0Ya6XzTHlCL1kieDxP6P5aUD76OhP/1M99BEsiIOjU6995Y/VP/XHeRcNxsRIhwAOL8iHrXAKtjf7K6tIg988LNvD/4oWctkP7OpTXUHBVpo32cHdy3Q/Wiwx8VLGcad3yvCNvNJgh6EQ3kOq+freY5XnJ5Z7Nj/on9psVbgVYae/h4r2Cjn47w7bPhd+XwZYZiRkGRVgTt6npGuJx73xQahvjWuO4cA3sh/XRHHlb+Nz7JkNpTERf78XuzTKByOwYVc/xcOD9kXsp2BDdd6P1d94jwmmORfLOxeuf7LhMB/jO0f2jumwPS0yRFIEBARDrLLu3Du7So+KzRxo5+aD+vaxt4vq5pwl+2ePIdAUyDQte2x+BtQ/Od9uTB/zR910exHMIGuF1lzA03s/LaiJYpBV044Uj2TYBEHEXOTSr08pWU1yfHGwj94mk3/6f1p19sK+6FRQrCN50t9XWqtGuX+LvjwreSXYisCcX6OnYGFbKEL3Bi2qVofAbDMs15X0JEfq4H8eYnJ7F0wyxz3zBKp2xBCIPiyrMuIkYQjYHfD+GZOyer2nsTEga417O2JSPp6uf3FIjFVhpdmIafo3k2PRfEKyLB/XjuEGZ8vk9CbkvlWt3S1e58W4MdPu4jZyDDXH7CdnoaZC2jRH0K8DQzAtDKjSLjD6J5u5T6mCNvPeD5ul2T+yQh1mrRogGLstSy6gDfykKLlYPB6YHgal8OVhAyyUoRKa0Y8zNryd4OlY3KpZU3jEOrjRnKXIluNJVqZcEEz9dvpFJIkfpfjkxvs18A7Rum3ApxsWDOcgJijOM4EwgG+8M0Mbta0MKDgbIWgIlK8P97Jb3QTxbOcK+msJit3s24KiiRpC7Vl3xU7Ct8TkJPuGM/Fh8TblTOtTFU0O/QaqVeIov/+HVzG0nebr8ck9CwP4zj6F9ynG3gO+SuFfx+U2Yxdi7oulWiNxtH2cDPm2IDf2Bq8FtV2hR4mEMtzWNziUN/0MJfOgbw+rQZ1HV5DgTkNZhHE8yYgzv6bl3qtPdpnhk+MhSAaNbfBaO8sBbeLGl1F8qPquXTqds+AJMf+LuT8k/PrNtDRP6a0rPVPFC/vT5/78i83Ju9H7DX+gz7xNyXENIQB1VKyvBnO/Kr5h64kfZEYOcWrqaXMoljz40eIYL3bPi0LEiO+/ZyAZZrJSDY0AGDHk5NFoI/tmr8LFmNGXjKRcVfz1uX5dsCUp3SRm9zSxbX0YTwgJps0QY25Ni/vJRWk6lUTzdPkwH1dqiBH3CMGupZCry7RcyUAdhjbskkHHAx+p5k2EqZufEiaD+6nCCUgs4vOqY+LyimhBkak83aZch64wgHCEXdF60B4Mxj2uO2ois7W460Z4j7/Npv/1C05TX2f1oU0EJ9XJ9OJG8jUAjyul3bjXnt08Hn/7SPR3q4vmU1vEqkWLkXDf3MpdbA/sBMspy7ontRtpmTPp3nDJkkFdklo3gG3vy7l26d8S0mUkKlkKmaHpx12Ji0LwkGVLmJyQVFOzpO12VK27lHpN1F8luppMvFOtV7LNWjZuCj79sJe+FUaGZEj1NYd+VJn6e4f7PSLG/no4wVWMMjjhghRwpGclIaFVziofer053UV3syl4ifmGb4oJXt/KXF+tPCoNfAh7RTAGOO8+3y9ifjIUEb2Ik9dkgNoKAi4AH68mM/CVirqjJ+SPklrCK0FJwOXwV+jaZnSe3gXRY85eVXphIktN3tcB34oMPZ6pC5KSOBNFigoA4K+i9j5ByGP8O808/+39gtejZ/ZgS3G/7uXZoy+5WuNwksUHvmjnkV7kECG9KrQdSSphf5quIcNVdoo2d7XIsqYAotAYcx4ij0XHRatJaT2qIAGfwZ3KWE1Wf1JK+NQabg5FX3Ugg5YjZplwN95eIseFybtV8McwIrSw0Gj7i8tBFlIuKQY2tRXyQoyLzrpMA/YwoRWSHlhxInjRU+cXLTXJ093n2eRe7tp87l3J3/T5LhDwLJtGSU2qxGL6F7rylBITn3jHGPwCRcdE/WJLLzMLL0bleD2VRQuQtbNUD+9AduTw=
*/