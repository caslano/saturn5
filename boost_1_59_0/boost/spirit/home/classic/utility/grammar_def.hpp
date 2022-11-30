/*=============================================================================
    Copyright (c) 2003 Hartmut Kaiser
    Copyright (c) 2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_GRAMMAR_DEF_HPP)
#define BOOST_SPIRIT_GRAMMAR_DEF_HPP

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/phoenix/tuples.hpp>
#include <boost/spirit/home/classic/core/assert.hpp>
#include <boost/spirit/home/classic/utility/grammar_def_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit predefined maximum grammar start parser limit. This limit defines
//  the maximum number of possible different parsers exposed from a
//  particular grammar. This number defaults to 3.
//  The actual maximum is rounded up in multiples of 3. Thus, if this value
//  is 4, the actual limit is 6. The ultimate maximum limit in this
//  implementation is 15.
//
//  It should NOT be greater than PHOENIX_LIMIT!
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT)
#define BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT PHOENIX_LIMIT
#endif

///////////////////////////////////////////////////////////////////////////////
//
// ensure BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT <= PHOENIX_LIMIT and
//        BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT <= 15 and
//        BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT > 0
//
///////////////////////////////////////////////////////////////////////////////
BOOST_STATIC_ASSERT(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT <= PHOENIX_LIMIT);
BOOST_STATIC_ASSERT(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT <= 15);
BOOST_STATIC_ASSERT(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT > 0);

//////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

struct same {};

///////////////////////////////////////////////////////////////////////////////
namespace impl {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The make_const_pointer meta function allows to generate a T const*
    //  needed to store the pointer to a given start parser from a grammar.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T0, typename T = T0>
    struct make_const_pointer {

    private:
        // T0 shouldn't be of type 'same'
        BOOST_STATIC_ASSERT((!boost::is_same<T0, same>::value));

        typedef typename boost::mpl::if_c<
                    boost::is_same<T, same>::value,
                    T0 const *,
                    T const *
                >::type
            ptr_type;

    public:
        // If the type in question is phoenix::nil_t, then the returned type
        // is still phoenix::nil_t, otherwise a constant pointer type to the
        // inspected type is returned.
        typedef typename boost::mpl::if_c<
                    boost::is_same<T, ::phoenix::nil_t>::value,
                    ::phoenix::nil_t,
                    ptr_type
                >::type
            type;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <int N, typename ElementT>
    struct assign_zero_to_tuple_member {

        template <typename TupleT>
        static void do_(TupleT &t)
        {
            ::phoenix::tuple_index<N> const idx;
            t[idx] = 0;
        }
    };

    template <int N>
    struct assign_zero_to_tuple_member<N, ::phoenix::nil_t> {

        template <typename TupleT>
        static void do_(TupleT& /*t*/) {}
    };

    struct phoenix_nil_type {

        typedef ::phoenix::nil_t type;
    };

    template <int N>
    struct init_tuple_member {

        template <typename TupleT>
        static void
        do_(TupleT &t)
        {
            typedef typename boost::mpl::eval_if_c<
                        (N < TupleT::length),
                        ::phoenix::tuple_element<N, TupleT>,
                        phoenix_nil_type
                    >::type
                element_type;

            assign_zero_to_tuple_member<N, element_type>::do_(t);
        }
    };

///////////////////////////////////////////////////////////////////////////////
}   // namespace impl

///////////////////////////////////////////////////////////////////////////////
//
//  grammar_def class
//
//      This class may be used as a base class for the embedded definition
//      class inside the grammar<> derived user grammar.
//      It exposes the two functions needed for start rule access:
//
//          rule<> const &start() const;
//
//      and
//
//          template <int N>
//          rule<> const *get_start_parser() const;
//
//      Additionally it exposes a set o 'start_parsers' functions, which are to
//      be called by the user to define the parsers to use as start parsers
//      of the given grammar.
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename T,
    BOOST_PP_ENUM_PARAMS(
        BOOST_PP_DEC(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT_A), typename T)
>
class grammar_def {

private:
    ///////////////////////////////////////////////////////////////////////////
    //
    //  This generates the full tuple type from the given template parameters
    //  T, T0, ...
    //
    //      typedef ::phoenix::tuple<
    //              typename impl::make_const_pointer<T>::type,
    //              typename impl::make_const_pointer<T, T0>::type,
    //              ...
    //          > tuple_t;
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_GRAMMARDEF_TUPLE_PARAM(z, N, _) \
        typename impl::make_const_pointer<T, BOOST_PP_CAT(T, N)>::type \
        /**/

    typedef ::phoenix::tuple<
            typename impl::make_const_pointer<T>::type,
            BOOST_PP_ENUM(
                BOOST_PP_DEC(BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT_A),
                BOOST_SPIRIT_GRAMMARDEF_TUPLE_PARAM,
                _
            )
        > tuple_t;

    #undef BOOST_SPIRIT_GRAMMARDEF_TUPLE_PARAM
    ///////////////////////////////////////////////////////////////////////////

protected:
    ///////////////////////////////////////////////////////////////////////////
    //
    //  This generates a sequence of 'start_parsers' functions with increasing
    //  number of arguments, which allow to initialize the tuple members with
    //  the pointers to the start parsers of the grammar:
    //
    //      template <typename TC0, ...>
    //      void start_parsers (TC0 const &t0, ...)
    //      {
    //          using ::phoenix::tuple_index_names::_1;
    //          t[_1] = &t0;
    //          ...
    //      }
    //
    //      where a TC0 const* must be convertible to a T0 const*
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_GRAMMARDEF_ENUM_PARAMS(z, N, _) \
        BOOST_PP_CAT(TC, N) const &BOOST_PP_CAT(t, N) \
        /**/
    #define BOOST_SPIRIT_GRAMMARDEF_ENUM_ASSIGN(z, N, _) \
        using ::phoenix::tuple_index_names::BOOST_PP_CAT(_, BOOST_PP_INC(N)); \
        t[BOOST_PP_CAT(_, BOOST_PP_INC(N))] = &BOOST_PP_CAT(t, N); \
        /**/
    #define BOOST_SPIRIT_GRAMMARDEF_ENUM_START(z, N, _) \
        template <BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_INC(N), typename TC)> \
        void \
        start_parsers(BOOST_PP_ENUM_ ## z(BOOST_PP_INC(N), \
            BOOST_SPIRIT_GRAMMARDEF_ENUM_PARAMS, _) ) \
        { \
            BOOST_PP_REPEAT_ ## z(BOOST_PP_INC(N), \
                BOOST_SPIRIT_GRAMMARDEF_ENUM_ASSIGN, _) \
        } \
        /**/

    BOOST_PP_REPEAT(
        BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT_A,
        BOOST_SPIRIT_GRAMMARDEF_ENUM_START, _)

    #undef BOOST_SPIRIT_GRAMMARDEF_ENUM_START
    #undef BOOST_SPIRIT_GRAMMARDEF_ENUM_ASSIGN
    #undef BOOST_SPIRIT_GRAMMARDEF_ENUM_PARAMS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    //
    //  This generates some initialization code, which allows to initialize all
    //  used tuple members to 0 (zero):
    //
    //      t[_1] = 0;
    //      impl::init_tuple_member<1>::do_(t);
    //      ...
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_GRAMMARDEF_ENUM_INIT(z, N, _) \
        impl::init_tuple_member<N>::do_(t); \
        /**/

    grammar_def()
    {
        using ::phoenix::tuple_index_names::_1;
        t[_1] = 0;
        BOOST_PP_REPEAT_FROM_TO(
            1, BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT_A,
            BOOST_SPIRIT_GRAMMARDEF_ENUM_INIT, _)
    }

    #undef BOOST_SPIRIT_GRAMMARDEF_ENUM_INIT
    ///////////////////////////////////////////////////////////////////////////

public:
    T const &
    start() const
    {
    //  If the following assertion is fired, you have probably forgot to call
    //  the start_parser() function from inside the constructor of your
    //  embedded definition class to initialize the start parsers to be exposed
    //  from your grammar.
        using ::phoenix::tuple_index_names::_1;
        BOOST_SPIRIT_ASSERT(0 != t[_1]);
        return *t[_1];
    }

    template <int N>
    typename ::phoenix::tuple_element<N, tuple_t>::crtype
    get_start_parser() const
    {
    //  If the following expression yields a compiler error, you have probably
    //  tried to access a start rule, which isn't exposed as such from your
    //  grammar.
        BOOST_STATIC_ASSERT(N > 0 && N < tuple_t::length);

        ::phoenix::tuple_index<N> const idx;

    //  If the following assertion is fired, you have probably forgot to call
    //  the start_parser() function from inside the constructor of your
    //  embedded definition class to initialize the start parsers to be exposed
    //  from your grammar.
    //  Another reason may be, that there is a count mismatch between
    //  the number of template parameters to the grammar_def<> class and the
    //  number of parameters used while calling start_parsers().
        BOOST_SPIRIT_ASSERT(0 != t[idx]);

        return t[idx];
    }

private:
    tuple_t t;
};

#undef BOOST_SPIRIT_GRAMMAR_STARTRULE_TYPE_LIMIT_A

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_GRAMMAR_DEF_HPP

/* grammar_def.hpp
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
*/