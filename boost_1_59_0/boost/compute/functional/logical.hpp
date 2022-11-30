//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_LOGICAL_HPP
#define BOOST_COMPUTE_FUNCTIONAL_LOGICAL_HPP

namespace boost {
namespace compute {
namespace detail {

template<class Predicate, class Expr>
class invoked_unary_negate_function
{
public:
    typedef int result_type;

    invoked_unary_negate_function(const Predicate &pred,
                                  const Expr &expr)
        : m_pred(pred),
          m_expr(expr)
    {
    }

    Predicate pred() const
    {
        return m_pred;
    }

    Expr expr() const
    {
        return m_expr;
    }

private:
    Predicate m_pred;
    Expr m_expr;
};

template<class Predicate, class Expr1, class Expr2>
class invoked_binary_negate_function
{
public:
    typedef int result_type;

    invoked_binary_negate_function(const Predicate &pred,
                                   const Expr1 &expr1,
                                   const Expr2 &expr2)
        : m_pred(pred),
          m_expr1(expr1),
          m_expr2(expr2)
    {
    }

    Predicate pred() const
    {
        return m_pred;
    }

    Expr1 expr1() const
    {
        return m_expr1;
    }

    Expr2 expr2() const
    {
        return m_expr2;
    }

private:
    Predicate m_pred;
    Expr1 m_expr1;
    Expr2 m_expr2;
};

} // end detail namespace

/// \internal_
template<class Arg, class Result>
struct unary_function
{
    typedef Arg argument_type;
    typedef Result result_type;
};

/// \internal_
template<class Arg1, class Arg2, class Result>
struct binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

/// \internal_
template<class Arg1, class Arg2, class Arg3, class Result>
struct ternary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Arg3 third_argument_type;
    typedef Result result_type;
};

/// The unary_negate function adaptor negates a unary function.
///
/// \see not1()
template<class Predicate>
class unary_negate : public unary_function<void, int>
{
public:
    explicit unary_negate(Predicate pred)
        : m_pred(pred)
    {
    }

    /// \internal_
    template<class Arg>
    detail::invoked_unary_negate_function<Predicate, Arg>
    operator()(const Arg &arg) const
    {
        return detail::invoked_unary_negate_function<
                   Predicate,
                   Arg
                >(m_pred, arg);
    }

private:
    Predicate m_pred;
};

/// The binnary_negate function adaptor negates a binary function.
///
/// \see not2()
template<class Predicate>
class binary_negate : public binary_function<void, void, int>
{
public:
    explicit binary_negate(Predicate pred)
        : m_pred(pred)
    {
    }

    /// \internal_
    template<class Arg1, class Arg2>
    detail::invoked_binary_negate_function<Predicate, Arg1, Arg2>
    operator()(const Arg1 &arg1, const Arg2 &arg2) const
    {
        return detail::invoked_binary_negate_function<
                   Predicate,
                   Arg1,
                   Arg2
                >(m_pred, arg1, arg2);
    }

private:
    Predicate m_pred;
};

/// Returns a unary_negate adaptor around \p predicate.
///
/// \param predicate the unary function to wrap
///
/// \return a unary_negate wrapper around \p predicate
template<class Predicate>
inline unary_negate<Predicate> not1(const Predicate &predicate)
{
    return unary_negate<Predicate>(predicate);
}

/// Returns a binary_negate adaptor around \p predicate.
///
/// \param predicate the binary function to wrap
///
/// \return a binary_negate wrapper around \p predicate
template<class Predicate>
inline binary_negate<Predicate> not2(const Predicate &predicate)
{
    return binary_negate<Predicate>(predicate);
}

/// The logical_not function negates its argument and returns it.
///
/// \see not1(), not2()
template<class T>
struct logical_not : public unary_function<T, int>
{
    /// \internal_
    template<class Expr>
    detail::invoked_function<int, boost::tuple<Expr> >
    operator()(const Expr &expr) const
    {
        return detail::invoked_function<int, boost::tuple<Expr> >(
            "!", std::string(), boost::make_tuple(expr)
        );
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_LOGICAL_HPP

/* logical.hpp
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
*/